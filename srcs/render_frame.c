/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:10:10 by vfries            #+#    #+#             */
/*   Updated: 2022/12/07 19:29:47 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw.h"
#include "deal_key.h"

int	render_frame(t_fdf *fdf)
{
	if (fdf->keys.keys_pressed)
		deal_key(fdf);
	draw_fdf(fdf);
	return (0);
}
