//
//  DirectionalLight.cpp
//  DalRT
//
//  Created by Dallas McNeil on 30/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "DirectionalLight.hpp"
#include <algorithm>

namespace DalRT {

    DirectionalLight::DirectionalLight()
    {
        direction = glm::vec3(0.0f,-1.0f,0.0f);
        color = glm::vec3(1.0f,1.0f,1.0f);
        distance = 1000.0f;
    }

    void DirectionalLight::SetDirection(glm::vec3 const &direction)
    {
        this->direction = glm::normalize(direction);
    }
    
    void DirectionalLight::SetColor(glm::vec3 const &color)
    {
        this->color = color;
    }
    
    void DirectionalLight::SetDistance(float distance)
    {
        this->distance = distance;
    }
    
    std::vector<Ray> DirectionalLight::GenerateRaysToLight(glm::vec3 const &location)
    {
        std::vector<Ray> rays;

        Ray ray;
        ray.origin = location;
        ray.direction = -direction;
        ray.distance = distance;
        ray.color = color;
        rays.push_back(ray);
        
        return rays;
    }
    
}

