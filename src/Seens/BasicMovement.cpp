#include "BasicMovement.hpp"

#include <GLFW/glfw3.h>



TestWorld::TestWorld() :  m_Effect(false), m_Width(800), m_Height(680),  m_running(false){
// This is just to set some basic vars


}

TestWorld::~TestWorld(){


    //m_TestVAO = std::make_unique<VertexArray>();

}


void TestWorld::Setup(){

    std::cout << "Press the K key to uninvert the camera, Press the L key to invert the camera" << std::endl;
    std::cout << "Press the ESC key to togle cursor lock" << std::endl;
    std::cout << "W A S D Moves the camera" << std::endl;



    //m_VAO = std::make_unique<VertexArray>();
    //m_Shader = std::make_unique<Shader>();
    //m_IBO = std::make_unique<IndexBuffer>();
    //m_Texture = std::make_unique<Texture>();
    //m_VertexBuffer = std::make_unique<VertexBuffer>();


    //FrameBufferTexture = m_Texture->MakeTexture("NULL", 800,600);
    //TestTexture = m_Texture->MakeTexture("assets/Textures/OtherBox.png");

    AdvancedCam.SetHorizontalSensitivity(0.1f);
    AdvancedCam.SetVerticalSensitivity(0.08f);
    AdvancedCam.InvertVertical();

    PlayerBlock.Setup();
    Land.Setup();
    Sun.Setup();
    TealBlock.Setup();

    BasicMetalCube.ambient.R = 0.3;
    BasicMetalCube.ambient.G = 0.3;
    BasicMetalCube.ambient.B = 0.3;

    BasicMetalCube.diffuse.R = 0.6f;
    BasicMetalCube.diffuse.G = 0.6f;
    BasicMetalCube.diffuse.B = 0.6f;

    BasicMetalCube.specular.R = 0.1f;
    BasicMetalCube.specular.G = 0.1f;
    BasicMetalCube.specular.B = 0.1f;

    BasicMetalCube.shininess = 32.0f;

    Sun.MakeLight(1.0f,1.0f,1.0f, 0.5f,0.5f,0.5f, 0.9f,0.9f,0.9f, 0.0f,0.0f,0.0f, 12.5f, 0.045f, 0.0075f);




    // This add 1 quad to the land object
    //Land.CreateCube(0.0f,0.0f,0.0f, 45.0f,0.0f,45.0f, 1.0f, 1.0f,1.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
   // Land.Create2dQuad(0.0f,0.0f,0.0f, F_NONE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    //Land.Create2dQuad(0.0f,10.0f,-10.0f, F_NORTH, 20.0f,20.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f);
    Land.Create2dQuad(0.0f,-3.0f,0.0f, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    for(int i = 1; i < 21; i++){
        for(int j = 1; j < 21; j++){
            //Land.Create2dQuad((float)i*5,(((float)((i+j)%6) * 0.01) + -5.0f),(float)j*5, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
            Land.Create2dQuad((float)i*5,-5.0f,(float)j*5, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
        }
    }


    //Land.Create2dQuad(8.0f,-2.5f,8.0f, -60.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    Land.Create2dQuad(15.0f,-4.5f,10.0f, -80.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Land.CreateCube(10,-3, 10, 0.0f,0.0f,0.0f, 2.0f,2.0f,2.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    Land.CreateCube(10,-1, 18, 0.0f,0.0f,0.0f, 4.0f,4.0f,4.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    Sun.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.10f,0.10f,0.10f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    PlayerBlock.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.9f,0.6f,0.9f, 10.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    //PlayerBlock.CreateCube(1.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.9f,2.0f,0.9f, 10.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    TealBlock.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 500.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    TealBlock.CreateCube(1.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 500.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    TealBlock.CreateCube(0.0f,0.0f,1.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 500.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);


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
    Land.SetShader("assets/Shaders/BasicLighting.shader");
    PlayerBlock.SetShader("assets/Shaders/BasicLighting.shader");
    TealBlock.SetShader("assets/Shaders/BasicLighting.shader");
    //TestObject.SetShader("assets/Shaders/MultiImg.shader");

    Sun.SetShader("assets/Shaders/BasicLightObject.shader");

    //m_Shader->SetShader("assets/Shaders/MultiImg.shader");
    //m_Shader->Bind();

    std::cout << "Shader set" << std::endl;

    //int samplers[3] = {0 ,1,2};

    m_FOV = 75.0f;

    TealBlock.SetPosition(8.0f,10.0f,8.0f);
    Land.SetPosition(0.0f,0.0f,0.0f);
  //  std::cout << "Total Squares = " << Object.GetVerticiesCount()/4 << std::endl;
   // std::cout << "Total Verticies Drawn = " << (Object.GetVerticiesCount()/4)*6 << std::endl;

   // Stuff that is only set once for an object
    Sun.SetLightColor(1.0f, 1.0f, 1.0f);
    Sun.SetColor(1.0f,0.9059f,0.0f, 0.86f);
    Sun.SetPosition(15.0f,0.0f,10.0f);


    Land.SetColor(0.3373f, 0.4902f, 0.2745f, 1.0f);
    Land.SetMaterial(BasicMetalCube);


    TealBlock.SetColor(0.5f, 0.75f, 0.75f, 1.0f);
}

void TestWorld::PhysicsUpdate(int MaxUpdateSpeed){
        //glfwPostEmptyEvent();
        // camera stuff 
        BasicPhysics.SetUpdateTime(MaxUpdateSpeed);
        AdvancedCam.Update(((float)MaxUpdateSpeed)/1000.0f, (float)m_Width/m_Height, m_FOV);
        m_Projection = AdvancedCam.GetProj();
        m_View = AdvancedCam.GetView();
        m_3dCamPos = AdvancedCam.GetCurrentPos();


        //bool Test = Object.AABBColision(CubeVertex, CubeVertexCount, CubePos, LandVertex, LandVertexCount,LandPos);
        // This is just to seperate the old colision system from the new one
        ColisionInfo PlayerTOObject, TealBlockColision;
        PlayerTOObject.IsColision = false;

        std::vector<QuadPhysicsBody> Player, PhysicsLand, PhysicsTealBlock;
        PhysicsPoint PlayerPos, TealBlockFuturePos;
        ForceDirection LeftFromOrigion;

        LeftFromOrigion.X = -1.0f;
        LeftFromOrigion.Y = 0.0f;
        LeftFromOrigion.Z = 0.0f;

        Player = BasicPhysics.MakePhysicsBods(PlayerBlock.GetVertexPositions(), PlayerBlock.GetVertexNormlPositions(), PlayerBlock.GetWeights());
        PhysicsLand = BasicPhysics.MakePhysicsBods(Land.GetVertexPositions(), Land.GetVertexNormlPositions(), Land.GetWeights());
        PhysicsTealBlock = BasicPhysics.MakePhysicsBods(TealBlock.GetVertexPositions(), TealBlock.GetVertexNormlPositions(), TealBlock.GetWeights());

        //BasicPhysics.QuadsToLinesVoid(Player, &TempPlayerLines);
        //BasicPhysics.QuadsToLinesVoid(PhysicsLand, &TempLandLines);

        //PlayerTOObject = BasicPhysics.AABBColision(Player, PlayerPos, PhysicsLand, Land.GetPhysicsPos());
        
        //PreviousePlayerPos = Object.GetPhysicsPos();

        //TealBlockFuturePos = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), LeftFromOrigion, 0.5f);

        //std::cout << m_NewPlayerDirection.X << " | " << m_NewPlayerDirection.Y << " | " << m_NewPlayerDirection.Z << std::endl;

        // Gravity acting befor player input
        //PlayerPos = BasicPhysics.MovePhysicsObject(PlayerBlock.GetPhysicsPos(), BasicPhysics.GetGravity().Direction, BasicPhysics.GetGravity().Power);
        //PlayerTOObject = BasicPhysics.AABBColision(Player, PlayerPos, PhysicsLand, Land.GetPhysicsPos());
        //if(PlayerTOObject.IsColision){
        //    PlayerPos = BasicPhysics.MovePhysicsObject(PlayerPos, PlayerTOObject.MovmentDirectionB, BasicPhysics.GetGravity().Power);
        //}
        //PlayerBlock.SetPosition(PlayerPos.X, PlayerPos.Y, PlayerPos.Z);
        //AdvancedCam.SetPos(PlayerPos.X, PlayerPos.Y+0.9f, PlayerPos.Z);



        TealBlockFuturePos = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), BasicPhysics.GetGravity().Direction, BasicPhysics.GetGravity().Power);

        TealBlockColision = BasicPhysics.AABBColision(PhysicsTealBlock, TealBlockFuturePos, PhysicsLand, Land.GetPhysicsPos());
        if(!TealBlockColision.IsColision){
            TealBlockColision = BasicPhysics.PointsToAABBColision(PhysicsTealBlock, TealBlockFuturePos, BasicPhysics.MinMaxFromQuads(PhysicsLand, Land.GetPhysicsPos()));
        }
        if(!TealBlockColision.IsColision){
            TealBlockColision = BasicPhysics.PointsToAABBColision(PhysicsLand, Land.GetPhysicsPos(), BasicPhysics.MinMaxFromQuads(PhysicsTealBlock, TealBlockFuturePos));
        }
        //TealBlockColision = BasicPhysics.SATColision(PhysicsTealBlock, TealBlockFuturePos, PhysicsLand, Land.GetPhysicsPos());
        //TealBlockColision = BasicPhysics.FullQuadLineColision(BasicPhysics.QuadsToLines(PhysicsTealBlock), TealBlock.GetPhysicsPos(), BasicPhysics.QuadsToLines(PhysicsLand), Land.GetPhysicsPos(), 1.01);

        
        //TealBlockColision = BasicPhysics.QuadBodyColision(PhysicsTealBlock, TealBlockFuturePos, PhysicsLand, Land.GetPhysicsPos());
        //TealBlockColision = BasicPhysics.QuadBodyColision(PhysicsLand, Land.GetPhysicsPos(), PhysicsTealBlock, TealBlockFuturePos);
        if(TealBlockColision.IsColision){
            TealBlockFuturePos = BasicPhysics.MovePhysicsObject(TealBlockFuturePos, TealBlockColision.MovmentDirectionB, BasicPhysics.GetGravity().Power);
        }
        TealBlock.SetPosition(TealBlockFuturePos.X, TealBlockFuturePos.Y, TealBlockFuturePos.Z);



        // Move Player based on player input
        PlayerPos = BasicPhysics.MovePhysicsObject(PlayerBlock.GetPhysicsPos(), BasicPhysics.NormalizeVectorOfForceDirection(m_NewPlayerDirection), PlayerMovmentSpeed);

        //PlayerTOObject = BasicPhysics.AABBColision(Player, PlayerPos, PhysicsLand, Land.GetPhysicsPos());
        //PlayerTOObject = BasicPhysics.SATColision(Player, PlayerPos, PhysicsLand, Land.GetPhysicsPos());
        //if(PlayerTOObject.IsColision){
            //PlayerPos = BasicPhysics.MovePhysicsObject(PlayerPos, PlayerTOObject.MovmentDirectionB, PlayerMovmentSpeed);
        //    std::cout << PlayerTOObject.MovmentDirectionB.X << " | " << PlayerTOObject.MovmentDirectionB.Y << " | " << PlayerTOObject.MovmentDirectionB.Z << std::endl;
        //}
        PlayerBlock.SetPosition(PlayerPos.X, PlayerPos.Y, PlayerPos.Z);
        AdvancedCam.SetPos(PlayerPos.X, PlayerPos.Y+0.9f, PlayerPos.Z);

        //BasicPhysics.FullQuadLineColisionVoid(TempPlayerLines, PlayerPos, TempLandLines, Land.GetPhysicsPos(), 1.02f, &PlayerTOObject);

        //TealBlockColision = BasicPhysics.AABBColision(PhysicsTealBlock, TealBlockFuturePos, Player, PlayerPos);
        //TealBlockColision = BasicPhysics.FullQuadLineColision(BasicPhysics.QuadsToLines(PhysicsTealBlock), TealBlock.GetPhysicsPos(), BasicPhysics.QuadsToLines(Player), PlayerPos, 1.01f);
        //TealBlockColision = BasicPhysics.SATColision(PhysicsTealBlock, TealBlockFuturePos, Player, PlayerPos);
        TealBlockColision = BasicPhysics.QuadBodyColision(PhysicsTealBlock, TealBlockFuturePos, Player, PlayerPos, 0.3f);
        //TealBlockColision = BasicPhysics.QuadBodyColision(Player, PlayerPos, PhysicsTealBlock, TealBlockFuturePos, 0.3f);
        //if(!TealBlockColision.IsColision){
        //    TealBlockColision = BasicPhysics.QuadBodyColision(Player, PlayerPos, PhysicsTealBlock, TealBlockFuturePos, 0.9f);
        //}

        if(TealBlockColision.IsColision){
            ForceDirection NewTealBlockDirecton =  TealBlockColision.MovmentDirectionA;
            //ForceDirection NewTealBlockDirecton = BasicPhysics.MakeForceDirection(PlayerPos, TealBlockFuturePos);
            NewTealBlockDirecton.Y = 0.1f;
            TealBlockFuturePos = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), NewTealBlockDirecton , PlayerMovmentSpeed);
            //TealBlock.SetPosition(TealBlockFuturePos.X, TealBlockFuturePos.Y, TealBlockFuturePos.Z);
        }
        TealBlock.SetPosition(TealBlockFuturePos.X, TealBlockFuturePos.Y, TealBlockFuturePos.Z);

        
        PlayerBlock.SetColision(PlayerTOObject.IsColision);

        //Object.SetPosition(m_3dCamPos.x, m_3dCamPos.y-1.0f, m_3dCamPos.z);

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
        m_NewPlayerDirection.clear();    
        PlayerMovmentSpeed = 4.317f;
        // Keys[] will be replaced with a vector or array of keyinput structs
        // Eventualy the movment will be forcebased

        if(Keys[6] == GLFW_PRESS){
            //SpeedStep = 12.51f *m_DeltaTime;
            PlayerMovmentSpeed = 6.612;
        }

        if(Keys[0] == GLFW_PRESS){
            m_pos2D[2] -= 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(FORWARD, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(FORWARD));
        }

        if(Keys[1] == GLFW_PRESS){
            m_pos2D[2] += 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(BACK, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(BACK));
        }

        if(Keys[2] == GLFW_PRESS){
            m_pos2D[0] -= 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(LEFT, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(LEFT));
        }

        if(Keys[3] == GLFW_PRESS){
            m_pos2D[0] += 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(RIGHT, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(RIGHT));
        }

        if(Keys[5] == GLFW_PRESS){
            m_pos2D[1] += 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(UP, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(UP));
        }

        if(Keys[4] == GLFW_PRESS){
            m_pos2D[1] -= 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(DOWN, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(DOWN));
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


        Sun.BindBufferData();
        //Sun.SetColor(1.0f,0.9059f,0.0f, 1.0f);
        
        Sun.SetDrawPos(m_Projection, m_View);
        //Sun.SetLight(Sun.GetLightColor(), Sun.GetPos());
        Sun.Paint();



        Land.BindBufferData();
        
        Land.SetDrawPos(m_Projection, m_View);
        Land.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        Land.Paint();

        TealBlock.BindBufferData();
        //TealBlock.SetColor(0.471f, 0.318f, 0.176f, 1.0f);
        
        TealBlock.SetMaterial(BasicMetalCube);
        TealBlock.SetDrawPos(m_Projection,m_View);
        TealBlock.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        TealBlock.Paint();


        PlayerBlock.BindBufferData();
        //Using this cube as as temp player for colision detection
        // This is only going to check colision with the single Land Object (IE the ground);
        // The position is only being set first so i can just call the cube object
        PlayerBlock.SetDrawPos(m_Projection, m_View);
        if(PlayerBlock.GetColision()){
            PlayerBlock.SetColor(1.0f,0.0f,0.0f, 1.0f);
        } else {
            PlayerBlock.SetColor(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
        }


        // FragPos will be used for object push back
        // for now it will be a simple bool


        PlayerBlock.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        PlayerBlock.SetMaterial(BasicMetalCube);
        PlayerBlock.Paint();

        if(m_Effect){
            // Post Draw Stuff if needed

        }


}

// This will be replaces with an internal GUI system;
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
