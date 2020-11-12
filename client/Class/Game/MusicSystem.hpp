/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** Client
*/

#ifndef __MusicSystem__
#define __MusicSystem__

#include "MusicSFML.hpp"

using namespace std;
namespace client {
    class MusicSystem {
        public:
            MusicSystem();
            ~MusicSystem();

            void main(void);
            void shot(void);
            void dead(void);
            void blowup(void);

        private:
            MusicSFML _main;
            MusicSFML _shot;
            MusicSFML _dead;
            MusicSFML _blowup;

        protected:
    };
};

#endif