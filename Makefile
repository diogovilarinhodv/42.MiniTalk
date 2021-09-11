CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= run

AR	= ar rc

RM	= rm -rf

OBJS_CLIENT	= ${SRC_CLIENT:.c=.o}

OBJS_SERVER	= ${SRC_SERVER:.c=.o}

OBJS_LIBFT = ${SRC_LIBFT:.c=.o}

LIB_CLIENT	= lib/client.a

LIB_SERVER	= lib/server.a

SRC_CLIENT	= src/client.c

SRC_SERVER = src/server.c

SRC_LIBFT	= Libft/ft_itoa.c Libft/ft_strlen.c Libft/ft_strdup.c Libft/ft_atoi.c

LIB_FOLDER	= lib

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	| $(LIB_FOLDER) $(NAME)  

$(NAME): ${OBJS_CLIENT} ${OBJS_SERVER} ${OBJS_LIBFT}
	${AR} ${LIB_CLIENT} ${OBJS_CLIENT} ${OBJS_LIBFT}
	${AR} ${LIB_SERVER} ${OBJS_SERVER} ${OBJS_LIBFT}
	${CC} ${CFLAGS} ${LIB_CLIENT} -o client
	${CC} ${CFLAGS} ${LIB_SERVER} -o server

$(LIB_FOLDER):
	mkdir -p $(LIB_FOLDER)

clean:
	${RM} ${OBJS_CLIENT}
	${RM} ${OBJS_SERVER}
	${RM} ${OBJS_LIBFT}
	${RM} client
	${RM} server

fclean:	clean
	${RM} ${LIB_CLIENT}
	${RM} ${LIB_SERVER}
	${RM} $(LIB_FOLDER)
	
re:	fclean all

bonus: ${OBJS_CLIENT} ${OBJS_SERVER} ${OBJS_LIBFT}
	${AR} ${LIB_CLIENT} ${OBJS_CLIENT} ${OBJS_LIBFT}
	${AR} ${LIB_SERVER} ${OBJS_SERVER} ${OBJS_LIBFT}
	${CC} ${CFLAGS} ${LIB_CLIENT} -o client
	${CC} ${CFLAGS} ${LIB_SERVER} -o server

rebonus: re bonus

.PHONY:	all bonus rebonus clean fclean re