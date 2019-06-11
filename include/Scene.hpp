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
    
    void SetCamera(Camera* camera);
    void SetMaxDepth(unsigned int depth);
    
    void AddGroup(Group* group);
    bool RemoveGroup(Group* group);
    
    void AddLight(Light* group);
    bool RemoveLight(Light* group);
    
private:
    void ProcessRay(Ray &ray, int depth);
    Object* FindObject(Ray &ray, Group* group, float anyWithinDistance, Collision& col);
    bool RayIntersectsObject(Ray &ray);
    
    std::vector<Group*> groups;
    std::vector<Light*> lights;
    std::vector<glm::vec3> render;
    Camera* camera;
    unsigned int maxDepth = 32;
};
    
}

#endif /* Scene_hpp */
