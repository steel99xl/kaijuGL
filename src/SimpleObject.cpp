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
        // Position Data;
        layout.Push(3,"float");
        // Normolized Positon Data;
        layout.Push(3,"float");
        // Texure Map Data;
        layout.Push(2,"float");
        //Texture ID
        layout.Push(1,"float");
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

void SimpleObject::Create2dQuad(float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, float sizeX, float sizeY, float tX, float tY, float TX, float TY, float TextureID){

        Vertex Temp;

        glm::vec3 TempPosVec(X,Y,Z);
        glm::vec3 SqrPt1(-0.5*sizeX, -0.5*sizeY, 0.0);
        glm::vec3 SqrPt2(0.5*sizeX, -0.5*sizeY, 0.0);
        glm::vec3 SqrPt3(0.5*sizeX, 0.5*sizeY, 0.0);
        glm::vec3 SqrPt4(-0.5*sizeX, 0.5*sizeY, 0.0);

        glm::vec3 TempLightPosVec(0.0f,0.0f,1.0f);


        SqrPt1 = Rotatex(SqrPt1,AngleX);
        SqrPt2 = Rotatex(SqrPt2,AngleX);
        SqrPt3 = Rotatex(SqrPt3,AngleX);
        SqrPt4 = Rotatex(SqrPt4,AngleX);
        TempLightPosVec = Rotatex(TempLightPosVec, AngleX);

        SqrPt1 = Rotatey(SqrPt1,AngleY);
        SqrPt2 = Rotatey(SqrPt2,AngleY);
        SqrPt3 = Rotatey(SqrPt3,AngleY);
        SqrPt4 = Rotatey(SqrPt4,AngleY);
        TempLightPosVec = Rotatey(TempLightPosVec, AngleY);

        SqrPt1 = Rotatez(SqrPt1,AngleZ);
        SqrPt2 = Rotatez(SqrPt2,AngleZ);
        SqrPt3 = Rotatez(SqrPt3,AngleZ);
        SqrPt4 = Rotatez(SqrPt4,AngleZ);
        TempLightPosVec = Rotatez(TempLightPosVec, AngleZ);



        Temp.Pos = {SqrPt1.x + TempPosVec.x, SqrPt1.y + TempPosVec.y, SqrPt1.z + TempPosVec.z};
        Temp.NormalPos = {TempLightPosVec.x, TempLightPosVec.y, TempLightPosVec.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {SqrPt2.x + TempPosVec.x, SqrPt2.y + TempPosVec.y, SqrPt2.z + TempPosVec.z};
        Temp.NormalPos = {TempLightPosVec.x, TempLightPosVec.y, TempLightPosVec.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {SqrPt3.x + TempPosVec.x, SqrPt3.y + TempPosVec.y, SqrPt3.z + TempPosVec.z};
        Temp.NormalPos = {TempLightPosVec.x, TempLightPosVec.y, TempLightPosVec.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {SqrPt4.x + TempPosVec.x, SqrPt4.y + TempPosVec.y, SqrPt4.z + TempPosVec.z};
        Temp.NormalPos = {TempLightPosVec.x, TempLightPosVec.y, TempLightPosVec.z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        

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

        glm::vec3 TempPosVec(X,Y,Z);
        glm::vec3 CubePt1(-0.5*SizeX, -0.5*SizeY, 0.5* SizeZ);
        glm::vec3 CubePt2(0.5*SizeX, -0.5*SizeY, 0.5 * SizeZ);
        glm::vec3 CubePt3(0.5*SizeX, 0.5*SizeY, 0.5 * SizeZ);
        glm::vec3 CubePt4(-0.5*SizeX, 0.5*SizeY, 0.5 * SizeZ);
        

        glm::vec3 CubePt5 = Rotatey(CubePt1,180.0f);
        glm::vec3 CubePt6 = Rotatey(CubePt2,180.0f); 
        glm::vec3 CubePt7 = Rotatey(CubePt3,180.0f); 
        glm::vec3 CubePt8 = Rotatey(CubePt4,180.0f);
        
        Vertex Temp;


        // This shoudl be improved so its calculated at the face
        glm::vec3 CubeLightNorth(0.0f,0.0f,1.0f); // this is replicated in each vector for its face
        glm::vec3 CubeLightSouth(0.0f,0.0f,-1.0f); // this is replicated in each vector for its face
        glm::vec3 CubeLightEast(1.0f,0.0f,0.0f); // this is replicated in each vector for its face
        glm::vec3 CubeLightWest(-1.0f,0.0f,0.0f); // this is replicated in each vector for its face
        glm::vec3 CubeLightUp(0.0f,1.0f,0.0f); // this is replicated in each vector for its face
        glm::vec3 CubeLightDown(0.0f,-1.0f,0.0f); // this is replicated in each vector for its face

        //std::cout << print()

        //TempPosVec = Rotatex(TempPosVec, 45.0f);
        //TempPosVec = Rotatey(TempPosVec, 45.0f);

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


        CubeLightNorth = Rotatex(CubeLightNorth, AngleX);
        CubeLightSouth = Rotatex(CubeLightSouth, AngleX);
        CubeLightEast = Rotatex(CubeLightEast, AngleX);
        CubeLightWest = Rotatex(CubeLightWest, AngleX);
        CubeLightUp = Rotatex(CubeLightUp, AngleX);
        CubeLightDown = Rotatex(CubeLightDown, AngleX);


        CubeLightNorth = Rotatey(CubeLightNorth, AngleY);
        CubeLightSouth = Rotatey(CubeLightSouth, AngleY);
        CubeLightEast = Rotatey(CubeLightEast, AngleY);
        CubeLightWest = Rotatey(CubeLightWest, AngleY);
        CubeLightUp = Rotatey(CubeLightUp, AngleY);
        CubeLightDown = Rotatey(CubeLightDown, AngleY);


        CubeLightNorth = Rotatez(CubeLightNorth, AngleZ);
        CubeLightSouth = Rotatez(CubeLightSouth, AngleZ);
        CubeLightEast = Rotatez(CubeLightEast, AngleZ);
        CubeLightWest = Rotatez(CubeLightWest, AngleZ);
        CubeLightUp = Rotatez(CubeLightUp, AngleZ);
        CubeLightDown = Rotatez(CubeLightDown, AngleZ);
        




        // North quad
        Temp.Pos = {CubePt1.x + TempPosVec.x, CubePt1.y + TempPosVec.y, CubePt1.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt2.x + TempPosVec.x, CubePt2.y + TempPosVec.y, CubePt2.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt3.x + TempPosVec.x, CubePt3.y + TempPosVec.y, CubePt3.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt4.x + TempPosVec.x, CubePt4.y + TempPosVec.y, CubePt4.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
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
        Temp.Pos = {CubePt5.x + TempPosVec.x, CubePt5.y + TempPosVec.y, CubePt5.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt6.x + TempPosVec.x, CubePt6.y + TempPosVec.y, CubePt6.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt7.x + TempPosVec.x, CubePt7.y + TempPosVec.y, CubePt7.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt8.x + TempPosVec.x, CubePt8.y + TempPosVec.y, CubePt8.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
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
        Temp.Pos = {CubePt2.x + TempPosVec.x, CubePt2.y + TempPosVec.y, CubePt2.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt5.x + TempPosVec.x, CubePt5.y + TempPosVec.y, CubePt5.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt8.x + TempPosVec.x, CubePt8.y + TempPosVec.y, CubePt8.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt3.x + TempPosVec.x, CubePt3.y + TempPosVec.y, CubePt3.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
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
        Temp.Pos = {CubePt6.x + TempPosVec.x, CubePt6.y + TempPosVec.y, CubePt6.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt1.x + TempPosVec.x, CubePt1.y + TempPosVec.y, CubePt1.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt4.x + TempPosVec.x, CubePt4.y + TempPosVec.y, CubePt4.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt7.x + TempPosVec.x, CubePt7.y + TempPosVec.y, CubePt7.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
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
        Temp.Pos = {CubePt4.x + TempPosVec.x, CubePt4.y + TempPosVec.y, CubePt4.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt3.x + TempPosVec.x, CubePt3.y + TempPosVec.y, CubePt3.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt8.x + TempPosVec.x, CubePt8.y + TempPosVec.y, CubePt8.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt7.x + TempPosVec.x, CubePt7.y + TempPosVec.y, CubePt7.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
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
        Temp.Pos = {CubePt6.x + TempPosVec.x, CubePt6.y + TempPosVec.y, CubePt6.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);
        

        Temp.Pos = {CubePt5.x + TempPosVec.x, CubePt5.y + TempPosVec.y, CubePt5.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt2.x + TempPosVec.x, CubePt2.y + TempPosVec.y, CubePt2.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt1.x + TempPosVec.x, CubePt1.y + TempPosVec.y, CubePt1.z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
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
        //m_Shader->SetUniform1i("u_Texture1", 2);
        //m_Shader->SetUniform1i("u_Texture2", 3);


}


void SimpleObject::SetPosition(float X, float Y, float Z, glm::mat4 &Projection, glm::mat4 &View){
        m_X = X;
        m_Y = Y;
        m_Z = Z;
        glm::mat4 ModlePos = glm::translate(glm::mat4(1.0f), glm::vec3(X,Y,Z));
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("Modle", ModlePos);
        m_Shader->SetUniformMat4f("View", View);
        m_Shader->SetUniformMat4f("Projection", Projection); 
}        

void SimpleObject::SetColor(float r, float g, float b, float a){
        m_R = r;
        m_G = g;
        m_B = b;
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", r, g, b, a);
}

void SimpleObject::SetLight(glm::vec3 lightColor, glm::vec3 lightPos, glm::vec3 camPos){
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_lightColor", lightColor.x, lightColor.y, lightColor.z);
        m_Shader->SetUniform3f("u_lightPos", lightPos.x, lightPos.y, lightPos.z);
        m_Shader->SetUniform3f("u_camPos", camPos.x, camPos.y, camPos.z);
        
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