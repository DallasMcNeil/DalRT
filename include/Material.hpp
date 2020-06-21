//
//  Material.hpp
//  DalRT
//
//  Created by Dallas McNeil on 12/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#pragma once

namespace DalRT {

/// Determines how a ray interacts with the object
struct Material
{
public:
    /// The colour of the object for diffuse lighting
    glm::vec3 color = glm::vec3(0.8f,0.8f,0.8f);
    
    /// Reflectiveness of the object
    float reflectiveness = 0.0f;

    /// Roughness of the object
    float roughness = 0.0f;
};
     
/// Default material for objects
static Material DefaultMaterial;

}
