#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include "Application.h"
#include "iostream"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"

#include "Shaders\Shader.h"



Application::Application()
{
    mWindow = std::make_unique<Window>(800, 600 , "TOY_GFX");

   

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD FAILED";
    }

    box = new TestBox(1.0f);
    light = new LightSource(1.0f);
    light->SetPosition(glm::vec3(0.0f, 0.0f, -6.0f));

    pyr = new TestPyramid(2.0f);

    ScreenPlane = new TestPlane(1.0f);


    CC = new TestContour();

    GRID = new TestGrid(1.0f);
    //SQ = new TestSquare();



    glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{

}

void Application::OnEvent()
{
    if (glfwGetKey(mWindow -> GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(mWindow -> GetWindow(), true);
    }

    if(glfwGetKey(mWindow -> GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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



    glm::mat4 cameraView;
    glm::mat4 projection = glm::mat4(1.0f);

    int Divs = 8;

    float squareSize = 2.0f / Divs;

    //ShaderSuite ss = ShaderSuite(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
    //    {"Shaders/BaseVertex.glsl", Shader::ShaderType::VERTEX},
    //    { "Shaders/CSG.glsl", Shader::ShaderType::FRAGMENT }
    //});

    //glm::vec2 res = glm::vec2(mWindow->GetHeight(), mWindow->GetWidth());


    while (!glfwWindowShouldClose(mWindow->GetWindow()))
    {

        mWindow->ProcessInput();
   

        glClearColor(0.91f, 0.64f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        cameraView = mWindow->mCamera.GetMatrix();
        cameraView = glm::translate(cameraView, glm::vec3(0.0f, 0.0f, 1.0f));

        projection = glm::perspective(glm::radians(45.0f), (float)mWindow->GetWidth() / (float)mWindow->GetHeight(), 0.1f, 100.0f);

       /* ss.setVec2("uResolution", res);
        ss.use();*/

        

        //box->ControlWND();
        //box->Draw(cameraView, projection);
        //box->GetShader()->setVec3("Color", 0.0f, 0.0f, 1.0f);

        
            //light->ControlWND();
            //light->Draw(cameraView, projection);
            //light->GetShader()->setVec3("Color", 1.0f, 1.0f, 1.0f);



        //pyr->ControlWND();
        //pyr->Draw(cameraView, projection);
        //pyr->GetShader()->setVec3("Color", 1.0f, 0.23f, 1.0f);
   


        //CC->ControlWND();
        //CC->Draw(cameraView, projection);
        //CC->GetShader()->setVec3("Color", 1.0f, 0.23f, 1.0f);

        


        GRID->ControlWND();
        GRID->Draw(cameraView, projection);
        GRID->GetShader()->setVec3("Color", 1.0f, 0.23f, 1.0f);

        //SQ->ControlWND();
        //SQ->Draw(cameraView, projection);
        //SQ->GetShader()->setVec3("Color", 1.0f, 0.23f, 1.0f);

 

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
