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

    
    FrameBufferTexture = m_Texture->MakeTexture("NULL", 800,600);


    AdvancedCam.SetHorizontalSensitivity(0.1f);
    AdvancedCam.SetVerticalSensitivity(0.08f);
    AdvancedCam.InvertVertical();

    Object.Setup();
    Land.Setup();
    Sun.Setup();

    BasicMetalCube.ambient.R = 0.3;
    BasicMetalCube.ambient.G = 0.3;
    BasicMetalCube.ambient.B = 0.3;

    BasicMetalCube.diffuse.R = 0.7f;
    BasicMetalCube.diffuse.G = 0.7f;
    BasicMetalCube.diffuse.B = 0.7f;

    BasicMetalCube.specular.R = 0.5f;
    BasicMetalCube.specular.G = 0.5f;
    BasicMetalCube.specular.B = 0.5f;

    BasicMetalCube.shininess = 32.0f;

    Sun.MakeLight(1.0f,1.0f,1.0f, 0.5f,0.5f,0.5f, 0.6f,0.6f,0.6f, -3.0f,-5.0f,3.0f, 12.5f, 0.045f, 0.0075f);




    // This add 1 quad to the land object
    //Land.CreateCube(0.0f,0.0f,0.0f, 45.0f,0.0f,45.0f, 1.0f, 1.0f,1.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);
   // Land.Create2dQuad(0.0f,0.0f,0.0f, F_NONE, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    //Land.Create2dQuad(0.0f,10.0f,-10.0f, F_NORTH, 20.0f,20.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f);

    Land.Create2dQuad(0.0f,-1.0f,0.0f, -90.0f,45.0f,0.0f, 100.0f,100.0f, 0.0f,0.0f, 1.0f,1.0f, 1.0f);

    Sun.CreateCube(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 1.0f,1.0f,1.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f);

    Object.CreateCube(0.0f,0.0f,0.0f, 45.0f,45.0f,45.0f, 1.0f,1.0f,1.0f, 0.0f,0.0f,1.0f,1.0f, 0.0f);

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
    Land.SetShader("assets/Shaders/MultiImg.shader");
    Object.SetShader("assets/Shaders/MultiImg.shader"); 
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

    m_Texture->LoadTexture("assets/Textures/OtherBox.png");
    m_Texture->LoadTexture("assets/Textures/Logo.jpeg",1);
    m_Texture->LoadTexture("assets/Textures/OtherBox.png",2);

    m_Texture->Bind(0);
    m_Texture->Bind(1);
    m_Texture->Bind(2);


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

void TestWorld::KeyInput(int key, int scancode, int action, int mods){
        float SpeedStep = 4.317f;

        if(mods == 1){
            //SpeedStep = 12.51f *m_DeltaTime;
            SpeedStep = 5.612;
        }


        if(action == GLFW_PRESS){
            switch(key){
                case GLFW_KEY_W:
                    m_pos2D[2] -= 5 + SpeedStep;
                    AdvancedCam.Move(FORWARD, SpeedStep);
                    break;

                case GLFW_KEY_S:
                    m_pos2D[2] += 5 + SpeedStep;
                    AdvancedCam.Move(BACK, SpeedStep);
                    break;

                case GLFW_KEY_SPACE:
                    m_pos2D[1] += 5 + SpeedStep;
                    AdvancedCam.Move(UP, SpeedStep);
                    //_look[1] += 5 + SpeedStep;
                    break;

                
                case GLFW_KEY_V:
                    m_pos2D[1] -= 5 + SpeedStep;
                    AdvancedCam.Move(DOWN, SpeedStep);
                    //m_look[1] -= 5 + SpeedStep;
                    break;

                case GLFW_KEY_A:
                    m_pos2D[0] -= 5 + SpeedStep;
                    AdvancedCam.Move(LEFT, SpeedStep);
                    //m_look[0] -= 5 + SpeedStep;
                    break;

                case GLFW_KEY_D:
                    m_pos2D[0] += 5 + SpeedStep;
                    AdvancedCam.Move(RIGHT, SpeedStep);
                    //m_look[0] += 5 + SpeedStep;
                    break;

                case GLFW_KEY_MINUS:
                    m_FOV -= 1.0f;
                    if(m_FOV <= 20.0f){
                        m_FOV = 20.0f;
                    }
                    break;

                case GLFW_KEY_EQUAL:
                    m_FOV += 1.0f;
                    if(m_FOV >= 120.0f){
                        m_FOV = 120.0f;
                    }
                    break;
                
                case GLFW_KEY_L:
                    AdvancedCam.InvertVertical();
                    break;
                case GLFW_KEY_K:
                    AdvancedCam.UnInvertVertical();
                    break;
            }
        }

         if(action == GLFW_REPEAT){
            switch(key){
                case GLFW_KEY_W:
                    m_pos2D[2] -= 5 + SpeedStep;
                    AdvancedCam.Move(FORWARD, SpeedStep);
                    break;

                case GLFW_KEY_S:
                    m_pos2D[2] += 5 + SpeedStep;
                    AdvancedCam.Move(BACK, SpeedStep);
                    break;

                case GLFW_KEY_SPACE:
                    m_pos2D[1] += 5 + SpeedStep;
                    AdvancedCam.Move(UP, SpeedStep);
                    //_look[1] += 5 + SpeedStep;
                    break;

                
                case GLFW_KEY_V:
                    m_pos2D[1] -= 5 + SpeedStep;
                    AdvancedCam.Move(DOWN, SpeedStep);
                    //m_look[1] -= 5 + SpeedStep;
                    break;

                case GLFW_KEY_A:
                    m_pos2D[0] -= 5 + SpeedStep;
                    AdvancedCam.Move(LEFT, SpeedStep);
                    //m_look[0] -= 5 + SpeedStep;
                    break;

                case GLFW_KEY_D:
                    m_pos2D[0] += 5 + SpeedStep;
                    AdvancedCam.Move(RIGHT, SpeedStep);
                    //m_look[0] += 5 + SpeedStep;
                    break;

                case GLFW_KEY_MINUS:
                    m_FOV -= 1.0f;
                    if(m_FOV <= 20.0f){
                        m_FOV = 20.0f;
                    }
                    break;

                case GLFW_KEY_EQUAL:
                    m_FOV += 1.0f;
                    if(m_FOV >= 120.0f){
                        m_FOV = 120.0f;
                    }
                    break;
            }
        }

}

void TestWorld::MouseInput(double xpos, double ypos){

    AdvancedCam.LookRelative(xpos,ypos);    

}



void TestWorld::OnRender(){

        glm::vec3 camPos = AdvancedCam.GetCurrentPos();

        //std::cout << AdvancedCam.GetCurrentLook().x << " | " << AdvancedCam.GetCurrentLook().y << " | " << AdvancedCam.GetCurrentLook().z << std::endl;



        Sun.BindBufferData();
        //Sun.SetColor(1.0f,0.9059f,0.0f, 1.0f);
        Sun.SetLightColor(1.0f, 1.0f, 1.0f);
        Sun.SetColor(1.0f,0.9059f,0.0f, 0.86f);
        Sun.SetPosition(3.0f,5.0f,-3.0f, m_Projection, m_View);
        //Sun.SetLight(Sun.GetLightColor(), Sun.GetPos());
        Sun.Paint();



        Land.BindBufferData();
        Land.SetColor(0.3373f, 0.4902f, 0.2745f, 1.0f);
        Land.SetMaterial(BasicMetalCube);
        Land.SetPosition(0.0f,0.0f,0.0f, m_Projection, m_View);
        Land.SetLight(Sun.GetLightInfo(), Sun.GetPos(), camPos);
        Land.Paint();





        // Dynamic Vertex Buffer!!!!
        //m_VertexBuffer->Bind();
        //Object.BindVertexBuffer();
        //GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, Object.GetVerticiesCount() * sizeof(Vertex), Object.GetVerticies().data()));

         

       //m_IBO->Bind();
        //Object.BindIndexBuffer();
        //GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Object.GetIndicCount(), Object.GetIndices().data()));
        
        // if the offset is not correct it wont draw, will messup a draw
        
        // You have to have a second vertex buffer object set up on the same Vertex array object

        //GLCall(glBufferSubData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vertex), 8 * sizeof(Vertex), vertAlt.data()));

        //Renderer renderer;


        //m_Shader->Bind();
        //GLCall(glUseProgram(m_Shader->GetRenderID()));

        // Keesp the world drawn modle at its origin
        
        
        //m_Shader->SetUniformMat4f("u_MVP", mvp); 
        //m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 0.0f);
        //auto loc = m_Shader->GetUniformLocation("u_MVP");
        //GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]));

        //renderer.Draw(*m_VAO, *m_IBO, *m_Shader);

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

        //

        Object.SetPosition(-2.0f,0.0f,0.0f, m_Projection, m_View);
        Object.SetColor(m_Color3.x, m_Color3.y, m_Color3.z, m_Color3.w);
        Object.SetLight(Sun.GetLightInfo(), Sun.GetPos(), camPos);
        Object.SetMaterial(BasicMetalCube);
        Object.Paint();





        if(m_Effect){
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
        }


        

        //renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        //m_VAO->Bind();
        //m_IBO->Bind();

        //GLCall(glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr));


    }

    void TestWorld::OnImGui(){
        ImGui::Begin("Batch Render");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("This test draws multiple quads in one draw call");
            //ImGui::SliderFloat3("Relative Possiton", &m_pos.x , -600.0f, 600.0f);
            ImGui::DragFloat("FOV", &m_FOV, 1.0f, 10.0f, 150.0f, "%.03f Camera FOV");
            ImGui::ColorEdit4("Color", (float *)&m_Color);
            ImGui::ColorEdit4("Color 2", (float *)&m_Color2);
            ImGui::ColorEdit4("Color 3", (float *)&m_Color3);
            ImGui::Checkbox("Toggle live effect", &m_Effect);
            ImGui::End();

        
    }
