#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "/Users/tsimitop/Documents/Testing/so_long_and_thanks_for_all_the_fish/Libft/libft.h"

typedef struct	s_game
{
	char	buffer[450];
	int		height; //y rows
	int		width; //x columns
	// int		enemy; //will I?
	int		escape; //== 1
	int		coins; // > 1
	int		pawn; // == 1

}				t_game;

void	run_all_checks(char **argv,t_game *info);
void	check_walls_paths(char **spl_buf, t_game *info);
// void	check_paths(char **spl_buf);
void	check_walls(char **spl_buf, t_game *info);
char	**split_buffer(t_game *info, int *esc, int *coin, int *pawn);
void	check_map_file_cont(char **argv, t_game *info);
void	fill_buffer_check_rect_empty(int fd, t_game *info);
void	error_handling(char *str, int *fd);
void	check_exit_coin_pawn(char *str, int *esc, int *coin, int *pawn);
int		check_rect(char *gnl);
void	assign_values(t_game *info, int *esc, int *coin, int *pawn);

// void	check_map_file_chars_shape(char **argv);
// void	check_map_empty_rect(int fd, int *esc, int *coin, int *pawn);
// void	map_height_width(char **argv, t_game *node);
// void	check_edges(t_game *node, char **argv);

#endif