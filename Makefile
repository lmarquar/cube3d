CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra -g
PARSER_FILES	:= parser.c
PARSER_DIR		:= parser/
PARSER			:= $(addprefix $(PARSER_DIR),$(PARSER_FILES))
SRC_FILES		:= cube3d.c $(PARSER)
SRCDIR			:= cubeh/
SRC				:= $(addprefix $(SRCDIR),$(SRC_FILES))
NAME			:= cube3d
LIBFT_DIR		:= $(SRCDIR)libft/
LIBFT			:= $(LIBFT_DIR)libft.a

ifeq ($(shell uname -s),Darwin)
	LBMLX	:= $(SRCDIR)mlx/libmlx.a
	LIBS	:= -L /usr/X11/lib -lXext -lX11
else
	LBMLX	:= $(SRCDIR)mlx/libmlx_Linux.a
	LIBS	:= -lXext -lX11 -lm
endif

all: $(NAME)

re: clean $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(LBMLX) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(SRCDIR)libft/

clean:
	make clean -C $(LIBFT_DIR)

fclean:
	make clean -C $(LIBFT_DIR)
	rm -f $(NAME)
