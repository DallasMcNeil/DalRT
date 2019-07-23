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

/// Determines how a ray interacts with the object
struct Material
{
public:
    /// The colour of the object for diffuse lighting
    glm::vec3 color = glm::vec3(0.8f,0.8f,0.8f);
    
    /// Reflectiveness of the object
    float reflectiveness = 0.0f;
    
    /// Colour of specular lighting
    glm::vec3 specular = glm::vec3(1.0f,1.0f,1.0f);
    
    /// Hardness of the object for specular lighting
    float specularHardness = 32.0f;
    
    /// Translucency of the object
    float translucency = 0.0f;
};
     
/// Default material for objects
static Material DefaultMaterial;

}


#endif /* Material_hpp */
