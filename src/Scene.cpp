//
//  Scene.cpp
//  DalRT
//
//  Created by Dallas McNeil on 2/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Scene.hpp"
#include "Sphere.hpp"

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
            glm::vec3 dir = rays[i].direction;
            render[i] = glm::vec3((dir.x + 1.0f) / 2.0f, (dir.y + 1.0f) / 2.0f, (dir.z + 1.0f) / 2.0f);
        }
    }
    
    void Scene::ProcessRay(Ray &ray, int depth)
    {
        if (depth >= maxDepth)
        {
            return;
        }
        
        Collision col;
        for (int g=0; g<groups.size(); g++)
        {
            // TODO: Check extents
            std::vector<Object*> objs = groups[g]->GetObjects();
            for (int o=0; o<objs.size(); o++)
            {
                if (objs[o]->RayColides(ray, col))
                {
                    ray.direction = glm::reflect(ray.direction, col.normal);
                    ray.origin = col.location + (ray.direction * 0.0001f);
                    ProcessRay(ray, ++depth);
                    return;
                }
            }
        }
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


