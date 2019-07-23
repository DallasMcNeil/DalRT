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
#include <glm/gtc/constants.hpp>
#include <vector>
#include "Ray.hpp"

namespace DalRT {

/// Generates initial rays for scene
class Camera
{
public:
    
    /// Different types of lenses
    enum Type
    {
        Perspective,
        Orthographic,
        Panoramic
    };
    
public:
    
    /// Set size of output image
    void SetSize(unsigned int width, unsigned int height);
    
    /// Set the field of view of the camera or width of orthographic lens
    void SetFOV(float fov);
    
    /// Set position of camera
    void SetPosition(glm::vec3 const &pos);
    
    /// Set direction camera is facing
    void SetDirection(glm::vec3 const &dir);
    
    /// Set up direction of camera
    void SetUp(glm::vec3 const &up);
    
    /// Set lens type of camera
    void SetType(Type type);
    
    /// Get the width of the output image
    unsigned int GetWidth();
    
    /// Get the height of the output image
    unsigned int GetHeight();
    
    /// Produce the initial rays for the image
    std::vector<Ray> ProduceRays();
    
private:
    unsigned int width = 640;
    unsigned int height = 480;
    
    float fov = glm::pi<float>()/2.0f;
    glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 direction = glm::vec3(0.0f,0.0f,1.0f);
    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    Type type = Type::Perspective;
};
    
}

#endif /* Camera_hpp */
