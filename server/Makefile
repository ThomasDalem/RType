##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##


NAME		=		r-type_server

SRC			=		main.cpp				\
					src/Server.cpp			\

OBJSHARED	=		Server.o				\

OBJ 		=		$(SRC:.cpp=.o)			\

CC			= 		g++

CPPFLAGS	=		-I./include

WALL 		=		-Wall -Wextra -Werror

all			:		$(NAME)

$(NAME)		:		$(OBJ)
					$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(WALL)
					mv $(NAME) ../bin/

clean		:
					rm -rf $(OBJ)
					rm -rf $(OBJSHARED)

fclean		:		clean
					rm -rf ../bin/$(NAME)

re			:		fclean all

.PHONY		:		all clean fclean re