//
//  Triangle.hpp
//  DalRT
//
//  Created by Dallas McNeil on 3/7/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <glm/glm.hpp>
#include "Object.hpp"

namespace DalRT {

/// Single triangle object
class Triangle : public Object
{
public:
    
    Triangle();
    
    /// Check if ray collides with triangle
    bool RayColides(Ray ray, Collision& collision) override;
    
    /// Set the points of the triangle
    void SetPoints(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
protected:
    void CalculateExtent() override;
    
private:
    glm::vec3 point1 = glm::vec3(1.0f,0.0f,0.0f);
    glm::vec3 point2 = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 point3 = glm::vec3(0.0f,0.0f,1.0f);
    
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 pos3;
};
    
}

#endif /* Triangle_hpp */
