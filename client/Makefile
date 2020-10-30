##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##


NAME = r-type_client

SRC = 	main.cpp				\
		\
		src/ImageSFML.cpp		\
		\
		src/BackgroundSFML.cpp	\
		src/Client.cpp			\
		src/ErrorHandler.cpp	\
		src/Player.cpp			\
		src/VMonster.cpp		\
		src/WindowHandler.cpp	\


OBJSHARED =		Client.o	\

OBJ =	$(SRC:.cpp=.o)	\

CC = g++

CPPFLAGS = -I./include -I./Class

EXT = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

WALL = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(WALL) $(EXT)
			mv $(NAME) ../bin/

clean:
		rm -rf $(OBJ)
		rm -rf $(OBJSHARED)

fclean: clean
		rm -rf ../bin/$(NAME)

re:	fclean all

.PHONY:	all clean fclean re