
#ifndef GAMEENGINEV2_VERTEXARRAY_H
#define GAMEENGINEV2_VERTEXARRAY_H

namespace gfx{
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind();
        void UnBind();

    private:
        unsigned objectID;

    };
}



#endif //GAMEENGINEV2_VERTEXARRAY_H
