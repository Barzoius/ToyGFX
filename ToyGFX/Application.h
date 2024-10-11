#include "Window.h"
#include "Camera.h"
#include "Timer.h"
#include "Shaders\Shader.h"

#include "memory"

#include "Perspective.h"

#include "InputDevices.h"



#include "TestSquare.h"
#include "TestBox.h"
#include "TestSphere.h"
#include "TestPlane.h"
#include "TestPyramid.h"
#include "TestPrism.h"



class Application
{
public:
    Application();
    ~Application();

    void Run();
    void OnEvent();

    bool OnWindowClose();

    inline Window* GetWindow() { return mWindow.get(); }

    //TestSquare test;

    TestBox* box;

    TestSphere* sphere;

    //TestSphere sphere{1.0f};

    //TestPlane plane{ 1.0f };

    //TestPyramid pyr{1.0f};

    //TestPrism prism{ 1.0f };
    
private:
    std::unique_ptr<Window> mWindow;
    bool mIsRunning = true;

    Camera camera;
    Timer timer;

   // Projection proj;



    
    std::unique_ptr<ShaderSuite> shaderProgram{};
};