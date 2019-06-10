//
//  Extent.cpp
//  DalRT
//
//  Created by Dallas McNeil on 1/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Extent.hpp"

namespace DalRT {

    Extent::Extent()
    {
        empty = true;
    }

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
