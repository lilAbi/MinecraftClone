
#ifndef GAMEENGINEV2_CHUNK_H
#define GAMEENGINEV2_CHUNK_H
#include <array>
#include "glm/glm.hpp"
#include "info.h"
#include "block.h"
#include "mesh/mesh.h"

namespace game{

    enum Dimension{
        Front = 0,
        Back,
        Left,
        Right,
        Top,
        Bottom,
        DimensionMaxSize
    };


    enum class ChunkStatus{
        NotLoaded = 0,  //chunk needs to be generated or loaded from memory
        Empty,          //chunk has no blocks inside
        Normal,         //chunk contains block and operating normally
        Modified        //blocks have been removed or added to chunk so a remesh is needed
    };

    class Chunk {
    public:
        explicit Chunk(glm::vec3 position);

        //  setting/getting chunk & mesh statues
        void        SetChunkStatus(ChunkStatus status){chunkStatus = status;}
        ChunkStatus GetChunkStatus(){return chunkStatus;}

        //  get location of chunk
        glm::vec3& GetChunkLocation(){return chunkPosition;}

        // get array of blocks contained in the world
        std::array<Block, CHUNK_SIZE_X*CHUNK_SIZE_Y*CHUNK_SIZE_Z>& GetBlockArray(){return blocks;}

        // get mesh object
        gfx::Mesh& GetMesh(){return chunkMesh;}

        //build a mesh
        void BuildMesh();

    private:


    private:
        //container for all the individual blocks in the chunk
        std::array<Block, CHUNK_SIZE_X*CHUNK_SIZE_Y*CHUNK_SIZE_Z> blocks{};
        //Mesh object
        gfx::Mesh chunkMesh;
        //position of chunk in world
        glm::vec3 chunkPosition;
        //status of the chunk
        ChunkStatus chunkStatus = ChunkStatus::NotLoaded;
    };
}


#endif //GAMEENGINEV2_CHUNK_H
