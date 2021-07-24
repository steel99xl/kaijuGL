#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/Renderer.h"
#include "src/Tests/TestClearColor.h"
#include "src/Tests/TestTexture2d.h"
#include "src/Tests/TestBatchRender.h"
#include "src/Tests/TestBatchStreamData.h"
//#include "src/IndexBuffer.h"
//#include "src/VertexArray.h"
//#include "src/Shader.h"

void KeyCallBack( GLFWwindow *window, int key, int scancode, int action, int mods){
    //std::cout << key << std::endl;

    std::cout << "key : " << (char)key << "| scancode : " << scancode << "| action : " << action << "| mods : " << mods << std::endl;
    /*
    if(key == GLFW_KEY_B && action == GLFW_PRESS){
        std::cout << "...boo" << std::endl;
    }
    if(key == GLFW_KEY_B && action == GLFW_REPEAT){
        std::cout << "oooooo";
    }

    if(key == GLFW_KEY_B && action == GLFW_RELEASE){
        std::cout << "oop..." << std::endl;
    }
    */
}

int main(void){
    
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


    test::Test* currentTest = nullptr;
    test::Test_Menu* menu = new test::Test_Menu(currentTest, window);
    currentTest = menu;

    menu->RegisterTest<test::TestClearColor>("Background Color");
    menu->RegisterTest<test::TestTexture2d>("Test Texture 2d");
    menu->RegisterTest<test::TestBatchRender>("Batch Rendering Test");
    menu->RegisterTest<test::TestBatchStreamData>("Dynamicly set vertex buffer test");

    glfwSetInputMode(window, GLFW_STICKY_KEYS,1);
    //glfwSetKeyCallback(window, KeyCallBack);

   
// Draw LOOP
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        glfwGetWindowSize(window, &width, &height);
       
        /* Render here */
        renderer.Clear();

         // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Set Shader, Draw Object
        //shader.SetUniform4f("u_Color", R, 0.0f, 0.0f, 1.0f );
        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        if(currentTest){


            currentTest->OnUpdate(0.0f);


            currentTest->OnRender(width, height, ScalePixle);

            ImGui::Begin("Test");
            
            if(currentTest != menu && ImGui::Button("<-")){
                delete currentTest;
                currentTest = menu; 
            }

            currentTest->OnImGui();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }



        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwTerminate();
    return 0;
}
