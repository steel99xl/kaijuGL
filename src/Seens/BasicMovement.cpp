#include "BasicMovement.hpp"

#include <GLFW/glfw3.h>





   

    

TestWorld::TestWorld() : m_running(false), m_Effect(false), m_Width(800), m_Height(680){
// This is just to set some basic vars

}

TestWorld::~TestWorld(){

}


void TestWorld::Setup(){

    AdvancedCam.SetHorizontalSensitivity(0.1f);
    AdvancedCam.SetVerticalSensitivity(0.08f);
    AdvancedCam.InvertVertical();


    const unsigned int MaxQuadCount = 10100;
    const unsigned int MaxVertexCount = MaxQuadCount * 4;
    const unsigned int MaxIndexCount = MaxQuadCount * 6;

      
    unsigned int indices[MaxIndexCount];
    int offset = 0;

    for (int i = 0; i < MaxIndexCount; i += 6){

        indices[i + 0] =  0 + offset;
        indices[i + 1] =  1 + offset;
        indices[i + 2] =  2 + offset;

        indices[i + 3] =  2 + offset;
        indices[i + 4] =  3 + offset;
        indices[i + 5] =  0 + offset; 

        offset += 4;

    }


        //Take info and put it in a vertex
    m_VAO = std::make_unique<VertexArray>();
    m_IBO = std::make_unique<IndexBuffer>(indices,sizeof(indices));
    std::cout << "set index buffer" << std::endl;
    m_Shader = std::make_unique<Shader>("assets/Shaders/MultiImg.shader");
    m_Texture = std::make_unique<Texture>("assets/Textures/Box.png");


    Tex1 = m_Texture->LoadTexture("assets/Textures/Box.png");
    Tex2 = m_Texture->LoadTexture("assets/Textures/Logo.jpeg");
    Tex3 = m_Texture->LoadTexture("assets/Textures/OtherBox.png");

        //std::cout << "bound texture 1" << std::endl;
    GLCall(glActiveTexture(GL_TEXTURE0 + 0));
    GLCall(glBindTexture(GL_TEXTURE_2D, Tex1));

        //std::cout << "bound texture 2 " << std::endl;
    GLCall(glActiveTexture(GL_TEXTURE0 + 1));
    GLCall(glBindTexture(GL_TEXTURE_2D, Tex2));

    GLCall(glActiveTexture(GL_TEXTURE0 + 2));
    GLCall(glBindTexture(GL_TEXTURE_2D, Tex3));

    
    // This sets the max amout of things in the vertex buffer
    m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * MaxVertexCount);



        //std::cout << m_IBO->Unquie() << std::endl;

    VertexBufferLayout layout;
        // This defines the layout 
    layout.Push(3,"float");
    layout.Push(2,"float");
    layout.Push(1,"float");
        //layout.Push(1,"float");
    m_VAO->AddBuffer(*m_VertexBuffer,layout);    

        //std::cout << "Seting shader program" << std::endl;

        //IndexBuffer ibo(SqIndex,6);
        //GLCall(glUseProgram(m_Shader->GetRenderID()));

    m_Shader->Bind();

    std::cout << "Shader set" << std::endl;

        //auto loc = m_Shader->GetUniformLocation("u_Textures");
    int samplers[3] = {0 ,1,2};
        //GLsizei size = 2;
        //GLCall(glUniform1iv(loc, size, samplers));
    m_Shader->SetUniform1iv("u_Textures", 3, samplers);

        //Shader shader("assets/Shaders/ImgLoad.shader");
        //m_Shader->Bind();

     // This has to match the bound texture buffer

        //m_Shader->SetUniform1i("u_Texture", 0);
    m_FOV = 75.0f;
        

   

    //glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0));

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


void TestWorld::OnUpdate(float deltaTime){
        glfwPollEvents();
        m_DeltaTime = deltaTime;

        // This is only going here just so i have a clear spot for it
        //m_View = glm::lookAt(
        //m_pos, // Camera is at (4,3,3), in World Space
        //m_look, // and looks at the origin
        //glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        //);
    }

void TestWorld::KeyInput(int key, int scancode, int action, int mods){
        float SpeedStep = 1.78f;

        if(mods == 1){
            //SpeedStep = 12.51f *m_DeltaTime;
            SpeedStep = 50.0f;
        }

        std::cout << key << std::endl;

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



void TestWorld::OnRender(int Width, int Height, float ScaleFactor){



        AdvancedCam.Update(m_DeltaTime, (float)Width/Height, m_FOV);


      

        //Keeping track of used verticies seperatly allows the buffer to be bigger than needed and not cause rendering errors

        std::vector<Vertex> verticies;
        int VertexCount = 0;

        Vertex *test = verticies.data();

        Object.Create2dQuad(&verticies, 200.0f,200.0f,50.0f, 150.0f, 150.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        Object.Create2dQuad(&verticies, 10.0f,10.0f,20.0f, 120.0f, 130.0f, 0.0f,0.0f , 1.0f, 1.0f, 1.0f);
        VertexCount += 8;
        //test = CreateQuad(test, 200.0f, 200.0f, 10.0f, 10.0f, 1.0f);


       int QuadCount = 50; 

        for(int y  = 0; y < QuadCount; y+= 1){
            
            for(int x = 0; x < QuadCount; x+= 1)
            {
                //buffer = CreateQuad(buffer, (float)x*1.0f, (float)y*1.0f , 1.0f, 1.0f, (float)((x+y)%2));
                Object.Create2dQuad(&verticies, (float) x*1.0f,(float)y*1.0f,0.0f,  1.0f, 1.0f, 0.0f,0.0f, 1.0f, 1.0f, (float)((x+y)%2));
                VertexCount += 4;
            }
            
        }

        //std::cout << vertices.size() << std::endl;

        //vertices.data() = buffer;



        
        //buffer = CreateQuad(buffer, 0.0f,0.0f, 200.0f, 0.0f);
        //buffer = CreateQuad(buffer, m_QuadPos2[0], m_QuadPos2[1], m_QuadPos2[2],m_QuadPos2[2], 2.0f);
        Object.Create2dQuad(&verticies, m_QuadPos2[0],m_QuadPos2[1],m_QuadPos2[2],  10.0f, 10.0f, 0.0f,0.0f, 1.0f, 1.0f, 2.0f);
        VertexCount += 4;

        //buffer = CreateQuad(buffer, 200.0f, 200.0f, 150.0f, 175.0f, 1.0f);
        //VertexCount += 4;

        //std::cout << vertices.data() << std::endl;

        //buffer = CreateQuad(buffer, 0.0f,201.0f, 20.0f, 1.0f);
        //buffer = CreateQuad(buffer, 0.0f,221.0f, 20.0f, 0.0f);
        //buffer = CreateQuad(buffer, 0.0f,241.0f, 20.0f, 1.0f);
        //buffer = CreateQuad(buffer, 0.0f,261.0f, 20.0f, 0.0f);


        ///Vertex2D poss[8];
        //memcpy(poss, q0.data(), q0.size() * sizeof(Vertex2D));
        //memcpy(poss + q0.size(), q1.data(), q1.size() * sizeof(Vertex2D));

        // Dynamic Vertex Buffer!!!!
        m_VertexBuffer->Bind();
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, VertexCount * sizeof(Vertex), verticies.data()));

        // if the offset is not correct it wont draw, will messup a draw
        
        // You have to have a second vertex buffer object set up on the same Vertex array object

        //GLCall(glBufferSubData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vertex), 8 * sizeof(Vertex), vertAlt.data()));

        Renderer renderer;



        //m_Shader->Bind();
        //GLCall(glUseProgram(m_Shader->GetRenderID()));

        // Keesp the world drawn modle at its origin
        glm::mat4 modle = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
        glm::mat4 mvp = AdvancedCam.GetProj() * AdvancedCam.GetView() * modle;

        //auto loc = m_Shader->GetUniformLocation("u_MVP");
        //GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]));

        m_Shader->SetUniformMat4f("u_MVP", mvp);

        if(m_Effect){
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
        }

        

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);


        

        //renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        //m_VAO->Bind();
        //m_IBO->Bind();

        //GLCall(glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr));


    }

    void TestWorld::OnImGui(){
        ImGui::Begin("Batch Render");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("This test draws multiple quads in one draw call");
            //ImGui::SliderFloat3("Relative Possiton", &m_pos.x , -600.0f, 600.0f);
            ImGui::DragFloat("FOV", &m_FOV, 1.0f, 10.0f, 200.0f, "%.03f Camera FOV");
            ImGui::DragFloat3("Second square poss and size", m_QuadPos2, 1.0f);
            ImGui::Checkbox("Toggle live effect", &m_Effect);
            ImGui::End();

        
    }
