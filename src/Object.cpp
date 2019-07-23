//
//  Object.cpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Object.hpp"
#include <glm/gtx/transform.hpp>

namespace DalRT {

    Object::Object()
    {
        CalculateTransform();
    }
    
    void Object::SetRotation(glm::vec3 const &rotation)
    {
        this->rotation = rotation;
        CalculateTransform();
        extentDirty = true;
    }

    void Object::SetPosition(glm::vec3 const &position)
    {
        this->position = position;
        CalculateTransform();
        extentDirty = true;
    }

    void Object::SetScale(glm::vec3 const &scale)
    {
        this->scale = scale;
        CalculateTransform();
        extentDirty = true;
    }
    
    void Object::CalculateTransform()
    {
        transform = glm::translate(position);
        transform = glm::rotate(transform, rotation.z, glm::vec3(0.0f,0.0f,1.0f));
        transform = glm::rotate(transform, rotation.x, glm::vec3(1.0f,0.0f,0.0f));
        transform = glm::rotate(transform, rotation.y, glm::vec3(0.0f,1.0f,0.0f));
        transform = glm::scale(transform, scale);
    }
    
    void Object::SetMaterial(Material *material)
    {
        this->material = material;
    }
    
    Material* Object::GetMaterial()
    {
        return material;
    }
    
    Extent* Object::GetExtent()
    {
        if (extentDirty)
        {
            CalculateExtent();
        }
        return &extent;
    }
    
}


