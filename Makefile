##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

all		:
				make -C ./server
				make -C ./client
				make -C ./game_engine

server	:
				make re -C ./server

client	:
				make re -C ./client

game_engine	:
				make re -C ./game_engine

clean	:
				make clean -C ./server
				make clean -C ./client
				make clean -C ./game_engine

fclean	:
				make fclean -C ./server
				make fclean -C ./client
				make fclean -C ./game_engine

re		:		fclean all

.PHONY: server client game_engine all clean fclean re