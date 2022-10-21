
#ifndef GAMEENGINEV2_VERTEXBUFFER_H
#define GAMEENGINEV2_VERTEXBUFFER_H



//

namespace gfx{
    class VertexBuffer {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void Bind();
        void UnBind();

    private:
        unsigned int objectID{0};
    };
}



#endif //GAMEENGINEV2_VERTEXBUFFER_H
