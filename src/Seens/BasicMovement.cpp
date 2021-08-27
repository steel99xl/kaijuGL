#include "BasicMovement.hpp"

#include <GLFW/glfw3.h>



TestWorld::TestWorld() : m_running(false), m_Effect(false), m_Width(800), m_Height(680){
// This is just to set some basic vars


}

TestWorld::~TestWorld(){


    //m_TestVAO = std::make_unique<VertexArray>();

}


void TestWorld::Setup(){

    std::cout << "Press the K key to uninvert the camera, Press the L key to invert the camera" << std::endl;
    std::cout << "Press the ESC key to togle cursor lock" << std::endl;
    std::cout << "W A S D Moves the camera" << std::endl;


    m_VAO = std::make_unique<VertexArray>();
    m_Shader = std::make_unique<Shader>();
    m_IBO = std::make_unique<IndexBuffer>();
    m_Texture = std::make_unique<Texture>();
    m_VertexBuffer = std::make_unique<VertexBuffer>();


    //FrameBufferTexture = m_Texture->MakeTexture("NULL", 800,600);
    TestTexture = m_Texture->MakeTexture("assets/Textures/OtherBox.png");

    AdvancedCam.SetHorizontalSensitivity(0.1f);
    AdvancedCam.SetVerticalSensitivity(0.08f);
    AdvancedCam.InvertVertical();

    Object.Setup();
    Land.Setup();
    Sun.Setup();
    SlowMovingBlock.Setup();

    BasicMetalCube.ambient.R = 0.3;
    BasicMetalCube.ambient.G = 0.3;
    BasicMetalCube.ambient.B = 0.3;

    BasicMetalCube.diffuse.R = 0.6f;
    BasicMetalCube.diffuse.G = 0.6f;
    BasicMetalCube.diffuse.B = 0.6f;

    BasicMetalCube.specular.R = 1.0f;
    BasicMetalCube.specular.G = 1.0f;
    BasicMetalCube.specular.B = 1.0f;

    BasicMetalCube.shininess = 32.0f;

    Sun.MakeLight(1.0f,1.0f,1.0f, 0.5f,0.5f,0.5f, 0.9f,0.9f,0.9f, 0.0f,-1.0f,0.0f, 12.5f, 0.014f, 0.07f);




    // This add 1 quad to the land object
    //Land.CreateCube(0.0f,0.0f,0.0f, 45.0f,0.0f,45.0f, 1.0f, 1.0f,1.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
   // Land.Create2dQuad(0.0f,0.0f,0.0f, F_NONE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    //Land.Create2dQuad(0.0f,10.0f,-10.0f, F_NORTH, 20.0f,20.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f);

    Land.Create2dQuad(0.0f,-1.0f,0.0f, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    Land.Create2dQuad(8.0f,1.0f,0.0f, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    Land.Create2dQuad(0.0f,4.0f,0.0f, 90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f,0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Land.Create2dQuad(0.0f,-1.0f,-2.5f, 0.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    Land.Create2dQuad(0.0f,-1.0f,2.5f, 0.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Land.Create2dQuad(-2.5f,-1.0f,0.0f, 0.0f,-90.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);




    Sun.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.10f,0.10f,0.10f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Object.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,2.0f,1.0f, 10.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    SlowMovingBlock.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 500.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);


    // Yes the FaceDir matters based on where you want it to be visible
    //Object.Create2dQuad(0.0f,0.0f,0.5f, F_UP ,1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 1.0f);
    //Object.Create2dQuad(0.0f,0.0f,-0.5f, F_DOWN ,1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 1.0f);

    //Object.Create2dQuad(0.0f,0.0f,0.5f, F_NORTH ,1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 2.0f);
    //Object.Create2dQuad(0.0f,0.0f,-0.5f, F_SOUTH ,1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 2.0f);

    //Object.Create2dQuad(0.0f,0.0f,0.5f, F_EAST ,1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 0.0f);
    //Object.Create2dQuad(0.0f,0.0f,-0.5f, F_WEST ,1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 0.0f);
    // If i want to be able to rotate the squares it the cube face would have to be like this
    //North Face(positive X from origin) Object.Create2dQuad(0.5f, 0.5f, 0.0f, )

    //Object.Create2dQuad(2.0f,2.0f,2.0f, F_NONE, 1.0f,1.0f, 0.0f,0.0f,1.0f,1.0f, 1.0f);


    //Object.Create2dQuad(0.0f,0.0f,-5.0f, F_UP, 3.0f,3.0f, 0.0f,0.0f, 1.0f,1.0f, 2.0f);


   // Object.Create2dQuad(1.0f,3.0f,0.1f, 1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 1.0f);
   // Object.Create2dQuad(1.0f,1.0f,0.1f, 1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 1.0f);

    //Object.Create2dQuad(3.0f,1.0f,0.1f, 1.0f,1.0f, 0.0f,0.0f, 1.0f, 1.0f, 1.0f);



        //Take info and put it in a vertex



    //m_IBO->MakeBuffer(Object.GetIndices().data(), Object.GetIndicCount() );
    //m_IBO->MakeBuffer(NULL, (Object.GetMaxQuadCound() * 4) * 6);
   // std::cout << "Index information " << std::endl;
    //m_IBO->Bind();
    //std::cout << "set index buffer" << std::endl;
    //FBOrec.SetShader("assets/Shaders/FrameBuffer.shader");
    Land.SetShader("assets/Shaders/BlinnPhong.shader");
    Object.SetShader("assets/Shaders/BlinnPhong.shader");
    SlowMovingBlock.SetShader("assets/Shaders/BlinnPhong.shader");
    //TestObject.SetShader("assets/Shaders/MultiImg.shader");

    Sun.SetShader("assets/Shaders/BasicLight.shader");

    //m_Shader->SetShader("assets/Shaders/MultiImg.shader");
    //m_Shader->Bind();

    std::cout << "Shader set" << std::endl;

    //int samplers[3] = {0 ,1,2};
   
    m_FOV = 75.0f;

  //  std::cout << "Total Squares = " << Object.GetVerticiesCount()/4 << std::endl;
   // std::cout << "Total Verticies Drawn = " << (Object.GetVerticiesCount()/4)*6 << std::endl;


}

void TestWorld::StaticUpdate(int MaxUpdateSpeed){
        // camera stuff 
        AdvancedCam.Update(((float)MaxUpdateSpeed)/1000.0f, (float)m_Width/m_Height, m_FOV);
        m_Projection = AdvancedCam.GetProj();
        m_View = AdvancedCam.GetView();
        m_3dCamPos = AdvancedCam.GetCurrentPos();



        Land.SetPosition(0.0f,0.0f,-6.0f);
        SlowMovingBlock.SetPosition(0.0f,0.0f,-3.0f);

        glm::vec3 CubePos = Object.GetPos();
        glm::vec3 LandPos = Land.GetPos();
        //bool Test = Object.AABBColision(CubeVertex, CubeVertexCount, CubePos, LandVertex, LandVertexCount,LandPos);
        // This is just to seperate the old colision system from the new one
        ColisionInfo SimpleColision;
        std::vector<QuadPhysicsBody> PhysBodyA, PhysBodyB;
        std::vector<float> ObjectAWeights, ObjectBWeights;
        ForceDirection ObjectAPos, ObjectBPos;

        ObjectAPos.X = CubePos[0];
        ObjectAPos.Y = CubePos[1];
        ObjectAPos.Z = CubePos[2];

        ObjectBPos.X = LandPos[0];
        ObjectBPos.Y = LandPos[1];
        ObjectBPos.Z = LandPos[2];


        ObjectAWeights = Object.GetWeights();
        ObjectBWeights = Land.GetWeights();


        PhysBodyA = BasicPhysics.MakePhysicsBods(Object.GetVertexPositions(), Object.GetVertexNormlPositions(), ObjectAWeights);
        PhysBodyB = BasicPhysics.MakePhysicsBods(Land.GetVertexPositions(), Land.GetVertexNormlPositions(), ObjectBWeights);

        SimpleColision = BasicPhysics.AABBColision(PhysBodyA, ObjectAPos, PhysBodyB, ObjectBPos);


        if(SimpleColision.IsColision){
            m_3dCamPos = m_3dCamPosPrevious;
        } else {
            m_3dCamPosPrevious = m_3dCamPos;
        }

        Object.SetColision(SimpleColision.IsColision);

        Object.SetPosition(m_3dCamPos.x, m_3dCamPos.y-1.0f, m_3dCamPos.z);

}

void TestWorld::OnUpdate(float deltaTime, float width, float height){
        glfwPollEvents();
        m_DeltaTime = deltaTime;

        m_Width = width;
        m_Height = height;

        

        // This is only going here just so i have a clear spot for it
        //m_View = glm::lookAt(
        //m_pos, // Camera is at (4,3,3), in World Space
        //m_look, // and looks at the origin
        //glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        //);
    }

void TestWorld::KeyInput(int Keys[]){
        float SpeedStep = 4.317f;
        // Keys[] will be replaced with a vector or array of keyinput structs
        // Eventualy the movment will be forcebased

        if(Keys[6] == GLFW_PRESS){
            //SpeedStep = 12.51f *m_DeltaTime;
            SpeedStep = 5.612;
        }

        if(Keys[0] == GLFW_PRESS){
           m_pos2D[2] -= 5 + SpeedStep;
            AdvancedCam.Move(FORWARD, SpeedStep);
        }

        if(Keys[1] == GLFW_PRESS){
           m_pos2D[2] += 5 + SpeedStep;
            AdvancedCam.Move(BACK, SpeedStep);
        }

        if(Keys[2] == GLFW_PRESS){
           m_pos2D[0] -= 5 + SpeedStep;
            AdvancedCam.Move(LEFT, SpeedStep);
        }

        if(Keys[3] == GLFW_PRESS){
           m_pos2D[0] += 5 + SpeedStep;
            AdvancedCam.Move(RIGHT, SpeedStep);
        }

        if(Keys[5] == GLFW_PRESS){
           m_pos2D[1] += 5 + SpeedStep;
            AdvancedCam.Move(UP, SpeedStep);
        }

        if(Keys[4] == GLFW_PRESS){
           m_pos2D[1] -= 5 + SpeedStep;
            AdvancedCam.Move(DOWN, SpeedStep);
        }

        if(Keys[22] == GLFW_PRESS){
            m_FOV -= 1.0f;
                    if(m_FOV <= 20.0f){
                        m_FOV = 20.0f;
                    }
        }

        if(Keys[23] == GLFW_PRESS){
            m_FOV += 1.0f;
                    if(m_FOV >= 120.0f){
                        m_FOV = 120.0f;
                    }
        }

        if(Keys[20] == GLFW_PRESS){
           AdvancedCam.InvertVertical();
        }

        if(Keys[21] == GLFW_PRESS){
           AdvancedCam.UnInvertVertical();
        }


}

void TestWorld::MouseInput(double xpos, double ypos){

    AdvancedCam.LookRelative(xpos,ypos);

}


void TestWorld::OnRender(){
        if(m_Effect){
            // Pre darw stuff if needed

        }

        GLCall(glClearColor(0.60f, 0.60f, 0.75f, 0.0f));



        
        //std::cout << AdvancedCam.GetCurrentLook().x << " | " << AdvancedCam.GetCurrentLook().y << " | " << AdvancedCam.GetCurrentLook().z << std::endl;



        Sun.BindBufferData();
        //Sun.SetColor(1.0f,0.9059f,0.0f, 1.0f);
        Sun.SetLightColor(1.0f, 1.0f, 1.0f);
        Sun.SetColor(1.0f,0.9059f,0.0f, 0.86f);
        Sun.SetPosition(0.0f,3.0f,-6.0f);
        Sun.SetDrawPos(m_Projection, m_View);
        //Sun.SetLight(Sun.GetLightColor(), Sun.GetPos());
        Sun.Paint();



        Land.BindBufferData();
        Land.SetColor(0.3373f, 0.4902f, 0.2745f, 1.0f);
        Land.SetMaterial(BasicMetalCube);
        Land.SetDrawPos(m_Projection, m_View);
        Land.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        Land.Paint();

        SlowMovingBlock.BindBufferData();
        SlowMovingBlock.SetColor(0.471f, 0.318f, 0.176f, 1.0f);
        SlowMovingBlock.SetMaterial(BasicMetalCube);
        SlowMovingBlock.SetDrawPos(m_Projection,m_View);
        SlowMovingBlock.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        SlowMovingBlock.Paint();


        Object.BindBufferData();

        //Using this cube as as temp player for colision detection
        // This is only going to check colision with the single Land Object (IE the ground);
        // The position is only being set first so i can just call the cube object
        Object.SetDrawPos(m_Projection, m_View);
        if(Object.GetColision()){
            Object.SetColor(1.0f,0.0f,0.0f, 1.0f);
        } else {
            Object.SetColor(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
        }


        // FragPos will be used for object push back
        // for now it will be a simple bool


        Object.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        Object.SetMaterial(BasicMetalCube);
        Object.Paint();

        if(m_Effect){
            // Post Draw Stuff if needed

        }


}


void TestWorld::OnImGui(){
    {
    ImGui::Begin("Box Colors");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::DragFloat("FOV", &m_FOV, 1.0f, 10.0f, 150.0f, "%.03f Camera FOV");
    ImGui::ColorEdit4("Color", (float *)&m_Color);
    ImGui::ColorEdit4("Color 2", (float *)&m_Color2);
    ImGui::ColorEdit4("Color 3", (float *)&m_Color3);
    ImGui::End();
    }

}
