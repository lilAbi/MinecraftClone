
#ifndef GAMEENGINEV2_SHADER_H
#define GAMEENGINEV2_SHADER_H
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "utility/utility.h"

namespace gfx{

    class Shader {
    public:
        Shader() = default;
        Shader(std::string_view vertShaderFilePath, std::string_view fragShaderFilePath);

        ~Shader() = default;

        void Use();
        void SetBool(std::string& name, bool value);
        void SetInt(std::string& name, int value);
        void SetFloat(std::string& name, float value);
        void SetVec2(std::string& name, glm::vec2& value);
        void SetVec2(std::string& name, float x, float y);
        void SetVec3(std::string& name, glm::vec3& value);
        void SetVec3(std::string& name, float x, float y, float z);
        void SetVec4(std::string& name, glm::vec4& value);
        void SetVec4(std::string& name, float x, float y, float z, float w);
        void SetMat2(std::string& name, glm::mat2& mat);
        void SetMat3(std::string& name, glm::mat3& mat);
        void SetMat4(std::string& name, glm::mat4& mat);

    private:
        void CheckForErrors(unsigned int shaderID, std::string_view type);

    public:
        unsigned int shaderID{};
    };

}


#endif //GAMEENGINEV2_SHADER_H
