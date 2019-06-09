//
//  Object.hpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <glm/glm.hpp>
#include "Extent.hpp"
#include "Ray.hpp"

namespace DalRT {

class Object
{
public:
    
    Object();
    
    virtual bool RayColides(Ray ray, Collision& collision) = 0;
    
    /// Y = yaw, then X = pitch, then Z = yaw
    void SetRotation(glm::vec3 const &rotation);
    void SetPosition(glm::vec3 const &position);
    void SetScale(glm::vec3 const &scale);
    
    Extent* GetExtent();
    
protected:
    virtual void CalculateExtent() = 0;

    glm::vec3 rotation;
    glm::vec3 position;
    glm::vec3 scale;
    
    bool extentDirty;
    Extent extent;
};
    
}

#endif /* Object_hpp */
