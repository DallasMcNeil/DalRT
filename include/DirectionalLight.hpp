//
//  DirectionalLight.hpp
//  DalRT
//
//  Created by Dallas McNeil on 30/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <glm/glm.hpp>
#include "Light.hpp"
#include "Ray.hpp"
#include <vector>

namespace DalRT {

class DirectionalLight : public Light
{
public:
    
    DirectionalLight();
    
    void SetDirection(glm::vec3 const &direction);
    void SetDistance(float distance);
    
    // Color (can go past 1 for brighter)
    void SetColor(glm::vec3 const &color);
    
    std::vector<Ray> GenerateRaysToLight(glm::vec3 const &location) override;
    
private:
    glm::vec3 direction;
    float distance;
    glm::vec3 color;
};
    
}

#endif /* DirectionalLight_hpp */
