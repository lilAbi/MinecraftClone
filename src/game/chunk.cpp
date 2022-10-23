
#include "chunk.h"

game::Chunk::Chunk(glm::vec3 position) : chunkPosition(position) {}

//construct mesh with greedy meshing algorithm
void game::Chunk::BuildMesh() {
    //container to hold the mesh
    std::vector<gfx::Vertex> meshContainer;
    meshContainer.reserve(1024);

    //small lamda function to handle invalid block states
    auto GetBlockTypeAt = [&](int x, int y, int z) -> BlockType {
        if(x < CHUNK_SIZE_X && x >= 0){
            if(y < CHUNK_SIZE_Y && y >= 0){
                if(z < CHUNK_SIZE_Z && z >= 0){
                    return blocks[x + (z*CHUNK_SIZE_X) + (y * CHUNK_SIZE_Z*CHUNK_SIZE_X)].blockType;
                }
            }
        }
        return BlockType::Air;
    };

    //iterate through each face of the chunk making 2d slices
    for(int dimension{0}; dimension < Dimension::DimensionMaxSize; ++dimension){
        std::size_t reserveSize{0};
        int maxHeight{0};
        int maxLength{0};
        int maxWidth{0};
        //calculate size of mask and length and width of current face
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
                maxHeight = 0;
                maxLength = 0;
                maxWidth = 0;
                break;
        }

        //iterate through all the slices
        for(int slice{0}; slice < maxHeight; ++slice){
            std::vector<game::BlockType> slice2D(reserveSize);

            //scan a 2d slice and fill out a mask
            for(int width{0}; width < maxWidth; ++width){
                for(int length{0}; length < maxLength; ++length){
                    game::BlockType currentBlock = BlockType::Air;

                    //get block type at position x,y,z
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

                    //vertex of quad
                    glm::vec3 lowerLeft{0.0f,0.0f,0.0f};
                    glm::vec3 lowerRight{0.0f,0.0f,0.0f};
                    glm::vec3 upperLeft{0.0f,0.0f,0.0f};
                    glm::vec3 upperRight{0.0f,0.0f,0.0f};
                    switch(Dimension(dimension)){
                        case Front:
                            lowerLeft.x = static_cast<float>(x);
                            lowerLeft.y = static_cast<float>(y);
                            lowerLeft.z = static_cast<float>(slice);

                            lowerRight.x = static_cast<float>(x) + static_cast<float>(meshLength);
                            lowerRight.y = static_cast<float>(y);
                            lowerRight.z = static_cast<float>(slice);

                            upperLeft.x = static_cast<float>(x);
                            upperLeft.y = static_cast<float>(y)+ static_cast<float>(meshHeight);
                            upperLeft.z = static_cast<float>(slice);

                            upperRight.x = static_cast<float>(x) + static_cast<float>(meshLength);
                            upperRight.y = static_cast<float>(y)+ static_cast<float>(meshHeight);
                            upperRight.z = static_cast<float>(slice);
                            break;

                        case Back:
                            lowerLeft.x = static_cast<float>(x) + static_cast<float>(meshLength);
                            lowerLeft.y = static_cast<float>(y);
                            lowerLeft.z = static_cast<float>(slice)+1.0f;

                            lowerRight.x = static_cast<float>(x);
                            lowerRight.y = static_cast<float>(y);
                            lowerRight.z = static_cast<float>(slice)+1.0f;

                            upperLeft.x = static_cast<float>(x) + static_cast<float>(meshLength);
                            upperLeft.y = static_cast<float>(y)+ static_cast<float>(meshHeight);
                            upperLeft.z = static_cast<float>(slice)+1.0f;

                            upperRight.x = static_cast<float>(x);
                            upperRight.y = static_cast<float>(y)+ static_cast<float>(meshHeight);
                            upperRight.z = static_cast<float>(slice)+1.0f;

                            break;

                        case Left:
                            lowerLeft.x = static_cast<float>(slice);
                            lowerLeft.y = static_cast<float>(y);
                            lowerLeft.z = static_cast<float>(x) + static_cast<float>(meshLength);

                            lowerRight.x = static_cast<float>(slice);
                            lowerRight.y = static_cast<float>(y);
                            lowerRight.z = static_cast<float>(x);

                            upperLeft.x = static_cast<float>(slice);
                            upperLeft.y = static_cast<float>(y) + static_cast<float>(meshHeight);
                            upperLeft.z = static_cast<float>(x) + static_cast<float>(meshLength);

                            upperRight.x = static_cast<float>(slice);
                            upperRight.y = static_cast<float>(y) + static_cast<float>(meshHeight);
                            upperRight.z = static_cast<float>(x);
                            break;

                        case Right:
                            lowerLeft.x = static_cast<float>(slice) + 1.0f;
                            lowerLeft.y = static_cast<float>(y);
                            lowerLeft.z = static_cast<float>(x);

                            lowerRight.x = static_cast<float>(slice) + 1.0f;
                            lowerRight.y = static_cast<float>(y);
                            lowerRight.z = static_cast<float>(x)+ static_cast<float>(meshLength);

                            upperLeft.x = static_cast<float>(slice) + 1.0f;
                            upperLeft.y = static_cast<float>(y) + static_cast<float>(meshHeight);
                            upperLeft.z = static_cast<float>(x);

                            upperRight.x = static_cast<float>(slice) + 1.0f;
                            upperRight.y = static_cast<float>(y) + static_cast<float>(meshHeight);
                            upperRight.z = static_cast<float>(x) + static_cast<float>(meshLength);

                            break;

                        case Top:
                            lowerLeft.x = static_cast<float>(x);
                            lowerLeft.y = static_cast<float>(slice) + 1.0f;
                            lowerLeft.z = static_cast<float>(y);

                            lowerRight.x = static_cast<float>(x) + static_cast<float>(meshLength);
                            lowerRight.y = static_cast<float>(slice) + 1.0f;
                            lowerRight.z = static_cast<float>(y);

                            upperLeft.x = static_cast<float>(x);
                            upperLeft.y = static_cast<float>(slice) + 1.0f;
                            upperLeft.z = static_cast<float>(y) + static_cast<float>(meshHeight);

                            upperRight.x = static_cast<float>(x) + + static_cast<float>(meshLength);
                            upperRight.y = static_cast<float>(slice) + 1.0f;
                            upperRight.z = static_cast<float>(y) + static_cast<float>(meshHeight);
                            break;

                        case Bottom:
                            lowerLeft.x = static_cast<float>(x) + static_cast<float>(meshLength);
                            lowerLeft.y = static_cast<float>(slice);
                            lowerLeft.z = static_cast<float>(y);

                            lowerRight.x = static_cast<float>(x);
                            lowerRight.y = static_cast<float>(slice);
                            lowerRight.z = static_cast<float>(y);

                            upperRight.x = static_cast<float>(x);
                            upperRight.y = static_cast<float>(slice);
                            upperRight.z = static_cast<float>(y) + static_cast<float>(meshHeight);

                            upperLeft.x = static_cast<float>(x) + + static_cast<float>(meshLength);
                            upperLeft.y = static_cast<float>(slice);
                            upperLeft.z = static_cast<float>(y) + static_cast<float>(meshHeight);
                            break;

                        case DimensionMaxSize:
                            break;
                    }

                    //add quad
                    meshContainer.push_back({lowerLeft});
                    meshContainer.push_back({upperLeft});
                    meshContainer.push_back({upperRight});
                    meshContainer.push_back({upperLeft});
                    meshContainer.push_back({upperRight});
                    meshContainer.push_back({lowerRight});

                    //clear out created mesh
                    for(int h{0}; h < meshHeight; ++h){
                        for(int l{0}; l < meshLength; ++l){
                            slice2D[(l+x) + ((h+y) * maxLength)] = BlockType::Air;
                        }
                    }

                }
            }//end of the building mesh

        }//end of slice

    }//end of dimension

    //move data into mesh
    chunkMesh.NewData(meshContainer);
}

//end of function
