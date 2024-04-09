/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:28:32 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/09 20:06:55 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*info;

	if (argc != 2)
		error_handling("Arguments should be: ./so_long map.ber\n", NULL, NULL);
	info = ft_calloc(1, sizeof(t_game));
	info->argv_map = argv[1];
	info->moves = 0;
	run_all_checks(argv, info);
	info->mlx = mlx_init(WIDTH, HEIGHT, "So long and thanks", true);
	if (!info->mlx)
		error_handling("Failed to allocate mlx", NULL, info);
	loading_images(info);
	map_render(info);
	// mlx_loop_hook(info->mlx, ft_hook, info);
	mlx_key_hook(info->mlx, ft_hook, info);
	//OR || AND
	// mlx_loop_hook(info->mlx, ft_hook, info->mlx);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
	ft_printf("You reached the end of the main function...");
	return (EXIT_SUCCESS);
}

void	ft_hook(mlx_key_data_t	cur_key, void *game)
{
	t_game *info;
	t_point	current_position;

	info = (t_game *)game;
// ft_printf("info->split_map[0][0] = %c\n", info->split_map[0][0]);
// ft_printf("info->split_map[info->pawn_position.x][info->pawn_position.y] = %c\n", info->split_map[info->pawn_position.x][info->pawn_position.y]);
	current_position = info->pawn_position;
	if (cur_key.action == MLX_PRESS || cur_key.action == MLX_REPEAT)
	{
		if (cur_key.key == MLX_KEY_ESCAPE)
		{
			free(info);//free anything else
			mlx_close_window(info->mlx);
			exit(EXIT_SUCCESS);
		}
		if (cur_key.key == MLX_KEY_UP || cur_key.key == MLX_KEY_W)
			go_up(info);
		else if (cur_key.key == MLX_KEY_DOWN || cur_key.key == MLX_KEY_S)
			go_down(info);
		else if (cur_key.key == MLX_KEY_LEFT || cur_key.key == MLX_KEY_A)
			go_left(info);
		else if (cur_key.key == MLX_KEY_RIGHT || cur_key.key == MLX_KEY_D)
			go_right(info);
		if (current_position.x != info->pawn_position.x || current_position.y != info->pawn_position.y)
		{
			ft_printf("Moves: %d\n", info->moves);
			current_position = info->pawn_position;
		}
	}
}

/**
 * This function sets the key callback, which is called when a key is pressed
 * on the keyboard. Useful for single keypress detection.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The keypress callback function.
 * @param[in] param An additional optional parameter.
 */
// void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param);

/**
 * Generic loop hook for any custom hooks to add to the main loop. 
 * Executes a function per frame, so be careful.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] f The function.
 * @param[in] param The parameter to pass on to the function.
 * @returns Whether or not the hook was added successfully. 
 */
// bool mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param);

/**
 * A key action such as pressing or releasing a key.
 * 
 * @param RELEASE Execute when the key is being released.
 * @param PRESS Execute when the key is being pressed.
 * @param REPEAT Execute when the key is being held down.
 */
// typedef enum action
// {
// 	MLX_RELEASE = 0,
// 	MLX_PRESS	= 1,
// 	MLX_REPEAT	= 2,
// }	action_t;

/**
 * Callback function used to handle key presses.
 * 
 * @param[in] keydata The callback data, contains info on key, action, ...
 * @param[in] param Additional parameter to pass on to the function.
 */
// typedef void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param);

/**
 * An image instance can be summarized as just a simple
 * x, y & z coordinate.
 * 
 * Coordinates start from the top left of the screen at 0,0 and increase
 * towards the bottom right.
 * 
 * NOTE: To change the z value, use mlx_set_instance_depth!
 * 
 * @param x The x location.
 * @param y The y location.
 * @param z The z depth, controls if the image is on the fore or background.
 * @param enabled If true, the instance is drawn, else it's not.
 */
// typedef struct mlx_instance
// {
// 	int32_t	x;
// 	int32_t	y;
// 	int32_t	z;
// 	bool	enabled;
// }	mlx_instance_t;

/**
 * Key function callback data.
 * Data related to the mlx_key_hook function
 * 
 * @param key The key that was pressed.
 * @param action The action that was done with the key.
 * @param os_key The os_key is unique for every key, and will have a 
 * different value/keycode depending on the platform. 
 * They may be consistent on different platforms.
 * @param modifier The modifier key that was pressed, 0 if no key was pressed.
 */
// typedef struct mlx_key_data
// {
// 	keys_t			key;
// 	action_t		action;
// 	int32_t			os_key;
// 	modifier_key_t	modifier;
// }	mlx_key_data_t;

