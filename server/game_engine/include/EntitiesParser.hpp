/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** EntitiesParser
*/

#ifndef ENTITIESPARSER_HPP_
#define ENTITIESPARSER_HPP_

#include <memory>
#include <vector>
#include <list>
#include "Entities/IEntities.hpp"
#include "EntitiesEnum.hpp"

namespace game_engine {
    class EntitiesParser {
        public:
            static std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> getEntities(std::vector<EntitiesType> typeList, std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> &listEntities)
            {
                std::shared_ptr<std::vector<std::shared_ptr<IEntities>>> newListEntities = std::make_shared<std::vector<std::shared_ptr<IEntities>>>();
                std::vector<std::shared_ptr<IEntities>>::iterator listEntitiesIter;
                int i = 0;

                for (listEntitiesIter = listEntities->begin(); listEntitiesIter != listEntities->end(); listEntitiesIter++) {
                    if (checkEntities(listEntitiesIter, typeList)) {
                        newListEntities->push_back(listEntities->at(i));
                    }
                    i++;
                }
                return (newListEntities);
            }

            static bool checkEntities(std::vector<std::shared_ptr<IEntities>>::iterator entitie, std::vector<EntitiesType> typeList)
            {
                for (int i = 0; i < typeList.size(); i++) {
                    if (entitie->get()->getEntitiesID() == typeList[i])
                        return (true);
                }
                return (false);
            }

            static bool isAnEnemy(game_engine::EntitiesType entitieID) {
                if (entitieID == game_engine::EntitiesType::ENEMYALIEN ||
                    entitieID == game_engine::EntitiesType::ENEMYBATTLESHIP ||
                    entitieID == game_engine::EntitiesType::ENEMYTROOPER)
                    return (true);
                return (false);
            }
        private:
        protected:
    };
}

#endif /* !ENTITIESPARSER_HPP_ */
