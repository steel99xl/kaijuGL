#include "Window.hpp"

Window::Window(int width, int height, std::string title, float OSResolutionScale ,int OpenGLMajorVersion, int OpenGLMinorVersion){
    m_Width = width;
    m_Height = height;
    m_Title = title;
    m_OSScale = OSResolutionScale;
    m_ResolutionScale = 1.0f;

    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLMinorVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

Window::~Window(){
    glfwDestroyWindow(m_Window);
}

void Window::Init(){
    std::cout << "Initializing Window" << std::endl;
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
    if(!m_Window){
        glfwTerminate();
        exit(-1);
    }
    std::cout << "Setting Windoow Context" << std::endl;
    glfwMakeContextCurrent(m_Window);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    //glBindVertexArray(0);
    //glUseProgram(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Window::Update(){
    m_CurrentFrameTime = glfwGetTime();
    m_DeltaTime = m_CurrentFrameTime - m_LastFrameTime;
    m_LastFrameTime = m_CurrentFrameTime;


    glfwPollEvents();
    glfwSetWindowTitle(m_Window, m_Title.c_str());
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);

    if(m_AtmpMaxFPS){
        Window::WindowThreadSleep();
    }

}

void Window::SetSeenRender(){
    glViewport(0, 0, Window::GetScaledWidth(), Window::GetScaledHeight());
}

void Window::SetPosFXRender(){
    glViewport(0, 0, m_Width * m_OSScale, m_Height * m_OSScale);
}

void Window::SwapRenderBuffer(){
    glfwSwapBuffers(m_Window);
}

void Window::SetResolutionScale(float scale){
    m_ResolutionScale = scale;
}

void Window::ManageVSync(bool enable){
    if(enable){
        glfwSwapInterval(1);
    }else{
        glfwSwapInterval(0);
    }
}


bool Window::IsOpen(){
    return !glfwWindowShouldClose(m_Window);
}