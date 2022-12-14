/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:55:44 by vfries            #+#    #+#             */
/*   Updated: 2022/12/09 19:21:54 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "slx_utils.h"
#include <math.h>

/*					Prespective projection matrix visualisation

[	(h/w)*(1/tan(fov/2))	0				0							0	]
[	0						(1/tan(fov/2))	0							0	]
[	0						0				zfar/(zfar-znear)			1	]
[	0						0				-(zfar/(zfar-znear))*znear	0	]

																			*/
t_matrix_4	get_prespective_proj_matrix(t_proj_m *data)
{
	t_matrix_4	m;
	double		fov_rad;
	double		z_far_z_near;

	fov_rad = 1.0 / tan(data->fov * 0.5 / 180.0 * M_PI);
	z_far_z_near = data->z_far / (data->z_far - data->z_near);
	slx_bzero(&m, sizeof(t_matrix_4));
	m.m[0][0] = data->aspect_ratio * fov_rad;
	m.m[1][1] = fov_rad;
	m.m[2][2] = z_far_z_near;
	m.m[3][2] = (-z_far_z_near) * data->z_near;
	m.m[2][3] = 1.0;
	return (m);
}
