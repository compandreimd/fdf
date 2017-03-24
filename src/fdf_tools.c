/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:31:00 by amalcoci          #+#    #+#             */
/*   Updated: 2016/12/14 13:31:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_buttons.h>
#include <mlx_color.h>
#include "fdf.h"

void			set_color(int a, int b, int c, t_env *env)
{
	env->a = ft_create_rgb(a);
	env->b = ft_create_rgb(b);
	env->c = ft_create_rgb(c);
}
void			fdf_draw(t_point p, void *data)
{
	t_env	*env;

	env = data;
	mlx_pixel_put(env->mlx, env->wind, p.x, p.y, ft_rgb_to_int(p.color));
}

void			std_colorhook(t_env *env)
{
	env->color++;
	if (env->color == 5)
		env->color = 0;
	if (env->color == 0)
		set_color(MLX_COLOR_WHITE, MLX_COLOR_WHITE, MLX_COLOR_WHITE, env);
	else if(env->color == 1)
		set_color(MLX_COLOR_BLUE, MLX_COLOR_SNOW, MLX_COLOR_GREENYELLOW, env);
	else if(env->color == 2)
		set_color(MLX_COLOR_DARKBLUE, MLX_COLOR_YELLOW, MLX_COLOR_BLUE, env);
	else if(env->color == 3)
		set_color(MLX_COLOR_DARKRED, MLX_COLOR_ORANGE, MLX_COLOR_RED, env);
	else
		set_color(MLX_COLOR_BLACK, MLX_COLOR_WHITE, MLX_COLOR_GRAY50, env);
}

void			std_keyhook(int keycode, t_env *env)
{
	if (keycode == MLX_BUTTON_ESC)
	{
		mlx_destroy_window(env->mlx, env->wind);
		exit(0);
	}
	if (keycode == MLX_BUTTON_J)
		env->zoom.x -= env->dt;
	if (keycode == MLX_BUTTON_L)
		env->zoom.x += env->dt;
	if (keycode == MLX_BUTTON_I)
		env->zoom.y -= env->dt;
	if (keycode == MLX_BUTTON_K)
		env->zoom.y += env->dt;
	if (keycode == MLX_BUTTON_O)
		env->zoom.z += env->dt;
	if (keycode == MLX_BUTTON_U)
		env->zoom.z -= env->dt;
	if(keycode == MLX_BUTTON_Z)
	{
		if(env->mod)
			env->mod = 0;
		else
			env->mod = 1;
		if(env->mod)
			key_pers(keycode, env);
		else
			key_orto(keycode, env);
	}
};
