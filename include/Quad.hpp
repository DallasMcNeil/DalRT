//
//  Quad.hpp
//  DalRT
//
//  Created by Dallas McNeil on 24/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>
#include "Object.hpp"

namespace DalRT {

/// Rectangle object
class Quad : public Object
{
public:
    
    Quad();
    
    /// Set the size of the quad
    void SetSize(float width, float height);
    
protected:
    void CalculateExtent() override;
    
private:
    float width;
    float height;
    
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 pos3;
    glm::vec3 pos4;
};
    
}
