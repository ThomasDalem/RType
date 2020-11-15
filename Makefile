##
## EPITECH PROJECT, 2020
## B-CPP-501-PAR-5-1-rtype-romeo.talovici
## File description:
## Makefile
##

ENTI = ./client/src/Entities/
ENVS = ./client/src/Env/
GAME = ./client/src/Game/
MENU = ./client/src/Menu/
NETW = ./client/src/Network/
SFML = ./client/src/SFML/

TESTS = ./tests/

SRC =	$(TESTS)test_Entities.cpp	\
		$(TESTS)test_Env.cpp		\
		$(TESTS)test_Game.cpp		\
		$(TESTS)test_SFML.cpp		\
		\
		$(ENVS)Exception.cpp		\
		$(ENVS)ErrorHandler.cpp		\
		\
		$(ENTI)Entities.cpp			\
		$(ENTI)Player.cpp			\
		\
		$(GAME)Animation.cpp		\
		$(GAME)Client.cpp			\
		$(GAME)Environment.cpp		\
		$(GAME)MusicSystem.cpp		\
		$(GAME)WindowHandler.cpp	\
		\
		$(MENU)Main.cpp				\
		$(MENU)Room.cpp				\
		\
		$(NETW)NetTCPClient.cpp		\
		$(NETW)NetUDPClient.cpp		\
		\
		$(SFML)BackgroundSFML.cpp	\
		$(SFML)Button.cpp			\
		$(SFML)ImageSFML.cpp		\
		$(SFML)MusicSFML.cpp		\
		$(SFML)ManetteSFML.cpp		\
		$(SFML)TextSFML.cpp			\


OBJ =	$(SRC:.cpp=.o)

CRIT = --coverage -lcriterion

CRITERION = unit_tests

E_SFML = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
E_THREAD = -pthread
E_BOOST = -lboost_system -lboost_thread

CPPFLAGS =	-I./client/include/		\
			\
			-I./client/Class/Entities	\
			-I./client/Class/Env		\
			-I./client/Class/Game		\
			-I./client/Class/Menu		\
			-I./client/Class/Network	\
			-I./client/Class/SFML		\

all:
	make -C ./server
	make -C ./client
	make -C ./lib

server:
	make re -C ./server

client:
	make re -C ./client

lib:
	make re -C ./lib

clean:
	make clean -C ./server
	make clean -C ./client
	make clean -C ./lib

fclean:
	make fclean -C ./server
	make fclean -C ./client
	make fclean -C ./lib

tests_run:	$(OBJ)
			g++ -o $(CRITERION) $(CRIT) $(OBJ) $(CPPFLAGS) $(E_SFML) $(E_THREAD) $(E_BOOST)
			./$(CRITERION)

clean_test: $(OBJ)
			g++ -o $(CRITERION) $(CRIT) $(OBJ) $(CPPFLAGS) $(E_SFML) $(E_THREAD) $(E_BOOST)
			./$(CRITERION)
			gcovr
			rm -vf *.o
			rm -vf *.gcno
			rm -vf *.gcda
			rm $(CRITERION)

re: fclean all

.PHONY: server client libc all clean fclean re