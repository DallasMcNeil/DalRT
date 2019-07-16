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

class Triangle : public Object
{
public:
    
    Triangle();
    
    bool RayColides(Ray ray, Collision& collision) override;
    void SetPoints(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
protected:
    void CalculateExtent() override;
    
private:
    glm::vec3 point1;
    glm::vec3 point2;
    glm::vec3 point3;
};
    
}

#endif /* Triangle_hpp */
