#include "Shader.hpp"


Shader::Shader() : m_RenderID(0){

    

}

Shader::~Shader(){

    GLCall(glDeleteProgram(m_RenderID));

}

void Shader::SetShader(const std::string &filePath){
    m_FilePath = filePath;
    ShaderProgramSource source = ParseShader();
    m_RenderID = CreateShader(source.vertexSource, source.fragmentSource);

}


void Shader::Bind() const{

    GLCall(glUseProgram(m_RenderID));

}

void Shader::UnBind(){

    GLCall(glUseProgram(0));

}

void Shader::SetUniform1i(const std::string &name, int value){

    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const std::string &name, GLsizei size, const GLint *array){
    GLCall(glUniform1iv(GetUniformLocation(name), size, array));
}

void Shader::SetUniform1f(const std::string &name, float value){

    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string &name, float v0, float v1, float v2){
   GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3){

    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));

}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix){

    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));

}

int Shader::GetUniformLocation(const std::string &name) const {

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RenderID, name.c_str()));
    if(location == -1){
        std::cout << "Error " << name << " is not being used or is not found..." << std::endl;
    }
    m_UniformLocationCache[name] =  location;
    return location;

}

ShaderProgramSource Shader::ParseShader(){
    std::ifstream File(m_FilePath);
    std::string lines;
    std::stringstream ss[2];

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    while(getline(File, lines)){
        if(lines.find("#Shader") != std::string::npos){
            if(lines.find("vertex") != std::string::npos){
                //set to vertex
                type = ShaderType::VERTEX;
                //std::cout << "vertex found" << std::endl;
            } else if(lines.find("fragment") != std::string::npos){
                //set to fragment
                type = ShaderType::FRAGMENT;
                //std::cout << "fragment found" << std::endl;
            }
        }  else {
        ss[(int)type] << lines << "\n";
        }

    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CreateShader(std::string &vertexShader, std::string &fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);


    return program;
}

unsigned int Shader::CompileShader(unsigned int type, std::string &source){
    unsigned int id =  glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id,1,&src, nullptr);

    glCompileShader(id);

    //TODO : error checking
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout  << "Error " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

