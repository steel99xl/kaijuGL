#include "Camera.hpp"

// 2DCamera Class

Camera2D::Camera2D(glm::vec3 Pos, float ScaleFactor, float Width, float Height, float Layers){
    m_pos = Pos;

    m_ScaleFactor = ScaleFactor;

    m_Width = Width;
    
    m_Height = Height;

    m_LayerDepth = Layers;
}

Camera2D::~Camera2D(){

}

void Camera2D::Setup(){

}

void Camera2D::Update(glm::vec3 Pos, float ScaleFactor , float Width , float Height , float Layers ){
    m_pos = Pos;
    
    if(ScaleFactor){m_ScaleFactor = ScaleFactor;}
    if(Width){m_Width = Width;}
    if(Height){m_Height = Height;}
    if(Layers){m_LayerDepth = Layers;}

    m_Proj = glm::ortho(0.0f, m_Width*m_ScaleFactor, 0.0f, m_Height*m_ScaleFactor, -1.0f, m_LayerDepth);
    //m_View = glm::lookAt(m_pos, m_look, m_rotation);
    m_View = glm::translate(glm::mat4(1.0f),m_pos);

}

void Camera2D::Input(){

}



// 3DCamera Class

Camera3D::Camera3D(glm::vec3 Pos, glm::vec3 Look, glm::vec3 Angle, float Ratio, float FOV, float ViewDistance){
    m_pos = Pos;

    m_look = Look;

    m_rotation = Angle;

    m_AspecRatio = Ratio;

    m_FOV = FOV;

    m_ViewDistance = ViewDistance;

    m_Proj = glm::perspective(glm::radians(m_FOV), m_AspecRatio, 0.1f, m_ViewDistance);
    m_View = glm::lookAt(m_pos, m_look, m_rotation);

}

Camera3D::~Camera3D(){

}


void Camera3D::Update(glm::vec3 Pos, glm::vec3 Look, glm::vec3 Angle, float Ratio, float FOV, float ViewDistance){
    m_pos = Pos;

    m_look = Look;

    m_rotation = Angle;
    
    if(Ratio){m_AspecRatio = Ratio;}
    if(FOV){m_FOV = FOV;}
    if(ViewDistance){m_ViewDistance = ViewDistance;}

    m_Proj = glm::perspective(glm::radians(m_FOV), m_AspecRatio, 0.1f, m_ViewDistance);
    m_View = glm::lookAt(m_pos, m_look, m_rotation);
}

void Camera3D::Input(){

}