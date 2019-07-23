
#include <string>
#include <iostream>

#include <DalRT.hpp>

//--------------------------------------------------------------
int main()
{
    glm::vec3 vec;
    
    // Scene
    DalRT::Scene scene;
    scene.SetMaxDepth(16);
    scene.SetBackgroundColor(glm::vec3(0.8f,0.8f,0.8f));
    scene.SetAmbientLight(glm::vec3(0.1f,0.1f,0.1f));
    
    // Camera
    DalRT::Camera camera;
    camera.SetSize(640, 640);
    camera.SetFOV(3.1415/2.0f);
    camera.SetType(DalRT::Camera::Type::Perspective);
    camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    camera.SetDirection(glm::vec3(0.0f,0.0f,1.0f));
    scene.SetCamera(&camera);
    
    // Spheres
    DalRT::Sphere sphere;
    sphere.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    sphere.SetRadius(2.0f);
    
    DalRT::Material material1;
    material1.color = glm::vec3(1.0f,0.0f,0.0f);
    material1.reflectiveness = 0.0f;
    material1.specular = glm::vec3(1.0f,1.0f,1.0f);
    material1.specularHardness = 32.0f;
    material1.translucency = 0.0f;
    sphere.SetMaterial(&material1);
    
    // Groups
    DalRT::Group group1;
    group1.AddObject(&sphere);
    
    // Lights
    DalRT::DirectionalLight light;
    light.SetDirection(glm::vec3(-0.5f,-1.0f,1.0f));
    light.SetColor(glm::vec3(1.5f,1.5f,1.5f));
    
    // Add all objects and lights
    scene.AddLight(&light);
    scene.AddGroup(&group1);
    
    // Render
    scene.RenderScene();
    
    bool result = scene.SaveToPNGFile("Test.png");
}
