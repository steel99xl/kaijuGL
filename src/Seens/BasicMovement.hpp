#pragma once
#include "../kaijuGL.hpp"

    
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
        SimpleObject Frame;

        double m_MouseX = 0.0, m_MouseY = 0.0;

        // This is currently hnit being used
        unsigned int ShadowMapFBO, ShadowMapRBO,ShadowMapTexture;
        unsigned int ShadowWidth = 2048;
        unsigned int ShadowHeight = 2048;
        //


        SimpleObject PlayerBlock;
        SimpleObject TealBlock;
        // Lol Voxl Land Test set back to about 5k when done
        SimpleObject Land;
        SimpleObject Platform;
        SimpleObject OtherSuns;
        SimpleObject Sun;




        //Elements for Physics Engine
        std::vector<SimplePhysics::ForceDirection> m_NewPlayerDirection;
        std::vector<SimplePhysics::ColisionInfo> m_ObjectColissions;
        std::vector<SimplePhysics::QuadPhysicsBody> PlayerPhysics, LandPhysics, TealBlockPhysics;

        // The TealBlock on the new physics Engine
        SimplePhysicsSphereObject TBPhysics;
        SimplePhysicsSphereObject PlayerPObject;
        // This is the Platform only being represented as the new objet
        SimplePhysicsBoxObject PlatformPhysics;

        // Temp PlaceHolder for Object Posisons;
        std::vector<SimplePhysics::PhysicsPos> m_ObjectWorldPositions;



        float PlayerMovmentSpeed;

        SimpleMaterialInfo BasicMetalCube;

        SimplePhysics::PhysicsEngine BasicPhysics = SimplePhysics::PhysicsEngine(2.0f ,0.0f,-1.0f,0.0f);

        Camera2D SimpleCam;
        //SimpleObject Object;// = SimpleObject(1000);
        Camera3D AdvancedCam;

    public:

        bool m_running;
        TestWorld();
        ~TestWorld();


        Vertex *CreateQuad(Vertex *target, float X, float Y, float sizeX, float sizeY, float TextureID);


        void Setup();

        void PhysicsUpdate(float MaxUpdateSpeed);

        void OnUpdate(float deltaTime, float width, float hight, float scale = 1.0f);
        void KeyInput(std::array<int, 512> Keys);
        void MouseButton(std::array<int, 32> MouseButtons);
        void MouseInput(double xpos, double ypos);
        // Yes this needs to be called every frame if you have moving objects;
        void GenShadows();
        void OnRender();
        void PaintFrame();
        void OnGui();

        inline void Start() { m_running = true; };
        inline bool IsWorldRunning() { return m_running; };
        inline void Stop() { m_running = false; };
        inline void Test(double xpos, double ypos){std::cout << xpos << " | " << ypos << std::endl;};


    };
