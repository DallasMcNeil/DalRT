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
#include "Material.hpp"

namespace DalRT {

/// Object that interacts with rays
class Object
{
public:
    
    Object();
    
    /// Determines if the ray intersects with the object
    virtual bool RayColides(Ray ray, Collision& collision) = 0;
    
    /// Set the rotation of the object, Y = yaw, X = pitch, Z = yaw
    void SetRotation(glm::vec3 const &rotation);
    
    /// Sets the position of the object
    void SetPosition(glm::vec3 const &position);
    
    /// Sets the scale of the object
    void SetScale(glm::vec3 const &scale);
    
    /// Set the object material
    void SetMaterial(Material *material);
    
    /// Get the object material
    Material* GetMaterial();
    
    /// Get the extent of the object
    Extent* GetExtent();
    
protected:
    virtual void CalculateExtent() = 0;
    void CalculateTransform();

    glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
    
    glm::mat4 transform;
    
    bool extentDirty = true;
    Extent extent;
    
    Material *material = &DefaultMaterial;
};
    
}

#endif /* Object_hpp */
