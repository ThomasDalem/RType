##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##


NAME		=		lib_system.so

SRC			=		src/System.cpp			\

OBJSHARED	=		System.o				\

OBJ 		=		$(SRC:.cpp=.o)			\

CC			= 		g++

CPPFLAGS	=		-I./include

all			:		$(NAME)

$(NAME)		:		$(OBJ)
					$(CC) -c -fPIC $(SRC) $(CPPFLAGS)
					$(CC) -shared -o $(NAME) $(OBJSHARED) $(CPPFLAGS)
					mv $(NAME) ../lib/

clean		:
					rm -rf $(OBJ)
					rm -rf $(OBJSHARED)

fclean		:		clean
					rm -rf ../lib/$(NAME)

re			:		fclean all

.PHONY		:		all clean fclean re