//
//  Triangle.cpp
//  DalRT
//
//  Created by Dallas McNeil on 3/7/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Triangle.hpp"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/normal.hpp>

namespace DalRT {

    Triangle::Triangle():Object()
    {
        point1 = glm::vec3(1.0f,0.0f,0.0f);
        point2 = glm::vec3(1.0f,1.0f,0.0f);
        point3 = glm::vec3(1.0f,0.0f,1.0f);
    }
        
    bool Triangle::RayColides(Ray ray, Collision& collision)
    {
        glm::vec4 pos1 = transform * glm::vec4(point1, 1.0f);
        glm::vec4 pos2 = transform * glm::vec4(point2, 1.0f);
        glm::vec4 pos3 = transform * glm::vec4(point3, 1.0f);
        
        glm::vec3 baryPos;
        bool result = glm::intersectRayTriangle(ray.origin, ray.direction, glm::vec3(pos1), glm::vec3(pos2), glm::vec3(pos3), baryPos);
        if (result)
        {
            collision.location = baryPos.x * pos2 + baryPos.y * pos3 + (1.0f - baryPos.x - baryPos.y) * pos1;
            collision.normal = glm::triangleNormal(glm::vec3(pos1), glm::vec3(pos2), glm::vec3(pos3));
        }
        
        return result;
    }
    
    // Width is X, height is Z
    void Triangle::SetPoints(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
    {
        this->point1 = point1;
        this->point2 = point2;
        this->point3 = point3;
        
        CalculateExtent();
        CalculateTransform();
    }
        
    void Triangle::CalculateExtent()
    {
        extent.Reset();

        glm::vec4 pos1 = transform * glm::vec4(point1, 1.0f);
        glm::vec4 pos2 = transform * glm::vec4(point2, 1.0f);
        glm::vec4 pos3 = transform * glm::vec4(point3, 1.0f);
        
        extent.Extend(glm::vec3(pos1));
        extent.Extend(glm::vec3(pos2));
        extent.Extend(glm::vec3(pos3));
        
        extentDirty = false;
    }
    
}
