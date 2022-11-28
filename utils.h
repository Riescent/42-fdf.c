/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:09:08 by vfries            #+#    #+#             */
/*   Updated: 2022/11/28 13:58:14 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_2d_point
{
	int	x;
	int	y;
}	t_2d_point;

typedef struct s_3d_point
{
	int	x;
	int	y;
	int	z;
}	t_3d_point;

typedef struct s_3d_point_double
{
	int	x;
	int	y;
	int	z;
}	t_3d_point_double;

typedef struct s_matrix_4
{
	double	mat[4][4];
}	t_matrix_4;

#endif
