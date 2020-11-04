/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "IEntities.hpp"
#include "../PlayerColor.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Sound.hpp"
#include "../Components/Health.hpp"
#include "../Components/Shoot.hpp"
#include "../Components/Collision.hpp"
#include "../Components/Render.hpp"

namespace game_engine {
    class Player : public IEntities {
        public:
            Player(Vector _position, PlayerColor playerColor, int clientID);
            ~Player() {};

            int getUniqueID() const {return (_uniqueID);};
            EntitiesType getEntitiesID() const {return (_entitesID);};
            std::vector<std::shared_ptr<AComponents>> getComponentList() const {return (_componentList);};

            std::shared_ptr<Transform> getTransform() const {return (_transform);};
            std::shared_ptr<Sound> getDeathSound() const {return (_deathSound);};
            std::shared_ptr<Health> getHealth() const {return (_health);};
            std::shared_ptr<Collision> getCollision() const {return (_collision);};
            std::shared_ptr<Render> getRender() const {return (_render);};
            std::shared_ptr<Shoot> getShoot() const {return (_shoot);};

            float getTimeInvincibility() const {return (_timeInvincibility);};
            float getSpeedMultiplicator() const {return (_speedMultiplicator);};
            void setTimeInvincibility(size_t timeInvincibility) {_timeInvincibility = timeInvincibility;}
            void setSpeedMultiplicator(float speedMultiplicateur) {_speedMultiplicator = speedMultiplicateur;}

        protected:
        private:
            int _uniqueID;
            int _clientID;
            EntitiesType _entitesID;

            std::shared_ptr<Transform> _transform;
            std::shared_ptr<Sound> _deathSound;
            std::shared_ptr<Health> _health;
            std::shared_ptr<Shoot> _shoot;
            std::shared_ptr<Collision> _collision;
            std::shared_ptr<Render> _render;
            std::vector<std::shared_ptr<AComponents>> _componentList;

            size_t _timeInvincibility;
            float _speedMultiplicator;
    };
}

#endif /* !PLAYER_HPP_ */
