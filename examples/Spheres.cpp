
#include <iostream>
#include <DalRT.hpp>

DalRT::Sphere spheres[4096];
DalRT::Material materials[4096];
DalRT::Group groups[4096];

int sphereCount = 0;
int groupCount = 0;

void MakeSpheres(DalRT::Group *group, glm::vec3 centre, float offset)
{
    for (int x=-1; x<2;x+=2)
    {
        for (int y=-1; y<2;y+=2)
        {
            for (int z=-1; z<2;z+=2)
            {
                glm::vec3 pos = centre + glm::vec3(x*offset, y*offset, z*offset);
                
                spheres[sphereCount].SetPosition(pos);
                spheres[sphereCount].SetRadius(1.5f);
                
                materials[sphereCount].color = glm::vec3(1.0f,0.0f,0.0f);
                materials[sphereCount].reflectiveness = 0.0f;
                materials[sphereCount].specular = glm::vec3(1.0f,1.0f,1.0f);
                materials[sphereCount].specularHardness = 32.0f;
                materials[sphereCount].translucency = 0.0f;
                
                spheres[sphereCount].SetMaterial(&materials[sphereCount]);
                group->AddObject(&spheres[sphereCount]);
                
                sphereCount++;
            }
        }
    }
}

void MakeGroups(DalRT::Group *group, int depth, glm::vec3 centre, float offset)
{
    for (int x=-1; x<2;x+=2)
    {
        for (int y=-1; y<2;y+=2)
        {
            for (int z=-1; z<2;z+=2)
            {
                glm::vec3 pos = centre + glm::vec3(x*offset, y*offset, z*offset);
                DalRT::Group* subGroup = &groups[groupCount];
                groupCount++;
                if (depth == 0)
                {
                    MakeSpheres(subGroup, pos, offset/2.0f);
                }
                else
                {
                    MakeGroups(subGroup, depth-1, pos, offset/2.0f);
                }
                
                group->AddSubGroup(subGroup);
                groupCount++;
            }
        }
    }
}

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
    camera.SetFOV(3.1415/2.0f);
    camera.SetType(DalRT::Camera::Type::Perspective);
    camera.SetPosition(glm::vec3(0.0f,0.0f,-150.0f));
    camera.SetDirection(glm::vec3(0.0f,0.0f,1.0f));
    scene.SetCamera(&camera);
    
    // Spheres
    DalRT::Group mainGroup;
    MakeGroups(&mainGroup, 2, glm::vec3(0.0f,0.0f,0.0f), 64.0f);
    scene.AddGroup(&mainGroup);

    // Lights
    DalRT::DirectionalLight light;
    light.SetDirection(glm::vec3(-0.2f,-1.0f,-0.3f));
    light.SetColor(glm::vec3(1.0f,1.0f,1.0f));
    light.SetDistance(1.0f);
    
    // Add all objects and lights
    scene.AddLight(&light);
    
    // Render
    scene.RenderScene();
    
    scene.SaveToPNGFile("Sphere.png");
    
    return 0;
}
