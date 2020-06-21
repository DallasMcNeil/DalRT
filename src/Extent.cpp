//
//  Extent.cpp
//  DalRT
//
//  Created by Dallas McNeil on 1/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Extent.hpp"
#include <algorithm>

namespace DalRT {

    void Extent::Extend(glm::vec3 const &point)
    {
        if (empty)
        {
            min = point;
            max = point;
            empty = false;
        }
        else
        {
            min.x = point.x < min.x ? point.x : min.x;
            min.y = point.y < min.y ? point.y : min.y;
            min.z = point.z < min.z ? point.z : min.z;
            
            max.x = point.x > max.x ? point.x : max.x;
            max.y = point.y > max.y ? point.y : max.y;
            max.z = point.z > max.z ? point.z : max.z;
        }
    }
    
    void Extent::Extend(Extent* extent)
    {
        if (!extent->Empty())
        {
            Extend(extent->GetMin());
            Extend(extent->GetMax());
        }
    }
    
    // bool Extent::RayIntersects(Ray* ray)
    // {
    //     float tmin = (min.x - ray->origin.x) / ray->direction.x;
    //     float tmax = (max.x - ray->origin.x) / ray->direction.x;
        
    //     if (tmin > tmax)
    //     {
    //         std::swap(tmin, tmax);
    //     }
        
    //     float tymin = (min.y - ray->origin.y) / ray->direction.y;
    //     float tymax = (max.y - ray->origin.y) / ray->direction.y;
        
    //     if (tymin > tymax)
    //     {
    //         std::swap(tymin, tymax);
    //     }
        
    //     if ((tmin > tymax) || (tymin > tmax))
    //     {
    //         return false;
    //     }
        
    //     if (tymin > tmin)
    //     {
    //         tmin = tymin;
    //     }
        
    //     if (tymax < tmax)
    //     {
    //         tmax = tymax;
    //     }
        
    //     float tzmin = (min.z - ray->origin.z) / ray->direction.z;
    //     float tzmax = (max.z - ray->origin.z) / ray->direction.z;
        
    //     if (tzmin > tzmax)
    //     {
    //         std::swap(tzmin, tzmax);
    //     }
        
    //     if ((tmin > tzmax) || (tzmin > tmax))
    //     {
    //         return false;
    //     }
        
    //     if (tzmin > tmin)
    //     {
    //         tmin = tzmin;
    //     }
        
    //     if (tzmax < tmax)
    //     {
    //         tmax = tzmax;
    //     }
        
    //     return true;
    // }

    void Extent::Reset()
    {
        empty = true;
    }

    bool Extent::ContainsPoint(glm::vec3 const &point)
    {
        return !empty && (min.x <= point.x && min.y <= point.y && min.z <= point.z && max.x >= point.x && max.y >= point.y && max.z >= point.z);
    }
    
    glm::vec3 Extent::GetMin()
    {
        return min;
    }
    
    glm::vec3 Extent::GetMax()
    {
        return max;
    }
    
    bool Extent::Empty()
    {
        return empty;
    }

}
