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
        //m_Shader->SetShader("assets/Shaders/MultiImg.shader");

        VertexBufferLayout layout;
        // This defines the layout 
        layout.Push(3,"float");
        layout.Push(2,"float");
        layout.Push(1,"float");
        //layout.Push(1,"float");
        m_VAO->AddBuffer(*m_VertexBuffer,layout); 
}


glm::vec3 SimpleObject::Rotatex(glm::vec3 Start, float Angle){
    float Cosin, Sin;
    glm::vec3 Buffer;
    Cosin = cos(glm::radians(Angle));
    Sin = sin(glm::radians(Angle));

    Buffer.x = (1 * Start.x) + (0 * Start.y) + (0 * Start.z);
    Buffer.y = (0 * Start.x) + (Cosin * Start.y) + (-Sin * Start.z);
    Buffer.z = (0 * Start.x) + (Sin * Start.y) + (Cosin * Start.z); 

    return Buffer;
}

glm::vec3 SimpleObject::Rotatey(glm::vec3 Start, float Angle){
    float Cosin, Sin;
    glm::vec3 Buffer;
    Cosin = cos(glm::radians(Angle));
    Sin = sin(glm::radians(Angle));

    Buffer.x = (Cosin * Start.x) + (0 * Start.y) + (Sin * Start.z);
    Buffer.y = (0 * Start.x) + (1 * Start.y) + (0 * Start.z);
    Buffer.z = (-Sin * Start.x) + (0 * Start.y) + (Cosin * Start.z); 

    return Buffer;
}

glm::vec3 SimpleObject::Rotatez(glm::vec3 Start, float Angle){
    float Cosin, Sin;
    glm::vec3 Buffer;
    Cosin = cos(glm::radians(Angle));
    Sin = sin(glm::radians(Angle));

    Buffer.x = (Cosin * Start.x) + (-Sin * Start.y) + (0 * Start.z);
    Buffer.y = (Sin * Start.x) + (Cosin * Start.y) + (0 * Start.z);
    Buffer.z = (0 * Start.x) + (0 * Start.y) + (1 * Start.z); 

    return Buffer;
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

                case F_NONE:
                        float sizeZ = 1.0f;
                        glm::vec3 TempVec(X,Y,Z);
                        glm::vec3 SqrPt1(-0.5*sizeX, -0.5*sizeY, 0.5);
                        glm::vec3 SqrPt2(0.5*sizeX, -0.5*sizeY, 0.5);
                        glm::vec3 SqrPt3(0.5*sizeX, 0.5*sizeY, 0.5);
                        glm::vec3 SqrPt4(-0.5*sizeX, 0.5*sizeY, 0.5);

                        //std::cout << print()

                        //TempVec = Rotatex(TempVec, 45.0f);
                        //TempVec = Rotatey(TempVec, 45.0f);
                        //SqrPt1 = Rotatex(SqrPt1,-28.0f);
                        //SqrPt2 = Rotatex(SqrPt2,-28.0f);
                        //SqrPt3 = Rotatex(SqrPt3,-28.0f);
                        //SqrPt4 = Rotatex(SqrPt4,-28.0f);



                        SqrPt1 = Rotatex(SqrPt1,45.0f);
                        SqrPt2 = Rotatex(SqrPt2,45.0f);
                        SqrPt3 = Rotatex(SqrPt3,45.0f);
                        SqrPt4 = Rotatex(SqrPt4,45.0f);

                        //SqrPt1 = Rotatez(SqrPt1,90.0f);
                        //SqrPt2 = Rotatez(SqrPt2,90.0f);
                        //SqrPt3 = Rotatez(SqrPt3,90.0f);
                        //SqrPt4 = Rotatez(SqrPt4,90.0f);


                        Temp.Pos = {SqrPt1.x + TempVec.x, SqrPt1.y + TempVec.y, SqrPt1.z + TempVec.z};
                        Temp.TexCord = {tX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);
        

                        Temp.Pos = {SqrPt2.x + TempVec.x, SqrPt2.y + TempVec.y, SqrPt2.z + TempVec.z};
                        Temp.TexCord = {TX, tY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);

                        Temp.Pos = {SqrPt3.x + TempVec.x, SqrPt3.y + TempVec.y, SqrPt3.z + TempVec.z};
                        Temp.TexCord = {TX, TY};
                        Temp.TexID = TextureID;

                        m_Verticies.push_back(Temp);


                        Temp.Pos = {SqrPt4.x + TempVec.x, SqrPt4.y + TempVec.y, SqrPt4.z + TempVec.z};
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

void SimpleObject::CreateCube(float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, float SizeX, float SizeY, float SizeZ, float tX, float tY, float TX, float TY, float TextureID){

        glm::vec3 TempVec(X,Y,Z);
        glm::vec3 CubePt1(-0.5*SizeX, -0.5*SizeY, 0.5* SizeZ);
        glm::vec3 CubePt2(0.5*SizeX, -0.5*SizeY, 0.5 * SizeZ);
        glm::vec3 CubePt3(0.5*SizeX, 0.5*SizeY, 0.5 * SizeZ);
        glm::vec3 CubePt4(-0.5*SizeX, 0.5*SizeY, 0.5 * SizeZ);

        glm::vec3 CubePt5 = Rotatey(CubePt1,180.0f);
        glm::vec3 CubePt6 = Rotatey(CubePt2,180.0f); 
        glm::vec3 CubePt7 = Rotatey(CubePt3,180.0f); 
        glm::vec3 CubePt8 = Rotatey(CubePt4,180.0f);
        
        Vertex Temp;

        //std::cout << print()

        //TempVec = Rotatex(TempVec, 45.0f);
        //TempVec = Rotatey(TempVec, 45.0f);

        CubePt1 = Rotatex(CubePt1, AngleX);
        CubePt2 = Rotatex(CubePt2, AngleX);
        CubePt3 = Rotatex(CubePt3, AngleX);
        CubePt4 = Rotatex(CubePt4, AngleX);
        CubePt5 = Rotatex(CubePt5, AngleX);
        CubePt6 = Rotatex(CubePt6, AngleX);
        CubePt7 = Rotatex(CubePt7, AngleX);
        CubePt8 = Rotatex(CubePt8, AngleX);


        CubePt1 = Rotatey(CubePt1, AngleY);
        CubePt2 = Rotatey(CubePt2, AngleY);
        CubePt3 = Rotatey(CubePt3, AngleY);
        CubePt4 = Rotatey(CubePt4, AngleY);
        CubePt5 = Rotatey(CubePt5, AngleY);
        CubePt6 = Rotatey(CubePt6, AngleY);
        CubePt7 = Rotatey(CubePt7, AngleY);
        CubePt8 = Rotatey(CubePt8, AngleY);


        CubePt1 = Rotatez(CubePt1, AngleZ);
        CubePt2 = Rotatez(CubePt2, AngleZ);
        CubePt3 = Rotatez(CubePt3, AngleZ);
        CubePt4 = Rotatez(CubePt4, AngleZ);
        CubePt5 = Rotatez(CubePt5, AngleZ);
        CubePt6 = Rotatez(CubePt6, AngleZ);
        CubePt7 = Rotatez(CubePt7, AngleZ);
        CubePt8 = Rotatez(CubePt8, AngleZ);




        // North quad
        Temp.Pos = {CubePt1.x + TempVec.x, CubePt1.y + TempVec.y, CubePt1.z + TempVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt2.x + TempVec.x, CubePt2.y + TempVec.y, CubePt2.z + TempVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt3.x + TempVec.x, CubePt3.y + TempVec.y, CubePt3.z + TempVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt4.x + TempVec.x, CubePt4.y + TempVec.y, CubePt4.z + TempVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;

        // South Quad
        Temp.Pos = {CubePt5.x + TempVec.x, CubePt5.y + TempVec.y, CubePt5.z + TempVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt6.x + TempVec.x, CubePt6.y + TempVec.y, CubePt6.z + TempVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt7.x + TempVec.x, CubePt7.y + TempVec.y, CubePt7.z + TempVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt8.x + TempVec.x, CubePt8.y + TempVec.y, CubePt8.z + TempVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;

        // East Quad
        Temp.Pos = {CubePt2.x + TempVec.x, CubePt2.y + TempVec.y, CubePt2.z + TempVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt5.x + TempVec.x, CubePt5.y + TempVec.y, CubePt5.z + TempVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt8.x + TempVec.x, CubePt8.y + TempVec.y, CubePt8.z + TempVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt3.x + TempVec.x, CubePt3.y + TempVec.y, CubePt3.z + TempVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;

        // West Quad
        Temp.Pos = {CubePt6.x + TempVec.x, CubePt6.y + TempVec.y, CubePt6.z + TempVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt1.x + TempVec.x, CubePt1.y + TempVec.y, CubePt1.z + TempVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt4.x + TempVec.x, CubePt4.y + TempVec.y, CubePt4.z + TempVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt7.x + TempVec.x, CubePt7.y + TempVec.y, CubePt7.z + TempVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;

        // "UP" Quad
        Temp.Pos = {CubePt4.x + TempVec.x, CubePt4.y + TempVec.y, CubePt4.z + TempVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt3.x + TempVec.x, CubePt3.y + TempVec.y, CubePt3.z + TempVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt8.x + TempVec.x, CubePt8.y + TempVec.y, CubePt8.z + TempVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt7.x + TempVec.x, CubePt7.y + TempVec.y, CubePt7.z + TempVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;


        // "Down Quad"
        Temp.Pos = {CubePt6.x + TempVec.x, CubePt6.y + TempVec.y, CubePt6.z + TempVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt5.x + TempVec.x, CubePt5.y + TempVec.y, CubePt5.z + TempVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt2.x + TempVec.x, CubePt2.y + TempVec.y, CubePt2.z + TempVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt1.x + TempVec.x, CubePt1.y + TempVec.y, CubePt1.z + TempVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        m_Indices.push_back(0 + m_IndicOffset);
        m_Indices.push_back(1 + m_IndicOffset);
        m_Indices.push_back(2 + m_IndicOffset);

        m_Indices.push_back(2 + m_IndicOffset);
        m_Indices.push_back(3 + m_IndicOffset);
        m_Indices.push_back(0 + m_IndicOffset);

        m_IndicOffset += 4;

        m_UsedQuads += 1;
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
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", MVP); 
}        

void SimpleObject::SetColor(float r, float g, float b, float a){
        m_Shader->Bind();
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