#include <iostream>
#include <thread>
#include <fstream>
#include <cstring>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include "src/Renderer.h"
#include "src/kijuwGL.hpp"
#include "src/Seens/BasicMovement.hpp"
//#include "src/IndexBuffer.h"
//#include "src/VertexArray.h"
//#include "src/Shader.h"

// Window Context
KijuwWindow window(720, 480, "Kijuw");

// Worlds
TestWorld World;

// Global Stuff to any thing can read or write it from this main file
bool CursorLock = false;
bool VSync = true;
double lastX = 0;
double lastY = 0;

float ResolutionScale = 1.0f;

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

    World.KeyInput(window.GetKeyArray());
    
    //World.KeyInput(Keys);

    // This is only done for an example of out of "world" controls

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Toggling Cursor Lock" << std::endl;
        CursorLock = !CursorLock;
        if(!CursorLock){
            glfwSetInputMode(InputWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(InputWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(InputWindow,lastX,lastY);
        }
    }

    if(key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS){
        ResolutionScale -= 0.02; 
        if(ResolutionScale > 1.0){
            std::cout << "Warning Resolusion scale above 1.0" << " | " << ResolutionScale << std::endl;
        } else if(ResolutionScale < 1.0){
            std::cout << "Warning Resolusion scale bellow 1.0" << " | " << ResolutionScale << std::endl;
        }  
        if(ResolutionScale < 0.01){
            ResolutionScale = 0.01;
        }
    }

    if(key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS){
        ResolutionScale += 0.02;  
        if(ResolutionScale > 1.0){
            std::cout << "Warning Resolusion scale above 1.0" << " | " << ResolutionScale << std::endl;
        }else if(ResolutionScale < 1.0){
            std::cout << "Warning Resolusion scale bellow 1.0" << " | " << ResolutionScale << std::endl;
        } 
        if(ResolutionScale > 2.00){
            ResolutionScale = 2.00;
        }
    }

    if(key == GLFW_KEY_V && action == GLFW_PRESS){
        VSync = !VSync;
        window.AttemptMaxFrameRateTarget();
        if(VSync){
            std::cout << "VSync : ON" << std::endl;
        } else {
            std::cout << "VSync : OFF" << std::endl;
        }
    }
    

}

void MousePosCallBack(GLFWwindow *window, double xpos, double ypos){

    if(CursorLock){
        World.MouseInput(xpos, ypos);
        lastX = xpos;
        lastY = ypos;
    }
}

//This is the Physics thread
void SecondThread(int UpdateSpeed){
    float currentPhysicsFrame, lastPhysicsFrame;
    lastPhysicsFrame = 0.0f;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto WaitTime = std::chrono::milliseconds(UpdateSpeed);
    while(World.m_running){
        currentPhysicsFrame= glfwGetTime();
        auto StartTime = std::chrono::steady_clock::now();
        World.PhysicsUpdate(currentPhysicsFrame - lastPhysicsFrame);
        lastPhysicsFrame = currentPhysicsFrame; 
        auto EndTime = std::chrono::steady_clock::now();

        auto ElapsedTime = EndTime - StartTime;
        auto FinalTime = WaitTime - ElapsedTime;
        if(FinalTime > std::chrono::milliseconds::zero()){
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::this_thread::sleep_for(FinalTime);
        }
    }
    
}

// Reserved for future use
void ThirdThread(){

}


int main(void){
    
    std::string TempTitle = "Some Dumb WindowGL ";
    // just to test/ show some options
    window.setWidth(720);
    window.setHeight(480);
    window.setOSScale(1.0f);
    window.ChangeWindowTitle("Kijuw");
    window.SetMaxFrameRateTarget(70);
    window.AttemptMaxFrameRateTarget();

    window.Init();



    if(glewInit() != GLEW_OK){
        std::cout << "ERROR..." << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;

    

    World.Setup();
    std::cout << "World Setup" << std::endl;
    std::thread PhysicsThread(SecondThread,15);
    PhysicsThread.detach();
    std::cout << "Thread information" << std::endl;
    std::cout << "True = " << true << "| False = " << false << std::endl;
    std::cout << PhysicsThread.joinable() << std::endl;
    std::cout << PhysicsThread.get_id() << std::endl;

    World.m_running = true;

    // Yes the KeyCallBack and MouseCallBack must be a function in main (or where ever you have the ability to call) or you can handle passing a static pointer from a class to it.
    glfwSetKeyCallback(window.GetWindow(), KeyCallBack);
    glfwSetCursorPosCallback(window.GetWindow(), MousePosCallBack);
    glfwSetInputMode(window.GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    
    //Temp Fixes/Places
    glEnable(GL_CULL_FACE);
    //glEnable(GL_FRAMEBUFFER_SRGB);

// Draw LOOP
    float FPS = 0;
    /* Loop until the user closes the window */
    while (window.IsOpen()){

        window.SetResolutionScale(ResolutionScale);
        
        FPS = 1.0f/window.GetDeltaTime();
        std::string NewTile = TempTitle + "( " + std::to_string(FPS) + "FPS)";
        window.ChangeWindowTitle(NewTile.c_str());

        window.Update();

        World.OnUpdate(window.GetDeltaTime(), (float)window.GetScaledWidth(), (float)window.GetScaledHeight());

        window.SetSeenRender();
        World.OnRender();

        window.SetPosFXRender();
        World.PaintFrame();

        window.SwapRenderBuffer();



    }

    World.m_running = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    glfwTerminate();
    return 0;
}
