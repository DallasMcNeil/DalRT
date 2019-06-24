//
//  Scene.cpp
//  DalRT
//
//  Created by Dallas McNeil on 2/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Scene.hpp"
#include "Sphere.hpp"
#include "Material.hpp"
#include <limits>

namespace DalRT {
    
    Scene::Scene()
    {
        maxDepth = 16;
    }

    void Scene::RenderScene()
    {
        std::vector<Ray> rays = camera->ProduceRays();
        
        for (int r=0; r<rays.size(); r++)
        {
            ProcessRay(rays[r], 0, nullptr);
        }
        
        unsigned int size = camera->GetWidth() * camera->GetHeight();
        render.resize(size);
        
        for (int i=0; i<size; i++)
        {
            render[i] = glm::min(rays[i].color, glm::vec3(1.0f,1.0f,1.0f));
        }
    }
    
    void Scene::ProcessRay(Ray &ray, int depth, Object* currentObject)
    {
        if (depth >= maxDepth)
        {
            return;
        }
        
        for (int g=0; g<groups.size(); g++)
        {
            Collision col;
            Object* result = FindObject(ray, groups[g], 0.0f, currentObject, col);
            if (result == nullptr)
            {
                continue;
            }
            else
            {
                
                Material* mat = result->GetMaterial();
                
                glm::vec3 diffuse = glm::vec3(0.0f,0.0f,0.0f);
                glm::vec3 specular = glm::vec3(0.0f,0.0f,0.0f);
                glm::vec3 reflection = glm::vec3(0.0f,0.0f,0.0f);
                
                // Diffuse
                for (int l=0; l<lights.size(); l++)
                {
                    std::vector<Ray> lightRays = lights[l]->GenerateRaysToLight(col.location);
                    for (int r=0; r<lightRays.size(); r++)
                    {
                        if (!RayIntersectsObject(lightRays[r], result))
                        {
                            float diff = std::max(glm::dot(col.normal, lightRays[r].direction),0.0f);
                            
                            glm::vec3 reflect = glm::reflect(-lightRays[r].direction, col.normal);
                            float spec = std::pow(std::max(glm::dot(ray.direction, -reflect),0.0f), mat->specularHardness);
                            
                            diffuse += (lightRays[r].color) * diff;
                            specular += (lightRays[r].color) * spec;
                        }
                    }
                }
                
                
                // Reflection
                
                if (mat->reflectiveness > 0.0f)
                {
                    Ray reflect = ray;
                    reflect.direction = glm::reflect(ray.direction, col.normal);
                    reflect.origin = col.location;
                    reflect.color = glm::vec3(0.0f,0.0f,0.0f);
                    ProcessRay(reflect, ++depth, result);
                    reflection += reflect.color;
                }
                
                ray.color = glm::vec3(0.0f,0.0f,0.0f);
                
                ray.color += mat->specular * specular;
                ray.color += mat->color * diffuse * (1.0f - mat->reflectiveness);
                ray.color += mat->color * reflection * mat->reflectiveness;
                return;
            }
        }
        if (depth == 0)
        {
            // Background
            ray.color = glm::vec3(0.2f,0.2f,0.2f);
        }
        else
        {
            ray.color = glm::vec3(0.2f,0.2f,0.2f);
        }
        return;
    }
    
    Object* Scene::FindObject(Ray &ray, Group* group, float anyWithinDistance, Object* ignoreObject, Collision& col)
    {
        Collision objCol;

        Object* closestObj = nullptr;
        float closestDist = std::numeric_limits<float>::max();
        
        std::vector<Object*> objs = group->GetObjects();
        for (int o=0; o<objs.size(); o++)
        {
            if (objs[o] != ignoreObject)
            {
                if (objs[o]->GetExtent()->RayIntersects(&ray))
                {
                    if (objs[o]->RayColides(ray, objCol))
                    {
                        float dist = glm::distance(ray.origin, objCol.location);
                        if (dist < closestDist)
                        {
                            closestObj = objs[o];
                            closestDist = dist;
                            col = objCol;
                        }
                        if (closestDist <= anyWithinDistance)
                        {
                            return closestObj;
                        }
                    }
                }
            }
        }
        
        std::vector<Group*> subGroups = group->GetSubGroups();
        for (int s=0; s<subGroups.size(); s++)
        {
            Object* result = FindObject(ray, subGroups[s], anyWithinDistance, ignoreObject, objCol);
            if (result != nullptr)
            {
                float dist = glm::distance(ray.origin, objCol.location);
                if (dist < closestDist)
                {
                    closestObj = result;
                    closestDist = dist;
                    col = objCol;
                }
                if (closestDist <= anyWithinDistance)
                {
                    return closestObj;
                }
            }
        }
        
        return closestObj;
    }
    
    bool Scene::RayIntersectsObject(Ray &ray, Object* ignoreObject)
    {
        for (int g=0; g<groups.size(); g++)
        {
            Collision col;
            Object* result = FindObject(ray, groups[g], ray.distance, ignoreObject, col);
            if (result != nullptr)
            {
                return true;
            }
        }
        return false;
    }
    
    std::vector<float> Scene::GetRender() 
    {
        std::vector<float> pixels(render.size() * 3);
        for (int i=0; i<render.size(); i++)
        {
            pixels[(i*3) + 0] = render[i].r;
            pixels[(i*3) + 1] = render[i].g;
            pixels[(i*3) + 2] = render[i].b;
        }
        return pixels;
    }
    
    void Scene::SetCamera(Camera* camera)
    {
        this->camera = camera;
    }
    
    void Scene::SetMaxDepth(unsigned int depth)
    {
        maxDepth = depth;
    }
    
    void Scene::AddGroup(Group* group)
    {
        groups.push_back(group);
    }
    
    bool Scene::RemoveGroup(Group* group)
    {
        for (int i=0; i<groups.size(); i++)
        {
            if (groups[i] == group)
            {
                groups.erase(groups.begin() + i);
                return true;
            }
        }
        return false;
    }
    
    void Scene::AddLight(Light* light)
    {
        lights.push_back(light);
    }
    
    bool Scene::RemoveLight(Light* light)
    {
        for (int i=0; i<lights.size(); i++)
        {
            if (lights[i] == light)
            {
                lights.erase(lights.begin() + i);
                return true;
            }
        }
        return false;
    }
}


