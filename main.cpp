#include <iostream>
#include <thread>
#include <fstream>
#include <cstring>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include "src/Renderer.h"
#include "src/Engine.hpp"
#include "src/Seens/BasicMovement.hpp"
//#include "src/IndexBuffer.h"
//#include "src/VertexArray.h"
//#include "src/Shader.h"


// Worlds
TestWorld World;

// Global Stuff to any thing can read or write it from this main file
bool CursorLock = false;
bool VSync = true;
double lastX = 0;
double lastY = 0;

float ResolutionScale = 1.0f;

// This is the Main keycall back function to pass keys to the world
void KeyCallBack( GLFWwindow *window, int key, int scancode, int action, int mods){
    //std::cout << key << std::endl;
    int Keys[100];
    Keys[0] = glfwGetKey(window, GLFW_KEY_W);
    Keys[1] = glfwGetKey(window, GLFW_KEY_S);
    Keys[2] = glfwGetKey(window, GLFW_KEY_A);
    Keys[3] = glfwGetKey(window, GLFW_KEY_D);

    Keys[4] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    Keys[5] = glfwGetKey(window, GLFW_KEY_SPACE);
    Keys[6] = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);

    Keys[10] = glfwGetKey(window, GLFW_KEY_F);
    Keys[11] = glfwGetKey(window, GLFW_KEY_S);
    Keys[12] = glfwGetKey(window, GLFW_KEY_A);
    Keys[13] = glfwGetKey(window, GLFW_KEY_D);

    Keys[14] = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
    Keys[15] = glfwGetKey(window, GLFW_KEY_RIGHT_ALT);
    Keys[16] = glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL);

    Keys[20] = glfwGetKey(window, GLFW_KEY_L);
    Keys[21] = glfwGetKey(window, GLFW_KEY_K);

    Keys[22] = glfwGetKey(window, GLFW_KEY_MINUS);
    Keys[23] = glfwGetKey(window, GLFW_KEY_EQUAL);



    
    World.KeyInput(Keys);

    // This is only done for an example of out of "world" controls

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        std::cout << "Toggling Cursor Lock" << std::endl;
        CursorLock = !CursorLock;
        if(!CursorLock){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window,lastX,lastY);
        }
    }

    if(key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS){
          ResolutionScale -= 0.02;  
          if(ResolutionScale < 0.01){
              ResolutionScale = 0.01;
          }
    }

    if(key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS){
          ResolutionScale += 0.02;  
          if(ResolutionScale > 1.00){
              ResolutionScale = 1.00;
          }
    }

    if(key == GLFW_KEY_V && action == GLFW_PRESS){
        VSync = !VSync;
        if(VSync){
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
    }
    

}

void MousePosCallBack(GLFWwindow *window, double xpos, double ypos){

    if(CursorLock){
        World.MouseInput(xpos, ypos);
        lastX = xpos;
        lastY = ypos;
    }
    
    // Why does this work..
    //World.Test(xpos, ypos);

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
    float deltaTime, lastFrame = 0.0f;

    std::string Title = "DUMB OPENGL WINDOW";
    int width = 720;
    int height = 480;
    int OSscaler = 2; // This is mainly for macOS


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    //Set OpenGL Version

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, Title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // Enables V sync
    glfwSwapInterval(1);

    /* setup GLEW */
    if(glewInit() != GLEW_OK){
        std::cout << "ERROR..." << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;
    


    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));



    Renderer renderer;


    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    World.Setup();
    std::thread PhysicsThread(SecondThread,15);
    PhysicsThread.detach();

    World.m_running = true;


    glfwSetKeyCallback(window, KeyCallBack);
    glfwSetCursorPosCallback(window, MousePosCallBack);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    
    //Temp Fixes/Places
    glEnable(GL_CULL_FACE);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    /* 
    
    */ 
   
// Draw LOOP
    float FPS = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        FPS = 1.0f/deltaTime;
        std::string NewTile = Title + " " + "( " + std::to_string(FPS) + "FPS)";
        glfwSetWindowTitle(window, NewTile.c_str());
        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);
        //glViewport(0,0, width*OSscaler, height*OSscaler);


        World.OnUpdate(deltaTime, width * ResolutionScale, height * ResolutionScale, OSscaler);
        // Make Shadows hopefully
        //glViewport(0,0, 2048,2048);
        //World.GenShadows();
        //glBindFramebuffer(GL_FRAMEBUFFER,0);
        //glViewport(0,0, width*OSscaler, height*OSscaler);

        /* Render here */
        renderer.Clear();

        World.OnGui();
        // Set Shader, Draw Object

        glViewport(0,0, (width*OSscaler) * ResolutionScale, (height*OSscaler) * ResolutionScale);
        World.OnRender();

        glViewport(0,0, (width*OSscaler), (height*OSscaler));
        World.PaintFrame();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        

    }

    World.m_running = false;

    glfwTerminate();
    return 0;
}
