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
    
private:
    void ProcessRay(Ray &ray, int depth);
    
    std::vector<Group*> groups;
    std::vector<glm::vec3> render;
    Camera* camera;
    unsigned int maxDepth = 32;
};
    
}

#endif /* Scene_hpp */
