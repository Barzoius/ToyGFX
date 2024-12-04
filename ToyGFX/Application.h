#include "Window.h"
#include "Camera.h"
#include "Timer.h"
#include "Shaders\Shader.h"

#include "memory"

#include "Perspective.h"

#include "InputDevices.h"




#include "TestBox.h"
#include "TestPyramid.h"
#include "LightSource.h"
#include "TestPlane.h"
#include "TestContour.h"
#include "TestSquare.h"
#include "TestGrid.h"
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

    TestBox* box;

    LightSource* light;


    TestPyramid* pyr;


    TestPlane* ScreenPlane;
    

    TestContour* CC;


    TestSquare* SQ;

    TestGrid* GRID;
    
private:
    std::unique_ptr<Window> mWindow;
    bool mIsRunning = true;

    Camera camera;
    Timer timer;

    
    std::unique_ptr<ShaderSuite> shaderProgram{};
};