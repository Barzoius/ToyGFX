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


    box = new TestBox(1.0f);
    sphere = new TestSphere(1.0f);



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



    while (!glfwWindowShouldClose(mWindow->GetWindow()))
    {

        mWindow->ProcessInput();
   

        glClearColor(0.91f, 0.64f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        glm::mat4 cameraView = mWindow->mCamera.GetMatrix();
        cameraView = glm::translate(cameraView, glm::vec3(0.0f, 0.0f, -6.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)mWindow->GetWidth() / (float)mWindow->GetHeight(), 0.1f, 100.0f);


        box->ControlWND();

        box->GetShader()->use();

        glm::mat4 boxMod = box->GetTransformMatrix();

        unsigned int modelBox = glGetUniformLocation(box->GetShader()->GetID(), "model");

        glUniformMatrix4fv(modelBox, 1, GL_FALSE, glm::value_ptr(boxMod));

        unsigned int viewLocBox = glGetUniformLocation(box->GetShader()->GetID(), "view");

        glUniformMatrix4fv(viewLocBox, 1, GL_FALSE, &cameraView[0][0]);

        box->GetShader()->setMat4("projection", projection);

        box->Draw();




        sphere->ControlWND();


        sphere->GetShader()->use();

        glm::mat4 sphereMod = sphere -> GetTransformMatrix();

        unsigned int modelSphere = glGetUniformLocation(sphere->GetShader()->GetID(), "model");

        glUniformMatrix4fv(modelSphere, 1, GL_FALSE, glm::value_ptr(sphereMod));

        unsigned int viewLoc = glGetUniformLocation(sphere->GetShader()->GetID(), "view");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &cameraView[0][0]);

        sphere -> GetShader() -> setMat4("projection", projection);

        sphere->Draw();

 





        

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
