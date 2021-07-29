#pragma once
//#include "VertexBuffer.hpp"
//#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
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

enum FaceDir{F_UP, F_DOWN, F_EAST,F_WEST, F_NORTH,F_SOUTH};


class SimpleObject{
    private:
        int m_MaxQuadCount;

        // Vectors a used so seach instance of an SimpleObject can have (m_MaxQuads * 4) verticies and (m_MaxQuads * 6) 
        std::vector<Vertex> m_Verticies;
        unsigned int m_VerticiesMax;

        std::vector<unsigned int> m_Indices;
        unsigned int m_IndicMax;
        unsigned int m_IndicOffset;

        int m_MaxQuads, m_UsedQuads;

        std::unique_ptr<VertexArray> m_VAO;

        //Astd::unique_ptr<Texture> m_Texture;
        //Texture m_Texture;

        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<IndexBuffer> m_IBO;







    public:

        SimpleObject(int MaxQuads = 10000);
        ~SimpleObject();

        void Setup();

        // This will be used my the shader to place the "object" in the world
        glm::vec3 m_Pos;


        // Each object can store a texture, and each object will be able to bind a texture 
        // Depending how a quad is set 1 object can use Textures of other objects

        // This function needs to be rewriten to not take "target" from the user
        // Should append to the indexbuffer
        void Create2dQuad(float X,float Y,float Z, FaceDir Direction, float sizeX, float sizeY, float tX, float tY, float TX, float TY, float TextureID);

        

        // A function that takes a vector of vertexes and appends it to this objects (so one object can draw all objects like it)
        // A function that takes in a vector of Vertex and replaces the current vector of Vertex
        // in each of these it should recalculate the indexbuffe object


        // Layout what i want functions to do

        // Add Quad to object ( so an object can be multiple quads)
            // Remove Quad from object
            // This would have to go back and remove stuff from the index buffer
        
        // Set Shader for object
        void SetShader();


        // Draw object
        // It is called paint for right now cause Renderer has a .Draw function
        // if all things drawn only read data, then the drawing could me moved to a seperate thread
        void Paint();




        inline std::vector<Vertex> GetVerticies(){ return m_Verticies;}
        inline int GetVerticiesCount() {return m_UsedQuads*4;} const
        inline std::vector<unsigned int> GetIndices(){return m_Indices;}
        inline int GetIndicCount() {return (m_UsedQuads*4)*6;}; const
        inline int GetMaxQuadCound() {return m_MaxQuadCount;}
        inline int GetUsedQuads() {return m_UsedQuads;}

        void SetShader(const std::string &filePath);

        void SetPosition(glm::mat4 MVP);

        void SetColor(float r, float g, float b, float a);



        void AddTexture(const std::string &filePath, unsigned int slot = 0);

        void BindBufferData();

        void BindVertexBuffer();
        void BindIndexBuffer();


        //inline std::unique_ptr<VertexArray> GetVertexArray() {return m_VAO;}
        //inline std::unique_ptr<IndexBuffer> GetIndexObject() {return m_IBO;}
        //inline std::unique_ptr<Shader> GetShader() {return m_Shader;}


};
