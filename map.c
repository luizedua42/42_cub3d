/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:51:57 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/15 12:09:31 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_creation(t_map *map)
{
	map->map = calloc(9, sizeof(char *));
	map->map[0] = "11111111";
	map->map[1] = "10010001";
	map->map[2] = "10010001";
	map->map[3] = "10010001";
	map->map[4] = "10000001";
	map->map[5] = "10000101";
	map->map[6] = "10000001";
	map->map[7] = "11111111";
	map->x = 0;
	map->y = 0;
}

void	draw_map(t_map *map,  t_mlx *mlx, char **bitmap)
{

	while (map->y < 8)
	{
		map->x = 0;
		while (map->x < 8)
		{
			if (bitmap[map->y][map->x] == '1')
				draw_square(mlx, map->x * 8, map->y * 8, 0xFFFFFF);
			else
				draw_square(mlx, map->x * 8, map->y * 8, 0x888888);
			map->x++;
		}
		map->y++;
	}
}
void draw_square(t_mlx *mlx, int map_x, int map_y, int color)
{
	int y = 0;
	while (y < 8)
	{
		int x = 0;
		while (x < 8)
		{
			paint_img(mlx, color, map_x + x, map_y + y);
			x++;
		}
		y++;
	}
}