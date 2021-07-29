#include <iostream>
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

void KeyCallBack( GLFWwindow *window, int key, int scancode, int action, int mods){
    //std::cout << key << std::endl;
    World.KeyInput(key, scancode, action, mods);

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

int main(void){
    float deltaTime, lastFrame = 0.0f;

    
    
    int width = 720;
    int height = 480;
    bool PixelMode = true;
    float ScalePixle = 1.0f;
    float ScaleFactor[2] = {0.0f,0.0f};
    float ScaleBuffer;

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
    window = glfwCreateWindow(width, height, "DUMB OPENGL WINDOW", NULL, NULL);
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


    glfwSetInputMode(window, GLFW_STICKY_KEYS,1);
    //glfwSetKeyCallback(window, KeyCallBack);

    World.Setup();

    glfwSetKeyCallback(window, KeyCallBack);
    glfwSetCursorPosCallback(window, MousePosCallBack);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


   GLCall(glEnable(GL_DEPTH_TEST));
 

   
// Draw LOOP
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);
       
        /* Render here */
        renderer.Clear();

         // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Set Shader, Draw Object

        World.OnUpdate(deltaTime);
        World.OnImGui();
        World.OnRender(width, height, ScalePixle);

        // Simple window to display fps
        {
            ImGui::Begin("Simple Info Display");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::DragFloat("Resolution scale", &ScalePixle, 0.01f, 0.25f, 10.0f, "%.03f Resolution Scale");
            ImGui::Text("Virtual Resolution of Window | %.3f width  %.3f height", (float)width*ScalePixle, (float)height*ScalePixle);
            ImGui::Text("Resolution of window | %d width    %d height", width, height);
            ImGui::End();
        }





        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwTerminate();
    return 0;
}
