//
//  Scene.hpp
//  DalRT
//
//  Created by Dallas McNeil on 2/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <glm/glm.hpp>
#include <vector>
#include "Camera.hpp"
#include "Group.hpp"
#include "Light.hpp"

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
    void SetBackgroundColor(glm::vec3 const& color);
    
    /// Set the ambient light colour in the scene
    void SetAmbientLight(glm::vec3 const& color);
    
    /// Add a group to the scene
    void AddGroup(Group* group);
    
    /// Remove a group from the scene
    bool RemoveGroup(Group* group);
    
    /// Add a light to the scene
    void AddLight(Light* group);
    
    /// Remove a light from the scene
    bool RemoveLight(Light* group);
    
private:
    void ProcessRay(Ray &ray, int depth, Object* currentObject);
    Object* FindObject(Ray &ray, Group* group, float anyWithinDistance, Object* ignoreObject, Collision& col);
    Object* RayIntersectsObject(Ray &ray, Object* ignoreObject, Collision& lightCol);
    
    glm::vec3 backgroundColor = glm::vec3(1.0f,1.0f,1.0f);
    glm::vec3 ambientColor = glm::vec3(0.0f,0.0f,0.0f);
    std::vector<Group*> groups;
    std::vector<Light*> lights;
    std::vector<glm::vec3> render;
    Camera* camera;
    unsigned int maxDepth = 16;
};
    
}

#endif /* Scene_hpp */
