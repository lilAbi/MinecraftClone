
#ifndef GAMEENGINEV2_MESH_H
#define GAMEENGINEV2_MESH_H
#include <vector>
#include "glm/glm.hpp"

namespace gfx{
    struct Vertex {
        glm::vec3 position;
    };

    //simple mesh object
    class Mesh {
    public:
        Mesh() = default;
        explicit Mesh(std::vector<Vertex>& vertexBuffer): vertices(std::move(vertexBuffer)){SetupMesh();};

        ~Mesh() = default;

        void NewData(std::vector<Vertex>& vertexBuffer){ vertices = std::move(vertexBuffer); SetupMesh();}

    private:
        void SetupMesh();
    private:
        std::vector<Vertex> vertices;
        unsigned int vao{};
        unsigned int vbo{};
    };

}

#endif //GAMEENGINEV2_MESH_H
