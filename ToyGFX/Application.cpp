#include "Application.h"
#include "iostream"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "glm\common.hpp"


Application::Application()
{
    mWindow = std::make_unique<Window>(800, 600 , "TOY_GFX");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD FAILED";
    }

    Assimp::Importer imp;
    auto model = imp.ReadFile("Resources\\Models\\suzanne.obj",
                              aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    shaderProgram = std::make_unique<ShaderSuite>(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
        {"Shaders/VertShader.glsl", Shader::ShaderType::VERTEX},
        { "Shaders/FragShader.glsl", Shader::ShaderType::FRAGMENT },
        { "Shaders/FragShader.glsl", Shader::ShaderType::FRAGMENT },
    });
 

    std::vector<float> vertices = {
        // positions         // colors
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  // bottom right
        0.5f, -0.5f, 0.0f,  0.543f, 1.0f, 0.0f,  // bottom left
        -0.5f,  -0.5f, 0.0f,  0.0f, 0.23f, 1.0f,   // top 
        -0.5f,  0.5f, 0.0f,  0.0f, 0.65f, 0.0f
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };


    ElementBuffer EB(indices);
   

    VertexArray VA;
    VA.Bind();

    VertexBuffer VB(vertices);


    VA.LinkVertexBuff(VB);

    EB.Bind();

    EBO = EB.GetID();
    
    VAO = VA.GetID();


}

Application::~Application()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

}


void Application::Run()
{

    while (!glfwWindowShouldClose(mWindow->GetWindow()))
    {

        mWindow->ProcessInput();

        glClearColor(0.91f, 0.64f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram -> use();
        glBindVertexArray(VAO);
       
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        mWindow->OnUpdate();
    }
}

bool Application::OnWindowClose()
{
    mIsRunning = false;
    return true;
}