/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 21:26:42 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/24 21:27:37 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGEBRA_H
# define ALGEBRA_H

# include "scene_types.h"

/*
** Linear algebra functions
*/

t_vector		ft_k_vct_prod(double k, t_vector v);
t_vector		ft_sub_vector(t_vector u, t_vector v);
t_vector		ft_add_vector(t_vector u, t_vector v);
double			ft_dot_product(t_vector u, t_vector v);
t_vector		ft_cross_product(t_vector u, t_vector v);
void			ft_normalize_vector(t_vector *v);
double			ft_mod_vector(t_vector v);
t_vector		ft_mtx_vct_prod(t_matrix m, t_vector v);
double			ft_abs(double num);
double			ft_det(t_matrix m);
t_matrix		ft_inv_matrix(t_matrix m);
int				ft_minus_vector(t_vector *v);
t_vector		ft_set_axis(char axis);
t_vector		ft_set_hor_axis(t_vector n);
int				ft_isvoid(t_vector vector);

#endif
