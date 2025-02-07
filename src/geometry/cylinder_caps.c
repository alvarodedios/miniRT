/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:21:35 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/24 22:04:08 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			ft_intersect_caps(t_scene *s, t_ray *r, int i, t_auxplane *auxplane)
{
	if (ft_intersect_plane(s, auxplane, r))
		if (ft_get_point_plane(s, auxplane, r))
			if (ft_mod_vector(ft_sub_vector(auxplane->p, auxplane->point))
					< s->cylinder[i]->radius)
			{
				if (auxplane->den > 0)
					auxplane->n = ft_k_vct_prod(-1, auxplane->n);
				return (1);
			}
	return (0);
}

t_vector	ft_nearest_cap(t_scene s, int i)
{
	t_vector	vect[2];
	t_vector	top_side;
	double		dist[2];

	top_side = ft_add_vector(s.cylinder[i]->point,
			ft_k_vct_prod(s.cylinder[i]->height, s.cylinder[i]->n));
	vect[0] = ft_sub_vector(s.camera[s.i_cam]->pos, s.cylinder[i]->point);
	vect[1] = ft_sub_vector(s.camera[s.i_cam]->pos, top_side);
	dist[0] = ft_mod_vector(vect[0]);
	dist[1] = ft_mod_vector(vect[1]);
	if (dist[0] > dist[1])
		return (top_side);
	return (s.cylinder[i]->point);
}

int			ft_draw_caps(t_scene s, t_ray *r, int i)
{
	double		last_t;
	t_obj_color	obj;
	t_auxplane	auxplane;

	last_t = r->t;
	if (s.cylinder[i]->m && s.cylinder[i]->m > s.cylinder[i]->height)
		auxplane.point = ft_add_vector(s.cylinder[i]->point,
				ft_k_vct_prod(s.cylinder[i]->height, s.cylinder[i]->n));
	else
		auxplane.point = ft_nearest_cap(s, i);
	auxplane.n = s.cylinder[i]->n;
	if (ft_intersect_caps(&s, r, i, &auxplane))
	{
		obj.p = auxplane.p;
		obj.normal = auxplane.n;
		obj.rgb = s.cylinder[i]->rgb;
		r->color = ft_get_color(s, obj);
		return (1);
	}
	r->t = last_t;
	return (0);
}
