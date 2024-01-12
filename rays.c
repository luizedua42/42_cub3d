/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:01:11 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/12 11:00:31 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	distance(double x1, double x2, double y1, double y2);
void	paint_walls(t_mlx *mlx, int map_x, int map_y);
void	draw_walls(t_mlx *mlx, int r, int color);
void	draw_lines(t_mlx *mlx, int map_x, int map_y, int color, double off);

void	h_rays(t_mlx *mlx, char **map)
{
	int mx,my;
	double rx,ry, xo, yo;

	mlx->rays.hd = 10000;
	mlx->rays.hx = mlx->p1.x;
	mlx->rays.hy = mlx->p1.y;
	double aTan=-1/tan(mlx->rays.ra);
	if (mlx->rays.ra > M_PI)
	{
		ry = (((int)mlx->p1.y / 8) * 8) - 0.0001;
		rx = (mlx->p1.y - ry) * aTan+mlx->p1.x; 
		yo = -8;
		xo = -yo * aTan;
	}
	if (mlx->rays.ra < M_PI)
	{
		ry = (((int)mlx->p1.y / 8) * 8) + 8;
		rx = (mlx->p1.y - ry) * aTan + mlx->p1.x;
		yo = 8;
		xo = -yo * aTan;
	}
	if (mlx->rays.ra == 0 || mlx->rays.ra == M_PI)
	{
		rx = mlx->p1.x;
		ry = mlx->p1.y;
	}
	while (true)
	{
		mx = (int)rx / 8;
		my = (int)ry / 8;
		if( my < 0 || mx < 0 || mx > 7 || my > 7 || map[my][mx] == '1')
		{
			mlx->rays.hx = rx;
			mlx->rays.hy = ry;
			mlx->rays.hd = distance(mlx->p1.x, mlx->rays.hx, mlx->p1.y, mlx->rays.hy);
			break;
		}
		rx += xo;
		ry += yo;
	}
}

void	v_rays(t_mlx *mlx, char **map)
{
	int mx,my;
	double rx,ry, xo, yo;

	mlx->rays.vd = 10000;
	mlx->rays.vx = mlx->p1.x;
	mlx->rays.vy = mlx->p1.y;
	double nTan=-tan(mlx->rays.ra);
	if (mlx->rays.ra > (M_PI / 2) && mlx->rays.ra < (3 * M_PI / 2))
	{
		rx = (((int)mlx->p1.x / 8) * 8) - 0.0001;
		ry = (mlx->p1.x - rx) * nTan+mlx->p1.y; 
		xo = -8;
		yo = -xo * nTan;
	}
	if (mlx->rays.ra < (M_PI / 2) || mlx->rays.ra > (3 * M_PI / 2))
	{
		rx = (((int)mlx->p1.x / 8) * 8) + 8;
		ry = (mlx->p1.x - rx) * nTan + mlx->p1.y;
		xo = 8;
		yo = -xo * nTan;
	}
	if (mlx->rays.ra == (M_PI / 2) || mlx->rays.ra == (3 * M_PI / 2))
	{
		rx = mlx->p1.x;
		ry = mlx->p1.y;
	}
	while (true)
	{
		mx = (int)rx / 8;
		my = (int)ry / 8;
		if( my < 0 || mx < 0 || mx > 7 || my > 7 || map[my][mx] == '1')
		{
			mlx->rays.vx = rx;
			mlx->rays.vy = ry;
			mlx->rays.vd = distance(mlx->p1.x, mlx->rays.vx, mlx->p1.y, mlx->rays.vy);
			break;
		}
		rx += xo;
		ry += yo;
	}
}

void	draw_rays(t_mlx *mlx, double x2, double y2)
{
	double	step;
	double	dx;
	double	dy;
	double	x;
	double	y;
	double	i;

	dx = x2  - mlx->p1.x;
	dy = y2  - mlx->p1.y;
	step = 0;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = mlx->p1.x;
	y = mlx->p1.y;
	i = 0;
	while (i <= (int)step)
	{
		if (x < 0 || y < 0 || x > WIN_W || y >  WIN_H)
			break ;
		paint_img(mlx, 0xFF, x, y);
		x += dx;
		y += dy;
		i++;
	}
}

double distance(double x1, double x2, double y1, double y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	rays(t_mlx *mlx, char ** map)
{
	int r = 0;
	int color = 0;
	double ri;

	mlx->rays.ra = (mlx->p1.ang - RAD * (FOV / 2.0));
	ri = RAD * FOV / WIN_W;
	while (r < WIN_W)
	{
		if(mlx->rays.ra < 0)
			mlx->rays.ra += 2 * M_PI;
		if (mlx->rays.ra > 2 * M_PI)
			mlx->rays.ra -= 2*M_PI;
		h_rays(mlx, map);
		v_rays(mlx, map);
		if(mlx->rays.hd > mlx->rays.vd)
		{
			mlx->rays.fdist = mlx->rays.vd;
			color = 0x8c8535;
		}
		if (mlx->rays.hd < mlx->rays.vd)
		{
			mlx->rays.fdist = mlx->rays.hd;
			color = 0x92925b;
		}
		draw_walls(mlx, r, color);
		mlx->rays.ra += ri;
		r++;
	}
	draw_map(&mlx->map, mlx, map);
	draw_p1line(mlx);
}

void	draw_walls(t_mlx *mlx, int r, int color)
{
	double lineh;
	double lineo;
	double finald;
	double camang;

	camang = mlx->rays.ra - mlx->p1.ang;
	if(mlx->rays.ra < 0)
		mlx->rays.ra += 2 * M_PI;
	if (mlx->rays.ra > 2 * M_PI)
		mlx->rays.ra -= 2*M_PI;
	finald = mlx->rays.fdist * cos(camang);
	lineh = (8 * WIN_H / 2) / finald;
	if (lineh > WIN_H)
		lineh =	WIN_H;
	lineo = (((double)WIN_H) - lineh) / 2;
	draw_lines(mlx, r, lineh+lineo, color, lineo);
}

void draw_lines(t_mlx *mlx, int map_x, int map_y, int color, double off)
{
	(void)off;
	int y = 0;
	while (y < map_y - off)
	{
		if (map_x < WIN_W &&  map_y <= WIN_H)
			paint_img(mlx, color, map_x, off + y);
		y++;
	}
}