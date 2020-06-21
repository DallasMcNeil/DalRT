//
//  Sphere.cpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include <algorithm>
#include "Sphere.hpp"
#include <glm/gtx/intersect.hpp>

namespace DalRT {
        
    // bool Sphere::RayColides(Ray ray, Collision& collision)
    // {
    //     return glm::intersectRaySphere(ray.origin, ray.direction, position, radius, collision.location, collision.normal);
    // }
        
    void Sphere::SetRadius(float radius)
    {
        this->radius = std::abs(radius);
    }
        
    void Sphere::CalculateExtent()
    {
        extent.Reset();
        
        extent.Extend(position - radius);
        extent.Extend(position + radius);
        
        extentDirty = false;
    }
    
}
