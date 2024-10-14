#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include "Application.h"
#include "iostream"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"




Application::Application()
{
    mWindow = std::make_unique<Window>(800, 600 , "TOY_GFX");

   

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD FAILED";
    }

    sphere = new TestSphere(1.0f);
    box = new TestBox(1.0f);

    plane = new TestPlane(1.0f);
    pyr = new TestPyramid(1.0f);
    prism = new TestPrism(1.0f);

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

    while (!glfwWindowShouldClose(mWindow->GetWindow()))
    {

        mWindow->ProcessInput();
   

        glClearColor(0.91f, 0.64f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        cameraView = mWindow->mCamera.GetMatrix();
        cameraView = glm::translate(cameraView, glm::vec3(0.0f, 0.0f, -6.0f));

        projection = glm::perspective(glm::radians(45.0f), (float)mWindow->GetWidth() / (float)mWindow->GetHeight(), 0.1f, 100.0f);

        pyr->ControlWND();
        //pyr->SetPosition();
        pyr->Draw(cameraView, projection);
        pyr->GetShader()->setVec3("Color", 1.0f, 0.0f, 0.0f);



        sphere->ControlWND();
        //sphere->SetPosition();
        sphere->Draw(cameraView, projection);
        sphere->GetShader()->setVec3("Color", 0.5f, 0.0f, 0.5f);



        box->ControlWND();
        //box->SetPosition();
        box->Draw(cameraView, projection);
        box->GetShader()->setVec3("Color", 0.0f, 0.0f, 1.0f);


        
        plane->ControlWND();
        //plane->SetPosition();
        plane->Draw(cameraView, projection);
        plane->GetShader()->setVec3("Color", 1.0f, 0.5f, 0.31f);
        plane->GetShader()->setFloat("SquareSize", squareSize);


  
       // prism->ControlWND();
        //prism->SetPosition();
        //prism->Draw(cameraView, projection);
        //prism->GetShader()->setVec3("Color", 0.0f, 0.23f, 0.3f);
        

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
