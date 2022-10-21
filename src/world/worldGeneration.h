
#ifndef GAMEENGINEV2_WORLDGENERATION_H
#define GAMEENGINEV2_WORLDGENERATION_H
#include <vector>
#include <iostream>
#include <array>
#include "game/chunk.h"
#include "game/info.h"
#include "player/player.h"
#include "FastNoise/FastNoise.h"


namespace game{

    using TerrainNoise2DArray = std::array<float, (CHUNK_SIZE_X  * CHUNK_SIZE_Z)>;
    using TerrainNoise3DArray = std::array<float, (CHUNK_SIZE_X  * CHUNK_SIZE_Y * CHUNK_SIZE_Z)>;

    void EmptyWorldGeneration(std::vector<Chunk>& worldChunkContainer, game::Player& player);

    void WorldGeneration(std::vector<Chunk>& worldChunkContainer);

    void BuildTerrainFromHeightMap(game::Chunk& chunk, TerrainNoise2DArray& noiseArr);
}


#endif //GAMEENGINEV2_WORLDGENERATION_H
