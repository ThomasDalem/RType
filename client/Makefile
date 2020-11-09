##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##


NAME = r-type_client

SRC = 	main.cpp						\
		\
		src/SFML/Button.cpp				\
		src/SFML/ImageSFML.cpp			\
		src/SFML/TextSFML.cpp			\
		src/SFML/BackgroundSFML.cpp		\
		\
		src/Menu/Main.cpp				\
		src/Menu/Room.cpp				\
		\
		src/Entities/Player.cpp			\
		src/Entities/Monster.cpp		\
		src/Entities/SMonster.cpp		\
		\
		src/Network/NetUDPClient.cpp	\
		\
		src/Client.cpp					\
		src/ErrorHandler.cpp			\
		src/WindowHandler.cpp			\


OBJSHARED =		Client.o	\

OBJ =	$(SRC:.cpp=.o)	\

CC = g++

CPPFLAGS =	-I./include			\
			-I./Class			\
			-I./Class/Entities	\
			-I./Class/SFML		\
			-I./Class/Menu		\

EXT = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -pthread

WALL = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(WALL) $(EXT)
			mv $(NAME) ../

clean:
		rm -rf $(OBJ)
		rm -rf $(OBJSHARED)

fclean: clean
		rm -rf ../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re