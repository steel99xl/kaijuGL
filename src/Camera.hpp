#pragma once
#include "Engine.hpp"


class Camera2D{
    private:
    float m_LayerDepth, m_ScaleFactor, m_Width, m_Height;
    glm::vec3  m_pos;
    // Camera is at (4,3,3), in World Space // and looks at the  //glm::vec3(0,1,0)
    glm::mat4 m_Proj, m_View; // This MVP stuff has the same naems


    public:

    Camera2D(glm::vec3 Pos, float ScaleFactor, float Width, float Height, float Layers);
    ~Camera2D();

    void Setup();

    void Update(glm::vec3 Pos, float ScaleFactor = 0.0f, float Width = 0.0f, float Height = 0.0f, float Layers = 0.0f);
    void Input();
    inline glm::mat4 GetProj() {return m_Proj;};
    inline glm::mat4 GetView() {return m_View;};


};


class Camera3D{
    private:
    float m_ViewDistance; // This is basicaly the same as layer depth
    float m_FOV;
    float m_AspecRatio;
    glm::vec3  m_pos, m_look, m_rotation;
    glm::mat4 m_Proj, m_View; // This MVP stuff has the same naems


    public:

    Camera3D(glm::vec3 Pos, glm::vec3 Look, glm::vec3 Angle, float Ratio, float FOV, float ViewDistance);
    ~Camera3D();

    void Update(glm::vec3 Pos, glm::vec3 Look, glm::vec3 Angle, float Ratio = 0.0f, float FOV = 0.0f, float ViewDistance = 0.0f);
    void Input();
    inline glm::mat4 GetProj() {return m_Proj;};
    inline glm::mat4 GetView() {return m_View;};
};

