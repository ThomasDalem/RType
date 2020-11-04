/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** IEntities
*/

#ifndef IENTITIES_HPP_
#define IENTITIES_HPP_

#include <memory>
#include <vector>
#include "../Exception.hpp"
#include "../Components/AComponents.hpp"
#include "../EntitiesEnum.hpp"

namespace game_engine {
    class IEntities {
        public:
            virtual ~IEntities() = default;
            virtual int getUniqueID() const = 0;
            virtual EntitiesType getEntitiesID() const = 0;
            virtual std::vector<std::shared_ptr<AComponents>> getComponentList() const = 0;
    };
}

#endif /* !IENTITIES_HPP_ */