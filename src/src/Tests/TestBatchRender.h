#pragma once
#include "test.h"

namespace test{
    
    class TestBatchRender : public Test{

        private:
            GLuint Box1, Box2;
            bool m_Effect;
            glm::vec3 m_pos;

            glm::mat4 m_Proj, m_View;

            std::unique_ptr<VertexArray> m_VAO;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<IndexBuffer> m_IBO;
            std::unique_ptr<Texture> m_Texture;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;

        public:
            bool m_running;
            TestBatchRender();
            ~TestBatchRender();


            void OnUpdate(float deltaTime) override;
            void OnRender(int Width, int Height, float ScaleFactor) override;
            void OnImGui() override;


    };
}