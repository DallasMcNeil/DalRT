
#include <DalRT.hpp>

int main()
{
    // Scene
    DalRT::Scene scene;
    scene.SetMaxDepth(16);
    scene.SetBackgroundColor(glm::vec3(0.8f,0.8f,0.8f));
    scene.SetAmbientLight(glm::vec3(0.1f,0.1f,0.1f));
    
    // Camera
    DalRT::Camera camera;
    camera.SetSize(640, 640);
    camera.SetFOV(3.1415/1.5f);
    camera.SetType(DalRT::Camera::Type::Perspective);
    camera.SetPosition(glm::vec3(4.0f,3.0f,-4.0f));
    camera.SetDirection(glm::vec3(-1.0f,-0.2f,2.0f));
    scene.SetCamera(&camera);
    
    // Sphere
    DalRT::Sphere sphere;
    sphere.SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    sphere.SetRadius(2.0f);
    
    DalRT::Material material1;
    material1.color = glm::vec3(0.0f,0.0f,1.0f);
    material1.reflectiveness = 0.0f;
    material1.specular = glm::vec3(1.0f,1.0f,1.0f);
    material1.specularHardness = 32.0f;
    material1.translucency = 0.0f;
    sphere.SetMaterial(&material1);
    
    // Walls
    DalRT::Quad wall1;
    wall1.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
    wall1.SetSize(10.0f, 10.0f);
    wall1.SetRotation(glm::vec3(glm::pi<float>()/2.0f, 0.0f, 0.0f));
    
    DalRT::Quad wall2;
    wall2.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    wall2.SetSize(10.0f, 10.0f);
    wall2.SetRotation(glm::vec3(glm::pi<float>()/2.0f, 0.0f, 0.0f));
    
    DalRT::Quad wall3;
    wall3.SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
    wall3.SetSize(10.0f, 10.0f);
    wall3.SetRotation(glm::vec3(0.0f, 0.0f, glm::pi<float>()/2.0f));
    
    DalRT::Quad wall4;
    wall4.SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
    wall4.SetSize(10.0f, 10.0f);
    wall4.SetRotation(glm::vec3(0.0f, 0.0f, glm::pi<float>()/2.0f));
    
    DalRT::Material material2;
    material2.color = glm::vec3(0.9f,0.95f,0.9f);
    material2.reflectiveness = 0.95f;
    material2.specular = glm::vec3(0.3f,0.3f,0.3f);
    material2.specularHardness = 32.0f;
    material2.translucency = 0.0f;
    
    wall1.SetMaterial(&material2);
    wall2.SetMaterial(&material2);
    wall3.SetMaterial(&material2);
    wall4.SetMaterial(&material2);
    
    DalRT::Quad floor;
    floor.SetPosition(glm::vec3(0.0f, -5.0f, 0.0f));
    floor.SetSize(10.0f, 10.0f);
    
    DalRT::Quad ceiling;
    ceiling.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    ceiling.SetSize(10.0f, 10.0f);
    
    DalRT::Material material3;
    material3.color = glm::vec3(0.6f,0.6f,0.6f);
    material3.reflectiveness = 0.0f;
    material3.specular = glm::vec3(0.8f,0.8f,0.8f);
    material3.specularHardness = 8.0f;
    material3.translucency = 0.0f;
    
    floor.SetMaterial(&material3);
    ceiling.SetMaterial(&material3);
    
    // Groups
    DalRT::Group group1;
    group1.AddObject(&sphere);
    DalRT::Group group2;
    group2.AddObject(&wall1);
    group2.AddObject(&wall2);
    group2.AddObject(&wall3);
    group2.AddObject(&wall4);
    group2.AddObject(&floor);
    group2.AddObject(&ceiling);
    
    
    // Lights
    DalRT::PointLight light;
    light.SetPosition(glm::vec3(0.0f,4.0f,0.0f));
    light.SetColor(glm::vec3(1.0f,1.0f,1.0f));
    
    // Add all objects and lights
    scene.AddLight(&light);
    scene.AddGroup(&group1);
    scene.AddGroup(&group2);
    
    // Render
    scene.RenderScene();
    
    scene.SaveToPNGFile("Reflection.png");
    
    return 0;
}
