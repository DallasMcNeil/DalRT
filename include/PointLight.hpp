//
//  PointLight.hpp
//  DalRT
//
//  Created by Dallas McNeil on 11/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <glm/glm.hpp>
#include "Light.hpp"
#include "Ray.hpp"
#include <vector>

namespace DalRT {

class PointLight : public Light
{
public:
    
    PointLight();
    
    void SetPosition(glm::vec3 const &position);
    
    // Color (can go past 1 for brighter)
    void SetColor(glm::vec3 const &color);
    void SetRadius(float radius);
    
    std::vector<Ray> GenerateRaysToLight(glm::vec3 const &location) override;
    
private:
    glm::vec3 position;
    float radius;
    glm::vec3 color;
};
    
}

#endif /* Light_hpp */
