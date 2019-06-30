//
//  Quad.hpp
//  DalRT
//
//  Created by Dallas McNeil on 24/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Quad_hpp
#define Quad_hpp

#include <glm/glm.hpp>
#include "Object.hpp"

namespace DalRT {

class Quad : public Object
{
public:
    
    Quad();
    
    bool RayColides(Ray ray, Collision& collision) override;
    void SetSize(float width, float height);
    
protected:
    void CalculateExtent() override;
    
private:
    float width;
    float height;
};
    
}

#endif /* Quad_hpp */
