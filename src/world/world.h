
#ifndef GAMEENGINEV2_WORLD_H
#define GAMEENGINEV2_WORLD_H
#include <vector>
#include "game/chunk.h"
#include "game/info.h"
#include "player/player.h"
#include "graphics/camera.h"
#include "graphics/viewFrustum.h"
#include "worldGeneration.h"


//simulate world tick
namespace game{

    class World {
    public:
        explicit World(gfx::Camera* cam);
        ~World() = default;

        void Update();

    private:
        std::vector<Chunk> worldChunksContainer;
        gfx::Camera* camera{nullptr};
        game::Player player{{0.0f, 0.0f, 0.0f}};
    };
}


#endif //GAMEENGINEV2_WORLD_H
