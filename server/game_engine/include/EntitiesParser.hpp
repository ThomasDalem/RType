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
            static std::vector<std::shared_ptr<IEntities>> &getEntities(std::vector<EntitiesType> typeList, std::vector<std::shared_ptr<IEntities>> &listEntities, std::vector<std::shared_ptr<IEntities>> &newListEntities)
            {
                std::vector<std::shared_ptr<IEntities>>::iterator listEntitiesIter;
                int i = 0;

                for (listEntitiesIter = listEntities.begin(); listEntitiesIter != listEntities.end(); listEntitiesIter++) {
                    if (checkEntities(listEntitiesIter, typeList) == true) {
                        newListEntities.push_back(listEntities[i]);
                    }
                    i++;
                }
                return (newListEntities);
            }

            static bool checkEntities(std::vector<std::shared_ptr<IEntities>>::iterator entitie, std::vector<EntitiesType> typeList)
            {
                std::vector<EntitiesType>::iterator typeListIter;
                int i = 0;

                for (typeListIter = typeList.begin(); typeListIter != typeList.end(); typeListIter++) {
                    if (entitie->get()->getEntitiesID() == typeListIter[i])
                        return (true);
                    i++;
                }
                return (false);
            }
    };
}

#endif /* !ENTITIESPARSER_HPP_ */
