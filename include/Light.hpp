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

class Light
{
public:
    
    virtual std::vector<Ray> GenerateRaysToLight(glm::vec3 const &location) = 0;

};
    
}

#endif /* Light_hpp */
