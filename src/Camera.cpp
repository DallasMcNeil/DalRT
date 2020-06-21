//
//  Ray.cpp
//  DalRT
//
//  Created by Dallas McNeil on 7/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include <glm/gtx/rotate_vector.hpp>
#include "Camera.hpp"

namespace DalRT
{
    void Camera::SetSize(unsigned int width, unsigned int height)
    {
        this->width = width;
        this->height = height;
    }
    
    void Camera::SetFOV(float fov)
    {
        this->fov = fov;
    }
    
    void Camera::SetPosition(glm::vec3 const &pos)
    {
        position = pos;
    }
    
    void Camera::SetDirection(glm::vec3 const &dir)
    {
        direction = glm::normalize(dir);
    }
    
    void Camera::SetUp(glm::vec3 const &up)
    {
        this->up = glm::normalize(up);
    }
    
    void Camera::SetType(Type type)
    {
        this->type = type;
    }
    
    unsigned int Camera::GetWidth()
    {
        return width;
    }
    
    unsigned int Camera::GetHeight()
    {
        return height;
    }
}
