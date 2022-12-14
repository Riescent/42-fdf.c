/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:23:28 by vfries            #+#    #+#             */
/*   Updated: 2022/12/10 13:15:27 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw.h"
#include "colors.h"

static void	fill_map_m(t_fdf *fdf)
{
	int	y;
	int	x;

	y = -1;
	while (++y < fdf->map.y_size)
	{
		x = -1;
		while (++x < fdf->map.x_size)
		{
			fdf->map.m[y][x] = matrix_times_vector(&fdf->mats.world,
					&fdf->map.a[y][x]);
			fdf->map.m[y][x] = matrix_times_vector(&fdf->mats.proj.m,
					&fdf->map.m[y][x]);
		}
	}
}

static int	get_color(t_fdf *fdf, double altitude_1, double altitude_2)
{
	double	highest_altitude;

	if (fdf->colors == false)
		return (COLOR_WHITE);
	if (altitude_1 < altitude_2)
		highest_altitude = -altitude_1;
	else
		highest_altitude = -altitude_2;
	if (highest_altitude > 300.0)
		return (COLOR_SNOW_WHITE);
	else if (highest_altitude > 120.0)
		return (COLOR_ROCK);
	else if (highest_altitude > 50.0)
		return (COLOR_DARK_GRASS);
	else if (highest_altitude > 15.0)
		return (COLOR_MID_GRASS);
	else if (highest_altitude > 6.0)
		return (COLOR_LIGHT_GRASS);
	else if (highest_altitude > 2.0)
		return (COLOR_SAND);
	else
		return (COLOR_SEA_BLUE + 32);
}

static void	draw_lines(t_fdf *fdf)
{
	int		y;
	int		x;

	y = -1;
	while (++y < fdf->map.y_size)
	{
		x = -1;
		while (++x < fdf->map.x_size)
		{
			if (x + 1 < fdf->map.x_size)
				draw_clipped_line(fdf->map.m[y][x], fdf->map.m[y][x + 1],
					fdf, get_color(fdf,
						fdf->map.o[y][x].z, fdf->map.o[y][x + 1].z));
			if (y + 1 < fdf->map.y_size)
				draw_clipped_line(fdf->map.m[y][x], fdf->map.m[y + 1][x],
					fdf, get_color(fdf,
						fdf->map.o[y][x].z, fdf->map.o[y + 1][x].z));
		}
	}
}

void	draw_fdf(t_fdf *fdf)
{
	reset_img(&fdf->img, 0x000000);
	fill_map_m(fdf);
	draw_lines(fdf);
	put_img(&fdf->img, &fdf->win);
}
