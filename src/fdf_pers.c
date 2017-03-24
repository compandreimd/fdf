/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:55:00 by amalcoci          #+#    #+#             */
/*   Updated: 2016/12/05 13:55:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_color.h>
#include "fdf.h"

static t_rgb	get_color2(t_info *a, t_env *env)
{
	t_rgb	c;

	if (a->color)
		c = *a->color;
	else
		c = get_color(*a->height, env);
	return (c);
}

static void		make_line(t_info *a, t_info *b, t_env *env)
{
	t_point		a2;
	t_point		b2;
	t_rgb		c;

	if (a->height && b->height)
	{
		c = get_color2(a, env);
		a2 = ft_perspective(ft_create_point_3d(a->i * env->zoom.x,
			a->j * env->zoom.y, *a->height * env->zoom.z, c),
			env->camera, env->phi, env->view);
		a2.x += env->move.x;
		a2.y += env->move.y;
		c = get_color2(b, env);
		b2 = ft_perspective(ft_create_point_3d(b->i * env->zoom.x,
			b->j * env->zoom.y, *b->height * env->zoom.z, c),
			env->camera, env->phi, env->view);
		b2.x += env->move.x;
		b2.y += env->move.y;
		ft_line(ft_create_line(a2, b2), env, 1, fdf_draw);
	}
}

void			fdf_p_init(t_env *env)
{
	env->phi = ft_create_point_3d(0, 0, 0, ft_create_rgb(0));
	env->view = ft_create_point_3d(0, 0, 0, ft_create_rgb(0));
	env->camera = ft_create_point_3d(0, 0, 0, ft_create_rgb(0));
}

void			fdf_pers(t_env *env)
{
	t_list	*tmp;
	t_info	*a;
	t_info	*b;

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
