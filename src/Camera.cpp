//
//  Ray.cpp
//  DalRT
//
//  Created by Dallas McNeil on 7/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include <glm/gtx/rotate_vector.hpp>
#include "Camera.hpp"

namespace DalRT
{
    Camera::Camera()
    {
        up = glm::vec3(0.0f,1.0f,0.0f);
        direction = glm::vec3(0.0f,0.0f,1.0f);
        position = glm::vec3(0.0f,0.0f,0.0f);
        width = 640;
        height = 480;
        fov = glm::pi<float>()/2.0f;
    }
    
    void Camera::SetSize(unsigned int width, unsigned int height)
    {
        this->width = width;
        this->height = height;
    }
    
    void Camera::SetFOV(float fov)
    {
        this->fov = fov;
    }
    
    void Camera::SetPosition(glm::vec3 const &pos)
    {
        position = pos;
    }
    
    void Camera::SetDirection(glm::vec3 const &dir)
    {
        direction = glm::normalize(dir);
    }
    
    void Camera::SetUp(glm::vec3 const &up)
    {
        this->up = glm::normalize(up);
    }
    
    unsigned int Camera::GetWidth()
    {
        return width;
    }
    
    unsigned int Camera::GetHeight()
    {
        return height;
    }
    
    std::vector<Ray> Camera::ProduceRays()
    {
        std::vector<Ray> rays;
        rays.reserve(width*height);
        
        if (false) // Fish eye
        {
            float angle = fov/float(width - 1);
            
            for (int h=0; h<height; h++)
            {
                float a = h - ((float(height) - 1.0f)/2.0f);
                
                glm::vec3 right = glm::cross(up, direction);
                glm::vec3 rotVert = glm::rotate(direction, angle*a, right);
                
                for (int w=0; w<width; w++)
                {
                    a = w - ((float(width) - 1.0f)/2.0f);
                    
                    glm::vec3 rotHorz = glm::rotate(rotVert, angle*a, up);
                    
                    Ray ray;
                    ray.color = glm::vec3(1.0f,1.0f,1.0f);
                    ray.direction = rotHorz;
                    ray.origin = position;
                    rays.push_back(ray);
                }
            }
        }
        else // Regular
        {
            float aspect = float(width)/float(height);
            float scale = std::tan(fov * 0.5);
            
            glm::mat4 toWorld = glm::lookAt(glm::vec3(0,0,0), -direction, up);
            
            for (int h=0; h<height; h++)
            {
                for (int w=0; w<width; w++)
                {
                    float x = (2.0f * (w + 0.5f) / float(width) - 1.0f) * aspect * scale;
                    float y = (1.0f - 2.0f * (h + 0.5f) / float(height)) * scale;
                    
                    Ray ray;
                    ray.color = glm::vec3(1.0f,1.0f,1.0f);
                    glm::vec3 out = glm::vec4(x,y,1,1) * toWorld;
                    ray.direction = glm::normalize(glm::vec3(out.x,out.y,out.z));
                    ray.origin = position;
                    rays.push_back(ray);
                }
            }
        }
        
        return rays;
    }
}
