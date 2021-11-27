#include "KaijuWindow.hpp"

KaijuWindow::KaijuWindow(int width, int height, std::string title, float OSResolutionScale ,int OpenGLMajorVersion, int OpenGLMinorVersion){
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

KaijuWindow::~KaijuWindow(){
    glfwDestroyWindow(m_Window);
}

void KaijuWindow::Init(){
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

    if(glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    glEnable(GL_CULL_FACE);

    //glBindVertexArray(0);
    //glUseProgram(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void KaijuWindow::Update(){
    m_CurrentFrameTime = glfwGetTime();
    m_DeltaTime = m_CurrentFrameTime - m_LastFrameTime;
    m_LastFrameTime = m_CurrentFrameTime;


    glfwPollEvents();
    glfwSetWindowTitle(m_Window, m_Title.c_str());
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);

    if(m_AtmpMaxFPS){
        KaijuWindow::WindowThreadSleep();
    }

}

void KaijuWindow::SetSeenRender(){
    glViewport(0, 0, KaijuWindow::GetScaledWidth(), KaijuWindow::GetScaledHeight());
}

void KaijuWindow::SetPosFXRender(){
    glViewport(0, 0, m_Width * m_OSScale, m_Height * m_OSScale);
}

void KaijuWindow::SwapRenderBuffer(){
    glfwSwapBuffers(m_Window);
}

void KaijuWindow::SetResolutionScale(float scale){
    m_ResolutionScale = scale;
}

void KaijuWindow::ManageVSync(bool enable){
    if(enable){
        glfwSwapInterval(1);
    }else{
        glfwSwapInterval(0);
    }
}

void KaijuWindow::SetKeyArray(int key){
    m_Keys[key] = glfwGetKey(m_Window, key);
}

void KaijuWindow::SetMouseButtonArray(int button){
    m_MouseButtons[button] = glfwGetMouseButton(m_Window, button);
}

void KaijuWindow::CursorLock(bool enable){
    if(enable){
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(m_Window, m_LastMouseX, m_LastMouseY);
    }else{
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}


bool KaijuWindow::IsOpen(){
    return !glfwWindowShouldClose(m_Window);
}