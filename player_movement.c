/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:12:50 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/12 13:58:58 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_mlx *mlx, double x, double y);

static void	move_player(int key, t_mlx *mlx)
{
	char **map;
	clear_display(mlx);
	map = map_creation(&mlx->map, mlx);
	if (key == XK_Up)
	{
		move(mlx, mlx->p1.dx, mlx->p1.dy);
	}
	else if (key == XK_Down)
	{
		move(mlx, -mlx->p1.dx, -mlx->p1.dy);
	}
	else if (key == XK_Left)
	{
		mlx->p1.ang -= RAD * 2;
		if (mlx->p1.ang < 0)
			mlx->p1.ang = RAD * 359;
	}
	else if (key == XK_Right)
	{
		mlx->p1.ang += RAD * 2;
		if (mlx->p1.ang > (2 * M_PI))
			mlx->p1.ang = RAD - RAD;
	}
	mlx->p1.dx = cos(mlx->p1.ang);
	mlx->p1.dy = sin(mlx->p1.ang);
	rays(mlx, map);
	draw_p1line(mlx);
}

int	key_press(int key_code, t_mlx *mlx)
{
	if (key_code == XK_Escape)
		close_win(mlx);
	else if (key_code == XK_Up || key_code == XK_Down ||
				key_code == XK_Left || key_code == XK_Right)
		move_player(key_code, mlx);
	return (0);
}

void	draw_p1line(t_mlx *mlx)
{
	double	step;
	double	dx;
	double	dy;
	double	x;
	double	y;
	double	i;

	dx = mlx->p1.dx * 8;
	dy = mlx->p1.dy * 8;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = mlx->p1.x;
	y = mlx->p1.y;
	i = 0;
	while (i <= step)
	{
		if (x < 0 || y < 0)
			break ;
		paint_img(mlx, 0x000FF, x, y);
		x += dx;
		y += dy;
		i++;
	}
}

void move(t_mlx *mlx, double x, double y)
{
	if (((mlx->p1.x / 8) + x) >= -0.9 && mlx->map.map[(int)mlx->p1.y / 8][(int)(mlx->p1.x + x) / 8] == '0')
		mlx->p1.x += x;
	if (((mlx->p1.y / 8) + y) >= -0.9 && mlx->map.map[(int)(mlx->p1.y + y) / 8][(int)(mlx->p1.x) / 8] == '0')
		mlx->p1.y += y;

}

