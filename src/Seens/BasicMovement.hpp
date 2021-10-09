#pragma once
#include "../Engine.hpp"

  
    
class TestWorld{

    private:
        float m_DeltaTime, m_PastTime, m_PhysicsDeltaTime, m_PhysicsPastTime;
        GLuint Tex1, Tex2, Tex3;
        bool m_Effect;
        glm::vec3 m_pos2D;
        float m_FOV;

        glm::vec3 m_3dCamPos, m_3dCamPosPrevious;

        glm::mat4 m_Projection, m_View;

        //ImVec4 m_Color, m_Color2, m_Color3;
        glm::vec4 m_Color = glm::vec4(0.0f,0.0f,1.0f,1.0f);

        //float m_yaw, m_pitch, m_lastX, m_lastY;
        // These are stored as floats so the rounding can be ajusted
        float m_Width, m_Height, m_Scale;

        FrameBufferObject m_FBO;
        SimpleObject Frame =  SimpleObject(2);

        unsigned int ShadowMapFBO, ShadowMapRBO,ShadowMapTexture;
        unsigned int ShadowWidth = 2048;
        unsigned int ShadowHeight = 2048;



        SimpleObject PlayerBlock = SimpleObject(18, DynamicBuffer);
        SimpleObject TealBlock = SimpleObject(18, DynamicBuffer);
        // Lol Voxl Land Test set back to about 5k when done
        SimpleObject Land = SimpleObject(15000, DynamicBuffer);
        SimpleObject OtherSuns = SimpleObject(32, DynamicBuffer);
        SimpleObject Sun = SimpleObject(6, DynamicBuffer);

        std::vector<ForceDirection> m_NewPlayerDirection;
        float PlayerMovmentSpeed;

        SimpleMaterialInfo BasicMetalCube;

        SimplePhysics BasicPhysics = SimplePhysics(2.0f ,0.0f,-1.0f,0.0f);

        Camera2D SimpleCam = Camera2D(glm::vec3(0.0f,0.0f,0.0f) , 1.0f, 200.0f, 200.0f, 100.0f );
        //SimpleObject Object;// = SimpleObject(1000);
        Camera3D AdvancedCam = Camera3D(glm::vec3(0.0, 0.0, 0.0f), glm::vec3(1.0, 0.0, 1.0f), glm::vec3(0.0, 1.0, 0.0f), 0.1f, 1.0f, 75.0f, 10000.0f );

    public:

        bool m_running;
        TestWorld();
        ~TestWorld();


        Vertex *CreateQuad(Vertex *target, float X, float Y, float sizeX, float sizeY, float TextureID);


        void Setup();

        void PhysicsUpdate(float MaxUpdateSpeed);

        void OnUpdate(float deltaTime, float width, float hight, float scale);
        void KeyInput(int Keys[]);
        void MouseInput(double xpos, double ypos);
        // Yes this needs to be called every frame if you have moving objects;
        void GenShadows();
        void OnRender();
        void OnGui();


        inline void Test(double xpos, double ypos){std::cout << xpos << " | " << ypos << std::endl;};


    };
