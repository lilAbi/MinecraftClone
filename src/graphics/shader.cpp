
#include "shader.h"

gfx::Shader::Shader(std::string_view vertShaderFilePath, std::string_view fragShaderFilePath) {
    //get shader source code
    std::string vertexShaderCode = std::move(util::ReadFromFile(vertShaderFilePath));
    std::string fragmentShaderCode = std::move(util::ReadFromFile(vertShaderFilePath));

    //shader ids
    unsigned int vertexShader, fragmentShader;

    //compile vertex shader program
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const auto* vertCode = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertCode, nullptr);
    glCompileShader(vertexShader);
    CheckForErrors(vertexShader, "VERTEX");

    //compile fragment shader program
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const auto* fragCode = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragCode, nullptr);
    glCompileShader(fragmentShader);
    CheckForErrors(fragmentShader, "FRAGMENT");

    //shader program
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);
    CheckForErrors(shaderID, "PROGRAM");

    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void gfx::Shader::Use() {
    glUseProgram(shaderID);
}

void gfx::Shader::SetBool(std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void gfx::Shader::SetInt(std::string& name, int value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void gfx::Shader::SetFloat(std::string& name, float value) {
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void gfx::Shader::SetVec2(std::string& name, glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void gfx::Shader::SetVec2(std::string& name, float x, float y) {
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}

void gfx::Shader::SetVec3(std::string& name, glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void gfx::Shader::SetVec3(std::string& name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}

void gfx::Shader::SetVec4(std::string& name, glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void gfx::Shader::SetVec4(std::string& name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}

void gfx::Shader::SetMat2(std::string& name, glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void gfx::Shader::SetMat3(std::string& name, glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void gfx::Shader::SetMat4(std::string& name, glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void gfx::Shader::CheckForErrors(unsigned int shader, std::string_view type) {
    int flag;
    char log[1024];

    if(type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &flag);
        if (!flag){
            glGetShaderInfoLog(shader, 1024, nullptr, log);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << log << "\n -- --------------------------------------------------- -- \n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &flag);
        if (!flag){
            glGetProgramInfoLog(shader, 1024, nullptr, log);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << log << "\n -- --------------------------------------------------- -- \n";
        }
    }

}
