//
//  Sphere.hpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>
#include "Object.hpp"

namespace DalRT {

/// Sphere object
class Sphere : public Object
{
public:
    
    /// Set the radius of the sphere
    void SetRadius(float radius);
    
protected:
    void CalculateExtent() override;
    
private:
    float radius;
};
    
}
