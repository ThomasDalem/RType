/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client Entities
*/

#ifndef __Entities__
#define __Entities__

#include <memory>
#include <vector>

#include "ImageSFML.hpp"

using namespace std;

namespace client {
    class Entities {
        public:
            Entities(int, size_t, string = "");
            ~Entities();

            void setId(int);
            void setName(string);
            int getId(void) const;
            string getName(void) const;
            shared_ptr<ImageSFML> getImage(void) const;
            size_t getEntityType() const;

        private:
            int _id;
            string _name;
            size_t _type;
            string _path;
            shared_ptr<ImageSFML> _image;

        protected:
    };
}

#endif