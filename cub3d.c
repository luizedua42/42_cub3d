/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:16:21 by luizedua          #+#    #+#             */
/*   Updated: 2024/01/10 12:02:06 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_window(t_mlx *mlx);
void	init_mlx(t_mlx **mlx);
int		close_win(t_mlx *mlx);
int		draw_player(t_mlx *mlx);
void	player_init(t_mlx *mlx, double x, double y);

int	main(int argc, char **argv)
{
	t_mlx	mlx_point;
	
	if (argc < 2)
	{
		printf("Wrong Arguments");
		return (EXIT_FAILURE);
	}
	(void)argv;
	run_window(&mlx_point);
	return(EXIT_SUCCESS);
}

void	run_window(t_mlx *mlx)
{
	init_mlx(&mlx);
	player_init(mlx, 2, 3);
	mlx_hook(mlx->p_win, 17, 0, close_win, mlx);
	mlx_hook(mlx->p_win, KeyPress, KeyPressMask, &key_press, mlx);
	rays(mlx, map_creation(&mlx->map, mlx));
	draw_p1line(mlx);
	// mlx_loop_hook(mlx->p_mlx, draw_player, mlx);
	mlx_loop(mlx->p_mlx);
	return;	
}

void	paint_img(t_mlx *mlx, int color, int x, int y)
{
	char	*dest;

	dest = mlx->i_add + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dest = color;
}

int	draw_player(t_mlx *mlx)
{
	int x = -5;
	int y = -5;
	while (y < 5)
	{
		x = -5;
		while ( x < 5)
		{
			paint_img(mlx, 0xFF0000, mlx->p1.x + x, mlx->p1.y + y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->p_win, mlx->p_img, 0, 0);
	return(EXIT_SUCCESS);
}
void	init_mlx(t_mlx **mlx)
{
	(*mlx)->p_mlx = mlx_init();
	(*mlx)->p_win = mlx_new_window((*mlx)->p_mlx, WIN_W, WIN_H, "cub3d");
	(*mlx)->p_img = mlx_new_image((*mlx)->p_mlx, WIN_W, WIN_H);
	(*mlx)->i_add = mlx_get_data_addr((*mlx)->p_img, &(*mlx)->bpp, &(*mlx)->size_line, \
			&(*mlx)->endian);
	(*mlx)->p1.x = 0;
	(*mlx)->p1.y = 0;
	(*mlx)->map.x = 0;
	(*mlx)->map.y = 0;
}

int	close_win(t_mlx *mlx)
{
	mlx_destroy_image(mlx->p_mlx, mlx->p_img);
	mlx_destroy_window(mlx->p_mlx, mlx->p_win);
	mlx_destroy_display(mlx->p_mlx);
	free(mlx->p_mlx);
	exit(EXIT_SUCCESS);
}

void player_init(t_mlx *mlx, double x, double y)
{
	mlx->p1.x = x * 64;
	mlx->p1.y = y * 64;
	mlx->p1.ang = 0;
	mlx->p1.dx = cos(mlx->p1.ang);
	mlx->p1.dy = sin(mlx->p1.ang);
}
