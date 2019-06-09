//
//  Sphere.hpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <glm/glm.hpp>
#include "Object.hpp"

namespace DalRT {

class Sphere : public Object
{
public:
    
    Sphere();
    
    void SetRadius(float radius);
    
    bool RayColides(Ray ray, Collision& collision) override;
    
protected:
    void CalculateExtent() override;
    
private:
    float radius;
};
    
}

#endif /* Sphere_hpp */
