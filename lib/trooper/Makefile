##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

NAME			=		lib_trooper.so

SRC				=		Trooper.cpp										\
						../../server/game_engine/src/Entities/Enemy.cpp	\

OBJSHARED		=		Trooper.o										\
						Enemy.o											\

OBJ 			=		$(SRC:.cpp=.o)

CC				= 		g++

CPPFLAGS		=		-I./ -I../../server/game_engine/include/Entities -I../../server/game_engine/include

all				:		$(NAME)

$(NAME)			:		$(OBJ)
						$(CC) -c -fPIC $(SRC) $(CPPFLAGS)
						$(CC) -shared -o $(NAME) $(OBJSHARED) $(CPPFLAGS)
						mv $(NAME) ../

clean		:
				rm -rf $(OBJSHARED)

fclean		:	clean
				rm -rf ../$(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re