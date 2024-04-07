/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:28:32 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/07 18:35:10 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*info;
	// mlx_t	*mlx;

	if (argc != 2)
		error_handling("Arguments should be: ./so_long map.ber\n", NULL, NULL);
	info = ft_calloc(1, sizeof(t_game));
	run_all_checks(argv, info);
	info->mlx = mlx_init(WIDTH, HEIGHT, "So long and thanks", true);
	if (!info->mlx)
		error_handling("Failed to allocate mlx", NULL, info);
	map_init(info);
	// mlx_key_hook(bomberman->mlx, ft_hook, bomberman);
	//OR || AND
	// mlx_loop_hook(info->mlx, ft_hook, info->mlx);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
	ft_printf("You reached the end of the main function...");
	return (EXIT_SUCCESS);
}
