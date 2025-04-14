# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -DDEBUG
RM          = rm -f
RMDIR       = rm -rf
SRCDIR      = src
# On déclare le dossier dans lequel on veut stocker nos fichiers objets
OBJDIR      = obj

# -----------------------------------------------------------------------------
# INCLUDES
# -----------------------------------------------------------------------------
INCS        = -I include

# **************************************************************************** #
#                    LISTE GLOBALE DES SOURCES ET DES OBJETS                   #
# **************************************************************************** #
# SRCS          = $(shell find $(SRCDIR) -type f -name '*.c')
SRCS          = src/action.c src/lifecycle.c src/main.c src/print.c src/setup.c src/state.c src/utils.c

# On veut que chaque .c soit compilé en obj/<path>.o
# ex: src/philo.c      -> obj/src/philo.o
#     lib/str/src/str_.. -> obj/lib/str/src/str_..o
OBJS        = $(SRCS:%.c=$(OBJDIR)/%.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

# -----------------------------------------------------------------------------
# Règle par défaut : all
# -----------------------------------------------------------------------------
all: $(NAME)

# -----------------------------------------------------------------------------
# Compilation de l'exécutable final
# -----------------------------------------------------------------------------
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $^ $(LIBS) -o $@

# -----------------------------------------------------------------------------
# Compilation des .c -> .o, placés dans obj/...
# -----------------------------------------------------------------------------
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

gdb:
	gdb --args ./philo 5 800 200 200 7

# -----------------------------------------------------------------------------
# Nettoyage des fichiers objets
# -----------------------------------------------------------------------------
clean:
	$(RMDIR) $(OBJDIR)

# -----------------------------------------------------------------------------
# Nettoyage complet (exécutable + objets)
# -----------------------------------------------------------------------------
fclean: clean
	$(RM) $(NAME)

# -----------------------------------------------------------------------------
# Recompilation totale
# -----------------------------------------------------------------------------
re: fclean all

# -----------------------------------------------------------------------------
# Installation (submodule) - si nécessaire
# -----------------------------------------------------------------------------
install:
	git submodule init
	git submodule update
	@echo "Submodules initialized/updated."


# -----------------------------------------------------------------------------
# Règles de debug, valgrind et TSAN
# -----------------------------------------------------------------------------
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
TEST_ARGUMENTS = 4 310 200 100

valgrind: CFLAGS += -g
valgrind: re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(TEST_ARGUMENTS)

data_race: CFLAGS += -pthread -fsanitize=thread -g -O1
data_race: re
	./$(NAME) $(TEST_ARGUMENTS)

debug: CFLAGS += -g
debug: re

# -----------------------------------------------------------------------------
# Déclaration des règles phony
# -----------------------------------------------------------------------------
.PHONY: all clean fclean re install debug valgrind