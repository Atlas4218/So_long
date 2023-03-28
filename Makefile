NAME = so_long

SRC = src
INC = inc
MINILIBX = minilibx-linux
LIBFT = libft
BIN = bin

SOURCE = ${SRC}/main.c\
	 ${SRC}/move.c\
	 ${SRC}/gest_map.c\
	 ${SRC}/gest_offset.c\
	 ${SRC}/get_next_line.c\
	 ${SRC}/get_next_line_utils.c\
	 ${SRC}/utils.c\
	 ${SRC}/init.c\
	 ${SRC}/renders.c

OBJECT = ${patsubst %,${BIN}/%, ${notdir ${SOURCE:.c=.o}}}

CFLAGS = -g3 -Wall -Wextra -Werror
RM = rm -f
CC = cc

${BIN}/%.o : ${SRC}/%.c 
	${CC} ${CFLAGS} -I${INC} -I/usr/include -I${MINILIBX} -I${LIBFT} -c $< -o $@

all:	${NAME}

${NAME}: ${OBJECT}
	cd ${MINILIBX};\
	make;\
	cd ../${LIBFT};\
	make;\
	cd ..;\
	${CC} -o ${NAME} ${OBJECT} -L${MINILIBX} -lmlx_Linux -L${LIBFT} -lft -L/usr/lib -I${MINILIBX} -I${LIBFT} -lXext -lX11;

clean:
	${RM} ${OBJECT};\
	cd ${LIBFT};\
	make clean;\
	cd ..;

fclean:		clean
		${RM} ${NAME};\
		cd ${LIBFT};\
		make fclean;\
		cd ../${MINILIBX};\
		make clean;\
		cd ..;
		
re:	fclean all

.PHONY: all clean fclean re
