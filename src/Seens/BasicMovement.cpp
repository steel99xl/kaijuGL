#include "BasicMovement.hpp"



TestWorld::TestWorld() :  m_Effect(false), m_Width(800.0f), m_Height(680.0f), m_Scale(1.0f),  m_running(false){
// This is just to set some basic vars
    

}

TestWorld::~TestWorld(){



}


void TestWorld::Setup(){

    std::cout << "Press the K key to uninvert the camera, Press the L key to invert the camera" << std::endl;
    std::cout << "Press the ESC key to togle cursor lock" << std::endl;
    std::cout << "W A S D Moves the camera" << std::endl;

    AdvancedCam.Setup(glm::vec3(0.0, 0.0, 0.0f), glm::vec3(1.0, 0.0, 1.0f), glm::vec3(0.0, 1.0, 0.0f), 0.1f, 1.0f, 75.0f, 10000.0f );

    AdvancedCam.SetHorizontalSensitivity(0.1f);
    AdvancedCam.SetVerticalSensitivity(0.08f);
    AdvancedCam.InvertVertical();


    m_FBO.Setup((int)m_Width, (int)m_Height,(int)m_Scale);
    Frame.Setup(2);
    Frame.SetShader("assets/Shaders/FrameVertex.shader");
    Frame.SetShader("assets/Shaders/FrameBuffer.shader");
    Frame.FinishShader();
    Frame.Create2dQuad(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 2.0f,2.0f, 1.0f, 0.0f,0.0f,1.0f,1.0f, 5.0f);
    Frame.SetTexture(0, "u_Texture");
    Frame.SetFloatUniform("u_Size.height", m_Height);
    Frame.SetFloatUniform("u_Size.width", m_Width);

    PlayerBlock.Setup(18, SimpleObject::DynamicBuffer);
    Land.Setup(15000, SimpleObject::StaticBuffer);
    OtherSuns.Setup(6, SimpleObject::DynamicBuffer);
    Sun.Setup(6, SimpleObject::StaticBuffer);
    TealBlock.Setup(6, SimpleObject::DynamicBuffer);

    ColisionInfo TempColison;
    for(int i = 0; i < 5; i++){
        m_ObjectColissions.push_back(TempColison);
    }
    PlayerBlock.ColisionID = 0;
    Land.ColisionID = 1;
    OtherSuns.ColisionID = 2;
    Sun.ColisionID = 3;
    TealBlock.ColisionID = 4;

    BasicMetalCube.ambient.R = 0.3;
    BasicMetalCube.ambient.G = 0.3;
    BasicMetalCube.ambient.B = 0.3;

    BasicMetalCube.diffuse.R = 0.7f;
    BasicMetalCube.diffuse.G = 0.7f;
    BasicMetalCube.diffuse.B = 0.7f;

    BasicMetalCube.specular.R = 1.0f;
    BasicMetalCube.specular.G = 1.0f;
    BasicMetalCube.specular.B = 1.0f;

    BasicMetalCube.shininess = 32.0f;

    Sun.MakeLight(0.2f,0.2f,0.2f, 0.7f,0.7f,0.7f, 1.0f,1.0f,1.0f, 0.0f,0.0f,0.0f, 12.5f, 0.027f, 0.0028f);

    OtherSuns.MakeLight(0.2f,0.2f,0.2f, 0.7f,0.7f,0.7f, 1.0f,1.0f,1.0f, 0.0f,0.0f,0.0f, 12.5f, 0.027f, 0.0028f);




    //Land.Create2dQuad(0.0f,-3.0f,0.0f, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    
    for(int i = 1; i < 41; i++){
        for(int j = 1; j < 41; j++){
            //for(int n = 1; n < 51; n++){
            //    Land.CreateCube((float)i*3,(float)j*3, (float)n*3, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);
           //}
            float TempY = (i+j)%6 /10.0f + -5.0f;
            Land.CreateCube((float)i*3, TempY, (float)j*3, 0.0f,0.0f,0.0f, 3.0f,1.0f,3.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);
            //Land.Create2dQuad((float)i*5,(((float)((i+j)%6) * 0.01) + -5.0f),(float)j*5, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
            //Land.Create2dQuad((float)i*5,-5.0f,(float)j*5, -90.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
            //Land.CreateCube((float)i*5,-5, (float)j*5, 0.0f,0.0f,0.0f, 5.0f,1.0f,5.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);
        }
    }


    //Land.Create2dQuad(8.0f,-2.5f,8.0f, -60.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    //Land.Create2dQuad(15.0f,-4.5f,10.0f, -80.0f,0.0f,0.0f, 5.0f,5.0f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    //Land.CreateCube(10,-3, 10, 0.0f,0.0f,0.0f, 2.0f,2.0f,2.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    //Land.CreateCube(10,-1, 18, 0.0f,0.0f,0.0f, 4.0f,4.0f,4.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    Sun.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.10f,0.10f,0.10f, 10.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    OtherSuns.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 2.0f,2.0f,2.0f, 10, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    PlayerBlock.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.9f,0.6f,0.9f, 10.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);
    //PlayerBlock.CreateCube(1.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.9f,2.0f,0.9f, 10.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    TealBlock.CreateCube(0.0f,0.0f,0.0f, 0.0f,45.0f,0.0f, 1.0f,1.0f,1.0f, 500.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);

    m_FOV = 75.0f;


    Land.SetShadowShader("assets/Shaders/ShadowVertex.shader");
    Land.SetShadowShader("assets/Shaders/ShadowFragment.shader");
    Land.FinishShadowShader();

    PlayerBlock.ImportShadowShaders(Land.ExportShadowShaders());
    PlayerBlock.FinishShadowShader();

    TealBlock.ImportShadowShaders(Land.ExportShadowShaders());
    TealBlock.FinishShadowShader();
    
    Land.ClearShadowShaderCache();
    PlayerBlock.ClearShadowShaderCache();
    TealBlock.ClearShadowShaderCache();

    Land.SetShader("assets/Shaders/BasicVertex.shader");
    Land.SetShader("assets/Shaders/BasicLighting.shader");
    Land.FinishShader();

    Land.SumAllWeights();
    std::cout << "Land Weights: " << Land.GetTotalWeight() << std::endl;

   

    PlayerBlock.ImportShaders(Land.ExportShaders());
    PlayerBlock.FinishShader();

    TealBlock.ImportShaders(Land.ExportShaders());
    TealBlock.FinishShader();

    Land.ClearShaderCache();
    //OtherSuns.ClearShaderCache();
    PlayerBlock.ClearShaderCache();
    TealBlock.ClearShaderCache();
    // The light does not get a shadow shader
    Sun.SetShader("assets/Shaders/BasicVertex.shader");
    Sun.SetShader("assets/Shaders/BasicLightObject.shader");

    OtherSuns.ImportShaders(Sun.ExportShaders());
    OtherSuns.FinishShader();
    OtherSuns.ClearShaderCache();
    //Sun.ImportShaders(Land.ExportShaders());
    Sun.FinishShader();
    Sun.ClearShaderCache();


    
    glGenFramebuffers(1, &ShadowMapFBO);

    glGenTextures(1, &ShadowMapTexture);

    glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //float clampColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ShadowWidth, ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMapTexture, 0);

    //glGenRenderbuffers(1, &ShadowMapRBO);
    //glBindRenderbuffer(GL_RENDERBUFFER, ShadowMapRBO);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ShadowWidth, ShadowHeight);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ShadowMapRBO);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, ShadowMapTexture);

    // THis stuff will be used for point light shadows
    /*
    glBindTexture(GL_TEXTURE_CUBE_MAP, ShadowMapTexture);

    for(unsigned int i = 0; i < 6; i++){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, ShadowWidth, ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    dumb test
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X ,ShadowMapTexture, 0);

    //glGenRenderbuffers(1, &ShadowMapRBO);
    //glBindRenderbuffer(GL_RENDERBUFFER, ShadowMapRBO);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ShadowWidth, ShadowHeight);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ShadowMapRBO);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    */


    

    Sun.SetLightColor(1.0f, 1.0f, 1.0f);
    Sun.SetColor(1.0f,0.9059f,0.0f, 0.86f);
    Sun.SetPosition(15.0f,10.0f,10.0f);

    Land.SetPosition(-20.0f,0.0f,-20.0f);
    Land.SetColor(0.3373f, 0.4902f, 0.2745f, 1.0f);
    Land.SetMaterial(BasicMetalCube);
    Land.PreFillLights(4);

    OtherSuns.SetPosition(30.0f,5.0f,30.0f);
    OtherSuns.SetColor(1.0f,0.0f,0.0f,1.0f);
    OtherSuns.SetLightColor(1.0f,1.0f,1.0f);
    //OtherSuns.SetMaterial(BasicMetalCube);
    //OtherSuns.PreFillLights(4);

    TealBlock.SetPosition(8.0f,40.0f,8.0f);
    TealBlock.SetColor(0.5f, 0.75f, 0.75f, 1.0f);
    TealBlock.SetMaterial(BasicMetalCube);
    TealBlock.PreFillLights(4);


    PlayerBlock.SetMaterial(BasicMetalCube);
    PlayerBlock.PreFillLights(4);

    Land.BindBufferData();
    Sun.BindBufferData();

    std::cout << PlayerBlock.GetVerticies()[1].Pos.X << " | " << PlayerBlock.GetVerticies()[0].Pos.Y << " | " << PlayerBlock.GetVerticies()[0].Pos.Z << std::endl;

    int NewTestInt;
    NewTestInt = PlayerBlock.GetObjectQuadID()->size();

    std::cout << NewTestInt << std::endl;

    m_running = true;
}

void TestWorld::PhysicsUpdate(float MaxUpdateSpeed){
    //std::cout << MaxUpdateSpeed << std::endl;
		// Physics rewite. So each object will be moved in an order
		// probaly as the use just adds or sets them, lol
		// but during the movment it will do sphear collision and if their is one
		// it will add it to the list of collisions to process.
		// Each of theast list items will be a thead. from thear each thead will
		// spin up and join. after that any editianl movments that are needed
		// hapen. Each thread goes through this hole process
        // Example of how i want this to function in the world  layout
        // PhysicsEngine.SetupdateTime(UpdateSpeed) // this will relativly the same as the current
        // PhysicsEngine.GeneralMovment() // This would move things that are effected by gravity, player input (Other movment optinos avalible out side thise function)
        // PhysicsEngine.Other movments ya its not a function plus a comment cause some time specialized movment is needed
        // PhysicsEngine.PhysicsResolve() // This will start resolving conflicst caused by the movment of object, and move them acordingly ish
        // Setting the physics for and what the object can colide with.
        // IE you can set Rigid or Dynamic
        // The finer detaild colision can be set along with the seize of the sphear colider
        // I also want the ability to limit all physics processing (including movment in the GeneralMovment) for objects outside some range of the player



        //glfwPostEmptyEvent();
        // camera stuff 
        BasicPhysics.SetUpdateTime(MaxUpdateSpeed);
        AdvancedCam.Update(MaxUpdateSpeed, (float)m_Width/m_Height, m_FOV);
        m_Projection = AdvancedCam.GetProj();
        m_View = AdvancedCam.GetView();
        m_3dCamPos = AdvancedCam.GetCurrentPos();


        //bool Test = Object.AABBColision(CubeVertex, CubeVertexCount, CubePos, LandVertex, LandVertexCount,LandPos);
        // This is just to seperate the old colision system from the new one
        ColisionInfo PlayerTOObject, TealBlockColision;
        PlayerTOObject.IsColision = false;

        //std::vector<QuadPhysicsBody> Player, PhysicsLand, OtherPhysicsLand, PhysicsTealBlock;
        //PhysicsPoint PlayerPos, TealBlockFuturePos, TealBlockCurrentPos, LandPhysPos, OtherSunsPhysPos;

        if(Land.ObjectPositionID == -1){
            Land.ObjectPositionID = m_ObjectWorldPositions.size();
            m_ObjectWorldPositions.push_back(Land.GetPhysicsPos());
        } else {
            m_ObjectWorldPositions[Land.ObjectPositionID] = Land.GetPhysicsPos();
        }

        if(TealBlock.ObjectPositionID == -1){
            TealBlock.ObjectPositionID =  m_ObjectWorldPositions.size();
            m_ObjectWorldPositions.push_back(TealBlock.GetPhysicsPos());
        } else {
            m_ObjectWorldPositions[TealBlock.ObjectPositionID] = TealBlock.GetPhysicsPos();
        }
        
        //TealBlockCurrentPos = TealBlock.GetPhysicsPos();
        //ForceDirection LeftFromOrigion;

        //LeftFromOrigion.X = -1.0f;
        //LeftFromOrigion.Y = 0.0f;
        //LeftFromOrigion.Z = 0.0f;

        PlayerPhysics = BasicPhysics.MakePhysicsQuads(PlayerBlock.GetVertexPositions(), PlayerBlock.GetVertexNormlPositions(), PlayerBlock.GetWeights());
        LandPhysics = BasicPhysics.MakePhysicsQuads(Land.GetVertexPositions(), Land.GetVertexNormlPositions(), Land.GetWeights());
        TealBlockPhysics = BasicPhysics.MakePhysicsQuads(TealBlock.GetVertexPositions(), TealBlock.GetVertexNormlPositions(), TealBlock.GetWeights());

        // Checking the Teal bocks current position for a colision incase it was missed
        BasicPhysics.AABBColision(TealBlockPhysics, m_ObjectWorldPositions[TealBlock.ObjectPositionID], LandPhysics, m_ObjectWorldPositions[Land.ObjectPositionID], &TealBlockColision);
        if(!TealBlockColision.IsColision){
            if(TealBlock.ObjectPositionFutureID == -1){
                // Makes and sets future posion
                TealBlock.ObjectPositionFutureID = m_ObjectWorldPositions.size();
                m_ObjectWorldPositions.push_back(BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionID], BasicPhysics.GetGravity(), BasicPhysics.GetGravity().Speed));
            } else {
                // Sets Future movment position;
                m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID] = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionID], BasicPhysics.GetGravity(), BasicPhysics.GetGravity().Speed);
            }
            //TealBlockFuturePos = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), BasicPhysics.GetGravity().Direction, BasicPhysics.GetGravity().Power);
        
        // We then check the futur position;
        BasicPhysics.AABBColision(TealBlockPhysics, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], LandPhysics,  m_ObjectWorldPositions[Land.ObjectPositionID], &TealBlockColision);

        // IF their is a colision we have the future position react to it;
            if(TealBlockColision){
                m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID] = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], TealBlockColision.MovmentDirectionB, BasicPhysics.GetGravity().Speed);
            //TealBlockFuturePos = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], TealBlockColision.MovmentDirectionB, BasicPhysics.GetGravity().Power);
            }
            // Finaly a Future position is set
                TealBlock.SetPosition(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].X, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].Y, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].Z);
                TealBlockColision.IsColision = false; // this is just to make sure the lower one isnt triped
        }
        if(TealBlockColision.IsColision){
            m_ObjectWorldPositions[TealBlock.ObjectPositionID] = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], TealBlockColision.MovmentDirectionB, BasicPhysics.GetGravity().Speed);
            TealBlock.SetPosition(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].X, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].Y, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].Z);
        }



        //if(!TealBlockColision.IsColision){
        //    TealBlockColision = BasicPhysics.PointsToAABBColision(PhysicsTealBlock, TealBlockFuturePos, BasicPhysics.MinMaxFromQuads(PhysicsLand, Land.GetPhysicsPos()));
        //}
        //if(!TealBlockColision.IsColision){
        //    TealBlockColision = BasicPhysics.PointsToAABBColision(PhysicsLand, Land.GetPhysicsPos(), BasicPhysics.MinMaxFromQuads(PhysicsTealBlock, TealBlockFuturePos));
        //}
        //if(!TealBlockColision.IsColision){
        //    TealBlockColision = BasicPhysics.AABBColision(PhysicsTealBlock, TealBlockFuturePos, OtherPhysicsLand, OtherSunsPhysPos);
        //}

        //TealBlockColision = BasicPhysics.SATColision(PhysicsTealBlock, TealBlockFuturePos, PhysicsLand, Land.GetPhysicsPos());
        //TealBlockColision = BasicPhysics.FullQuadLineColision(BasicPhysics.QuadsToLines(PhysicsTealBlock), TealBlock.GetPhysicsPos(), BasicPhysics.QuadsToLines(PhysicsLand), Land.GetPhysicsPos(), 1.01);
        
        //TealBlockColision = BasicPhysics.QuadBodyColision(PhysicsTealBlock, TealBlockFuturePos, PhysicsLand, Land.GetPhysicsPos());
        //TealBlockColision = BasicPhysics.QuadBodyColision(PhysicsLand, Land.GetPhysicsPos(), PhysicsTealBlock, TealBlockFuturePos);

        // remove when done testing
        //PhysicsPos TempPos = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), BasicPhysics.GetGravity(), BasicPhysics.GetGravity().Speed);
        //TealBlock.SetPosition(TempPos.X, TempPos.Y, TempPos.Z);
        /*
        SphearPhysicsBody TestSphear;
        TestSphear.PosA.Pos = TealBlock.GetPhysicsPos();
        TestSphear.Radius = 1.0f;

        //BasicPhysics.SphearToPlanetColision(TestSphear, PhysicsLand, Land.GetPhysicsPos(), &TealBlockColision);
        TealBlockColision.IsColision = false;
        for(unsigned long i = 0; i < LandPhysics.size(); i++){
            TealBlockColision = BasicPhysics.SphearToPlane(TestSphear, LandPhysics[i], Land.GetPhysicsPos());
            if(TealBlockColision.IsColision){
                std::cout << "Colision" << std::endl;
                //std::cout << TealBlock.GetPhysicsPos().X << " " << TealBlock.GetPhysicsPos().Y << " " << TealBlock.GetPhysicsPos().Z << std::endl;
                break;
            }
        }


        if(TealBlockColision.IsColision){
            TealBlock.SetPosition(TealBlock.GetPhysicsPos().X * TealBlockColision.MovmentDirectionB.X, TealBlock.GetPhysicsPos().Y * TealBlockColision.MovmentDirectionB.Y, TealBlock.GetPhysicsPos().Z * TealBlockColision.MovmentDirectionB.Z);
        }

        */
        

        // Move Player based on player input
        if(PlayerBlock.ObjectPositionID == -1){
            PlayerBlock.ObjectPositionID = m_ObjectWorldPositions.size();
            m_ObjectWorldPositions.push_back(BasicPhysics.MovePhysicsObject(PlayerBlock.GetPhysicsPos(), BasicPhysics.NormalizeVectorOfForceDirection(m_NewPlayerDirection), PlayerMovmentSpeed));
        } else {
            m_ObjectWorldPositions[PlayerBlock.ObjectPositionID] = BasicPhysics.MovePhysicsObject(PlayerBlock.GetPhysicsPos(), BasicPhysics.NormalizeVectorOfForceDirection(m_NewPlayerDirection), PlayerMovmentSpeed);
        }
        //PlayerPos = BasicPhysics.MovePhysicsObject(PlayerBlock.GetPhysicsPos(), BasicPhysics.NormalizeVectorOfForceDirection(m_NewPlayerDirection), PlayerMovmentSpeed);

        //PlayerTOObject = BasicPhysics.AABBColision(Player, PlayerPos, PhysicsLand, Land.GetPhysicsPos());
        //PlayerTOObject = BasicPhysics.SATColision(Player, PlayerPos, PhysicsLand, Land.GetPhysicsPos());
        //if(PlayerTOObject.IsColision){
            //PlayerPos = BasicPhysics.MovePhysicsObject(PlayerPos, PlayerTOObject.MovmentDirectionB, PlayerMovmentSpeed);
        //    std::cout << PlayerTOObject.MovmentDirectionB.X << " | " << PlayerTOObject.MovmentDirectionB.Y << " | " << PlayerTOObject.MovmentDirectionB.Z << std::endl;
        //}
        PlayerBlock.SetPosition(m_ObjectWorldPositions[PlayerBlock.ObjectPositionID].X, m_ObjectWorldPositions[PlayerBlock.ObjectPositionID].Y, m_ObjectWorldPositions[PlayerBlock.ObjectPositionID].Z);
        AdvancedCam.SetPos(m_ObjectWorldPositions[PlayerBlock.ObjectPositionID].X, m_ObjectWorldPositions[PlayerBlock.ObjectPositionID].Y+0.9f, m_ObjectWorldPositions[PlayerBlock.ObjectPositionID].Z);

        //BasicPhysics.FullQuadLineColisionVoid(TempPlayerLines, PlayerPos, TempLandLines, Land.GetPhysicsPos(), 1.02f, &PlayerTOObject);

        //TealBlockColision = BasicPhysics.AABBColision(PhysicsTealBlock, TealBlockFuturePos, Player, PlayerPos);
        //TealBlockColision = BasicPhysics.FullQuadLineColision(BasicPhysics.QuadsToLines(PhysicsTealBlock), TealBlock.GetPhysicsPos(), BasicPhysics.QuadsToLines(Player), PlayerPos, 1.01f);
        //TealBlockColision = BasicPhysics.SATColision(PhysicsTealBlock, TealBlockFuturePos, Player, PlayerPos);
        //TealBlockColision = BasicPhysics.QuadBodyColision(PhysicsTealBlock, TealBlockFuturePos, Player, PlayerPos, 0.3f);
        ///TealBlockColision = BasicPhysics.QuadBodyColision(Player, PlayerPos, PhysicsTealBlock, TealBlockFuturePos, 0.3f);
        //if(!TealBlockColision.IsColision){
        //    TealBlockColision = BasicPhysics.QuadBodyColision(Player, PlayerPos, PhysicsTealBlock, TealBlockFuturePos, 0.9f);
        //}

        // The player can push the block and the block should not beable to clip throught the land from the interaction

        BasicPhysics.SphearColison(TealBlock.GetPhysicsPos(), 2.0f, PlayerBlock.GetPhysicsPos(), 2.0f, &TealBlockColision);

        if(TealBlockColision){
            BasicPhysics.QuadBodyColision(TealBlockPhysics, TealBlock.GetPhysicsPos(), PlayerPhysics, PlayerBlock.GetPhysicsPos(), &TealBlockColision, 0.9f);
            TealBlockColision.MovmentDirectionA =  TealBlockColision.MovmentDirectionB;
            //TealBlockColision = BasicPhysics.QuadBodyColision(Player, PlayerPos, PhysicsTealBlock, TealBlockFuturePos, 0.3f);
            if(!TealBlockColision){
                BasicPhysics.QuadBodyColision(PlayerPhysics, PlayerBlock.GetPhysicsPos(), TealBlockPhysics, TealBlock.GetPhysicsPos(), &TealBlockColision, 1.0f);
                TealBlockColision.MovmentDirectionA = TealBlockColision.MovmentDirectionA;
            }
            if(TealBlockColision){
                //ForceDirection 
                //ForceDirection NewTealBlockDirecton = BasicPhysics.MakeForceDirection(PlayerPos, TealBlockFuturePos);
                m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID] = BasicPhysics.MovePhysicsObject(TealBlock.GetPhysicsPos(), TealBlockColision.MovmentDirectionA , PlayerMovmentSpeed);
                BasicPhysics.AABBColision(TealBlockPhysics, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], LandPhysics, m_ObjectWorldPositions[Land.ObjectPositionID], &TealBlockColision);
                if(TealBlockColision.IsColision){
                    TealBlockColision.PastMovmentDirectionA.Speed = PlayerMovmentSpeed;
                    TealBlockColision.MovmentDirectionA.Speed = BasicPhysics.GetGravity().Speed + PlayerMovmentSpeed;
                    BasicPhysics.NormalizeForceDirection(TealBlockColision.PastMovmentDirectionA, TealBlockColision.MovmentDirectionA, &TealBlockColision.CurentMovmentDirectionA);
                    m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID] = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], TealBlockColision.CurentMovmentDirectionA, TealBlockColision.CurentMovmentDirectionA.Speed);

                BasicPhysics.AABBColision(TealBlockPhysics, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], LandPhysics, m_ObjectWorldPositions[Land.ObjectPositionID], &TealBlockColision);
                    if(TealBlockColision.IsColision){
                    BasicPhysics.NormalizeForceDirection(TealBlockColision.PastMovmentDirectionA, TealBlockColision.MovmentDirectionA, &TealBlockColision.CurentMovmentDirectionA);
                    TealBlockColision.CurentMovmentDirectionA = BasicPhysics.GetGravity();
                    TealBlockColision.CurentMovmentDirectionA.Y = TealBlockColision.CurentMovmentDirectionA.Y * -1.0f; 
                    TealBlockColision.MovmentDirectionA.Speed = BasicPhysics.GetGravity().Speed + PlayerMovmentSpeed*2.0f;
                    m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID] = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], TealBlockColision.CurentMovmentDirectionA, TealBlockColision.CurentMovmentDirectionA.Speed);
                    } 
                }else {
                    m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID] = BasicPhysics.MovePhysicsObject(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID], TealBlockColision.MovmentDirectionA, PlayerMovmentSpeed);
                }

            }
                
                
        }
            //TealBlock.SetPosition(TealBlockFuturePos.X, TealBlockFuturePos.Y, TealBlockFuturePos.Z);
        
        TealBlock.SetPosition(m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].X, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].Y, m_ObjectWorldPositions[TealBlock.ObjectPositionFutureID].Z);

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

void TestWorld::KeyInput(std::array<int,512> Keys){
        m_NewPlayerDirection.clear();    
        PlayerMovmentSpeed = 4.317f;
        // Keys[] will be replaced with a vector or array of keyinput structs
        // Eventualy the movment will be forcebased

        if(Keys[GLFW_KEY_F] == GLFW_PRESS){
            PhysicsPos Temp = PlayerBlock.GetPhysicsPos();
            Temp.Y += 10.0f;
            //TealBlock.SetNextPhysicsPos(Temp.X, Temp.Y, Temp.Z);
        }

        if(Keys[GLFW_KEY_LEFT_CONTROL] == GLFW_PRESS){
            //SpeedStep = 12.51f *m_DeltaTime;
            PlayerMovmentSpeed = 6.612;
        }

        if(Keys[GLFW_KEY_W] == GLFW_PRESS){
            m_pos2D[2] -= 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(FORWARD, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(FORWARD));
        }

        if(Keys[GLFW_KEY_S] == GLFW_PRESS){
            m_pos2D[2] += 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(BACK, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(BACK));
        }

        if(Keys[GLFW_KEY_A] == GLFW_PRESS){
            m_pos2D[0] -= 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(LEFT, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(LEFT));
        }

        if(Keys[GLFW_KEY_D] == GLFW_PRESS){
            m_pos2D[0] += 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(RIGHT, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(RIGHT));
        }

        if(Keys[GLFW_KEY_SPACE] == GLFW_PRESS){
            m_pos2D[1] += 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(UP, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(UP));
        }

        if(Keys[GLFW_KEY_LEFT_SHIFT] == GLFW_PRESS){
            m_pos2D[1] -= 5 + PlayerMovmentSpeed;
            //AdvancedCam.Move(DOWN, SpeedStep);
            m_NewPlayerDirection.push_back(AdvancedCam.MoveDir(DOWN));
        }

        if(Keys[GLFW_KEY_MINUS] == GLFW_PRESS){
            m_FOV -= 1.0f;
                    if(m_FOV <= 20.0f){
                        m_FOV = 20.0f;
                    }
        }

        if(Keys[GLFW_KEY_EQUAL] == GLFW_PRESS){
            m_FOV += 1.0f;
                    if(m_FOV >= 120.0f){
                        m_FOV = 120.0f;
                    }
        }

        if(Keys[GLFW_KEY_L] == GLFW_PRESS){
            AdvancedCam.InvertVertical();
        }

        if(Keys[GLFW_KEY_K] == GLFW_PRESS){
            AdvancedCam.UnInvertVertical();
        }



}

void TestWorld::MouseButton(std::array<int,32> MouseButtons){
    if(MouseButtons[GLFW_MOUSE_BUTTON_LEFT] == GLFW_PRESS){
        glm::vec3 Temp = AdvancedCam.GetCurrentLook();
        std::cout << "Current Look : " << Temp.x << " | " << Temp.y << " | " << Temp.z << std::endl;
    }
}

void TestWorld::MouseInput(double xpos, double ypos){

    AdvancedCam.LookRelative(xpos,ypos);

}


void TestWorld::GenShadows(){
    // The lights should not be drawn in the "shadow reml"

    glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO);
    //GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D ,ShadowMapTexture, 0));
    //glBindRenderbuffer(GL_RENDERBUFFER, ShadowMapRBO);
    //glClear(GL_DEPTH_BUFFER_BIT);

    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glEnable(GL_DEPTH_TEST));

    float near_plane = 0.1f, far_plane = 75.0f;
    //glm::mat4 ShadowView = glm::perspective(glm::radians(90.0f), (float)ShadowWidth/(float)ShadowHeight, near_plane, far_plane);
    glm::mat4 ShadowProjection = glm::ortho(-10.0f,10.0f, -10.0f,10.0f, near_plane, far_plane);
    glm::mat4 LightView = glm::lookAt(Sun.GetPos(), glm::vec3(6.0f,-5.0f,10.0f), glm::vec3(0.0f, 1.0f, 0.0f));



    
    //PlayerBlock.SetShadowPos(lightProjection, lightView);
    //Land.SetShadowPos(lightProjection, lightView);
    //TealBlock.SetShadowPos(lightProjection, lightView);

    //PlayerBlock.SetShadowPos(lightSpaceMatrix);
    //Land.SetShadowPos(lightSpaceMatrix);
    //TealBlock.SetShadowPos(lightSpaceMatrix);

    PlayerBlock.SetShadowPos(ShadowProjection, LightView);
    Land.SetShadowPos(ShadowProjection, LightView);
    TealBlock.SetShadowPos(ShadowProjection, LightView);


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


        //Sun.BindBufferData();
        //Sun.SetColor(1.0f,0.9059f,0.0f, 1.0f);
        
        Sun.SetDrawPos(m_Projection, m_View);
        //Sun.SetLight(Sun.GetLightColor(), Sun.GetPos());
        Sun.Paint();



        //Land.BindBufferData();
        
        Land.SetDrawPos(m_Projection, m_View);
        Land.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        Land.SetLight(OtherSuns.GetLightInfo(), OtherSuns.GetPos(), m_3dCamPos, 1);
        Land.Paint();

        OtherSuns.BindBufferData();
        OtherSuns.SetDrawPos(m_Projection, m_View);
        //OtherSuns.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        OtherSuns.Paint();

        
        TealBlock.BindBufferData();
        //TealBlock.SetColor(0.471f, 0.318f, 0.176f, 1.0f);
        
        TealBlock.SetDrawPos(m_Projection,m_View);
        TealBlock.SetLight(Sun.GetLightInfo(), Sun.GetPos(), m_3dCamPos);
        TealBlock.SetLight(OtherSuns.GetLightInfo(), OtherSuns.GetPos(), m_3dCamPos, 1);
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
        PlayerBlock.SetLight(OtherSuns.GetLightInfo(), OtherSuns.GetPos(), m_3dCamPos, 1);

        
        PlayerBlock.Paint();
        

        if(m_Effect){
            // Post Draw Stuff if needed

        }

        //glViewport(0,0 ,(int)(m_Width*m_Scale), (int)(m_Height*m_Scale));

        


}


void TestWorld::PaintFrame(){
    glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, FrameBuffTexture);
    glBindTexture(GL_TEXTURE_2D, m_FBO.GetTexture());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GLCall(glDisable(GL_DEPTH_TEST)); 
    Frame.BindBufferData();
    Frame.Paint();

}

// This will be replaces with an internal GUI system;
void TestWorld::OnGui(){


}
