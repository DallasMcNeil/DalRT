//
//  Extent.hpp
//  DalRT
//
//  Created by Dallas McNeil on 1/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Extent_hpp
#define Extent_hpp

#include <glm/glm.hpp>

namespace DalRT {

/// Represents a rectangular region of space
class Extent
{
public:
    Extent();
    
    /// Increases the extent to contain the point or extent
    void Extend(glm::vec3 const &point);
    void Extend(Extent* extent);
    
    /// Resets the region back to nothing
    void Reset();
    
    /// Determines if the point is within the extent
    bool ContainsPoint(glm::vec3 const &point);
    
    glm::vec3 GetMin();
    glm::vec3 GetMax();
    bool Empty();
    
private:
    glm::vec3 min;
    glm::vec3 max;
    bool empty;
};
    
}

#endif /* Extent_hpp */
