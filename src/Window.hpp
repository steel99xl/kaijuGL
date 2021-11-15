#pragma once
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>


class Window{
    private:
        // ya great naming scheme...
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
        std::string m_Title;
        // scale is determined by the OS, Mac is 2.0... unless on a non-retina display
        int m_OSScale;
        float m_ResolutionScale;


        float m_CurrentFrameTime, m_LastFrameTime, m_DeltaTime;

        int m_MaxFrameRate;
        bool m_AtmpMaxFPS = false;

        inline void WindowThreadSleep() {std::this_thread::sleep_for(std::chrono::milliseconds(m_MaxFrameRate)); };


    public:
        Window(int width, int height, std::string title, float OSResolutionScale = 1.0f, int OpenGLMajorVersion = 3, int OpenGLMinorVersion = 3);
        ~Window();


        void Init();

        void Update();

        void SetSeenRender();

        void SetPosFXRender();

        void SwapRenderBuffer();

        void SetResolutionScale(float scale);

        void ManageVSync(bool enabled);

        inline void SetMaxFrameRateTarget(int target) {m_MaxFrameRate = 1000/target;}

        inline void AttemptMaxFrameRateTarget() { m_AtmpMaxFPS = !m_AtmpMaxFPS; }; 

        inline void ChangeWindowTitle(std::string title){m_Title = title;}

        inline  std::string GetWindowTitle() {return m_Title;}

        inline float GetDeltaTime() {return m_DeltaTime;}

        inline GLFWwindow* GetWindow() {return m_Window;}


        bool IsOpen();



        inline int GetScaledWidth() const { return m_Width * m_ResolutionScale;}
        inline int GetScaledHeight() const { return m_Height * m_ResolutionScale;}


};