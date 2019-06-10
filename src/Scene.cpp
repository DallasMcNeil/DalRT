//
//  Scene.cpp
//  DalRT
//
//  Created by Dallas McNeil on 2/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Scene.hpp"
#include "Sphere.hpp"
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
            ProcessRay(rays[r], 0);
        }
        
        unsigned int size = camera->GetWidth() * camera->GetHeight();
        render.resize(size);
        
        for (int i=0; i<size; i++)
        {
            render[i] = rays[i].color;
        }
    }
    
    void Scene::ProcessRay(Ray &ray, int depth)
    {
        if (depth >= maxDepth)
        {
            return;
        }
        
        for (int g=0; g<groups.size(); g++)
        {
            Collision col;
            Object* result = FindObject(ray, groups[g], col);
            if (result == nullptr)
            {
                continue;
            }
            else
            {
                ray.direction = glm::reflect(ray.direction, col.normal);
                ray.origin = col.location + (ray.direction * 0.0001f);
                
                ray.color = glm::vec3((ray.direction.x + 1.0f) / 2.0f, (ray.direction.y + 1.0f) / 2.0f, (ray.direction.z + 1.0f) / 2.0f);
                
                ProcessRay(ray, ++depth);
                return;
            }
        }
        if (depth == 0)
        {
            ray.color = glm::vec3(0.5f,0.5f,0.5f);
        }
        return;
    }
    
    Object* Scene::FindObject(Ray &ray, Group* group, Collision& col)
    {
        Collision objCol;

        Object* closestObj = nullptr;
        float closestDist = std::numeric_limits<float>::max();
        
        std::vector<Object*> objs = group->GetObjects();
        for (int o=0; o<objs.size(); o++)
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
                }
            }
        }
        
        std::vector<Group*> subGroups = group->GetSubGroups();
        for (int s=0; s<subGroups.size(); s++)
        {
            Object* result = FindObject(ray, subGroups[s], objCol);
            if (result != nullptr)
            {
                float dist = glm::distance(ray.origin, objCol.location);
                if (dist < closestDist)
                {
                    closestObj = result;
                    closestDist = dist;
                    col = objCol;
                }
            }
        }
        
        return closestObj;
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
}


