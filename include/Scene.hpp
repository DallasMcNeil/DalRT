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

class Scene
{
public:
    Scene();
    
    void RenderScene();
    std::vector<float> GetRender();
    bool SaveToPNGFile(std::string filename);
    
    void SetCamera(Camera* camera);
    void SetMaxDepth(unsigned int depth);
    void SetBackgroundColor(glm::vec3 const& color);
    void SetAmbientLight(glm::vec3 const& color);
    
    void AddGroup(Group* group);
    bool RemoveGroup(Group* group);
    
    void AddLight(Light* group);
    bool RemoveLight(Light* group);
    
private:
    void ProcessRay(Ray &ray, int depth, Object* currentObject);
    Object* FindObject(Ray &ray, Group* group, float anyWithinDistance, Object* ignoreObject, Collision& col);
    Object* RayIntersectsObject(Ray &ray, Object* ignoreObject, Collision& lightCol);
    
    glm::vec3 backgroundColor;
    glm::vec3 ambientColor;
    std::vector<Group*> groups;
    std::vector<Light*> lights;
    std::vector<glm::vec3> render;
    Camera* camera;
    unsigned int maxDepth = 32;
};
    
}

#endif /* Scene_hpp */
