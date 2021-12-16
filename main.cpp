#include "src/kaijuGL.hpp"
#include "src/Seens/BasicMovement.hpp"

// Window Context
KaijuWindow window(720, 480, "Kaiju");

// Worlds
TestWorld World;

// This is the Main keycall back function so you can either manage key iputs globaly or have the worlds handle it
void KeyCallBack( GLFWwindow *InputWindow, int key, int scancode, int action, int mods){
    //std::cout << key << std::endl;
    // Some keys put in to an array to be passed to the worlds
    window.SetKeyArray(GLFW_KEY_W);
    window.SetKeyArray(GLFW_KEY_S);
    window.SetKeyArray(GLFW_KEY_A);
    window.SetKeyArray(GLFW_KEY_D);
    window.SetKeyArray(GLFW_KEY_LEFT_SHIFT);
    window.SetKeyArray(GLFW_KEY_SPACE);
    window.SetKeyArray(GLFW_KEY_LEFT_CONTROL);
    window.SetKeyArray(GLFW_KEY_F);
    window.SetKeyArray(GLFW_KEY_S);
    window.SetKeyArray(GLFW_KEY_L);
    window.SetKeyArray(GLFW_KEY_K);
    window.SetKeyArray(GLFW_KEY_MINUS);
    window.SetKeyArray(GLFW_KEY_EQUAL);
    window.SetKeyArray(GLFW_KEY_UP);
    window.SetKeyArray(GLFW_KEY_DOWN);
    window.SetKeyArray(GLFW_KEY_LEFT);
    window.SetKeyArray(GLFW_KEY_RIGHT);

    World.KeyInput(window.GetKeyArray());
    
    // This is only done for an example of out of "world" controls

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Toggling Cursor Lock" << std::endl;
        window.ToggleCursorLock();
        window.CursorLock(window.IsCursorLock());
    }

    if(key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS){
        window.SetResolutionScale(window.GetResolutionScale() - 0.02);
        if(window.GetResolutionScale() > 1.0){
            std::cout << "Warning Resolusion scale above 1.0" << " | " << window.GetResolutionScale() << std::endl;
        } else if(window.GetResolutionScale() < 1.0){
            std::cout << "Warning Resolusion scale bellow 1.0" << " | " << window.GetResolutionScale() << std::endl;
        }  
        if(window.GetResolutionScale() < 0.01){
            window.SetResolutionScale(0.01);
        }
    }

    if(key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS){
        window.SetResolutionScale(window.GetResolutionScale() + 0.02);
        if(window.GetResolutionScale() > 1.0){
            std::cout << "Warning Resolusion scale above 1.0" << " | " << window.GetResolutionScale() << std::endl;
        }else if(window.GetResolutionScale() < 1.0){
            std::cout << "Warning Resolusion scale bellow 1.0" << " | " << window.GetResolutionScale() << std::endl;
        } 
        if(window.GetResolutionScale() > 2.00){
            window.SetResolutionScale(2.00);
        }
    }

    if(key == GLFW_KEY_V && action == GLFW_PRESS){
        window.AttemptMaxFrameRateTarget();
        if(window.IsAttemptMaxFrameRateTarget()){
            std::cout << "VSync : ON" << std::endl;
        } else {
            std::cout << "VSync : OFF" << std::endl;
        }
    }
    

}

void MousePosCallBack(GLFWwindow *InputWindow, double xpos, double ypos){
    // Global Locking and unlocking of the mouse position
    if(window.IsCursorLock()){
        World.MouseInput(xpos, ypos);
        window.SetMousePos(xpos, ypos);
    }
}

void MouseButtonCallBack(GLFWwindow *InputWindow, int button, int action, int mods){
    window.SetMouseButtonArray(GLFW_MOUSE_BUTTON_LEFT);
    World.MouseButton(window.GetMouseButtonArray());
}
//This is the Physics thread
void SecondThread(int UpdateSpeed){
    // This needs to be moved into the Physics Engine for a cleaner look
    float currentPhysicsFrame, lastPhysicsFrame;
    lastPhysicsFrame = 0.0f;
    // This is to wait for the renderinfg thread to startup
    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto WaitTime = std::chrono::milliseconds(UpdateSpeed);
    while(World.IsWorldRunning()){
        currentPhysicsFrame= glfwGetTime();
        auto StartTime = std::chrono::steady_clock::now();

        World.PhysicsUpdate(currentPhysicsFrame - lastPhysicsFrame);
        lastPhysicsFrame = currentPhysicsFrame; 

        auto EndTime = std::chrono::steady_clock::now();
        auto ElapsedTime = EndTime - StartTime;
        auto FinalTime = WaitTime - ElapsedTime;
        if(FinalTime > std::chrono::milliseconds::zero()){
            std::this_thread::sleep_for(FinalTime);
        }
    }
    
}

// Reserved for future use, lol
void ThirdThread(){

}


int main(void){
    
    std::string TempTitle = "Some Dumb WindowGL ";
    // just to test/show some options
    window.setWidth(720);
    window.setHeight(480);
    window.setOSScale(2.0f);
    window.SetResolutionScale(1.0f);
    window.ChangeWindowTitle("Kijuw");
    window.SetMaxFrameRateTarget(70);
    window.AttemptMaxFrameRateTarget();

    window.Init();


    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;


    World.Setup();
    //World.m_running = true;
    std::cout << "World Setup" << std::endl;
    std::thread PhysicsThread(SecondThread,15);
    PhysicsThread.detach();
    std::cout << "Physics Thread Running..." << std::endl;

    // Yes the KeyCallBack and MouseCallBack must be a function in main (or where ever you have the ability to call) or you can handle passing a static pointer from a class to it.
    glfwSetKeyCallback(window.GetWindow(), KeyCallBack);
    glfwSetCursorPosCallback(window.GetWindow(), MousePosCallBack);
    glfwSetMouseButtonCallback(window.GetWindow(), MouseButtonCallBack);
    glfwSetInputMode(window.GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    

    // Draw LOOP
    float FPS = 0;
    /* Loop until the user closes the window */
    while (window.IsOpen()){

        //window.SetResolutionScale(ResolutionScale);

        window.Update();
        
        FPS = 1.0f/window.GetDeltaTime();
        std::string NewTile = TempTitle + "( " + std::to_string(FPS) + "FPS)";
        window.ChangeWindowTitle(NewTile.c_str());


        World.OnUpdate(window.GetDeltaTime(), (float)window.GetScaledWidth(), (float)window.GetScaledHeight());

        window.SetSeenRender();
        World.OnRender();

        window.SetPosFXRender();
        World.PaintFrame();

        window.SwapRenderBuffer();

    }
    World.Stop();
    //World.m_running = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    glfwTerminate();
    return 0;
}
