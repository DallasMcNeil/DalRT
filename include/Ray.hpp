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

/// Represents a ray of light with a starting position and direction, with a possible fixed length
struct Ray
{
public:
    /// Starting location
    glm::vec3 origin;
    
    /// Ray direction
    glm::vec3 direction;
    
    /// Color and intensity of light
    glm::vec3 color;
    
    /// Possible length of ray
    float distance;
};
    
/// A collision between a ray and an object, with a location and normal of object surface
struct Collision
{
public:
    /// Location where ray collides with object
    glm::vec3 location;
    
    /// Normal of object surface collided with
    glm::vec3 normal;
};
    
}
#endif /* Ray_hpp */
