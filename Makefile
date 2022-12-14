NAME =			fdf

NAME_DEBUG =	fdf_debug

H_FILES =	deal_key.h		\
			draw.h			\
			fdf.h			\
			init_fdf.h		\
			move_camera.h	\
			parsing.h		\
			render_frame.h	\
			start_fdf.h		\

HEADERS = ${addprefix includes/, ${H_FILES}}


INCLUDES =	-I ${LIBFT_PATH}includes/	\
			-I ${SLX_PATH}/includes/	\
			-I ${MLX_PATH}				\
			-I includes


SRCS_DIR = srcs/

SRCS =	deal_key/deal_key.c			\
		deal_key/move_camera_z.c	\
		deal_key/move_camera.c		\
		draw/draw_clipped_line.c	\
		draw/draw.c					\
		parsing/parsing_utils.c	\
		parsing/parsing.c		\
		init_fdf.c			\
		render_frame.c		\
		start_fdf.c	\
		main.c


DIR_OBJS = 		build/

OBJS =			${addprefix ${DIR_OBJS},${SRCS:.c=.o}}

OBJS_DEBUG =	${addprefix ${DIR_OBJS},${SRCS:.c=_debug.o}}


FLAGS =			-Wall -Wextra -Werror -O3

FLAGS_DEBUG	=	-Wall -Wextra -Werror -g3 -fsanitize=address


SLX_PATH =		libs/super_lib_x/

SLX_A =			${SLX_PATH}libslx.a

SLX_A_DEBUG =	${SLX_PATH}libslx_debug.a

SLX_L	=		-L${SLX_PATH} -lslx

SLX_L_DEBUG	=	-L${SLX_PATH} -lslx_debug


MLX_PATH =	${SLX_PATH}minilibx_macos/


LIBFT_L =		-L${LIBFT_PATH} -lft

LIBFT_L_DEBUG =	-L${LIBFT_PATH} -lft_debug

LIBFT_A =		${LIBFT_PATH}libft.a

LIBFT_A_DEBUG =	${LIBFT_PATH}libft_debug.a

LIBFT_PATH =	libs/libft/


SHARED_DEPENDENCIES =	Makefile ${HEADERS}

DEFAULT_DEPENDENCIES =	${LIBFT_A} ${SLX_A}

DEBUG_DEPENDENCIES = 	${LIBFT_A_DEBUG} ${SLX_A_DEBUG}


FRAMEWORKS =	-framework OpenGL -framework AppKit


DEBUG_L = ${LIBFT_L_DEBUG} ${SLX_L_DEBUG}

DEFAULT_L = ${LIBFT_L} ${SLX_L}


RMF =	 		rm -f

MKDIR = 		mkdir -p

MAKE_LIBFT =	${MAKE} -C ${LIBFT_PATH}

MAKE_SLX = 		${MAKE} -C ${SLX_PATH}


all:			${DIR_OBJS}
				${MAKE_LIBFT}
				${MAKE_SLX}
				@${MAKE} -j ${NAME}

$(NAME):		${OBJS}
				${CC} ${FLAGS} ${FRAMEWORKS} ${INCLUDES}	\
					${DEFAULT_L} ${OBJS} -o ${NAME}

${DIR_OBJS}%.o: ${SRCS_DIR}%.c ${SHARED_DEPENDENCIES} ${DEFAULT_DEPENDENCIES}
				${CC} ${FLAGS} ${INCLUDES} -c $< -o $@

debug:			${DIR_OBJS}
				${MAKE_LIBFT} debug
				${MAKE_SLX} debug
				${MAKE} -j ${NAME_DEBUG}

${NAME_DEBUG}:	${OBJS_DEBUG}
				${CC} ${FLAGS_DEBUG} ${FRAMEWORKS} ${INCLUDES}	\
					${DEBUG_L} ${OBJS_DEBUG} -o ${NAME_DEBUG}

${DIR_OBJS}%_debug.o: ${SRCS_DIR}%.c ${SHARED_DEPENDENCIES} ${DEBUG_DEPENDENCIES}
					cc ${FLAGS_DEBUG} ${INCLUDES} -c $< -o $@

clean:
				${MAKE_SLX} clean
				${MAKE_LIBFT} clean
				${RMF} ${OBJS} ${OBJS_DEBUG}

fclean:			clean
				${MAKE_LIBFT} fclean
				${MAKE_SLX} fclean
				${RMF} ${NAME} ${NAME_DEBUG}

re:				fclean
				${MAKE} all

re_debug:				fclean
				${MAKE} debug

${DIR_OBJS}: Makefile
				@echo ${OBJS} | tr ' ' '\n'\
					| sed 's|\(.*\)/.*|\1|'\
					| sed 's/^/${MKDIR} /'\
					| sh -s
				@# Prints all OBJS. 1 per line
					@# Removes the .o file names
					@# Adds mkdir -p at start of each lines
					@# Executes the script (Creates all folders)

run:			all
				./fdf data/france.fdf

run_debug:		debug
				./fdf_debug data/france.fdf

.PHONY:			all debug clean fclean re re_debug run run_debug
