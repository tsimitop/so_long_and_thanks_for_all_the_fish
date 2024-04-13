#ifndef SO_LONG_H
# define SO_LONG_H

// # define WIDTH 1000
// # define HEIGHT 1000
# define TILE_SIZE 32 // biggest will be 64
// # define UP info->split_map[info->pawn_position.x - 1][info->pawn_position.y]
// # define DOWN info->split_map[info->pawn_position.x + 1][info->pawn_position.y]
// # define LEFT info->split_map[info->pawn_position.x][info->pawn_position.y - 1]
// # define RIGHT info->split_map[info->pawn_position.x][info->pawn_position.y + 1]

# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"

typedef struct 	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_game
{
	char	buffer[5000];
	// char	*buffer;
	mlx_t	*mlx;
	int		height; //max height for 32 = 40
	int		width; //max width for 32 = 79
	int		escape;
	int		coins;
	int		init_coins;
	t_point	dimentions;
	t_point	pawn_position;
	char	**split_map; //free
	char	*argv_map;
	int		moves;
	mlx_image_t	*image_pawn;
	mlx_image_t	*image_floor;
	mlx_image_t	*image_wall;
	mlx_image_t	*image_exit;
	mlx_image_t	*image_coin;
}				t_game;

void	run_all_checks(char **argv,t_game *info);
void	check_walls_paths(char **spl_buf, t_game *info);
void	check_paths(char **spl_buf, t_game *info);
void	fill(char **spl_buf, t_point size, t_point spot);

void	check_walls(char **spl_buf, t_game *info);
char	**split_buffer(t_game *info, int *esc, int *coin, int *pawn);
void	check_map_file_cont(char **argv, t_game *info);
void	fill_buffer_check_rect_empty(int fd, t_game *info);
void	error_handling(char *str, int *fd, t_game *info);
void	check_exit_coin_pawn(char *str, int *esc, int *coin, int *pawn);
int		check_rect(char *gnl);
void	assign_values(t_game *info, int *esc, int *coin);

// void	map_init(t_game *info);
void	put_wall_floor(t_game *info, char c, int i, int j);
// mlx_image_t	*put_element(t_game *info, int i, int j, char *str);
void	go_up(t_game *info);
void	go_left(t_game *info);
void	go_down(t_game *info);
void	go_right(t_game *info);
void	ft_hook(mlx_key_data_t	cur_key, void *game);
void	map_render(t_game *info);
void	loading_images(t_game *info);
void	print_buffer(t_game *info);
void	print_spl_buf(char **spl_buf);
void	remove_coin_instance(t_game *info);
void	put_coin_pawn(t_game *info, char c, int i, int j);

#endif