/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Environment
*/

#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include "IEntities.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Sound.hpp"
#include "../Components/Render.hpp"

namespace game_engine {
    class Environment : public IEntities {
        public:
            Environment(Vector _position);
            ~Environment() {};

            int getUniqueID() const {return (_uniqueID);};
            EntitiesType getEntitiesID() const {return (_entitesID);};
            std::vector<std::shared_ptr<AComponents>> getComponentList() const {return (_componentList);};

            std::shared_ptr<Transform> getTransform() const {return (_transform);};
            std::shared_ptr<Sound> getMusic() const {return (_music);};
            std::shared_ptr<Render> getRender() const {return (_render);};

        protected:
        private:
            int _uniqueID;
            EntitiesType _entitesID;

            std::shared_ptr<Transform> _transform;
            std::shared_ptr<Sound> _music;
            std::shared_ptr<Render> _render;
            std::vector<std::shared_ptr<AComponents>> _componentList;
    };
}

#endif /* !ENVIRONMENT_HPP_ */
