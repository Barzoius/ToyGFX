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

    box = new TestBox(0.5f);
    light = new LightSource(2.0f);
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



glm::vec3 randomColor()
{
    // Generate random float values between 0.0f and 1.0f
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value for Red
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value for Green
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Random value for Blue

    return glm::vec3(r, g, b);
}

// Optionally, you can call this to seed the random number generator at the start of your program
void seedRandom()
{
    std::srand(static_cast<unsigned int>(std::time(0)));  // Seed the random number generator with the current time
}

void Application::Run()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mWindow -> GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");



    seedRandom();

    glm::mat4 cameraView;
    glm::mat4 projection = glm::mat4(1.0f);

    int Divs = 8;

    float squareSize = 2.0f / Divs;

    //ShaderSuite ss = ShaderSuite(std::initializer_list<std::pair<std::string_view, Shader::ShaderType>>{
    //    {"Shaders/BaseVertex.glsl", Shader::ShaderType::VERTEX},
    //    { "Shaders/CSG.glsl", Shader::ShaderType::FRAGMENT }
    //});

    //glm::vec2 res = glm::vec2(mWindow->GetHeight(), mWindow->GetWidth());

    std::vector<glm::vec3> translations;
    int numObjects = 100;       
    //float offset = 2.0f;        
    float heightIncrement = 0.1f; 
    float radiusIncrement = 0.1f; 
    float initialRadius = 2.0f;  

    std::vector<glm::vec3> colors;

    //for (int i = 0; i < numObjects; ++i)
    //{
    //    // Adjust the radius to be incremented along with the loop index (i)
    //    float radius = initialRadius + radiusIncrement * float(i); // Increment the radius as you go along the spiral

    //    // Angle for circular motion based on the current index (i)
    //    float theta = 2.0f * glm::pi<float>() * float(i) / numObjects;

    //    // Vertical height increases with each object
    //    float height = heightIncrement * float(i); // Vertical height, space them further apart

    //    // Calculate the translation position of the object
    //    glm::vec3 translation;
    //    translation.x = radius * cos(theta) + offset; // X position based on radius and angle
    //    translation.y = radius * sin(theta) + offset; // Y position based on radius and angle
    //    translation.z = height + offset; // Z position (height) increasing with each object

    //    translations.push_back(translation);
    //}

    int index = 0;
    float offset = 0.1f;  // Optional offset
    float spaceBetweenCubes = 2.0f; // Increase the space between cubes

    for (int z = -15; z < 15; z++)
    {
        for (int y = -15; y < 15; y++)
        {
            for (int x = -15; x < 15; x++)
            {
                glm::vec3 translation;
                translation.x = x * spaceBetweenCubes + offset;
                translation.y = y * spaceBetweenCubes + offset;
                translation.z = z * spaceBetweenCubes + offset;
                translations.push_back(translation);
            }
        }
    }


    const int numObj = 1000;   
    const float r = 4.0f;        
    const float c = 0.1f;         
    const float deltaT = 1.5f;    


/*    for (int i = 0; i < numObj; i++) {
        float t = i * deltaT;  
        float x = r * cos(t); 
        float y = r * sin(t); 
        float z = c * t;       

        translations.push_back(glm::vec3(x, y, z));
    }
       */ 
 


    for (int i = 0; i < 20*20*20*20; ++i)
    {
        colors.push_back(randomColor());
        colors.push_back(randomColor());
        colors.push_back(randomColor());
        colors.push_back(randomColor());

    }



    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, colorBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);


    //box->InitInstancedData<decltype(*this)>(translations);
     light->InitInstancedData<decltype(*this)>(translations);

    

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

        projection = glm::perspective(glm::radians(45.0f), (float)mWindow->GetWidth() / (float)mWindow->GetHeight(), 0.1f, 1000.0f);

       /* ss.setVec2("uResolution", res);
        ss.use();*/

        

       // box->ControlWND();
        //box->Draw(cameraView, projection);
        

       // box->DrawIndexed(translations, cameraView, projection);
        
       // box->GetShader()->setVec3("Color", 0.0f, 0.0f, 1.0f);

        
        light->ControlWND();
        //light->Draw(cameraView, projection);
        light->DrawIndexed(translations, cameraView, projection);
        GLuint colorBlockIndex = glGetUniformBlockIndex(light->GetShader()->GetID(), "ColorBlock");
        glUniformBlockBinding(light->GetShader()->GetID(), colorBlockIndex, 0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, colorBuffer);
       // light->GetShader()->setVec3("Color", randomColor());



        //pyr->ControlWND();
        //pyr->Draw(cameraView, projection);
        //pyr->GetShader()->setVec3("Color", 0.478f, 0.522f, 1.0f);
   


        //CC->ControlWND();
        //CC->Draw(cameraView, projection);
        //CC->GetShader()->setVec3("Color", 1.0f, 0.23f, 1.0f);

        


        //GRID->ControlWND();
        //GRID->Draw(cameraView, projection);
        //GRID->GetShader()->setVec3("Color", 1.0f, 0.23f, 1.0f);

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
