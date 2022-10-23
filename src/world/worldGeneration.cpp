
#include "worldGeneration.h"


void game::EmptyWorldGeneration(std::vector<Chunk>& worldChunkContainer, game::Player& player){
    //take an empty container and build the chunks around the player
    //get nearest lower left multiple
    auto& center = player.GetPlayerPosition();
    int startX = static_cast<int>(center.x) - (GRID_SIZE_X/2);
    int endX = static_cast<int>(center.x) + (GRID_SIZE_X/2);
    int startY = static_cast<int>(center.z) - (GRID_SIZE_Y/2);
    int endY = static_cast<int>(center.z) + (GRID_SIZE_Y/2);

    for(int y{startY}; y <= endY; ++y){
        for(int x{startX}; x <= endX; ++x){
            worldChunkContainer.emplace_back(glm::vec3{static_cast<float>(x*CHUNK_SIZE_X),0.0f,static_cast<float>(y*CHUNK_SIZE_Z)});
        }
    }
};

//--------------------------------------------------------------------------------------------------------------------------------
void game::WorldGeneration(std::vector<Chunk>& worldChunkContainer){
    //container for noise values
    TerrainNoise2DArray terrainHeightMap{0.0f};

    //simple noise function
    auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
    auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();
    fnFractal->SetSource( fnSimplex );
    fnFractal->SetOctaveCount( 5 );

    for(auto& chunk : worldChunkContainer){
        //get starting chunk position
        glm::vec3 start = chunk.GetChunkLocation();
        //calculate noise values for ranges for this chunk aread
        fnFractal->GenUniformGrid2D(terrainHeightMap.data(),
                                    0,
                                    0,
                                    CHUNK_SIZE_X,
                                    CHUNK_SIZE_Z,
                                    .5f,
                                    1337);

        //copy it into the chunk
        BuildTerrainFromHeightMap(chunk, terrainHeightMap);
        //chunk has been modified
        chunk.SetChunkStatus(game::ChunkStatus::Modified);
    }

}

void game::BuildTerrainFromHeightMap(game::Chunk &chunk, TerrainNoise2DArray& heightMap){

    auto& blocks = chunk.GetBlockArray();

    for(int y = 0; y < CHUNK_SIZE_Y; y++){
        for(int z = 0; z < CHUNK_SIZE_Z; z++){
            for(int x = 0; x < CHUNK_SIZE_X; x++){
                //extract
                int heightValue = static_cast<int>(100 + (heightMap[x + (z * CHUNK_SIZE_Z)] * 20));
                auto& blockType = blocks[x + (z * CHUNK_SIZE_X) + (y * CHUNK_SIZE_X * CHUNK_SIZE_Z)].blockType;
                (y < heightValue) ? blockType = BlockType::Stone : blockType = BlockType::Air;
            }
        }
    }

}
