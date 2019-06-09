//
//  Ray.hpp
//  DalRT
//
//  Created by Dallas McNeil on 1/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <glm/glm.hpp>

namespace DalRT {

struct Ray
{
public:
    glm::vec3 origin;
    glm::vec3 direction;
    
    glm::vec3 color;
    float intensity;
};
    
struct Collision
{
public:
    glm::vec3 location;
    glm::vec3 normal;
};
    
}

#endif /* Ray_hpp */
