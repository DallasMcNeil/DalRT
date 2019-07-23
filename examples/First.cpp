
#include <string>
#include <iostream>
#include <sys/time.h>

#include <DalRT.hpp>

//--------------------------------------------------------------
int main()
{
    glm::vec3 vec;
    
    // Scene
    DalRT::Scene scene;
    scene.SetMaxDepth(16);
    vec = glm::vec3(1.0f,1.0f,1.0f);
    scene.SetBackgroundColor(vec);
    vec = glm::vec3(0.2f,0.2f,0.2f);
    scene.SetAmbientLight(vec);
    
    // Camera
    DalRT::Camera camera;
    camera.SetSize(640, 640);
    camera.SetFOV(3.1415/0.2f);
    camera.SetType(DalRT::Camera::Type::Orthographic);
    vec = glm::vec3(5.0f,5.0f,-5.0f);
    //vec = glm::vec3(0.0f,5.0f,-5.0f);
    camera.SetPosition(vec);
    vec = glm::vec3(-1.0f,-1.0f,1.0f);
    //vec = glm::vec3(-1.0f,-0.5f,1.0f);
    camera.SetDirection(vec);
    scene.SetCamera(&camera);
    
    // Spheres
    DalRT::Sphere sphere1;
    vec = glm::vec3(-3.0f, 2.0f, 5.0f);
    sphere1.SetPosition(vec);
    sphere1.SetRadius(2.0f);
    
    DalRT::Material material1;
    material1.color = glm::vec3(1.0f,0.0f,0.0f);
    material1.reflectiveness = 0.0f;
    material1.specular = glm::vec3(1.0f,1.0f,1.0f);
    material1.specularHardness = 32.0f;
    material1.translucency = 0.5f;
    sphere1.SetMaterial(&material1);
    
    DalRT::Sphere sphere2;
    vec = glm::vec3(0.0f, 2.0f, 5.0f);
    sphere2.SetPosition(vec);
    sphere2.SetRadius(1.0f);
    
    DalRT::Material material2;
    material2.color = glm::vec3(1.0f,1.0f,0.5f);
    material2.reflectiveness = 0.5f;
    material2.specular = glm::vec3(1.0f,1.0f,1.0f);
    material2.specularHardness = 32.0f;
    material2.translucency = 0.0f;
    sphere2.SetMaterial(&material2);
    
    DalRT::Sphere sphere3;
    vec = glm::vec3(3.0f, 2.0f, 5.0f);
    sphere3.SetPosition(vec);
    sphere3.SetRadius(2.0f);
    
    DalRT::Material material3;
    material3.color = glm::vec3(0.0f,0.0f,1.0f);
    material3.reflectiveness = 1.0f;
    material3.specular = glm::vec3(1.0f,1.0f,1.0f);
    material3.specularHardness = 64.0f;
    material3.translucency = 0.0f;
    sphere3.SetMaterial(&material3);
    
    DalRT::Quad quad1;
    quad1.SetSize(20.0f,40.0f);
    vec = glm::vec3(0.0f, -4.0f, 0.0f);
    quad1.SetPosition(vec);
    vec = glm::vec3(0.0f, 0.0f, 0.0f);
    quad1.SetRotation(vec);
    
    DalRT::Quad quad2;
    quad2.SetSize(20.0f,20.0f);
    vec = glm::vec3(-10.0f, 0.0f, 0.0f);
    quad2.SetPosition(vec);
    vec = glm::vec3(0.0f, 0.0f, -3.1415f/2.0f);
    quad2.SetRotation(vec);
    
    DalRT::Material material4;
    material4.color = glm::vec3(1.0f,1.0f,1.0f);
    material4.reflectiveness = 0.0f;
    material4.specular = glm::vec3(1.0f,1.0f,1.0f);
    material4.specularHardness = 128.0f;
    material4.translucency = 0.0f;
    quad1.SetMaterial(&material4);
    quad2.SetMaterial(&material4);
    
    DalRT::Triangle tri;
    vec = glm::vec3(-5.0f, 0.0f, 0.0f);
    tri.SetPosition(vec);
    vec = glm::vec3(5.0f, 5.0f, 5.0f);
    tri.SetScale(vec);
    
    
    
    DalRT::Material material5;
    material5.color = glm::vec3(0.0f,1.0f,0.0f);
    material5.reflectiveness = 1.0f;
    material5.specular = glm::vec3(1.0f,1.0f,1.0f);
    material5.specularHardness = 32.0f;
    material5.translucency = 0.5f;
    tri.SetMaterial(&material5);
    
    // Group
    DalRT::Group group;
    group.AddObject(&sphere1);
    group.AddObject(&sphere2);
    group.AddObject(&sphere3);
    group.AddObject(&quad1);
    group.AddObject(&quad2);
    group.AddObject(&tri);
    
    // Lights
    DalRT::PointLight light;
    vec = glm::vec3(0.0f,5.0f,0.0f);
    light.SetPosition(vec);
    vec = glm::vec3(1.5f,1.5f,1.5f);
    light.SetColor(vec);
    
    DalRT::DirectionalLight light2;
    vec = glm::vec3(-0.2f,-1.0f,-0.3f);
    light2.SetDirection(vec);
    vec = glm::vec3(0.7f,0.7f,0.7f);
    light2.SetColor(vec);
    
    //scene.AddLight(&light);
    scene.AddLight(&light2);
    scene.AddGroup(&group);
    
    // Render
    struct timeval tps;
    struct timeval tpe;
    gettimeofday(&tps, NULL);
    scene.RenderScene();
    gettimeofday(&tpe, NULL);
    std::cout << "Rendered in " << ((tpe.tv_sec - tps.tv_sec) * 1000) + ((tpe.tv_usec - tps.tv_usec) / 1000) << "ms" << std::endl;
    
    bool result = scene.SaveToPNGFile("Test.png");
}
