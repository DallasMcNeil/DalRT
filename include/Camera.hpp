//
//  Camera.hpp
//  DalRT
//
//  Created by Dallas McNeil on 7/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <vector>
#include "Ray.hpp"

namespace DalRT {

class Camera
{
public:
    Camera();
    
    enum Type
    {
    Perspective,
    Orthographic,
    Panoramic
    };
    
    void SetSize(unsigned int width, unsigned int height);
    void SetFOV(float fov);
    void SetPosition(glm::vec3 const &pos);
    void SetDirection(glm::vec3 const &dir);
    void SetUp(glm::vec3 const &up);
    void SetType(Type type);
    
    unsigned int GetWidth();
    unsigned int GetHeight();
    
    std::vector<Ray> ProduceRays();
    
private:
    unsigned int width;
    unsigned int height;
    
    float fov;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    Type type;
};
    
}

#endif /* Camera_hpp */
