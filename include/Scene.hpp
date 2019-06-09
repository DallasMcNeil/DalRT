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

namespace DalRT {

class Scene
{
public:
    void RenderScene();
    std::vector<float> GetRender();
    
    void SetCamera(Camera* camera);
    
    void AddGroup();
    void RemoveGroup();
    
private:
    std::vector<glm::vec3> render;
    Camera* camera;
};
    
}

#endif /* Scene_hpp */
