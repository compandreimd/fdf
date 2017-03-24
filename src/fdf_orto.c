/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_orto.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:55:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/02/27 14:04:43 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_color.h>
#include "fdf.h"

t_rgb				get_color(int height, t_env *env)
{
	int		avg;
	int		pos;
	double	dt;
	t_rgb	rs;

	avg = (env->max + env->min) / 2;
	if (height < avg)
	{
		pos = height - env->min;
		dt = (avg - env->min);
		rs.r = (unsigned char)(env->a.r + (env->b.r - env->a.r) * pos / dt);
		rs.g = (unsigned char)(env->a.g + (env->b.g - env->a.g) * pos / dt);
		rs.b = (unsigned char)(env->a.b + (env->b.b - env->a.b) * pos / dt);
	}
	else
	{
		pos = env->max - height;
		dt = (env->max - avg);
		if (dt == 0)
			dt = 1;
		rs.r = (unsigned char)(env->b.r + (env->c.r - env->b.r) * pos / dt);
		rs.g = (unsigned char)(env->b.g + (env->c.g - env->b.g) * pos / dt);
		rs.b = (unsigned char)(env->b.b + (env->c.b - env->b.b) * pos / dt);
	}
	return (rs);
}

static t_rgb		get_color2(t_info *info, t_env *env)
{
	t_rgb	c;

	if (info->color)
		c = *info->color;
	else
		c = get_color(*info->height, env);
	return (c);
}

static void			make_line(t_info *a, t_info *b, t_env *env)
{
	t_point		a2;
	t_point		b2;
	t_rgb		c;

	if (a->height && b->height)
	{
		c = get_color2(a, env);
		a2 = ft_3d_to_2d(ft_create_point_3d(a->i * env->zoom.x,
			a->j * env->zoom.y, *a->height * env->zoom.z,
			c), env->orto_point);
		a2.x += env->move.x;
		a2.y += env->move.y;
		c = get_color2(b, env);
		b2 = ft_3d_to_2d(ft_create_point_3d(b->i * env->zoom.x,
			b->j * env->zoom.y, *b->height * env->zoom.z,
			c), env->orto_point);
		b2.x += env->move.x;
		b2.y += env->move.y;
		ft_line(ft_create_line(a2, b2), env, 1, fdf_draw);
	}
}

void				fdf_orto(t_env *env)
{
	t_list		*tmp;
	t_info		*a;
	t_info		*b;

	tmp = env->map;
	while (tmp)
	{
		a = (t_info*)tmp->content;
		if ((b = find_info(tmp, a->i - 1, a->j)))
		{
			make_line(a, b, env);
		}
		if ((b = find_info(tmp, a->i, a->j - 1)))
		{
			make_line(a, b, env);
		}
		tmp = tmp->next;
	}
}
