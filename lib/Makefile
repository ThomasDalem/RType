##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

all		:
				make -C ./alien
				make -C ./trooper
				make -C ./battleship

alien	:
				make re -C ./alien

trooper	:
				make re -C ./trooper

battleship	:
				make re -C ./battleship

clean	:
				make clean -C ./alien
				make clean -C ./trooper
				make clean -C ./battleship

fclean	:
				make fclean -C ./alien
				make fclean -C ./trooper
				make fclean -C ./battleship

re		:		fclean all

.PHONY	: 		alien trooper battleship all clean fclean re