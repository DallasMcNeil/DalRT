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

    void PointLight::SetPosition(glm::vec3 const &position)
    {
        this->position = position;
    }
    
    void PointLight::SetColor(glm::vec3 const &color)
    {
        this->color = color;
    }
    
    std::vector<Ray> PointLight::GenerateRaysToLight(glm::vec3 const &location)
    {
        std::vector<Ray> rays(1);
        
        Ray ray;
        ray.origin = location;
        ray.direction = glm::normalize(position - location);
        ray.distance = glm::distance(position, location);
        ray.color = color / std::sqrt(ray.distance);
        rays[0] = ray;
        
        return rays;
    }
    
}


