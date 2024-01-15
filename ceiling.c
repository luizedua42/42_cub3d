/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:26:25 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/10 12:03:41 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ceiling_color(int color, t_mlx* mlx)
{
	int y = 0;
	while (y < WIN_H / 2)
	{
		int x = 0;
		while (x < WIN_W)
		{
			paint_img(mlx, color, x, y);
			x++;
		}
		y++;
	}
}
void	floor_color(int color, t_mlx* mlx)
{
	int y = WIN_H / 2;
	while (y < WIN_H)
	{
		int x = 0;
		while (x < WIN_W)
		{
			paint_img(mlx, color, x, y);
			x++;
		}
		y++;
	}
}