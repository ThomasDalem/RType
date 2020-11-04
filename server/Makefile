##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

GAME_ENGINE_PATH	=	game_engine/src

NAME		=		r-type_server

SRC			=		main.cpp											\
					src/Server.cpp										\
					$(GAME_ENGINE_PATH)/System.cpp						\
					$(GAME_ENGINE_PATH)/MoveSystem.cpp					\
					$(GAME_ENGINE_PATH)/CollisionSystem.cpp				\
					$(GAME_ENGINE_PATH)/SpawnSystem.cpp					\
					$(GAME_ENGINE_PATH)/DamageSystem.cpp				\
					$(GAME_ENGINE_PATH)/Exception.cpp					\
					$(GAME_ENGINE_PATH)/Entities/Bullet.cpp				\
					$(GAME_ENGINE_PATH)/Entities/DestroyableTile.cpp	\
					$(GAME_ENGINE_PATH)/Entities/Enemy.cpp				\
					$(GAME_ENGINE_PATH)/Entities/Environment.cpp		\
					$(GAME_ENGINE_PATH)/Entities/Player.cpp				\
					$(GAME_ENGINE_PATH)/Entities/PowerUp.cpp			\
					$(GAME_ENGINE_PATH)/Entities/StageObstacle.cpp		\

OBJSHARED	=		Server.o				\

OBJ 		=		$(SRC:.cpp=.o)			\

CC			= 		g++

CPPFLAGS	=		-I./game_engine/include -I./Class -I./game_engine/include/Entities

WALL 		=		-Wall -Wextra -Werror

all			:		$(NAME)

$(NAME)		:		$(OBJ)
					$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(WALL)
					mv $(NAME) ../

clean		:
					rm -rf $(OBJ)
					rm -rf $(OBJSHARED)

fclean		:		clean
					rm -rf ../$(NAME)

re			:		fclean all

.PHONY		:		all clean fclean re