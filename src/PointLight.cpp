//
//  PointLight.cpp
//  DalRT
//
//  Created by Dallas McNeil on 11/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "PointLight.hpp"
#include <algorithm>

namespace DalRT {

    PointLight::PointLight()
    {
        position = glm::vec3(0.0f,0.0f,0.0f);
        color = glm::vec3(1.0f,1.0f,1.0f);
        radius = 0.0f;
    }

    void PointLight::SetPosition(glm::vec3 const &position)
    {
        this->position = position;
    }
    
    void PointLight::SetColor(glm::vec3 const &color)
    {
        this->color = color;
    }
    
    void PointLight::SetRadius(float radius)
    {
        this->radius = radius;
    }
    
    std::vector<Ray> PointLight::GenerateRaysToLight(glm::vec3 const &location)
    {
        std::vector<Ray> rays;
        if (radius <= 0.0f)
        {
            Ray ray;
            ray.origin = location;
            ray.direction = glm::normalize(position - location);
            ray.distance = glm::distance(position, location);
            ray.color = color / std::sqrt(ray.distance);
            rays.push_back(ray);
        }
        else
        {
            
        }
        return rays;
    }
    
}


