#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATIO
#include "Imports/stb_image/stb_image.h"

Texture::Texture(const std::string &filePath) : m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0){
    
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    //std::cout << m_Width << std::endl;
    //std::cout << m_Height << std::endl;

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID)); 

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer ));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_LocalBuffer){
        stbi_image_free(m_LocalBuffer);
    }

}

Texture::~Texture(){

    GLCall(glDeleteTextures(1, &m_RendererID));

}

void Texture::Bind(unsigned int slot) const{

    GLCall(glActiveTexture(GL_TEXTURE0 + slot));

    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

}

void Texture::UnBind() const{

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}

GLuint Texture::LoadTexture(const std::string &filePath){
    int w,h, bits;
    stbi_set_flip_vertically_on_load(1); 

    auto pixels = stbi_load(filePath.c_str(), &w, &h, &bits, 4);
    GLuint TextureID;
    GLCall(glGenTextures(1, &TextureID));
    GLCall(glBindTexture(GL_TEXTURE_2D, TextureID));


    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels ));

    stbi_image_free(pixels);

    return TextureID;

}