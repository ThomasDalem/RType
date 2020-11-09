/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DestroyableTile
*/

#ifndef DESTROYABLETILE_HPP_
#define DESTROYABLETILE_HPP_

#include "IEntities.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Sound.hpp"
#include "../Components/Health.hpp"
#include "../Components/Collision.hpp"
#include "../Components/Render.hpp"

namespace game_engine {
    class DestroyableTile : public IEntities {
        public:
            DestroyableTile(Vector _position, int id);
            ~DestroyableTile() {};

            int getUniqueID() const {return (_uniqueID);};
            EntitiesType getEntitiesID() const {return (_entitesID);};
            std::vector<std::shared_ptr<AComponents>> getComponentList() const {return (_componentList);};

            std::shared_ptr<Transform> getTransform() const {return (_transform);};
            std::shared_ptr<Sound> getDeathSound() const {return (_deathSound);};
            std::shared_ptr<Health> getHealth() const {return (_health);};
            std::shared_ptr<Collision> getCollision() const {return (_collision);};
            std::shared_ptr<Render> getRender() const {return (_render);};

        protected:
        private:
            int _uniqueID;
            EntitiesType _entitesID;

            std::shared_ptr<Transform> _transform;
            std::shared_ptr<Sound> _deathSound;
            std::shared_ptr<Health> _health;
            std::shared_ptr<Collision> _collision;
            std::shared_ptr<Render> _render;
            std::vector<std::shared_ptr<AComponents>> _componentList;
    };
}

#endif /* !DESTROYABLETILE_HPP_ */
