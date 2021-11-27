#pragma once

#include "kaijuGL.hpp"



class KaijuWindow{
    protected:
        // ya great naming scheme...
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
        std::string m_Title;
        // scale is determined by the OS, Mac is 2.0... unless on a non-retina display
        int m_OSScale;
        float m_ResolutionScale;

        // This should be more than enough keys for any keyboard
        std::array<int,512> m_Keys;

        // So far the most mouse buttons ive seen on a mouse is 19
        std::array<int, 32> m_MouseButtons;
        int m_MouseX, m_MouseY, m_LastMouseX, m_LastMouseY;

        bool m_CursorLock = false;

        float m_CurrentFrameTime, m_DeltaTime;
        float m_LastFrameTime = 0.0f;

        int m_MaxFrameRate;
        bool m_AtmpMaxFPS = false;

        inline void WindowThreadSleep() {std::this_thread::sleep_for(std::chrono::milliseconds(m_MaxFrameRate)); };


    public:
        KaijuWindow(int width, int height, std::string title, float OSResolutionScale = 1.0f, int OpenGLMajorVersion = 3, int OpenGLMinorVersion = 3);
        ~KaijuWindow();


        void Init();

        void Update();

        void SetSeenRender();

        void SetPosFXRender();

        void SwapRenderBuffer();

        void SetResolutionScale(float scale);

        inline float GetResolutionScale() { return m_ResolutionScale; };

        void ManageVSync(bool enabled);

        inline void SetMaxFrameRateTarget(int target) {m_MaxFrameRate = 1000/target;}

        inline void AttemptMaxFrameRateTarget() { m_AtmpMaxFPS = !m_AtmpMaxFPS; };

        inline bool IsAttemptMaxFrameRateTarget() { return m_AtmpMaxFPS; }

        inline void ChangeWindowTitle(std::string title){m_Title = title;}

        inline  std::string GetWindowTitle() {return m_Title;}

        inline float GetDeltaTime() {return m_DeltaTime;}

        inline GLFWwindow* GetWindow() {return m_Window;}

        void SetKeyArray(int key);

        inline std::array<int,512> GetKeyArray() {return m_Keys;}

        void SetMouseButtonArray(int button);

        inline std::array<int,32> GetMouseButtonArray() {return m_MouseButtons;}

        inline void SetMousePos(int x, int y) {m_LastMouseX = m_MouseX; m_LastMouseY = m_MouseY; m_MouseX = x; m_MouseY = y;}

        inline void SetLastMousePos(int x, int y) {m_LastMouseX = x; m_LastMouseY = y;}
        
        inline int GetLastMouseX() {return m_LastMouseX;}

        inline int GetLastMouseY() {return m_LastMouseY;}

        inline void ToggleCursorLock() {m_CursorLock = !m_CursorLock;}
        
        inline bool IsCursorLock() {return m_CursorLock;}

        void CursorLock(bool enabled);

        bool IsOpen();

        inline void setWidth(int width) {m_Width = width;}
        inline void setHeight(int height) {m_Height = height;}
        inline void setOSScale(float scale) {m_OSScale = scale;}

        inline int GetScaledWidth() const { return m_Width * m_ResolutionScale;}
        inline int GetScaledHeight() const { return m_Height * m_ResolutionScale;}


};