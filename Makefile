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
#                              SOURCES PRINCIPAUX                              #
# **************************************************************************** #
# philo_SRCS = \
# src/philo.c \
# src/algorithm/closest_index.c \
# src/algorithm/move_operations.c \
# src/algorithm/move_operations2.c \
# src/algorithm/rotation_cases.c \
# src/algorithm/rotation_costs.c \
# src/algorithm/sort_operations.c \
# src/algorithm/turk_algorithm.c \
# src/args/args.c \
# src/ope/ope.c \
# src/ope/push.c \
# src/ope/rotate.c \
# src/ope/rrotate.c \
# src/tools/tools.c \
# src/tools/max_min.c \
# src/tools/atoi.c \
# src/error.c \
# src/init.c \
# src/node.c \

# **************************************************************************** #
#                    LISTE GLOBALE DES SOURCES ET DES OBJETS                   #
# **************************************************************************** #
# SRCS        = $(philo_SRCS) $(MEM_SRCS) $(STR_SRCS)
SRCS          = $(shell find $(SRCDIR) -type f -name '*.c')

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
# Règles de debug, valgrind
# -----------------------------------------------------------------------------
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
TEST_ARGUMENTS = 4 410 200 200 80

valgrind: CFLAGS += -g
valgrind: re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(TEST_ARGUMENTS)

helgrind: CFLAGS += -g
helgrind: VALGRIND_FLAGS = --quiet --tool=helgrind
helgrind: re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(TEST_ARGUMENTS)

debug: CFLAGS += -g
debug: re

# -----------------------------------------------------------------------------
# Déclaration des règles phony
# -----------------------------------------------------------------------------
.PHONY: all clean fclean re install debug valgrind