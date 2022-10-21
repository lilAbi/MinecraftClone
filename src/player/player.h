
#ifndef GAMEENGINEV2_PLAYER_H
#define GAMEENGINEV2_PLAYER_H

#include "glm/glm.hpp"

namespace game{

    //player object
    class Player {
    public:
        explicit Player(glm::vec3 position): playerPosition(position){}
        ~Player() = default;

        glm::vec3& GetPlayerPosition(){return playerPosition;}

    private:
        glm::vec3 playerPosition;
    };

}


#endif //GAMEENGINEV2_PLAYER_H
