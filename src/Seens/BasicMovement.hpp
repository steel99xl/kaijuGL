#pragma once
#include "../Engine.hpp"



struct Vertex2DPos{
    float X;
    float Y;
    float Z;
};

struct Vertex2DTexCord{
    float X;
    float Y;
};

struct Vertex2D{
                Vertex2DPos Pos;
                Vertex2DTexCord TexCord;
                float TexID;
             };

  
    
class TestWorld{

    private:
        GLuint Tex1, Tex2, Tex3;
        bool m_Effect;
        glm::vec3 m_pos, m_look;
        float m_FOV;

        int m_Width, m_Height;

        float m_QuadPos2[3] = {200.0f,210.0f,200.0f};

        glm::mat4 m_Proj, m_View;

        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        SimpleObject Object;

        Camera2D SimpleCam = Camera2D(glm::vec3(0.0f,0.0f,0.0f) , 1.0f, 200.0f, 200.0f, 100.0f );
        Camera3D AdvancedCam = Camera3D(glm::vec3(0.0, 0.0, 1.0f), glm::vec3(0.0, 0.0, 1.0f), glm::vec3(0.0, 0.0, 1.0f), 1.0f, 75.0f, 10000.0f );

    public:
             
        bool m_running;
        TestWorld();
        ~TestWorld();


        Vertex *CreateQuad(Vertex *target, float X, float Y, float sizeX, float sizeY, float TextureID);

        void Setup();

        void OnUpdate(float deltaTime);
        void Input(int key, int scancode, int action, int mods);
        void OnRender(int Width, int Height, float ScaleFactor);
        void OnImGui();


    };
