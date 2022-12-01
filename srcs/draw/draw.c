/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:23:28 by vfries            #+#    #+#             */
/*   Updated: 2022/12/01 06:38:24 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "points.h"
#include "draw.h"
#include "get_no_clip_vectors.h"
#include <stdlib.h>

#define BACK_GROUND_COLOR 0x000000

static t_2d_point_i	get_2d_point_from_vector(t_vector_d vec)
{
	t_2d_point_i	new;

	new.x = vec.x + 0.5;
	new.y = vec.y + 0.5;
	return (new);
}

static void	draw_lines(t_fdf *fdf, t_list *vectors)
{
	t_list	*free_me;

	while (vectors)
	{
		if (vectors->content == NULL)
		{
			vectors = vectors->next;
			continue ;
		}
		draw_line(&fdf->img,
			get_2d_point_from_vector(((t_vector_d *)(vectors->content))[0]),
			get_2d_point_from_vector(((t_vector_d *)(vectors->content))[1]));
		free(vectors->content);
		free_me = vectors;
		vectors = vectors->next;
		free(free_me);
	}
}

static void	fill_m_v_map(t_fdf *fdf)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 11)
	{
		x = -1;
		while (++x < 19)
			fdf->map.m_v_map[y][x] = matrix_times_vector(&fdf->mats.world,
					&fdf->map.o_v_map[y][x]);
	}
}

static t_list	*fix_clipping(t_fdf *fdf)
{
	int		y;
	int		x;
	t_list	*vectors;

	vectors = NULL;
	y = -1;
	while (++y < fdf->map.y_size)
	{
		x = -1;
		while (++x < fdf->map.x_size)
		{
			if (x + 1 < 19)
				get_no_clip_vectors(fdf, &vectors,
					fdf->map.m_v_map[y][x], fdf->map.m_v_map[y][x + 1]);
			if (y + 1 < 11)
				get_no_clip_vectors(fdf, &vectors,
					fdf->map.m_v_map[y][x], fdf->map.m_v_map[y + 1][x]);
		}
	}
	return (vectors);
}

void	draw_fdf(t_fdf *fdf)
{
	int	y;
	int	x;

	y = -1;
	while (++y < fdf->img.y_size)
	{
		x = -1;
		while (++x < fdf->img.x_size)
			put_pixel_on_img(&fdf->img, y, x, BACK_GROUND_COLOR);
	}
	fill_m_v_map(fdf);
	draw_lines(fdf, fix_clipping(fdf));
	put_img(&fdf->img, &fdf->win);
}