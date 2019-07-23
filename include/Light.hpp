//
//  Light.hpp
//  DalRT
//
//  Created by Dallas McNeil on 11/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <glm/glm.hpp>
#include "Ray.hpp"
#include <vector>

namespace DalRT {

/// Represents a light which generates light rays to illuminate object
class Light
{
public:
    /// Rays of light from location to this light
    virtual std::vector<Ray> GenerateRaysToLight(glm::vec3 const &location) = 0;
};
    
}

#endif /* Light_hpp */
