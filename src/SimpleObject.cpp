#include "SimpleObject.hpp"

SimpleObject::SimpleObject(int MaxQuads){
        m_MaxQuadCount = MaxQuads;
        m_VerticiesMax = MaxQuads * 4;
        m_IndicOffset = 0;

        //m_VertexBuffer.MakeBuffer(nullptr, sizeof(Vertex) * m_IndicMax);
 

}

SimpleObject::~SimpleObject(){

}

void SimpleObject::Create2dQuad(float X, float Y, float Z, float sizeX, float sizeY, float tX, float tY, float TX, float TY, float TextureID){

        Vertex Temp;
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