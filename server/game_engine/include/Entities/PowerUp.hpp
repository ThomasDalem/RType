/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "IEntities.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Sound.hpp"
#include "../Components/Collision.hpp"
#include "../Components/Render.hpp"
#include "Player.hpp"

namespace game_engine
{
    enum PowerUpType {
        INCREASEFIRERATE,
        SPEEDBOOST,
        SHIELD,
    };

    class PowerUp : public IEntities {
        public:
            PowerUp(Vector _position);
            ~PowerUp() {};

            int getUniqueID() const {return (_uniqueID);};
            EntitiesType getEntitiesID() const {return (_entitesID);};
            std::vector<std::shared_ptr<AComponents>> getComponentList() const {return (_componentList);};

            std::shared_ptr<Transform> getTransform() const {return (_transform);};
            std::shared_ptr<Sound> getSound() const {return (_sound);};
            std::shared_ptr<Collision> getCollision() const {return (_collision);};
            std::shared_ptr<Render> getRender() const {return (_render);};

            void activePowerUp(Player &player);
            void activeIncreaseFireRate(Player &player);
            void activeSheild(Player &player);
            void activeSpeedBoost(Player &player);

        protected:
        private:
            int _uniqueID;
            EntitiesType _entitesID;

            std::shared_ptr<Transform> _transform;
            std::shared_ptr<Sound> _sound;
            std::shared_ptr<Collision> _collision;
            std::shared_ptr<Render> _render;
            std::vector<std::shared_ptr<AComponents>> _componentList;

            PowerUpType _powerUpType;
    };
}

#endif /* !POWER_UP_HPP_ */
