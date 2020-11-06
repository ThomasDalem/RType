##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

all		:
				make -C ./server
				make -C ./client
				make -C ./lib

server	:
				make re -C ./server

client	:
				make re -C ./client

lib		:
				make re -C ./lib

clean	:
				make clean -C ./server
				make clean -C ./client
				make clean -C ./lib

fclean	:
				make fclean -C ./server
				make fclean -C ./client
				make fclean -C ./lib

re		:		fclean all

.PHONY: server client libc all clean fclean re