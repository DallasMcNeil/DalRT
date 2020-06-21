//
//  Scene.hpp
//  DalRT
//
//  Created by Dallas McNeil on 2/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Camera.hpp"
#include "Group.hpp"

namespace DalRT {

/// Represents a 3D space with objects, light and a camera
class Scene
{
public:
    
    /// Render the scene
    void RenderScene();
    
    /// Get the rendered image of the scene as RGB floats. Starting in the top left by row by column
    std::vector<float> GetRender();
    
    /// Save the rendered image in PNG format to the specified file
    bool SaveToPNGFile(std::string filename);
    
    /// Set the camera of the scene
    void SetCamera(Camera* camera);
    
    /// Set the maximum number of intersection a ray will do
    void SetMaxDepth(unsigned int depth);
    
    /// Set the background colour of the scene
    void SetBackgroundColor(glm::vec4 const& color);
    
    /// Add a group to the scene
    void AddGroup(Group* group);
    
    /// Remove a group from the scene
    bool RemoveGroup(Group* group);
    
private:

    glm::vec3 backgroundColor = glm::vec4(1.0f,1.0f,1.0f, 0.0f);
    std::vector<Group*> groups;
    std::vector<glm::vec4> render;
    Camera* camera;
    unsigned int maxDepth = 16;
};
    
}
