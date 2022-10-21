
#include "chunk.h"

game::Chunk::Chunk(glm::vec3 position) : chunkPosition(position) {

}

//construct mesh with greedy
void game::Chunk::BuildMesh() {

    auto GetBlockTypeAt = [&](int x, int y, int z) -> BlockType {
        if(x < CHUNK_SIZE_X && x >= 0){
            if(y < CHUNK_SIZE_Y && y >= 0){
                if(z < CHUNK_SIZE_Z && z >= 0){
                    return blocks[x + (z*CHUNK_SIZE_Z) + (y * CHUNK_SIZE_Z*CHUNK_SIZE_X)].blockType;
                }
            }
        }
        return BlockType::Air;
    };

    for(int dimension{0}; dimension < Dimension::DimensionMaxSize; ++dimension){
        std::size_t reserveSize{0};
        int maxHeight{0};
        int maxLength{0};
        int maxWidth{0};

        switch (Dimension(dimension)){
            case Front:
            case Back:
                reserveSize = CHUNK_SIZE_X*CHUNK_SIZE_Y;
                maxHeight = CHUNK_SIZE_Z;
                maxLength = CHUNK_SIZE_X;
                maxWidth = CHUNK_SIZE_Y;
                break;
            case Left:
            case Right:
                reserveSize = CHUNK_SIZE_Z*CHUNK_SIZE_Y;
                maxHeight = CHUNK_SIZE_X;
                maxLength = CHUNK_SIZE_Z;
                maxWidth = CHUNK_SIZE_Y;
                break;
            case Top:
            case Bottom:
                reserveSize = CHUNK_SIZE_X*CHUNK_SIZE_Z;
                maxHeight = CHUNK_SIZE_Y;
                maxLength = CHUNK_SIZE_X;
                maxWidth = CHUNK_SIZE_Z;
                break;
            case DimensionMaxSize:
                break;
        }

        //break up into slices
        for(int slice{0}; slice < maxHeight; ++slice){
            std::vector<game::BlockType> slice2D(reserveSize);

            //scan a 2d slice and fill out a mask
            for(int width{0}; width < maxWidth; ++width){
                for(int length{0}; length < maxLength; ++length){
                    //access block in
                    game::BlockType currentBlock = BlockType::Air;

                    //get block
                    switch (Dimension(dimension)) {
                        case Front:
                            if(GetBlockTypeAt(length, width, slice-1) == BlockType::Air){
                                currentBlock = GetBlockTypeAt(length, width, slice);
                            }
                        case Back:
                            if(GetBlockTypeAt(length, width, slice+1) == BlockType::Air){
                                currentBlock = GetBlockTypeAt(length, width, slice);
                            }
                            break;
                        case Left:
                            if(GetBlockTypeAt(slice-1, width, length) == BlockType::Air){
                                currentBlock = GetBlockTypeAt(length, width, slice);
                            }
                        case Right:
                            if(GetBlockTypeAt(slice+1, width, length) == BlockType::Air){
                                currentBlock = GetBlockTypeAt(length, width, slice);
                            }
                            break;
                        case Top:
                            if(GetBlockTypeAt(length, slice + 1, width) == BlockType::Air){
                                currentBlock = GetBlockTypeAt(length, slice, width);
                            }
                        case Bottom:
                            if(GetBlockTypeAt(length, slice - 1, width) == BlockType::Air){
                                currentBlock = GetBlockTypeAt(length, slice, width);
                            }
                            break;
                        case DimensionMaxSize:
                            currentBlock = BlockType::Air;
                            break;
                    }
                    //set block at position
                    slice2D[length + (width * maxLength)] = currentBlock;
                }
            }//end of filling out 2D slice


            //build mesh from mask
            for(int y{0}; y < maxWidth; ++y){
                for(int x{0}; x < maxLength; ++x){
                    game::BlockType currentBlockType = slice2D[x + (y * maxLength)];

                    //don't mesh air blocks
                    if(currentBlockType == game::BlockType::Air){
                        continue;
                    }

                    //find max length of mesh
                    int meshLength{1};
                    while( x+meshLength < maxLength && currentBlockType == slice2D[(x + meshLength)+(y * maxLength)] ){
                        ++meshLength;
                    }

                    //find max mesh height
                    int meshHeight{1};
                    bool exit{false};
                    for(int h = y+meshHeight; h < maxWidth; ++h){
                        for(int l = x; l < meshLength; ++l ){
                            if(currentBlockType != slice2D[l + (h * maxLength)]){
                                exit = true;
                            }
                        }
                        if(exit){break;}
                        ++meshHeight;
                    }

                    //TODO: finish this
                    glm::vec3 quad = chunkPosition;
                    switch(Dimension(dimension)){
                        case Front:
                            quad.x += static_cast<float>(x);
                            quad.y += static_cast<float>(y);
                            quad.z += static_cast<float>(slice);
                            break;
                        case Back:
                            quad.x += static_cast<float>(x);
                            quad.y += static_cast<float>(y);
                            quad.z += static_cast<float>(slice)+1.0f;
                            break;
                        case Left:
                            quad.x += static_cast<float>(x);
                            quad.y += static_cast<float>(y);
                            quad.z += static_cast<float>(slice);
                            break;
                        case Right:
                            break;
                        case Top:
                            break;
                        case Bottom:
                            break;
                        case DimensionMaxSize:
                            break;
                    }




                    //clear out created mesh
                    for(int b = y; b < y+meshHeight; b++){

                    }

                }
            }


        }//end of slice

    }//end of dimension

}//end of function
