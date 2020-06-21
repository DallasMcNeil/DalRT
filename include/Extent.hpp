//
//  Extent.hpp
//  DalRT
//
//  Created by Dallas McNeil on 1/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>

namespace DalRT {

/// Represents a rectangular region of space
class Extent
{
public:
    
    /// Increases the extent to contain the point or extent
    void Extend(glm::vec3 const &point);
    
    /// Increase the extent to contain another extent
    void Extend(Extent* extent);
    
    /// Resets the region back to nothing
    void Reset();
    
    /// Determines if the point is within the extent
    bool ContainsPoint(glm::vec3 const &point);
    
    /// Get the minimum of the extent
    glm::vec3 GetMin();
    
    /// Get the maximum of the extent
    glm::vec3 GetMax();
    
    /// Check if the extent is empty
    bool Empty();
    
private:
    glm::vec3 min;
    glm::vec3 max;
    bool empty = true;
};
    
}
