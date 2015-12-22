##
## Makefile for Rtype in /home/Opcoz/rendu/rtype/R-Type/Server
##
## Made by tran_0
## Login   <Opcoz@epitech.net>
##
## Started on  Wed Dec  9 16:40:40 2015 tran_0
## Last update Wed Dec  9 16:40:40 2015 tran_0
##

DEBUG		=	yes

CC		=	g++

RM		=	rm -fr

#########################################################
#                       SERVER                          #
#########################################################

NAME_SERVER	=	server

SRC_SERVER	=	main.cpp		\
			ThreadPool.cpp		\
			Client.cpp		\
			Server.cpp		\
			Game.cpp		\
			IEntity.cpp		\

OBJ_DIR		=	obj/

SRC_DIR		=	src/

LIBS_DIR	=	libs/

INC_DIR		=	includes/

#########################################################
#                       UDP                             #
#########################################################

SRC_UDP	=		Connection.cpp	\
			UDPSocket.cpp	\
			Address.cpp

OBJ_DIR_UDP	=	obj/

SRC_DIR_UDP	=	../Network/UDP/src/

INC_DIR_UDP	=	../Network/UDP/includes/

INC_DIR_INTER	=	../Network/Interfaces/

#########################################################
#                       TCP                             #
#########################################################

SRC_TCP	=		TCPConnection.cpp	\
			TCPSocket.cpp		\

OBJ_DIR_TCP	=	obj/

SRC_DIR_TCP	=	../Network/TCP/src/

INC_DIR_TCP	=	../Network/TCP/includes/

#########################################################
#                        FLAGS                          #
#########################################################

CFLAGS		=	-W -Wall -Wextra -I$(LIBS_DIR) -I$(INC_DIR)

CFLAGS		+=	-I$(INC_DIR_UDP) -I$(INC_DIR_TCP) -I$(INC_DIR_INTER) -std=c++11

LFLAGS		= 	-lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lpthread

ifeq ($(DEBUG),yes)

CFLAGS 		+= 	-g3

else

CFLAGS		+= 	-O3

endif

#########################################################
#                        RULES                          #
#########################################################

BUILD_PRINT	=	\e[1;34mBuilding\e[0m \e[1;33m$<\e[0m

OBJS		=	$(patsubst %.cpp,${OBJ_DIR}%.o, $(SRC_SERVER))

OBJS_UDP	=	$(patsubst %.cpp,${OBJ_DIR_UDP}%.o, $(SRC_UDP))

OBJS_TCP	=	$(patsubst %.cpp,${OBJ_DIR_TCP}%.o, $(SRC_TCP))

FIRST		:=	$(shell test -d $(OBJ_DIR) || mkdir $(OBJ_DIR))

FIRST		:=	$(shell test -d $(OBJ_DIR_UDP) || mkdir $(OBJ_DIR_UDP))

FIRST		:=	$(shell test -d $(OBJ_DIR_TCP) || mkdir $(OBJ_DIR_TCP))

$(OBJ_DIR)%.o	:	$(patsubst %.cpp, ${SRC_DIR}%.cpp, %.cpp)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_UDP)%.o:	$(patsubst %.cpp, ${SRC_DIR_UDP}%.cpp, %.cpp)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_UDP)%.o:	$(patsubst %.cpp, ${SRC_DIR_TCP}%.cpp, %.cpp)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERVER)	:	$(OBJS) $(OBJS_UDP) $(OBJS_TCP)
			$(CC) $(OBJS) $(OBJS_UDP) $(OBJS_TCP) -o $(NAME_SERVER) $(LFLAGS)

all		:
			@$(MAKE) --no-print-directory $(NAME_SERVER)

clean		:
			$(RM) $(OBJS) $(OBJ_DIR) $(OBJS_UDP) $(OBJS_TCP) $(OBJ_DIR_UDP) $(OBJ_DIR_TCP)

fclean		:	clean
			$(RM) $(NAME_SERVER)

re		:	fclean all

.PHONY		:	all clean fclean re
