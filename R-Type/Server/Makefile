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
#                       COMMON                          #
#########################################################

SRC_COMMON	=

OBJ_DIR_COMMON	=	obj/

SRC_DIR_COMMON	=	src/

INC_DIR_COMMON	=	includes/

#########################################################
#                        FLAGS                          #
#########################################################

CFLAGS		=	-W -Wall -Wextra -I$(LIBS_DIR) -I$(INC_DIR)

CFLAGS		+=	-I$(INC_DIR_COMMON) -std=c++11

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

OBJS_COMMON	=	$(patsubst %.cpp,${OBJ_DIR_COMMON}%.o, $(SRC_COMMON))

FIRST		:=	$(shell test -d $(OBJ_DIR) || mkdir $(OBJ_DIR))

FIRST		:=	$(shell test -d $(OBJ_DIR_COMMON) || mkdir $(OBJ_DIR_COMMON))

$(OBJ_DIR)%.o	:	$(patsubst %.cpp, ${SRC_DIR}%.cpp, %.cpp)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_COMMON)%.o:	$(patsubst %.cpp, ${SRC_DIR_COMMON}%.cpp, %.cpp)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERVER)	:	$(OBJS) $(OBJS_COMMON)
			$(CC) $(OBJS) $(OBJS_COMMON) -o $(NAME_SERVER) $(LFLAGS)

all		:
			@$(MAKE) --no-print-directory $(NAME_SERVER)

clean		:
			$(RM) $(OBJS) $(OBJ_DIR) $(OBJS_COMMON) $(OBJ_DIR_COMMON)

fclean		:	clean
			$(RM) $(NAME_SERVER)

re		:	fclean all

.PHONY		:	all clean fclean re
