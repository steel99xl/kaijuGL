#pragma once
//#include "VertexBuffer.hpp"
//#include "VertexBufferLayout.hpp"
#include "Engine.hpp"


struct VertexPos{
    float X;
    float Y;
    float Z;
};

struct VertexTexCord{
    float X;
    float Y;
};

struct Vertex{
                VertexPos Pos;
                VertexTexCord TexCord;
                float TexID;
};


class SimpleObject{
    private:
        // Vectors a used so seach instance of an SimpleObject can have 10,000 verticies
        std::vector<Vertex> m_Verticies;
        Vertex *m_Vbuffer = m_Verticies.data();
        int m_VerticiesCount;

        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<IndexBuffer> m_IBO;
        
        //std::unique_ptr<Texture> m_Texture;
        





    public:

        SimpleObject();
        ~SimpleObject();

        // This will be used my the shader to place the "object" in the world
        glm::vec3 m_Pos;


        // Each object can store a texture, and each object will be able to bind a texture 
        GLuint m_Texture;
        // Depending how a quad is set 1 object can use Textures of other objects

        // This function needs to be rewriten to not take "target" from the user
        std::vector<Vertex> Create2dQuad(std::vector<Vertex> *tartget, float X, float Y, float sizeX, float sizeY, float tX, float tY, float TX, float TY, float TextureID);


        // A function

        // Layout what i want functions to do

        // Add Quad to object ( so an object can be multiple quads)
            // Remove Quad from object
        
        // Set Shader for object
        void SetShader();


        // Draw object
        // It is called paint for right now cause Renderer has a .Draw function
        void Paint();




        inline std::vector<Vertex> GetVerticies(){ return m_Verticies;}
        inline int GetVerticiesCount() {return m_VerticiesCount;}


};