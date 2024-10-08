#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include "Application.h"
#include "iostream"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"


#include "TestSquare.h"
#include "TestBox.h"
#include "TestSphere.h"
#include "TestPlane.h"
#include "TestPyramid.h"
#include "TestPrism.h"


Application::Application()
{
    mWindow = std::make_unique<Window>(800, 600 , "TOY_GFX");

    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD FAILED";
    }

    glEnable(GL_DEPTH_TEST);
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

    TestSquare test;

    TestBox box(1.0f);

    TestSphere sphere(1.0f);

    TestPlane plane(1.0f);

    TestPyramid pyr(1.0f);

    TestPrism prism(1.0f);

    while (!glfwWindowShouldClose(mWindow->GetWindow()))
    {

        mWindow->ProcessInput();
   

        glClearColor(0.91f, 0.64f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //test.Draw();
        box.Draw();

        //prism.Draw();

        

        //sphere.Draw();

        //plane.Draw();

        //pyr.Draw();
      
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        //model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));

        //model = box.Translate(model);

        glm::mat4 model = box.GetTransformMatrix();


        glm::mat4 cameraView = mWindow->mCamera.GetMatrix();
        cameraView = glm::translate(cameraView, glm::vec3(0.0f, 0.0f, -6.0f));


        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)mWindow->GetWidth() / (float)mWindow -> GetHeight(), 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(test.GetShader() -> GetID(), "model");
        unsigned int viewLoc = glGetUniformLocation(test.GetShader()->GetID(), "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &cameraView[0][0]);

        test.GetShader() -> setMat4("projection", projection);

        box.ControlWND();
        //prism.ControlWND();
        sphere.ControlWND();

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
