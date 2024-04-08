#ifndef SO_LONG_H
# define SO_LONG_H

# define WIDTH 1000
# define HEIGHT 1000

# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "/Users/tsimitop/Documents/Testing/so_long_and_thanks_for_all_the_fish/Libft/libft.h"

typedef struct 	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_game
{
	char	buffer[450];
	mlx_t	*mlx;
	int		height;
	int		width;
	int		escape;
	int		coins;
	int		pawn;
	t_point	dimentions;
	t_point	pawn_position;
	char	**split_map; //free
	char	*argv_map;
	char	**allocated_map; //remove, works with split map
	// char	*collectible_path_png;
	// char	*pawn_path_png;
	// char	*floor_path_png;
	// char	*wall_path_png;
	// char	*exit_path_png;
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
void	assign_values(t_game *info, int *esc, int *coin, int *pawn);

void	map_init(t_game *info);
void	put_image(t_game *info, char c, int i, int j);
void	put_element(t_game *info, int i, int j, char *str);

#endif