
#include <DalRT.hpp>

int main()
{
    // Scene
    DalRT::Scene scene;
    scene.SetMaxDepth(16);
    scene.SetBackgroundColor(glm::vec3(0.4f,0.8f,1.0f));
    scene.SetAmbientLight(glm::vec3(0.1f,0.1f,0.1f));
    
    // Camera
    DalRT::Camera camera;
    camera.SetSize(640, 640);
    camera.SetFOV(3.1415/2.0f);
    camera.SetType(DalRT::Camera::Type::Perspective);
    camera.SetPosition(glm::vec3(1.0f,6.0f,-2.0f));
    camera.SetDirection(glm::vec3(-0.3f,-0.4f,1.0f));
    scene.SetCamera(&camera);
    
    // Fins
    DalRT::Group group1;
    
    DalRT::Triangle tris[8];
    DalRT::Material materials[8];
    glm::vec3 colors[8] = {
        glm::vec3(1.0f,0.0f,0.0f),
        glm::vec3(1.0f,0.5f,0.0f),
        glm::vec3(1.0f,1.0f,0.0f),
        glm::vec3(0.0f,1.0f,0.0f),
        glm::vec3(0.0f,1.0f,1.0f),
        glm::vec3(0.0f,0.5f,1.0f),
        glm::vec3(0.5f,0.0f,1.0f),
        glm::vec3(1.0f,0.0f,1.0f)
    };
    
    for (int i=0; i<8; i++)
    {
        tris[i].SetPoints(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.5f,0.5f,0.0f));
        tris[i].SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
        tris[i].SetRotation(glm::vec3(0.0f,0.0f,glm::pi<float>() * (float(i)/4.0f)));
        group1.AddObject(&tris[i]);
        
        materials[i].color = colors[i];
        materials[i].reflectiveness = 0.0f;
        materials[i].specular = glm::vec3(0.0f,0.0f,0.0f);
        materials[i].specularHardness = 32.0f;
        materials[i].translucency = 0.8f;
        tris[i].SetMaterial(&materials[i]);
    }
    
    // Stick
    DalRT::Quad stick;
    stick.SetSize(0.1f, 5.0f);
    stick.SetPosition(glm::vec3(0.0f,2.5f,0.0f));
    stick.SetRotation(glm::vec3(glm::pi<float>()/2.0f,0.0f,0.0f));
    
    DalRT::Group group2;
    group2.AddObject(&stick);
    
    DalRT::Material material2;
    material2.color = glm::vec3(0.0f,0.0f,0.0f);
    material2.reflectiveness = 0.0f;
    material2.specular = glm::vec3(0.0f,0.0f,0.0f);
    material2.specularHardness = 32.0f;
    material2.translucency = 0.0f;
    stick.SetMaterial(&material2);
    
    // Ground
    DalRT::Quad ground;
    ground.SetSize(100.0f,100.0f);
    ground.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    
    DalRT::Group group3;
    group3.AddObject(&ground);
    
    DalRT::Material material3;
    material3.color = glm::vec3(1.0f,1.0f,1.0f);
    material3.reflectiveness = 0.0f;
    material3.specular = glm::vec3(0.0f,0.0f,0.0f);
    material3.specularHardness = 32.0f;
    material3.translucency = 0.0f;
    ground.SetMaterial(&material3);
    
    // Lights
    DalRT::DirectionalLight light;
    light.SetDirection(glm::vec3(0.5f,-1.0f,1.0f));
    light.SetColor(glm::vec3(1.0f,1.0f,1.0f));
    
    // Add all objects and lights
    scene.AddLight(&light);
    scene.AddGroup(&group1);
    scene.AddGroup(&group2);
    scene.AddGroup(&group3);
    
    // Render
    scene.RenderScene();
    
    scene.SaveToPNGFile("Transparency.png");
    
    return 0;
}
