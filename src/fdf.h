/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:17:00 by amalcoci          #+#    #+#             */
/*   Updated: 2016/11/07 14:17:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>

typedef struct	s_col_name
{
	char		*name;
	int			value;
}				t_col_name;

typedef struct	s_info
{
	int		i;
	int		j;
	int		*height;
	t_rgb	*color;
}				t_info;

typedef struct	s_env
{
	void			*mlx;
	void			*wind;
	int				width;
	int				height;
	int				color;
	int				max;
	int				min;
	int				dt;
	t_rgb			a;
	t_rgb			b;
	t_rgb			c;
	t_point_3d		zoom;
	t_point			move;
	t_point			orto_point;
	t_list			*map;
	t_point_3d		camera;
	t_point_3d		phi;
	t_point_3d		view;
	int				mod;
}				t_env;

void			fdf_draw(t_point p, void *data);
t_list			*fdf_map(int fd, t_env *map);
t_info			*find_info(t_list *list, int i, int j);
void			fdf_orto(t_env *env);
void			fdf_pers(t_env *env);
t_rgb			get_color(int height, t_env *env);
void			fdf_p_init(t_env *env);
void			set_color(int a, int b, int c, t_env *env);
void			std_keyhook(int keycode, t_env *env);
void			key_orto(int keycode, t_env *env);
void			key_pers(int keycode, t_env *env);
void			std_colorhook(t_env *env);
#endif
