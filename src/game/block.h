
#ifndef GAMEENGINEV2_BLOCK_H
#define GAMEENGINEV2_BLOCK_H


namespace game{
    enum class BlockType {
        Air = 0,
        Grass,
        CobbleStone,
        Stone,
        Wood,
        Sand,
        Bricks,
        Water,
        Unknown
    };

    BlockType CalculateBlockType(float terrainNoiseValue);

    struct Block {
        BlockType blockType{BlockType::Air};
    };

}


#endif //GAMEENGINEV2_BLOCK_H
