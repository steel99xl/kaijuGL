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
    FBOrec.Setup();

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

    Land.Create2dQuad(0.0f,-1.0f,0.0f, -90.0f,0.0f,0.0f, 5.0f,5.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
    Land.Create2dQuad(8.0f,1.0f,0.0f, -90.0f,0.0f,0.0f, 5.0f,5.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Land.Create2dQuad(0.0f,-1.0f,-6.0f, 0.0f,0.0f,0.0f, 5.0f,5.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);


    Sun.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.10f,0.10f,0.10f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Object.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);

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
    //TestObject.SetShader("assets/Shaders/MultiImg.shader");
    
    Sun.SetShader("assets/Shaders/BasicLight.shader");

    //m_Shader->SetShader("assets/Shaders/MultiImg.shader");
    //m_Shader->Bind();

    std::cout << "Shader set" << std::endl;

        //auto loc = m_Shader->GetUniformLocation("u_Textures");
    //int samplers[3] = {0 ,1,2};
        //GLsizei size = 2;
        //GLCall(glUniform1iv(loc, size, samplers));
    ///m_Shader->SetUniform1iv("u_Textures", 3, samplers);
    //m_Shader->SetUniform1iv("u_Textures", 3, samplers);
    
    //m_Texture = std::make_unique<Texture>("assets/Textures/Box.png");


    //Tex1 = m_Texture->LoadTexture("assets/Textures/Box.png");
    //Tex2 = m_Texture->LoadTexture("assets/Textures/Logo.jpeg");
    //Tex3 = m_Texture->LoadTexture("assets/Textures/OtherBox.png");

    //Object.AddTexture("assets/Textures/Box.png");
    //Object.AddTexture("assets/Textures/Logo.jpeg",1);
    //Object.AddTexture("assets/Textures/OtherBox.png",2);


    // All The funcinality that has to be in the setup of the FrameBuffer Object
    //GLCall(glGenFramebuffers(1, &m_FBO));
    //GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));


    //FrameBufferTexture = m_Texture->MakeTexture("NULL", 720, 480);

    //

    //GLCall(glGenRenderbuffers(1, &m_RBO));
    //GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RBO));
    //

    //

    
    

    
    FBOrec.Create2dQuad(1.0f,1.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f, 0.0f,0.0f, 1.0f,1.0f, 1.0f);

    //m_Texture->LoadTexture("assets/Textures/OtherBox.png");
    //m_Texture->LoadTexture("assets/Textures/Logo.jpeg",1);
    //m_Texture->LoadTexture("assets/Textures/OtherBox.png",2);

    //m_Texture->Bind(0);
    //m_Texture->Bind(1);
    //m_Texture->Bind(2);


        //std::cout << "bound texture 1" << std::endl;
    //GLCall(glActiveTexture(GL_TEXTURE0 + 0));
    //GLCall(glBindTexture(GL_TEXTURE_2D, Tex1));

        //std::cout << "bound texture 2 " << std::endl;
    //GLCall(glActiveTexture(GL_TEXTURE0 + 1));
    //GLCall(glBindTexture(GL_TEXTURE_2D, Tex2));

    //GLCall(glActiveTexture(GL_TEXTURE0 + 2));
    //GLCall(glBindTexture(GL_TEXTURE_2D, Tex3));

    
    // This sets the max amout of things in the vertex buffer
    //m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 100);

   //m_VertexBuffer->MakeBuffer(NULL, sizeof(Vertex) * (Object.GetMaxQuadCound() * 4 ));



        //std::cout << m_IBO->Unquie() << std::endl;

    //VertexBufferLayout layout;
        // This defines the layout 
    //layout.Push(3,"float");
    //layout.Push(2,"float");
    //layout.Push(1,"float");
    //layout.Push(1,"float");
    //m_VAO->AddBuffer(*m_VertexBuffer,layout);    

        //std::cout << "Seting shader program" << std::endl;

        //IndexBuffer ibo(SqIndex,6);
        //GLCall(glUseProgram(m_Shader->GetRenderID()));

    //m_Shader->Bind();
 

        //Shader shader("assets/Shaders/ImgLoad.shader");
        //m_Shader->Bind();

     // This has to match the bound texture buffer

        //m_Shader->SetUniform1i("u_Texture", 0);
    m_FOV = 75.0f;


   

    

    //std::cout << "Total Verticies Sent = " << Object.GetVerticiesCount() << std::endl;
  //  std::cout << "Total Squares = " << Object.GetVerticiesCount()/4 << std::endl;
   // std::cout << "Total Verticies Drawn = " << (Object.GetVerticiesCount()/4)*6 << std::endl;


}


Vertex *TestWorld::CreateQuad(Vertex *target, float X, float Y, float sizeX, float sizeY, float TextureID){

        target->Pos = {X, Y, 0.0f};
        target->TexCord = {0.0f, 0.0f};
        target->TexID = TextureID;

        target++;

        target->Pos = {X+sizeX, Y, 0.0f};
        target->TexCord = {1.0f, 0.0f};
        target->TexID = TextureID;

        target++;

        target->Pos = {X+sizeX, Y+sizeY, 0.0f};
        target->TexCord = {1.0f, 1.0f};
        target->TexID = TextureID;

        target++;

        target->Pos = {X, Y+sizeY, 0.0f};
        target->TexCord = {0.0f, 1.0f};
        target->TexID = TextureID;

        target++;


        return target;

    }


void TestWorld::OnUpdate(float deltaTime, float width, float height){
        glfwPollEvents();
        m_DeltaTime = deltaTime;
        AdvancedCam.Update(m_DeltaTime, (float)m_Width/m_Height, m_FOV);
        m_Projection = AdvancedCam.GetProj();
        m_View = AdvancedCam.GetView();

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

        glm::vec3 camPos = AdvancedCam.GetCurrentPos();

        //std::cout << AdvancedCam.GetCurrentLook().x << " | " << AdvancedCam.GetCurrentLook().y << " | " << AdvancedCam.GetCurrentLook().z << std::endl;



        Sun.BindBufferData();
        //Sun.SetColor(1.0f,0.9059f,0.0f, 1.0f);
        Sun.SetLightColor(1.0f, 1.0f, 1.0f);
        Sun.SetColor(1.0f,0.9059f,0.0f, 0.86f);
        Sun.SetPosition(0.0f,4.0f,0.0f, m_Projection, m_View);
        //Sun.SetLight(Sun.GetLightColor(), Sun.GetPos());
        Sun.Paint();



        Land.BindBufferData();
        Land.SetColor(0.3373f, 0.4902f, 0.2745f, 1.0f);
        Land.SetMaterial(BasicMetalCube);
        Land.SetPosition(0.0f,0.0f,0.0f, m_Projection, m_View);
        Land.SetLight(Sun.GetLightInfo(), Sun.GetPos(), camPos);
        Land.Paint();





        // Dynamic Vertex Buffer!!!!


         

       //m_IBO->Bind();
        //Object.BindIndexBuffer();
        //GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Object.GetIndicCount(), Object.GetIndices().data()));
        
        // if the offset is not correct it wont draw, will messup a draw
        
        // You have to have a second vertex buffer object set up on the same Vertex array object

        // Evrything else still needed for a seperate draw call
        // This only needs to be calld once if you are drawing the same object multiple times
        Object.BindBufferData();

        Object.SetPosition(0.0f,2.0f,0.0f, m_Projection, m_View);
        Object.SetColor(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
        Object.SetLight(Sun.GetLightInfo(), Sun.GetPos(), camPos);
        Object.SetMaterial(BasicMetalCube);
        Object.Paint();


        Object.SetPosition(2.0f, 0.0f, 0.0f, m_Projection,m_View);
        Object.SetColor(m_Color2.x, m_Color2.y, m_Color2.z, m_Color2.w);
        Object.SetLight(Sun.GetLightInfo(), Sun.GetPos(), camPos);
        Object.SetMaterial(BasicMetalCube);
        Object.Paint();

        //Using this cube as as temp player for colision detection
        // This is only going to check colision with the single Land Object (IE the ground);
        // The position is only being set first so i can just call the cube object
        Object.SetPosition(camPos.x, camPos.y-1.3f, camPos.z, m_Projection, m_View);

        std::vector<Vertex> CubeVertex = Object.GetVerticies();
        int CubeVertexCount = Object.GetVerticiesCount();
         glm::vec3 CubePos = Object.GetPos();

        std::vector<Vertex> LandVertex = Land.GetVerticies();
        int LandVertexCount =  Land.GetVerticiesCount();
        glm::vec3 LandPos = Land.GetPos();

        // FragPos will be used for object push back
        // for now it will be a simple bool
        bool Test = SimpleColisionFunction(CubeVertex, CubeVertexCount, CubePos, LandVertex, LandVertexCount,LandPos);
        
        if(Test){
            Object.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
        } else {
            Object.SetColor(m_Color3.x, m_Color3.y, m_Color3.z, 1.0f);
        }
        Object.SetLight(Sun.GetLightInfo(), Sun.GetPos(), camPos);
        Object.SetMaterial(BasicMetalCube);
        Object.Paint();

        if(m_Effect){
            // Post Draw Stuff if needed

        }
        

    }

bool TestWorld::SimpleColisionFunction(std::vector<Vertex> ObjectAVerticies, int ObjectAVerticiesCount, glm::vec3 ObjectAPos, std::vector<Vertex> ObjectBVerticies, int ObjectBVerticiesCount, glm::vec3 ObjectBPos){
    bool XColission = false;
    bool YColission = false;
    bool ZColission = false;

    std::vector <VertexPos> MinMaxA;
    int MinMaxACount = 0; // This is just for testing
    std::vector <VertexPos> MinMaxB;
    int MinMaxBCount = 0; // This is also just for testing

    VertexPos Max;
    VertexPos Min;

    float XMin = INFINITY;
    float YMin = INFINITY;
    float ZMin = INFINITY;

    float XMax = -INFINITY;
    float YMax = -INFINITY;
    float ZMax = -INFINITY;

    int Count = 0; //This is so every min and max is pushed back every quad
    for(int i = 0; i < ObjectAVerticiesCount; i++){
        Count++;
        float X = ObjectAVerticies[i].Pos.X + ObjectAPos[0];
        float Y = ObjectAVerticies[i].Pos.Y + ObjectAPos[1];
        float Z = ObjectAVerticies[i].Pos.Z + ObjectAPos[2];

        if(X < XMin){
            XMin = X;
        } else if(X > XMax){
            XMax = X;
        }

        if(Y < YMin){
            YMin = Y;
        } else if(Y > YMax){
            YMax = Y;
        }

        if(Z < ZMin){
            ZMin = Z;
        } else if(Z > ZMax){
            ZMax = Z;
        }

        if(Count == 4){
            Count = 0;

            Min.X = XMin;
            Min.Y = YMin;
            Min.Z = ZMin;

            Max.X = XMax;
            Max.Y = YMax;
            Max.Z = ZMax;

            MinMaxA.push_back(Min);
            MinMaxA.push_back(Max);
            MinMaxACount += 2;

            XMin = INFINITY;
            YMin = INFINITY;
            ZMin = INFINITY;

            XMax = -INFINITY;
            YMax = -INFINITY;
            ZMax = -INFINITY;

        }
    }

    // I should not have to reset the Min and Max but this is just to be save;
    XMin = INFINITY;
    YMin = INFINITY;
    ZMin = INFINITY;

    XMax = -INFINITY;
    YMax = -INFINITY;
    ZMax = -INFINITY;

    Count = 0; //This is so every min and max is pushed back every quad
    for(int i = 0; i < ObjectBVerticiesCount; i++){
        Count++;
        float X = ObjectBVerticies[i].Pos.X + ObjectBPos[0];
        float Y = ObjectBVerticies[i].Pos.Y + ObjectBPos[1];
        float Z = ObjectBVerticies[i].Pos.Z + ObjectBPos[2];

        if(X < XMin){
            XMin = X;
        } else if(X > XMax){
            XMax = X;
        }

        if(Y < YMin){
            YMin = Y;
        } else if(Y > YMax){
            YMax = Y;
        }

        if(Z < ZMin){
            ZMin = Z;
        } else if(Z > ZMax){
            ZMax = Z;
        }

        if(Count == 4){
            Count = 0;

            Min.X = XMin;
            Min.Y = YMin;
            Min.Z = ZMin;

            Max.X = XMax;
            Max.Y = YMax;
            Max.Z = ZMax;

            MinMaxB.push_back(Min);
            MinMaxB.push_back(Max);
            MinMaxBCount += 2;

            XMin = INFINITY;
            YMin = INFINITY;
            ZMin = INFINITY;

            XMax = -INFINITY;
            YMax = -INFINITY;
            ZMax = -INFINITY;

        }
    }


    

    //std::cout << MinMaxA[2].X << " | " << MinMaxA[2].Y << " | " << MinMaxA[2].Z << std::endl;
    // OK so this looks nearly Vertex Perfext on X and Z 
    int b,d;
    for(int a = 0; a < MinMaxACount; a += 2){
        b = (a + 1) % MinMaxACount;
        
        for( int c = 0; c < MinMaxBCount; c += 2){
            d = (c + 1) % MinMaxBCount;

            /*
            std::cout << "TITLE BAR FOR EASE OF USE" << std::endl;
            std::cout << a << " : Curent MinMax pare on object A" << std::endl;
            std::cout << MinMaxA[a].X << " | " << MinMaxA[a].Y << " | " << MinMaxA[a].Z << std::endl;
            std::cout << MinMaxA[b].X << " | " << MinMaxA[b].Y << " | " << MinMaxA[b].Z << std::endl;
            std::cout << "Plane" << std::endl;
            std::cout << MinMaxB[c].X << " | " << MinMaxB[c].Y << " | " << MinMaxB[c].Z << std::endl;
            std::cout << MinMaxB[d].X << " | " << MinMaxB[d].Y << " | " << MinMaxB[d].Z << std::endl;
            */
            
            if((MinMaxA[a].X <= MinMaxB[c].X && MinMaxA[b].X >= MinMaxB[d].X) || (MinMaxA[a].X >= MinMaxB[c].X && MinMaxA[b].X <= MinMaxB[d].X)){
                XColission = true;
            } else {
                XColission = false;
            }
            if((MinMaxA[a].Y <= MinMaxB[c].Y && MinMaxA[b].Y >= MinMaxB[d].Y) || (MinMaxA[a].Y >= MinMaxB[c].Y && MinMaxA[b].Y <= MinMaxB[d].Y)){
                YColission = true;
            } else {
                YColission = false;
            }
            if((MinMaxA[a].Z <= MinMaxB[c].Z && MinMaxA[b].Z >= MinMaxB[d].Z) || (MinMaxA[a].Z >= MinMaxB[c].Z && MinMaxA[b].Z <= MinMaxB[d].Z)){
                ZColission = true;
            } else {
                ZColission = false;
            }

            if(XColission && ZColission && YColission){
                return true;
            }

            /*
            std::cout << "End of check" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            */
        }
    }

    return false;

    // Super Basic AABB
    /*
    for(int a = 1; a < ObjectAVerticiesCount; a += 4){
        b = a + 2;
        for( int c = 1; c < ObjectBVerticiesCount; c += 4){
            d = c + 2;
            //std::cout << "Current Pos Based on the first Vertex of ObjectA" << std::endl;
            //std::cout << ObjectAVerticies[0].Pos.X + ObjectAPos[0] << " | " << ObjectBVerticies[c].Pos.X + ObjectBPos[0] << " | " << ObjectBVerticies[d].Pos.X + ObjectBPos[0] << std::endl;
            if(ObjectAVerticies[a].Pos.X + ObjectAPos[0] <= ObjectBVerticies[c].Pos.X + ObjectBPos[0] && ObjectAVerticies[a].Pos.X + ObjectAPos[0] >= ObjectBVerticies[d].Pos.X + ObjectBPos[0]){
                XColission = true;
            }
            
            // This cheks opposite compared to the other
            if(ObjectBVerticies[c].Pos.Y + ObjectBPos[1] >= ObjectAVerticies[a].Pos.Y + ObjectAPos[1] && ObjectBVerticies[c].Pos.Y + ObjectBPos[1] <= ObjectAVerticies[b].Pos.Y + ObjectAPos[1]){
                YColission = true;

            }

            
            if(ObjectAVerticies[a].Pos.Z + ObjectAPos[2] <= ObjectBVerticies[c].Pos.Z + ObjectBPos[2] && ObjectAVerticies[a].Pos.Z + ObjectAPos[2] >= ObjectBVerticies[d].Pos.Z + ObjectBPos[2]){
                ZColission = true;
            }
        }
    }
    */
    

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
