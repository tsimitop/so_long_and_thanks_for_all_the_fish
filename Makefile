################################################################################
#									CONSTANTS								   #
################################################################################
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# LIBS = libft.h
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
LDFLAGS = -L $(LIBFT_PATH) -lft
PARSING_PATH = ./parsing
LIBMLX = ./MLX42
HEADERS = -I $(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -lglfw

NAME = so_long

################################################################################
#									MAIN PART								   #
################################################################################

SRCS =	$(PARSING_PATH)/valid_parse.c \
		$(PARSING_PATH)/flood.c \
		main.c

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) libmlx $(NAME)

libmlx :
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(OBJS) : %.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) -I$(LIBFT_PATH) -I include/ && printf "Compiling: $(notdir $<)"
# @$(CC) -c $(CFLAGS) -I $(LIBFT_PATH) -I include/ $< -o $@

clean :
	@echo "Removing $(OBJS)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(LIBMLX)/build

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
