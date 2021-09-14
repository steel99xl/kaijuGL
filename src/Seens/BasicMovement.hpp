#pragma once
#include "../Engine.hpp"

  
    
class TestWorld{

    private:
        float m_DeltaTime, m_PastTime;
        GLuint Tex1, Tex2, Tex3;
        bool m_Effect;
        glm::vec3 m_pos2D;
        float m_FOV;

        glm::vec3 m_3dCamPos, m_3dCamPosPrevious;

        // TODO : implement frame buffer object
        //Frame Buffer Info
        unsigned int m_FBO;
        unsigned int FrameBufferTexture;
        unsigned int TestTexture;

        unsigned int m_RBO;

        glm::mat4 m_Projection, m_View;

        ImVec4 m_Color, m_Color2, m_Color3;

        //float m_yaw, m_pitch, m_lastX, m_lastY;

        int m_Width, m_Height;


       // VertexArray m_TestVAO;
        
        //std::unique_ptr<VertexArray> m_VAO;
        //std::unique_ptr<VertexArray> m_TestVAO;
        //std::unique_ptr<IndexBuffer> m_IBO;

    
        //std::unique_ptr<Texture> m_Texture;
        //std::unique_ptr<Shader> m_Shader;
        //std::unique_ptr<VertexBuffer> m_VertexBuffer;

        SimpleObject PlayerBlock = SimpleObject(6, DynamicBuffer);
        SimpleObject TealBlock = SimpleObject(6, DynamicBuffer);
        SimpleObject Land; //SimpleObject(6 StaticBuffer);
        SimpleObject Sun = SimpleObject(6, DynamicBuffer);

        std::vector<ForceDirection> m_NewPlayerDirection;
        float PlayerMovmentSpeed;

        SimpleMaterialInfo BasicMetalCube;

        SimplePhysics BasicPhysics = SimplePhysics(2.0f ,0.0f,-1.0f,0.0f);

        // Literaly just to show that you can set your own size

        Camera2D SimpleCam = Camera2D(glm::vec3(0.0f,0.0f,0.0f) , 1.0f, 200.0f, 200.0f, 100.0f );
        //SimpleObject Object;// = SimpleObject(1000);
        Camera3D AdvancedCam = Camera3D(glm::vec3(0.0, 0.0, 2.0f), glm::vec3(0.0, 0.0, -1.0f), glm::vec3(0.0, 1.0, 0.0f), 0.1f, 1.0f, 75.0f, 10000.0f );

    public:

        bool m_running;
        TestWorld();
        ~TestWorld();


        Vertex *CreateQuad(Vertex *target, float X, float Y, float sizeX, float sizeY, float TextureID);


        void Setup();

        void PhysicsUpdate(int MaxUpdateSpeed);

        void OnUpdate(float deltaTime, float width, float hight);
        void KeyInput(int Keys[]);
        void MouseInput(double xpos, double ypos);
        void OnRender();
        void OnImGui();


        inline void Test(double xpos, double ypos){std::cout << xpos << " | " << ypos << std::endl;};


    };
