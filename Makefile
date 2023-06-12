###########################################################
#### NAME

NAME			= pipex

###########################################################
#### PATH TO SOURCES

PATH_SRCS 		+= srcs/

SRCS			+= 01_pipex.c
SRCS			+= 02_initialisation.c
SRCS			+= 03_parsing.c
SRCS			+= 04_set_files.c
SRCS			+= 05_utils.c

vpath %.c $(PATH_SRCS)

###########################################################
#### OBJS

PATH_OBJS		= objs/
OBJS			= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

###########################################################
#### INCLUDES

INCLUDES			= -I inc/ -I libft
HEADER			= inc/pipex.h
LIBFTPATH		= -L libft -lft
LIBS			= ${INCLUDE} ${LIBFTPATH}

###########################################################
#### COMPILATION

CC				=	clang
CFLAGS			+=	-Wall
CFLAGS			+=	-Wextra
CFLAGS			+=	-Werror

###########################################################
#### RULES

all: $(NAME)

$(NAME): $(OBJS)
	@	+$(MAKE) -C libft
		$(CC) $(CFLAGS) $(OBJS) -o $@ ${LIBS} $(INCLUDES)

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADER)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) 

clean:
	@	+$(MAKE) -C libft clean
	$(RM) -R $(PATH_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE)\

.PHONY: all clean fclean re

###########################################################
#### HELP

#		CIBLE > DEPENDANCES > REGLES
# 		variables spéciales :
#
# $+ idem que $^ mais avec les doublons
# $| idem que $^ mais avec les doublons et triés
# $% nom de la cible d'une règle de substitution
# $! nom de la cible d'une règle de substitution
# $< nom de la première dépendance d'une règle de substitution
# $> nom de la dernière dépendance d'une règle de substitution
# $^ liste des dépendances d'une règle de substitution
# $@ nom de la cible d'une règle de substitution
# $? liste des dépendances plus récentes que la cible d'une règle de substitution
# $* nom du fichier sans son extension d'une règle de substitution
# $(@D) pour extraire le chemin du répertoire de destination du fichier .o et crée le répertoire si nécessaire.
