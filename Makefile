################################################################################
#									CONSTANTS								   #
################################################################################
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
LDFLAGS = -L $(LIBFT_PATH) -L $(LIBMLX_PATH)/build -lft -lmlx42 -lglfw -ldl -lm -pthread
PARSING_PATH = ./parsing
MOVING_PATH = ./moving
LIBMLX_PATH = ./MLX42
HEADERS = -I $(LIBMLX_PATH)/include
LIBS = $(LIBMLX_PATH)/build/libmlx42.a -lglfw

NAME = so_long

################################################################################
#									MAIN PART								   #
################################################################################

SRCS =	$(PARSING_PATH)/valid_parse.c \
		$(PARSING_PATH)/flood.c \
		$(PARSING_PATH)/main_check.c \
		$(MOVING_PATH)/go_places.c \
		$(MOVING_PATH)/position_cases.c \
		$(MOVING_PATH)/final_moves.c \
		checks.c \
		main.c \
		initialization.c

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(LIBS) $(NAME)

$(LIBS) :
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build

$(NAME) : $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(OBJS) : %.o : %.c
	@$(CC) -c $(CFLAGS) -I$(LIBFT_PATH) -I include/ $(HEADERS) $< -o $@ && printf "Compiling: $(notdir $<\n)"

clean :
	@echo "Removing $(OBJS)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(LIBMLX_PATH)/build

fclean : clean
	@echo "Removing $(NAME)"
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re : fclean all

################################################################################
#									LIBFT									   #
################################################################################

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_PATH) --no-print-directory

.PHONY :
	all clean fclean re libmlx
