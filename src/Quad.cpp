//
//  Quad.cpp
//  DalRT
//
//  Created by Dallas McNeil on 24/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Quad.hpp"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/normal.hpp>

namespace DalRT {

    Quad::Quad():Object()
    {
        width = 1.0f;
        height = 1.0f;
    }
        
    bool Quad::RayColides(Ray ray, Collision& collision)
    {
        glm::vec4 pos1 = transform * glm::vec4(-width/2.0f, 0.0f, -height/2.0f, 1.0f);
        glm::vec4 pos2 = transform * glm::vec4(-width/2.0f, 0.0f, height/2.0f, 1.0f);
        glm::vec4 pos3 = transform * glm::vec4(width/2.0f, 0.0f, height/2.0f, 1.0f);
        glm::vec4 pos4 = transform *  glm::vec4(width/2.0f, 0.0f, -height/2.0f, 1.0f);
        
        glm::vec3 baryPos;
        bool result = glm::intersectRayTriangle(ray.origin, ray.direction, glm::vec3(pos1), glm::vec3(pos2), glm::vec3(pos3), baryPos);
        if (!result)
        {
            result = glm::intersectRayTriangle(ray.origin, ray.direction, glm::vec3(pos1), glm::vec3(pos3), glm::vec3(pos4), baryPos);
            if (result)
            {
                collision.location = baryPos.x * pos3 + baryPos.y * pos4 + (1.0f - baryPos.x - baryPos.y) * pos1;
            }
        }
        else
        {
            collision.location = baryPos.x * pos2 + baryPos.y * pos3 + (1.0f - baryPos.x - baryPos.y) * pos1;
        }
        
        if (result)
        {
            collision.normal = glm::triangleNormal(glm::vec3(pos1), glm::vec3(pos2), glm::vec3(pos3));
        }
        
        return result;
    }
    
    // Width is X, height is Z
    void Quad::SetSize(float width, float height)
    {
        this->width = width;
        this->height = height;
        
        CalculateExtent();
        CalculateTransform();
    }
        
    void Quad::CalculateExtent()
    {
        extent.Reset();

        glm::vec4 pos1 = transform * glm::vec4(-width/2.0f, 0.0f, -height/2.0f, 1.0f);
        glm::vec4 pos2 = transform * glm::vec4(-width/2.0f, 0.0f, height/2.0f, 1.0f);
        glm::vec4 pos3 = transform * glm::vec4(width/2.0f, 0.0f, height/2.0f, 1.0f);
        glm::vec4 pos4 = transform * glm::vec4(width/2.0f, 0.0f, -height/2.0f, 1.0f);
        
        extent.Extend(glm::vec3(pos1));
        extent.Extend(glm::vec3(pos2));
        extent.Extend(glm::vec3(pos3));
        extent.Extend(glm::vec3(pos4));
        
        extentDirty = false;
    }
    
}
