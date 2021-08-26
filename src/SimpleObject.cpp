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

        SimpleColision = false;

        std::cout << m_MaxQuadCount << std::endl;

        m_IBO->MakeBuffer(NULL, (m_MaxQuadCount*4)*6 );
        m_VertexBuffer->MakeBuffer(NULL, sizeof(Vertex) * (m_MaxQuadCount*4));
        //m_Shader->SetShader("assets/Shaders/MultiImg.shader");
        // This is just to set the basic rotation for the object in work space
        m_rX = 0.0f;
        m_rY = 1.0f;
        m_rZ = 0.0f;

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

void SimpleObject::Create2dQuad(float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, float sizeX, float sizeY, float Weight, float tX, float tY, float TX, float TY, float TextureID){

        Vertex Temp;




        glm::vec3 TempPosVec(X,Y,Z);
        std::vector<glm::vec3> SqrPt;
        SqrPt.push_back(glm::vec3 (-0.5*sizeX, -0.5*sizeY, 0.0));
        SqrPt.push_back(glm::vec3 (0.5*sizeX, -0.5*sizeY, 0.0));
        SqrPt.push_back(glm::vec3 (0.5*sizeX, 0.5*sizeY, 0.0));
        SqrPt.push_back(glm::vec3 (-0.5*sizeX, 0.5*sizeY, 0.0));

        glm::vec3 TempLightPosVec(0.0f,0.0f,1.0f);


        SqrPt[0] = Rotatex(SqrPt[0],AngleX);
        SqrPt[1] = Rotatex(SqrPt[1],AngleX);
        SqrPt[2] = Rotatex(SqrPt[2],AngleX);
        SqrPt[3] = Rotatex(SqrPt[3],AngleX);
        TempLightPosVec = Rotatex(TempLightPosVec, AngleX);

        SqrPt[0] = Rotatey(SqrPt[0],AngleY);
        SqrPt[1] = Rotatey(SqrPt[1],AngleY);
        SqrPt[2] = Rotatey(SqrPt[2],AngleY);
        SqrPt[3] = Rotatey(SqrPt[3],AngleY);
        TempLightPosVec = Rotatey(TempLightPosVec, AngleY);

        SqrPt[0] = Rotatez(SqrPt[0],AngleZ);
        SqrPt[1] = Rotatez(SqrPt[1],AngleZ);
        SqrPt[2] = Rotatez(SqrPt[2],AngleZ);
        SqrPt[3] = Rotatez(SqrPt[3],AngleZ);
        TempLightPosVec = Rotatez(TempLightPosVec, AngleZ);

        for(int i = 0; i < 4; i++){
                std::cout << i << std::endl;
                Temp.Pos = {SqrPt[i].x + TempPosVec.x, SqrPt[i].y + TempPosVec.y, SqrPt[i].z + TempPosVec.z};
                Temp.NormalPos = {TempLightPosVec.x, TempLightPosVec.y, TempLightPosVec.z};
                switch(i){
                        case 0:
                                Temp.TexCord = {tX, tY};
                                break;
                        case 1:
                                Temp.TexCord = {TX, tY};
                                break;
                        case 2:
                                Temp.TexCord = {TX, TY};
                                break;
                        case 3:
                                Temp.TexCord = {tX, TY};
                                break;
                }
        //        Temp.TexCord = {tX, tY};
                Temp.TexID = TextureID;

                m_Verticies.push_back(Temp);

                if(Weight == 0){
                        m_Weights.push_back(0);
                } else {
                        m_Weights.push_back(Weight/4);
                }
                
        }

        //std::cout << TempLightPosVec[0] << " | " << TempLightPosVec[1] << " | " << TempLightPosVec[2] << std::endl;




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

void SimpleObject::CreateCube(float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, float SizeX, float SizeY, float SizeZ, float Weight, float tX, float tY, float TX, float TY, float TextureID){
        // This hole function needs to be re-writen but for now im just adding this
        for(int i = 0; i < 24; i++){
                m_Weights.push_back(Weight/24);
        }

        glm::vec3 TempPosVec(X,Y,Z);
        std::vector<glm::vec3> CubePt;
        CubePt.push_back(glm::vec3 (-0.5*SizeX, -0.5*SizeY, 0.5* SizeZ));
        CubePt.push_back(glm::vec3 (0.5*SizeX, -0.5*SizeY, 0.5 * SizeZ));
        CubePt.push_back(glm::vec3 (0.5*SizeX, 0.5*SizeY, 0.5 * SizeZ));
        CubePt.push_back(glm::vec3 (-0.5*SizeX, 0.5*SizeY, 0.5 * SizeZ));


        CubePt.push_back(Rotatey(CubePt[0],180.0f));
        CubePt.push_back(Rotatey(CubePt[1],180.0f));
        CubePt.push_back(Rotatey(CubePt[2],180.0f));
        CubePt.push_back(Rotatey(CubePt[3],180.0f));

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

        CubePt[0] = Rotatex(CubePt[0], AngleX);
        CubePt[1] = Rotatex(CubePt[1], AngleX);
        CubePt[2] = Rotatex(CubePt[2], AngleX);
        CubePt[3] = Rotatex(CubePt[3], AngleX);
        CubePt[4] = Rotatex(CubePt[4], AngleX);
        CubePt[5] = Rotatex(CubePt[5], AngleX);
        CubePt[6] = Rotatex(CubePt[6], AngleX);
        CubePt[7] = Rotatex(CubePt[7], AngleX);


        CubePt[0] = Rotatey(CubePt[0], AngleY);
        CubePt[1] = Rotatey(CubePt[1], AngleY);
        CubePt[2] = Rotatey(CubePt[2], AngleY);
        CubePt[3] = Rotatey(CubePt[3], AngleY);
        CubePt[4] = Rotatey(CubePt[4], AngleY);
        CubePt[5] = Rotatey(CubePt[5], AngleY);
        CubePt[6] = Rotatey(CubePt[6], AngleY);
        CubePt[7] = Rotatey(CubePt[7], AngleY);


        CubePt[0] = Rotatez(CubePt[0], AngleZ);
        CubePt[1] = Rotatez(CubePt[1], AngleZ);
        CubePt[2] = Rotatez(CubePt[2], AngleZ);
        CubePt[3] = Rotatez(CubePt[3], AngleZ);
        CubePt[4] = Rotatez(CubePt[4], AngleZ);
        CubePt[5] = Rotatez(CubePt[5], AngleZ);
        CubePt[6] = Rotatez(CubePt[6], AngleZ);
        CubePt[7] = Rotatez(CubePt[7], AngleZ);


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
        Temp.Pos = {CubePt[0].x + TempPosVec.x, CubePt[0].y + TempPosVec.y, CubePt[0].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[1].x + TempPosVec.x, CubePt[1].y + TempPosVec.y, CubePt[1].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt[2].x + TempPosVec.x, CubePt[2].y + TempPosVec.y, CubePt[2].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightNorth.x, CubeLightNorth.y, CubeLightNorth.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[3].x + TempPosVec.x, CubePt[3].y + TempPosVec.y, CubePt[3].z + TempPosVec.z};
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
        Temp.Pos = {CubePt[4].x + TempPosVec.x, CubePt[4].y + TempPosVec.y, CubePt[4].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[5].x + TempPosVec.x, CubePt[5].y + TempPosVec.y, CubePt[5].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt[6].x + TempPosVec.x, CubePt[6].y + TempPosVec.y, CubePt[6].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightSouth.x, CubeLightSouth.y, CubeLightSouth.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[7].x + TempPosVec.x, CubePt[7].y + TempPosVec.y, CubePt[7].z + TempPosVec.z};
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
        Temp.Pos = {CubePt[1].x + TempPosVec.x, CubePt[1].y + TempPosVec.y, CubePt[1].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[4].x + TempPosVec.x, CubePt[4].y + TempPosVec.y, CubePt[4].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt[7].x + TempPosVec.x, CubePt[7].y + TempPosVec.y, CubePt[7].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightEast.x, CubeLightEast.y, CubeLightEast.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[2].x + TempPosVec.x, CubePt[2].y + TempPosVec.y, CubePt[2].z + TempPosVec.z};
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
        Temp.Pos = {CubePt[5].x + TempPosVec.x, CubePt[5].y + TempPosVec.y, CubePt[5].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[0].x + TempPosVec.x, CubePt[0].y + TempPosVec.y, CubePt[0].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt[3].x + TempPosVec.x, CubePt[3].y + TempPosVec.y, CubePt[3].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightWest.x, CubeLightWest.y, CubeLightWest.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[6].x + TempPosVec.x, CubePt[6].y + TempPosVec.y, CubePt[6].z + TempPosVec.z};
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
        Temp.Pos = {CubePt[3].x + TempPosVec.x, CubePt[3].y + TempPosVec.y, CubePt[3].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[2].x + TempPosVec.x, CubePt[2].y + TempPosVec.y, CubePt[2].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt[7].x + TempPosVec.x, CubePt[7].y + TempPosVec.y, CubePt[7].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightUp.x, CubeLightUp.y, CubeLightUp.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[6].x + TempPosVec.x, CubePt[6].y + TempPosVec.y, CubePt[6].z + TempPosVec.z};
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
        Temp.Pos = {CubePt[5].x + TempPosVec.x, CubePt[5].y + TempPosVec.y, CubePt[5].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[4].x + TempPosVec.x, CubePt[4].y + TempPosVec.y, CubePt[4].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);

        Temp.Pos = {CubePt[1].x + TempPosVec.x, CubePt[1].y + TempPosVec.y, CubePt[1].z + TempPosVec.z};
        Temp.NormalPos = {CubeLightDown.x, CubeLightDown.y, CubeLightDown.z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        m_Verticies.push_back(Temp);


        Temp.Pos = {CubePt[0].x + TempPosVec.x, CubePt[0].y + TempPosVec.y, CubePt[0].z + TempPosVec.z};
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

void SimpleObject::SetMaterial(SimpleMaterialInfo &Material){
    m_Shader->Bind();

    m_Shader->SetUniform3f("u_Material.ambient", Material.ambient.R, Material.ambient.G, Material.ambient.B);
    m_Shader->SetUniform3f("u_Material.diffuse", Material.diffuse.R, Material.diffuse.G, Material.diffuse.B);
    m_Shader->SetUniform3f("u_Material.specular", Material.specular.R, Material.specular.G, Material.specular.B);
    m_Shader->SetUniform1f("u_Material.shininess", Material.shininess);
}

void SimpleObject::MakeMaterial(float AmbientR, float AmbientG, float AmbientB, float DiffuseR, float DiffuseG, float DiffuseB, float SpecularR, float SpecularG, float SpecularB, float Shininess){
        m_Material.ambient.R = AmbientR;
        m_Material.ambient.G = AmbientG;
        m_Material.ambient.B = AmbientB;

        m_Material.diffuse.R = DiffuseR;
        m_Material.diffuse.G = DiffuseG;
        m_Material.diffuse.B = DiffuseB;

        m_Material.specular.R = SpecularR;
        m_Material.specular.G = SpecularG;
        m_Material.specular.B = SpecularB;

        m_Material.shininess = Shininess;
}

void SimpleObject::MakeLight(float AmbientR, float AmbientG, float AmbientB, float DiffuseR, float DiffuseG, float DiffuseB, float SpecularR, float SpecularG, float SpecularB, float LightDirX, float LightDirY, float LightDirZ, float AngleSize, float Linear, float Quadratic){
        m_Light.ambient.R = AmbientR;
        m_Light.ambient.G = AmbientG;
        m_Light.ambient.B = AmbientB;

        m_Light.diffuse.R = DiffuseR;
        m_Light.diffuse.G = DiffuseG;
        m_Light.diffuse.B = DiffuseB;

        m_Light.specular.R = SpecularR;
        m_Light.specular.G = SpecularG;
        m_Light.specular.B = SpecularB;

        m_Light.Angle = glm::cos(glm::radians(AngleSize));

        m_Light.Const = 1.0f;
        m_Light.Linear = Linear;
        m_Light.Quadratic = Quadratic;

}

void SimpleObject::SetLight(SimpleLightInfo lightInfo, glm::vec3 lightPos, glm::vec3 camPos){
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_Light.position", lightPos.x, lightPos.y, lightPos.z);
        m_Shader->SetUniform3f("u_Light.lightPoint", lightInfo.lightDir.X, lightInfo.lightDir.Y, lightInfo.lightDir.Z);
        m_Shader->SetUniform3f("u_Light.ambient", lightInfo.ambient.R, lightInfo.ambient.G, lightInfo.ambient.B);
        m_Shader->SetUniform3f("u_Light.diffuse", lightInfo.diffuse.R, lightInfo.diffuse.G, lightInfo.diffuse.B);
        m_Shader->SetUniform3f("u_Light.specular", lightInfo.specular.R, lightInfo.specular.G, lightInfo.specular.B);
        m_Shader->SetUniform1f("u_Light.Asize", glm::cos(glm::radians(lightInfo.Angle)));
        m_Shader->SetUniform1f("u_Light.constant", lightInfo.Const);
        m_Shader->SetUniform1f("u_Light.linear", lightInfo.Linear);
        m_Shader->SetUniform1f("u_Light.quadratic", lightInfo.Quadratic);
        m_Shader->SetUniform3f("u_camPos", camPos.x, camPos.y, camPos.z);

}

bool SimpleObject::AABBColision(std::vector<Vertex> ObjectAVerticies, int ObjectAVerticiesCount, glm::vec3 ObjectAPos, std::vector<Vertex> ObjectBVerticies, int ObjectBVerticiesCount, glm::vec3 ObjectBPos){
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

    int b,d;
    for(int a = 0; a < MinMaxACount; a += 2){
        b = (a + 1) % MinMaxACount;
        
        for( int c = 0; c < MinMaxBCount; c += 2){
            d = (c + 1) % MinMaxBCount;
            
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
        }
    }


    return false;

}

void SimpleObject::AddTexture(const std::string &filePath, unsigned int slot){
        //m_Texture.LoadTexture(filePath, slot);

        //m_Texture.Bind(slot);
}

void SimpleObject::SetTexture(unsigned int Texture, const std::string &UniformName){
        m_Shader->Bind();
        m_Shader->SetUniform1i(UniformName, Texture);
}

void SimpleObject::SetFloatUniform(const std::string &UniformName, float data){
        m_Shader->Bind();
        m_Shader->SetUniform1f(UniformName, data);
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
