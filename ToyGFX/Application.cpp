#include "Application.h"
#include "iostream"

#include "VertexBuffer.h"
#include "VertexArray.h"

Application::Application()
{
    mWindow = std::make_unique<Window>(800, 600 , "TERRAIN_GENERATION");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD FAILED";
    }

    shaderProgram = std::make_unique<ShaderSuite>(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
        {"Shaders/VertShader.glsl", Shader::ShaderType::VERTEX},
        { "Shaders/FragShader.glsl", Shader::ShaderType::FRAGMENT },
    });

    std::cout<<shaderProgram -> GetID();

    std::vector<float> vertices = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    VertexArray VA;
    VA.Bind();

    VertexBuffer VB(vertices);

    VA.LinkVertexBuff(VB);
    
    VAO = VA.GetVAO();


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
       
        glDrawArrays(GL_TRIANGLES, 0, 3);

       /* float fov = 45.0f;
        glm::mat4 projection = glm::perspective(glm::radians(fov), 
            (float)mWindow -> GetHeight() / (float)mWindow->GetWidth(), 0.1f, 100.0f);*/

        mWindow->OnUpdate();
    }
}

bool Application::OnWindowClose()
{
    mIsRunning = false;
    return true;
}