//
//  Object.cpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Object.hpp"

namespace DalRT {

    Object::Object()
    {
        rotation = glm::vec3(0.0f,0.0f,0.0f);
        position = glm::vec3(0.0f,0.0f,0.0f);
        scale = glm::vec3(1.0f,1.0f,1.0f);
        extentDirty = true;
    }
    
    void Object::SetRotation(glm::vec3 const &rotation)
    {
        this->rotation = rotation;
        extentDirty = true;
    }

    void Object::SetPosition(glm::vec3 const &position)
    {
        this->position = position;
        extentDirty = true;
    }

    void Object::SetScale(glm::vec3 const &scale)
    {
        this->scale = scale;
        extentDirty = true;
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


