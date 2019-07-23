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

/// Constant light from a single direction
class DirectionalLight : public Light
{
public:
    
    /// Set direction of light
    void SetDirection(glm::vec3 const &direction);
    
    /// Set distance away from object light comes from
    void SetDistance(float distance);
    
    /// Set color of light (can go past 1 for brighter)
    void SetColor(glm::vec3 const &color);
    
    /// Generates a single ray following direction
    std::vector<Ray> GenerateRaysToLight(glm::vec3 const &location) override;
    
private:
    glm::vec3 direction = glm::vec3(0.0f,-1.0f,0.0f);
    float distance = 1000.0f;
    glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f);
};
    
}

#endif /* DirectionalLight_hpp */
