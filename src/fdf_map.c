/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:35:00 by amalcoci          #+#    #+#             */
/*   Updated: 2016/11/29 14:35:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

static unsigned			hex(const char *s)
{
	unsigned	result;

	result = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n'
			|| *s == '\v' || *s == '\r' || *s == '\f')
		s++;
	if ('0' == *s && 'x' == *(s + 1))
	{
		s += 2;
		while (*s)
		{
			result = result << 4;
			if (*s >= '0' && *s <= '9')
				result += (unsigned)(*s - '0');
			else if (*s >= 'A' && *s <= 'F')
				result += (unsigned)(*s - 'A' + 10);
			else if (*s >= 'a' && *s <= 'f')
				result += (unsigned)(*s - 'a' + 10);
			++s;
		}
	}
	return (result);
}

void					maxmin(int h, t_env *env, int first)
{
	if (first)
	{
		env->max = h;
		env->min = h;
	}
	else
	{
		if (env->max < h)
			env->max = h;
		if (env->min > h)
			env->min = h;
	}
}

static	t_info			*get_info(int i, int j, char *str, t_env *env)
{
	t_info	*l;
	char	**s;

	l = ft_memalloc(sizeof(t_point_3d));
	l->i = i;
	l->j = j;
	s = ft_strsplit(str, ',');
	if (s[0])
	{
		l->height = ft_memalloc(sizeof(int));
		*l->height = ft_atoi(s[0]);
		maxmin(*l->height, env, (int)(i == 0 && j == 0));
	}
	if (s[1])
	{
		l->color = ft_memalloc(sizeof(t_rgb));
		*l->color = ft_create_rgb(hex(s[1]));
	}
	return (l);
}

t_list					*fdf_map(int fd, t_env *env)
{
	char	*str;
	t_list	*map;
	char	**splits;
	int		i;
	int		j;

	i = 0;
	map = NULL;
	while (get_next_line(fd, &str))
	{
		splits = ft_strsplit(str, ' ');
		j = 0;
		while (splits[j])
		{
			ft_lstadd(&map, ft_lstnew(get_info(j, i,
							splits[j], env), sizeof(t_info)));
			j++;
		}
		i++;
	}
	env->map = map;
	return (map);
}

t_info					*find_info(t_list *list, int i, int j)
{
	t_info *rs;

	while (list)
	{
		rs = list->content;
		if (rs->i == i && rs->j == j)
			return (rs);
		list = list->next;
	}
	return (NULL);
}
