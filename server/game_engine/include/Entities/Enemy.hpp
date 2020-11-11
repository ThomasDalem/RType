/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Enemy
*/

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <ctime>

#include "IEntities.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Sound.hpp"
#include "../Components/Health.hpp"
#include "../Components/Shoot.hpp"
#include "../Components/Collision.hpp"
#include "../Components/Render.hpp"
#include "../InputEnum.hpp"

namespace game_engine {
    class Enemy : public IEntities {
        public:
            Enemy(Vector _position, int id);
            ~Enemy() {};

            int getUniqueID() const {return (_uniqueID);};
            EntitiesType getEntitiesID() const {return (_entitesID);};
            std::vector<std::shared_ptr<AComponents>> getComponentList() const {return (_componentList);};
            std::vector<InputEnum> getInputBuffer() const {return (inputBuffer);};

            InputEnum getFirstEnum() const {
                if (!inputBuffer.empty())
                    return (inputBuffer[0]);
                return (InputEnum::NOTHING);
            }
            void popFirstInput() {
                if (!inputBuffer.empty())
                    inputBuffer.erase(inputBuffer.begin());
            };
            std::shared_ptr<Transform> getTransform() const {return (_transform);};
            std::shared_ptr<Sound> getDeathSound() const {return (_deathSound);};
            std::shared_ptr<Health> getHealth() const {return (_health);};
            std::shared_ptr<Collision> getCollision() const {return (_collision);};
            std::shared_ptr<Render> getRender() const {return (_render);};
            std::shared_ptr<Shoot> getShoot() const {return (_shoot);};

            virtual void enemyIA() {};

        protected:
            int _uniqueID;
            EntitiesType _entitesID;
            std::vector<InputEnum> inputBuffer;
            std::time_t _fireTimer;

            std::shared_ptr<Transform> _transform;
            std::shared_ptr<Sound> _deathSound;
            std::shared_ptr<Health> _health;
            std::shared_ptr<Shoot> _shoot;
            std::shared_ptr<Collision> _collision;
            std::shared_ptr<Render> _render;
            std::vector<std::shared_ptr<AComponents>> _componentList;
    };
}

#endif /* !ENEMY_HPP_ */
