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
#include "../InputEnum.hpp"
#include "../../include/NetUDPServer.hpp"


namespace game_engine {
    class Player : public IEntities {
        public:
            Player(Vector _position, PlayerColor playerColor, int clientID, boost::asio::ip::udp::endpoint &endpoint);
            ~Player() {};

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

            boost::asio::ip::udp::endpoint getClientEndpoint() const {return (_endpoint);}
            float getTimeInvincibility() const {return (_timeInvincibility);};
            float getSpeedMultiplicator() const {return (_speedMultiplicator);};
            int getScore() const {return(_score);}
            void setTimeInvincibility(size_t timeInvincibility) {_timeInvincibility = timeInvincibility;}
            void setSpeedMultiplicator(float speedMultiplicateur) {_speedMultiplicator = speedMultiplicateur;}
            void addNewInput(network::Event event, int value[10]);

        protected:
        private:
            int _uniqueID;
            int _clientID;
            int _score;
            boost::asio::ip::udp::endpoint _endpoint;
            EntitiesType _entitesID;
            std::vector<InputEnum> inputBuffer;

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
