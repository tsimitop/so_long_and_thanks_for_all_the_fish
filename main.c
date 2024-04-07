/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:28:32 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/07 12:37:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*info;

	info = ft_calloc(1, sizeof(t_game));
	if (argc == 2)
	{
		run_all_checks(argv, info);
		// map_height_width(argv, node);
	}
	else
		ft_printf("Arguments should be: ./so_long map.ber\n"); //If any misconfiguration of any kind is encountered in the file, the program must exit in a clean way, and return "Error\n" followed by 
	ft_printf("You reached the end of the main function...");
	return (0);
}
