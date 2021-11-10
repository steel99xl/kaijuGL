#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window{
    private:
        // ya great naming scheme...
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
        // scale is determined by the OS, Mac is 2.0... unless on a non-retina display
        int m_Scale;
        float m_ResolutionScale;



    public:
        Window(int width, int height, const char* title, float resolutionScale = 0.0f);
        ~Window();


        void update();
        bool isClosed();


};