
#include "world.h"

game::World::World(gfx::Camera* cam): camera(cam) {
    //generate an "empty world"
    worldChunksContainer.reserve(GRID_SIZE_X * GRID_SIZE_Y);

    //fill the container with "empty" chunks
    game::EmptyWorldGeneration(worldChunksContainer, player);

    //build terrain out of empty chunks
    game::WorldGeneration(worldChunksContainer);
}

//called every frame and update blocks/lighting/player
void game::World::Update() {
    std::vector<Chunk*> redrawList;
    redrawList.reserve(GRID_SIZE_Y*GRID_SIZE_X);

    //render distance

    //what chunk is the player in

    bool redraw;
    for(auto& chunk : worldChunksContainer){
        if(chunk.GetChunkStatus() != ChunkStatus::NotLoaded){
            //does the chunk contain blocks?
            if(chunk.GetChunkStatus() != ChunkStatus::Empty){
                if(chunk.GetChunkStatus() == ChunkStatus::Modified){
                    //trigger redraw
                    redraw = true;
                    redrawList.push_back({&chunk});

                } else if(chunk.GetChunkStatus() == ChunkStatus::Normal) {
                    //simulate chunk
                    //chunk.Update();
                }
            }

        } else {
            /*
            if(IsChunkInFile(chunk)){
                //copy all chunk data from file into this chunk
                chunk = LoadChunkFromFile()
            } else {
                GeneratedFromNoise(chunk);
            }
             */
        }
    }


    //mesh chunk
    if(redraw){
        for(auto* chunk : redrawList){
            chunk->BuildMesh();
            chunk->SetChunkStatus(ChunkStatus::Normal);
        }
    }

}
