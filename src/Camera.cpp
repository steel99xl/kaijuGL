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

Camera3D::Camera3D(glm::vec3 Pos, glm::vec3 Look, glm::vec3 Angle, float Sensitivity, float Ratio, float FOV, float ViewDistance){
    m_pos = Pos;

    m_look = Look;

    m_rotation = Angle;

    m_Hsensitivity = Sensitivity;
    m_Vsensitivity = Sensitivity;

    m_AspecRatio = Ratio;

    m_FOV = FOV;

    m_ViewDistance = ViewDistance;

    m_Proj = glm::perspective(glm::radians(m_FOV), m_AspecRatio, 0.1f, m_ViewDistance);
    m_View = glm::lookAt(m_pos, m_look, m_rotation);

}

Camera3D::~Camera3D(){

}


void Camera3D::Update(float DeltaTime, float Ratio, float FOV, float ViewDistance){
    m_DeltaTime = DeltaTime;


    if(Ratio){m_AspecRatio = Ratio;}
    if(FOV){m_FOV = FOV;}
    if(ViewDistance){m_ViewDistance = ViewDistance;}

    m_Proj = glm::perspective(glm::radians(m_FOV), m_AspecRatio, 0.1f, m_ViewDistance);
    m_View = glm::lookAt(m_pos, m_pos+m_look, m_rotation);
}

void Camera3D::Input(){

}

void Camera3D::Move(Direction direction, float Speed){

    Speed = Speed * m_DeltaTime;

     float Buff = m_pos[1];

    switch(direction){
        case UP:
            m_pos[1] += Speed;
            break;

        case DOWN:
            m_pos[1] -= Speed;
            break;

        case LEFT:
            m_pos -= glm::normalize(glm::cross(m_look, m_rotation)) * (float)(Speed);
            break;

        case RIGHT:
            m_pos += glm::normalize(glm::cross(m_look, m_rotation)) * (float)(Speed);
            break;

        case FORWARD:
            m_pos[0] += (float)(Speed) * m_WalkingDir[0];
            m_pos[2] += (float)(Speed) * m_WalkingDir[1]; 
            m_pos[1] = Buff;
            break;

        case BACK:
            m_pos[0] -= (float)(Speed) * m_WalkingDir[0];
            m_pos[2] -= (float)(Speed) * m_WalkingDir[1];
            m_pos[1] = Buff;
            break;

    }

}

void Camera3D::LookRelative(double xpos, double ypos){

    float xoffset = m_Xinvert*(xpos - m_LlastinputX);
    float yoffset = m_Yinvert*(m_LlastinputY - ypos); 
    m_LlastinputX = xpos;
    m_LlastinputY = ypos;

    
    xoffset *= m_Hsensitivity;
    yoffset *= m_Vsensitivity;

    m_Lyaw   += xoffset;
    m_Lpitch += yoffset;

    if(m_Lpitch > 89.0f)
        m_Lpitch = 89.0f;
    if(m_Lpitch < -89.0f)
        m_Lpitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Lyaw)) * cos(glm::radians(m_Lpitch));
    direction.y = sin(glm::radians(m_Lpitch));
    direction.z = sin(glm::radians(m_Lyaw)) * cos(glm::radians(m_Lpitch));
    m_look = glm::normalize(direction);
    m_WalkingDir.x = direction.x;
    m_WalkingDir.y = direction.z; 
    m_WalkingDir = glm::normalize(m_WalkingDir);

}