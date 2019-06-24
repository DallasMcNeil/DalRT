//
//  Material.hpp
//  DalRT
//
//  Created by Dallas McNeil on 12/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

namespace DalRT {

struct Material
{
public:
    glm::vec3 color;
    float reflectiveness;
    glm::vec3 specular;
    float specularHardness;
    float translucency;
    float indexOfRefraction;
};
    
}

#endif /* Material_hpp */
