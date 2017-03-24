/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 13:26:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/02/27 13:26:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <mlx_color.h>
#include <mlx_buttons.h>
#include <fcntl.h>
#include "fdf.h"

void		key_orto(int keycode, t_env *env)
{
	if (keycode == MLX_BUTTON_A)
		env->move.x -= env->dt;
	if (keycode == MLX_BUTTON_D)
		env->move.x += env->dt;
	if (keycode == MLX_BUTTON_W)
		env->move.y -= env->dt;
	if (keycode == MLX_BUTTON_S)
		env->move.y += env->dt;
}

void		key_pers(int keycode, t_env *env)
{
	if (keycode == MLX_BUTTON_A)
		env->camera.x -= env->dt;
	if (keycode == MLX_BUTTON_D)
		env->camera.x += env->dt;
	if (keycode == MLX_BUTTON_W)
		env->camera.y -= env->dt;
	if (keycode == MLX_BUTTON_S)
		env->camera.y += env->dt;
	if (keycode == MLX_BUTTON_Q)
		env->camera.z -= env->dt;
	if (keycode == MLX_BUTTON_E)
		env->camera.z += env->dt;
	if (keycode == MLX_BUTTON_F)
		env->phi.x -= env->dt;
	if (keycode == MLX_BUTTON_H)
		env->phi.x += env->dt;
	if (keycode == MLX_BUTTON_T)
		env->phi.y -= env->dt;
	if (keycode == MLX_BUTTON_G)
		env->phi.y += env->dt;
	if (keycode == MLX_BUTTON_R)
		env->phi.z -= env->dt;
	if (keycode == MLX_BUTTON_Y)
		env->phi.z += env->dt;
}

int			key_hook(int keycode, void *data)
{
	t_env	*env;

	env = (t_env*)data;
	if (keycode == MLX_BUTTON_C)
	{
		std_colorhook(env);
	}
	std_keyhook(keycode, env);
	mlx_clear_window(env->mlx, env->wind);
	if (env->mod)
		fdf_pers(env);
	else
		fdf_orto(env);
	return (1);
}

void		create_wind(t_env *env)
{
	t_info		*info;
	int			i;

	info = env->map->content;
	env->width = 1000;
	env->height = 1000;
	env->color = 0;
	env->mod = 0;
	set_color(MLX_COLOR_WHITE, MLX_COLOR_WHITE, MLX_COLOR_WHITE, env);
	i = info->i;
	if (i < info->j)
		i = info->j;
	env->zoom.x = (int)800 / i;
	env->zoom.y = env->zoom.x;
	env->zoom.z = (int)env->zoom.x / 10;
	if (!env->zoom.z)
		env->zoom.z = 1;
	env->dt = 1;
	env->wind = mlx_new_window(env->mlx, env->width, env->height, "FDF");
}

int			main(int argc, char **argv)
{
	int		fd;
	t_env	*env;

	fd = -1;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fd = open("42.fdf", O_RDONLY);
	env = ft_memalloc(sizeof(t_env));
	fdf_map(fd, env);
	env->color = 0;
	env->mlx = mlx_init();
	create_wind(env);
	fdf_p_init(env);
	env->orto_point.x = 0.5;
	env->orto_point.y = 0.5;
	env->move.x = 0;
	env->move.y = 0;
	fdf_orto(env);
	mlx_key_hook(env->wind, key_hook, env);
	mlx_loop(env->mlx);
	close(fd);
	return (0);
}
