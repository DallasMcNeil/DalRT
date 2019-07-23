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

/// Represents a light focused at a single point
class PointLight : public Light
{
public:
    
    /// Set the position of the light
    void SetPosition(glm::vec3 const &position);
    
    // Set light color (can go past 1 for brighter light)
    void SetColor(glm::vec3 const &color);
    
    /// Generates a ray with intensity based on distance
    std::vector<Ray> GenerateRaysToLight(glm::vec3 const &location) override;
    
private:
    glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f);
};
    
}

#endif /* PointLight_hpp */
