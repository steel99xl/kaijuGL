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


// Test 
TestWorld World;


bool CursorLock = false;
double lastX = 0;
double lastY = 0;

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

    Keys[10] = glfwGetKey(window, GLFW_KEY_W);
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
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    auto WaitTime = std::chrono::milliseconds(UpdateSpeed);
    while(true){
        auto StartTime = std::chrono::steady_clock::now();
        World.PhysicsUpdate(UpdateSpeed);
        auto EndTime = std::chrono::steady_clock::now();

        auto ElapsedTime = EndTime - StartTime;

        auto FinalTime = WaitTime - ElapsedTime;
        if(FinalTime > std::chrono::milliseconds::zero()){
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::this_thread::sleep_for(FinalTime);
        }
    }
    
}

void ThirdThread(){

}

int main(void){
    float deltaTime, lastFrame = 0.0f;

    std::string Title = "DUMB OPENGL WINDOW";
    int width = 720;
    int height = 480;
    bool PixelMode = true;
    float ScalePixle = 8.0f;
    float ScaleFactor[2] = {0.0f,0.0f};
    float ScaleBuffer;

    int OSscaler = 2; // This is mainly for mac os

    ScaleBuffer = (float)width/(float)height;

    if(ScaleBuffer < 1.0f){
        ScaleBuffer = (float)height/(float)width;
        ScaleFactor[0] = 1.0f;
        ScaleFactor[1] = ScaleBuffer;
    } else {
        ScaleFactor[0] = ScaleBuffer;
        ScaleFactor[1] = 1.0f;
    }

    std::cout << ScaleFactor[0] << std::endl;
    std::cout << ScaleFactor[1] << std::endl;

    glm::mat4 proj;
    // View can be camera
    glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));
    // Modles position
    //glm::mat4 modle = glm::translate(glm::mat4(1.0f), glm::vec3(100,100,0));
    glm::vec3 posOff(100,100,0);
    glm::mat4 modle = glm::translate(glm::mat4(1.0f), posOff);

    glm::mat4 mvp = proj * view * modle;
    glm::mat4 pv = proj * view; 

    if(PixelMode){

        proj = glm::ortho(0.0f, (float)width*ScalePixle, 0.0f, (float)height*ScalePixle, -1.0f, 1.0f);


    } else{

        proj = glm::ortho(-ScaleFactor[0]*ScalePixle, ScaleFactor[0]*ScalePixle, -ScaleFactor[1]*ScalePixle, ScaleFactor[1]*ScalePixle, -1.0f, 1.0f);

    }



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

    // This can be set once, it does not depend on shader

    const char *glsl_version = "#version 330 core";


    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    //glfwSetKeyCallback(window, KeyCallBack);

    World.Setup();
    std::thread PhysicsThread(SecondThread,15);
    PhysicsThread.detach();


    glfwSetKeyCallback(window, KeyCallBack);
    glfwSetCursorPosCallback(window, MousePosCallBack);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    
    //Temp Fixes/Places
    glEnable(GL_CULL_FACE);

    unsigned int FBO;

    glGenFramebuffers(1, &FBO);
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER ,FBO));

    unsigned int FrameBuffTexture;

    glGenTextures(1, &FrameBuffTexture);
    glBindTexture(GL_TEXTURE_2D, FrameBuffTexture);
    glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, width*OSscaler, height*OSscaler, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D ,FrameBuffTexture, 0);
    
    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width*OSscaler, height*OSscaler);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);


    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if(fboStatus != GL_FRAMEBUFFER_COMPLETE){
            std::cout << "ERROR FRAMEBUFFER " << fboStatus << std::endl;
        }

    SimpleObject Frame;
    Frame.Setup();
    Frame.SetShader("assets/Shaders/FrameBuffer.shader");
    Frame.Create2dQuad(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 2.0f,2.0f, 1.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    Frame.SetTexture(0, "u_Texture");
    Frame.SetFloatUniform("u_Size.height", height/4);
    Frame.SetFloatUniform("u_Size.width", width/4);

   
// Draw LOOP
    unsigned int FrameTimeCount = 0;
    float FPS = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        FPS = 1.0f/deltaTime;
        std::string NewTile = Title + " " + "( " + std::to_string(FPS) + "FPS)";
        glfwSetWindowTitle(window, NewTile.c_str());


        // Frame Buffer Object Stuff

        glBindFramebuffer(GL_FRAMEBUFFER,  FBO);

        glBindTexture(GL_TEXTURE_2D, FrameBuffTexture);
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, width*OSscaler, height*OSscaler, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D ,FrameBuffTexture, 0);


        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width*OSscaler, height*OSscaler);




        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLCall(glEnable(GL_DEPTH_TEST));

       // End of FrameBuffer Stuff for setting it to be writen to

        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);

        


        glViewport(0,0, width*OSscaler, height*OSscaler);
       
        /* Render here */
        renderer.Clear();

         // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Set Shader, Draw Object

        World.OnUpdate(deltaTime, width, height);
        World.OnImGui();
        World.OnRender();

        // Simple window to display fps
        {
            //ImGui::Begin("Simple Info Display");
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //ImGui::Text("Resolution of window | %d width    %d height", width, height);
            //ImGui::End();
        }

        // This has to be drawn on the bottom buffer on mac but on linux it has to be the top
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        


        // Frame Buffer Object Drawing..
        // The Frame Buffer Object SHould be provided by the window
        glBindTexture(GL_TEXTURE_2D, FrameBuffTexture);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLCall(glDisable(GL_DEPTH_TEST)); 
        Frame.BindBufferData();

        //float Twidth = (float)width;
        //float Theight = (float)height;

        //Frame.SetFloatUniform("u_Size.height", Twidth);
        //Frame.SetFloatUniform("u_Size.width", Theight);
        Frame.Paint();

        


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        

    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwTerminate();
    return 0;
}
