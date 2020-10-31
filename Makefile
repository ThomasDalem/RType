##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

all		:
				make -C ./server
				make -C ./client

server	:
				make re -C ./server

client	:
				make re -C ./client

clean	:
				make clean -C ./server
				make clean -C ./client

fclean	:
				make fclean -C ./server
				make fclean -C ./client

re		:		fclean all

.PHONY: server client all clean fclean re