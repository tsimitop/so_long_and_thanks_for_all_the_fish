/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:27:42 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/09 19:30:17 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_render(t_game *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info->split_map[i])
	{
		while (info->split_map[i][j])
		{
			put_image(info, info->split_map[i][j], j, i);
			j++;
		}
		i++;
		j = 0;
	}
}

void	put_image(t_game *info, char c, int i, int j)
{
	if (c == '0')
	{
		if (mlx_image_to_window(info->mlx, info->image_floor, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
	}
		// put_element(info, i, j, "texture_folder/floor.png");
	else if (c == '1')
	{
		if (mlx_image_to_window(info->mlx, info->image_wall, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
	}
		// put_element(info, i, j, "png_folder/wall.png");
	else if (c == 'E')
	{
		if (mlx_image_to_window(info->mlx, info->image_exit, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
	}
		// put_element(info, i, j, "png_folder/exit.png");
	else if (c == 'C')
	{
		if (mlx_image_to_window(info->mlx, info->image_floor, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
		if (mlx_image_to_window(info->mlx, info->image_coin, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
	}
		// put_element(info, i, j, "png_folder/collectible.png");
	else if (c == 'P')
	{
		if (mlx_image_to_window(info->mlx, info->image_floor, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
		// put_element(info, i, j, "png_folder/floor.png");
		if (mlx_image_to_window(info->mlx, info->image_pawn, i * TILE_SIZE, j * TILE_SIZE) == -1)
			error_handling("Image", NULL, info);
		// put_element(info, i, j, "png_folder/player.png");
	}
}

// mlx_image_t	*_element(t_game *info, int i, int j, char *str)
// {
// 	mlx_texture_t	*texture;
// 	mlx_image_t		*img;

// 	i *= TILE_SIZE;
// 	j *= TILE_SIZE;
// 	texture = mlx_load_png(str);
// 	if (!texture)
// 		error_handling("texture", NULL, info);
// 	img = mlx_texture_to_image(info->mlx, texture); //info->image change it
// 	if (!img)
// 		error_handling("texture", NULL, info);
// 	mlx_resize_image(img, TILE_SIZE, TILE_SIZE);
// 	if (mlx_image_to_window(info->mlx, img, i, j))
// 		error_handling("Image", NULL, info);
// 	mlx_delete_texture(texture);
// 	return (img);
// }

static mlx_image_t	*load_image(char *str, t_game *info)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	// i *= TILE_SIZE;
	// j *= TILE_SIZE;
	texture = mlx_load_png(str);
	if (!texture)
		error_handling("texture", NULL, info);
	img = mlx_texture_to_image(info->mlx, texture); //info->image change it
	if (!img)
		error_handling("texture", NULL, info);
	mlx_delete_texture(texture);
	mlx_resize_image(img, TILE_SIZE, TILE_SIZE);
	return (img);
}

void	loading_images(t_game *info)
{
	info->image_pawn = load_image("png_folder/player.png", info);
	info->image_floor = load_image("png_folder/floor.png", info);
	info->image_wall = load_image("png_folder/wall.png", info);
	info->image_exit = load_image("png_folder/exit.png", info);
	info->image_coin = load_image("png_folder/collectible.png", info);
}
