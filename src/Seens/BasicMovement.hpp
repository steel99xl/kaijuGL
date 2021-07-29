#pragma once
#include "../Engine.hpp"

  
    
class TestWorld{

    private:
        float m_DeltaTime, m_PastTime;
        GLuint Tex1, Tex2, Tex3;
        bool m_Effect;
        glm::vec3 m_pos2D;
        float m_FOV;

        ImVec4 m_Color;

        //float m_yaw, m_pitch, m_lastX, m_lastY;

        int m_Width, m_Height;


       // VertexArray m_TestVAO;
        
        std::unique_ptr<VertexArray> m_VAO;
        //std::unique_ptr<VertexArray> m_TestVAO;
        std::unique_ptr<IndexBuffer> m_IBO;

    
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;

        SimpleObject Object;

        // Literaly just to show that you can set your own size

        Camera2D SimpleCam = Camera2D(glm::vec3(0.0f,0.0f,0.0f) , 1.0f, 200.0f, 200.0f, 100.0f );
        //SimpleObject Object;// = SimpleObject(1000);
        Camera3D AdvancedCam = Camera3D(glm::vec3(0.0, 0.0, 3.0f), glm::vec3(0.0, 0.0, -1.0f), glm::vec3(0.0, 1.0, 0.0f), 0.1f, 1.0f, 75.0f, 10000.0f );

    public:
             
        bool m_running;
        TestWorld();
        ~TestWorld();


        Vertex *CreateQuad(Vertex *target, float X, float Y, float sizeX, float sizeY, float TextureID);

        void Setup();

        void OnUpdate(float deltaTime);
        void KeyInput(int key, int scancode, int action, int mods);
        void MouseInput(double xpos, double ypos);
        void OnRender(int Width, int Height, float ScaleFactor);
        void OnImGui();


        inline void Test(double xpos, double ypos){std::cout << xpos << " | " << ypos << std::endl;};


    };
