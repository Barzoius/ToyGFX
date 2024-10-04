#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include "Application.h"
#include "iostream"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"


#include "TestSquare.h"



Application::Application()
{
    mWindow = std::make_unique<Window>(800, 600 , "TOY_GFX");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD FAILED";
    }



    //shaderProgram = std::make_unique<ShaderSuite>(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
    //    {"Shaders/VertShader.glsl", Shader::ShaderType::VERTEX},
    //    { "Shaders/FragShader.glsl", Shader::ShaderType::FRAGMENT }
    //});


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


    //ElementBuffer EB(indices);
   

    //VertexArray VA;
    

    //VertexBuffer VB(vertices);

   // VB.Bind();
    //VA.Bind();

    //EB.Bind();


}

Application::~Application()
{
   // glDeleteVertexArrays(1, &VAO);
   // glDeleteBuffers(1, &VBO);

}

void Application::OnEvent()
{
    if (glfwGetKey(mWindow -> GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(mWindow -> GetWindow(), true);
    }

    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        //glfwSetWindowShouldClose(mWindow->GetWindow(), true);
        std::cout << "E";
    }

}


void Application::Run()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mWindow -> GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    TestSquare test;

    while (!glfwWindowShouldClose(mWindow->GetWindow()))
    {

        mWindow->ProcessInput();
   

        glClearColor(0.91f, 0.64f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

      
        test.Draw();
        //glm::mat4 projection = glm::perspective(glm::radians(mWindow->mCamera.zoom), (float)mWindow->GetWidth() / (float)mWindow ->  GetHeight(), 0.1f, 100.0f);

        //shaderProgram->setMat4("projection", projection);

        //glm::mat4 view = mWindow->mCamera.GetViewMatrix();

        //shaderProgram->setMat4("view", view);

       
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        float size; 
        float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
        ImGui::Begin("IMGUI");
        ImGui::Text("IMGUI MSG");

        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);

        ImGui::ColorEdit4("Color", color);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        mWindow->OnUpdate();
    }
}

bool Application::OnWindowClose()
{
    mIsRunning = false;
    return true;
}
