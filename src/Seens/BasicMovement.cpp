#include "BasicMovement.hpp"

#include <GLFW/glfw3.h>



TestWorld::TestWorld() :  m_Effect(false), m_Width(800.0f), m_Height(680.0f), m_Scale(1.0f),  m_running(false){
// This is just to set some basic vars


}

TestWorld::~TestWorld(){


    //m_TestVAO = std::make_unique<VertexArray>();

}


void TestWorld::Setup(){

    std::cout << "Press the K key to uninvert the camera, Press the L key to invert the camera" << std::endl;
    std::cout << "Press the ESC key to togle cursor lock" << std::endl;
    std::cout << "W A S D Moves the camera" << std::endl;


    AdvancedCam.SetHorizontalSensitivity(0.1f);
    AdvancedCam.SetVerticalSensitivity(0.08f);
    AdvancedCam.InvertVertical();

    m_FBO.Setup((int)m_Width, (int)m_Height,(int)m_Scale);
    Frame.Setup();
    Frame.SetShader("assets/Shaders/FrameKernel.shader");
    Frame.Create2dQuad(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 2.0f,2.0f, 1.0f, 0.0f,0.0f,1.0f,1.0f, 5.0f);
    Frame.SetTexture(0, "u_Texture");
    Frame.SetFloatUniform("u_Size.height", m_Height);
    Frame.SetFloatUniform("u_Size.width", m_Width);

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

    Sun.MakeLight(0.9f,0.9f,0.9f, 0.7f,0.7f,0.7f, 0.9f,0.9f,0.9f, 0.0f,0.0f,0.0f, 12.5f, 0.027f, 0.0028f);




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

    m_FOV = 75.0f;


    Land.SetShadowShader("assets/Shaders/SimpleDepth.shader");
    PlayerBlock.SetShadowShader("assets/Shaders/SimpleDepth.shader");
    TealBlock.SetShadowShader("assets/Shaders/SimpleDepth.shader");

    //Land.SetShadowShader("assets/Shaders/BasicLighting.shader");
    //PlayerBlock.SetShadowShader("assets/Shaders/BasicLighting.shader");
    //TealBlock.SetShadowShader("assets/Shaders/BasicLighting.shader");


    Land.SetShader("assets/Shaders/BasicLighting.shader");
    PlayerBlock.SetShader("assets/Shaders/BasicLighting.shader");
    TealBlock.SetShader("assets/Shaders/BasicLighting.shader");
    // The light does not get a shadow shader
    Sun.SetShader("assets/Shaders/BasicLightObject.shader");


    
    glGenFramebuffers(1, &ShadowMapFBO);

    glGenTextures(1, &ShadowMapTexture);
    glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ShadowRes, ShadowRes, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMapTexture, 0);

    //glGenRenderbuffers(1, &ShadowMapRBO);
    //glBindRenderbuffer(GL_RENDERBUFFER, ShadowMapRBO);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ShadowRes, ShadowRes);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ShadowMapRBO);


    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  






    TealBlock.SetPosition(8.0f,10.0f,8.0f);
    Land.SetPosition(0.0f,0.0f,0.0f);

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
        //ForceDirection LeftFromOrigion;

        //LeftFromOrigion.X = -1.0f;
        //LeftFromOrigion.Y = 0.0f;
        //LeftFromOrigion.Z = 0.0f;

        Player = BasicPhysics.MakePhysicsBods(PlayerBlock.GetVertexPositions(), PlayerBlock.GetVertexNormlPositions(), PlayerBlock.GetWeights());
        PhysicsLand = BasicPhysics.MakePhysicsBods(Land.GetVertexPositions(), Land.GetVertexNormlPositions(), Land.GetWeights());
        PhysicsTealBlock = BasicPhysics.MakePhysicsBods(TealBlock.GetVertexPositions(), TealBlock.GetVertexNormlPositions(), TealBlock.GetWeights());




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
            ForceDirection NewTealBlockDirecton =  TealBlockColision.MovmentDirectionB;
            //ForceDirection NewTealBlockDirecton = BasicPhysics.MakeForceDirection(PlayerPos, TealBlockFuturePos);
            NewTealBlockDirecton.Y = 0.1f;
            TealBlockFuturePos = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), NewTealBlockDirecton , PlayerMovmentSpeed);
            //TealBlock.SetPosition(TealBlockFuturePos.X, TealBlockFuturePos.Y, TealBlockFuturePos.Z);
        }
        TealBlock.SetPosition(TealBlockFuturePos.X, TealBlockFuturePos.Y, TealBlockFuturePos.Z);

        // Just sets a bool for now 
        PlayerBlock.SetColision(PlayerTOObject.IsColision);

}

void TestWorld::OnUpdate(float deltaTime, float width, float height, float scale){
        glfwPollEvents();
        m_DeltaTime = deltaTime;

        m_Width = width;
        m_Height = height;
        m_Scale = scale;

        

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


void TestWorld::GenShadows(){
    //glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    //glClear(GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ShadowRes, ShadowRes, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMapTexture, 0);

    //glBindRenderbuffer(GL_RENDERBUFFER, ShadowMapRBO);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ShadowRes, ShadowRes);

    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glEnable(GL_DEPTH_TEST));

    float near_plane = 1.0f, far_plane = 75.0f;
    glm::mat4 lightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt(Sun.GetPos(), glm::vec3( 0.0f, 0.0f,  0.0f), glm::vec3( 0.0f, 1.0f,  0.0f)); 

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    
    //PlayerBlock.SetShadowPos(lightProjection, lightView);
    //Land.SetShadowPos(lightProjection, lightView);
    //TealBlock.SetShadowPos(lightProjection, lightView);

    PlayerBlock.SetShadowPos(lightSpaceMatrix);
    Land.SetShadowPos(lightSpaceMatrix);
    TealBlock.SetShadowPos(lightSpaceMatrix);


    Land.PaintShadow();
    PlayerBlock.PaintShadow();
    TealBlock.PaintShadow();

    /*
    glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, FrameBuffTexture);
    glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GLCall(glDisable(GL_DEPTH_TEST)); 
    Frame.BindBufferData();

    Frame.Paint();

    */

}

void TestWorld::OnRender(){
        if(m_Effect){
            // Pre darw stuff if needed

        }
        m_FBO.Update((int)m_Width,(int)m_Height,(int)m_Scale);

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

        glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, FrameBuffTexture);
        glBindTexture(GL_TEXTURE_2D, m_FBO.GetTexture());
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLCall(glDisable(GL_DEPTH_TEST)); 
        Frame.BindBufferData();

        Frame.Paint();


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
