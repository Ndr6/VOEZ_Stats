##
## EPITECH PROJECT, 2017
## Make-make's Makefile
## File description:
## By Ndr
##

###############
#  VARIABLES  #
###############

#Nom du projet (binaire)
NAME=		voez_stats

#Répertoire des sources (.c)
SRC_DIR=	$(realpath ./src)

UT_DIR=	$(realpath ./tests)

#Répertoire de la lib (.a)
LIB_DIR=	$(realpath ./lib/my)

#Répertoire des includes (.h)
INC_DIR=	$(realpath ./include)

#Fichiers sources à compiler
#(Par défaut, compile tous les .c du dossier src)
SRC=		$(SRC_DIR)/*.c

UT_SRC=	$(UT_DIR)/*.c

#Lib à inclure
LIB=		my

#Fichiers objets (.o)
OBJ=		$(SRC:.c=.o)

#Arguments gcc (Ajoutez ici les libs supplémentaires)
#Ex: -lm pour math.h, -lncurses pour ncurses, ...
GCC_ARG=	-L$(LIB_DIR) -l$(LIB) -I$(INC_DIR)
GCC_ARG_DEBUG=	-L$(LIB_DIR) -l$(LIB) -I$(INC_DIR) -g
GCC_ARG_UT=	-L$(LIB_DIR) -l$(LIB) -I$(INC_DIR) -g -lcriterion


############
#  RÈGLES  #
############

all:		$(NAME)

#Compilation normale (lib + binaire)
$(NAME):
		make -C $(LIB_DIR)
		@echo "\n\033[1m\033[36mCompiling $(NAME)...\033[0m"
		gcc -o $(NAME) $(SRC) $(GCC_ARG)

#Compilation "debug" pour Valgrind et GDB (binaire uniquement)
debug:
		@echo "\033[1m\033[92mCompiling $(NAME) in debug mode...\033[0m"
		gcc -o $(NAME) $(SRC) $(GCC_ARG_DEBUG)

tests:		fclean
		make -C $(LIB_DIR)
		@echo "\033[1m\033[92mCompiling $(NAME) in testing mode...\033[0m"
		gcc -o $(NAME) $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c)) $(UT_SRC) $(GCC_ARG_UT)
		@echo "\033[1m\033[92mLaunching $(NAME) tests...\033[0m"
		@./$(NAME) --list
		@./$(NAME) --verbose=1

#Efface les .o dans lib/my
clean:
		make clean -C $(LIB_DIR)
		@echo "\n\033[1m\033[33mCleaning files...\033[0m"
		rm -f $(OBJ)

#Efface le binaire et la lib
fclean:
		@echo "\n\033[1m\033[33mCleaning files and binary...\033[0m"
		rm -f $(NAME)
		make fclean -C $(LIB_DIR)

re:		fclean all