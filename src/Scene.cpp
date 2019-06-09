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

    void Scene::RenderScene()
    {
        std::vector<Ray> rays = camera->ProduceRays();
        
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f);
        Sphere sphere;
        sphere.SetPosition(pos);
        
        Collision col;
        for (int r=0; r<rays.size(); r++)
        {
            if (sphere.RayColides(rays[r], col)) {
                rays[r].direction = glm::reflect(rays[r].direction, col.normal);
                rays[r].origin = col.location;
            }
        }
        
        unsigned int size = camera->GetWidth() * camera->GetHeight();
        render.resize(size);
        
        for (int i=0; i<size; i++)
        {
            glm::vec3 dir = rays[i].direction;
            render[i] = glm::vec3((dir.x + 1.0f) / 2.0f, (dir.y + 1.0f) / 2.0f, (dir.z + 1.0f) / 2.0f);
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
    
    void Scene::AddGroup()
    {
        
    }
    
    void Scene::RemoveGroup()
    {
        
    }
}


