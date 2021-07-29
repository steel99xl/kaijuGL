#include "SimpleObject.hpp"

SimpleObject::SimpleObject(int MaxQuads){
        m_MaxQuadCount = MaxQuads;
        m_VerticiesMax = MaxQuads * 4;
        m_IndicOffset = 0;


      

        //std::cout << "really.. " << std::endl;
       
       



       
          

}

SimpleObject::~SimpleObject(){

}

void SimpleObject::Setup(){
        //
        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>();
        m_Shader = std::make_unique<Shader>();
        m_IBO = std::make_unique<IndexBuffer>();
        //m_Texture = std::make_unique<Texture>();

        std::cout << m_MaxQuadCount << std::endl;

        m_IBO->MakeBuffer(NULL, (m_MaxQuadCount*4)*6 );
        m_VertexBuffer->MakeBuffer(NULL, sizeof(Vertex) * (m_MaxQuadCount*4));
        m_Shader->SetShader("assets/Shaders/MultiImg.shader");

        VertexBufferLayout layout;
        // This defines the layout 
        layout.Push(3,"float");
        layout.Push(2,"float");
        layout.Push(1,"float");
        //layout.Push(1,"float");
        m_VAO->AddBuffer(*m_VertexBuffer,layout); 
}

void SimpleObject::Create2dQuad(float X, float Y, float Z, FaceDir Direction, float sizeX, float sizeY, float tX, float tY, float TX, float TY, float TextureID){

        Vertex Temp;

        switch(Direction){
                case F_UP:
                        
                        Temp.Pos = {(0.5f *sizeX) + X, Z, (-0.5f * sizeY) + Y};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {(-0.5f*sizeX) + X, Z, (-0.5f * sizeY) + Y};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        
                        Temp.Pos = { (-0.5f * sizeX) + X, Z, (0.5f * sizeY)+ Y};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);


                        Temp.Pos = { (0.5f * sizeX) +X , Z, (0.5f * sizeY) + Y};
                        Temp.TexCord = {tX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        break;
                case F_DOWN:

                        Temp.Pos = {(-0.5f*sizeX) + X, Z, (-0.5f * sizeY) + Y};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {(0.5f *sizeX) + X, Z, (-0.5f * sizeY) + Y};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        Temp.Pos = { (0.5f * sizeX) +X , Z, (0.5f * sizeY) + Y};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);


                        Temp.Pos = { (-0.5f * sizeX) + X, Z, (0.5f * sizeY)+ Y};
                        Temp.TexCord = {tX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        break;


                case F_NORTH:

                        Temp.Pos = {(-0.5f*sizeX) + X, (-0.5f * sizeY) + Y, Z};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {(0.5f *sizeX) + X, (-0.5f * sizeY) + Y, Z};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        Temp.Pos = { (0.5f * sizeX) +X , (0.5f * sizeY) + Y, Z};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);


                        Temp.Pos = { (-0.5f * sizeX) + X, (0.5f * sizeY)+ Y, Z};
                        Temp.TexCord = {tX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        break;

                
                case F_SOUTH:
                        Temp.Pos = {(0.5f *sizeX) + X, (-0.5f * sizeY) + Y, Z};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {(-0.5f*sizeX) + X, (-0.5f * sizeY) + Y, Z};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        
                        Temp.Pos = { (-0.5f * sizeX) + X, (0.5f * sizeY)+ Y, Z};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        Temp.Pos = { (0.5f * sizeX) +X , (0.5f * sizeY) + Y, Z};
                        Temp.TexCord = {tX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        break;


                case F_EAST:
                        Temp.Pos = {Z , (-0.5f * sizeY) + Y, (0.5f *sizeX) + X};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {Z, (-0.5f * sizeY) + Y, (-0.5f*sizeX) + X};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        Temp.Pos = { Z, (0.5f * sizeY)+ Y, (-0.5f * sizeX) +X};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);


                        Temp.Pos = { Z , (0.5f * sizeY) + Y, (0.5f * sizeX) +X};
                        Temp.TexCord = {tX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        break;
                case F_WEST:

                        Temp.Pos = {Z, (-0.5f * sizeY) + Y, (-0.5f*sizeX) + X};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {Z , (-0.5f * sizeY) + Y, (0.5f *sizeX) + X};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        Temp.Pos = { Z , (0.5f * sizeY) + Y, (0.5f * sizeX) +X};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);


                        Temp.Pos = { Z, (0.5f * sizeY)+ Y, (-0.5f * sizeX) +X};
                        Temp.TexCord = {tX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        break;
        }

        

        std::cout << "Texture ID " << TextureID << std::endl;
        




        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);
        

        //indices[i + 3] =  2 + offset;
        //indices[i + 4] =  3 + offset;
        //indices[i + 5] =  0 + offset; 

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;

        //m_IndicCount += 6;

}


void SimpleObject::Paint(){
        Renderer renderer;

        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
}


void SimpleObject::SetShader(const std::string &filePath){
        m_Shader->SetShader(filePath);
        
        // this is just for testing
        //int samplers[] = {0, 1, 2};
        int samplers[] = {0};
        //m_Shader->SetUniform1iv("u_Textures", 3, samplers);
        //m_Shader->SetUniform1iv("u_Textures", 3, samplers);
        //m_Shader->SetUniform1i("u_Texture", 0);
        m_Shader->SetUniform1i("u_Texture0", 1);
        //                      u_Texture0
        m_Shader->SetUniform1i("u_Texture1", 1);
        m_Shader->SetUniform1i("u_Texture2", 2);


}


void SimpleObject::SetPosition(glm::mat4 MVP){
        m_Shader->SetUniformMat4f("u_MVP", MVP); 
}        

void SimpleObject::SetColor(float r, float g, float b, float a){
        m_Shader->SetUniform4f("u_Color", r, g, b, a);
}



void SimpleObject::AddTexture(const std::string &filePath, unsigned int slot){
        //m_Texture.LoadTexture(filePath, slot);

        //m_Texture.Bind(slot);
}


void SimpleObject::BindBufferData(){ 
        m_VertexBuffer->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, (m_UsedQuads*4) * sizeof(Vertex), m_Verticies.data());

        m_IBO->Bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, (m_UsedQuads*4)*6, m_Indices.data());
}

void SimpleObject::BindVertexBuffer(){
        m_VertexBuffer->Bind();
}

void SimpleObject::BindIndexBuffer(){
        m_IBO->Bind();
}