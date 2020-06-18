/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:17:31 by vde-dios          #+#    #+#             */
/*   Updated: 2020/01/25 20:09:48 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void            ft_scene_to_screen(t_scene *scene)
{
    //Cuando vara a guardar en bmp hay que modificar esta función ya que de momento
    //sólo muestra por pantalla después de renderizar
    ft_render_scene(scene);
    mlx_clear_window(scene->window.mlx_ptr, scene->window.win_ptr);
    mlx_put_image_to_window(scene->window.mlx_ptr, scene->window.win_ptr,
            scene->img.id, 0, 0);
    mlx_string_put(scene->window.mlx_ptr, scene->window.win_ptr,
            scene->axis.x.x, scene->axis.x.y, 0x00FF0000, "x");
    mlx_string_put(scene->window.mlx_ptr, scene->window.win_ptr,
            scene->axis.y.x, scene->axis.y.y, 0x0000FF00, "y");
    mlx_string_put(scene->window.mlx_ptr, scene->window.win_ptr,
            scene->axis.z.x, scene->axis.z.y, 0x000000FF, "z");
}

int 		ft_exit(t_window *window)
{
    mlx_destroy_window(window->mlx_ptr, window->win_ptr);
    exit(EXIT_SUCCESS);
}

int             ft_handle_keyboard(int key, t_scene *s)
{
    printf("%d\n", key);
    t_vector    aux;
    /*
     * A - 0
     * D - 2
     *
     * W - 13
     * S - 1
     *
     * E - 14
     * Q - 12
     */
    if (key == 2)
    {
        aux = (t_vector){1, 0, 0};
        aux = ft_mtx_vct_prod(s->camera[s->i_cam]->base, aux);
        s->camera[s->i_cam]->pos = ft_add_vector(aux, s->camera[s->i_cam]->pos);
        ft_scene_to_screen(s);
    }
    else if (key == 0)
    {
        aux = (t_vector){-1, 0, 0};
        aux = ft_mtx_vct_prod(s->camera[s->i_cam]->base, aux);
        s->camera[s->i_cam]->pos = ft_add_vector(aux, s->camera[s->i_cam]->pos);
        ft_scene_to_screen(s);
    }
    else if (key == 13)
    {
        aux = (t_vector){0, 1, 0};
        aux = ft_mtx_vct_prod(s->camera[s->i_cam]->base, aux);
        s->camera[s->i_cam]->pos = ft_add_vector(aux, s->camera[s->i_cam]->pos);
        ft_scene_to_screen(s);
    }
    else if (key == 1)
    {
        aux = (t_vector){0, -1, 0};
        aux = ft_mtx_vct_prod(s->camera[s->i_cam]->base, aux);
        s->camera[s->i_cam]->pos = ft_add_vector(aux, s->camera[s->i_cam]->pos);
        ft_scene_to_screen(s);
    }
    else if (key == 14)
    {
        aux = (t_vector){0, 0, -1};
        aux = ft_mtx_vct_prod(s->camera[s->i_cam]->base, aux);
        s->camera[s->i_cam]->pos = ft_add_vector(aux, s->camera[s->i_cam]->pos);
        ft_scene_to_screen(s);
    }
    else if (key == 12)
    {
        aux = (t_vector){0, 0, 1};
        aux = ft_mtx_vct_prod(s->camera[s->i_cam]->base, aux);
        s->camera[s->i_cam]->pos = ft_add_vector(aux, s->camera[s->i_cam]->pos);
        ft_scene_to_screen(s);
    }
    else if (key == 123)
    {
        if (s->i_cam > 0)
            s->i_cam = s->i_cam - 1;
        else
            s->i_cam = s->n_cams - 1;
        ft_scene_to_screen(s);
    }
    else if (key == 124)
    {
        if (s->i_cam < s->n_cams - 1)
            s->i_cam = s->i_cam + 1;
        else
            s->i_cam = 0;
        ft_scene_to_screen(s);
    } 
    else if (key == 53)
        ft_exit(&s->window);
    return (0);
}

int             ft_handle_mouse(int press, int u, int v, t_scene *s)
{
    (void)press;
    t_vector new_normal;

    new_normal = ft_local_camera_ray(*s, (double)u, (double)v);
    new_normal = ft_mtx_vct_prod(s->camera[s->i_cam]->base, new_normal);
    ft_normalize_vector(&new_normal);
    s->camera[s->i_cam]->n = new_normal;
    ft_scene_to_screen(s);
    return (0);
}

void            ft_miniRT(t_scene scene)
{
    scene.i_cam = 0;
    scene.window.mlx_ptr = mlx_init();
    scene.window.win_ptr = mlx_new_window(scene.window.mlx_ptr,
            scene.x, scene.y, "miniRT");
    scene.img.id = mlx_new_image(scene.window.mlx_ptr, scene.x, scene.y);
    scene.img.addr = mlx_get_data_addr(scene.img.id, &scene.img.bitpixl,
            &scene.img.len,&scene.img.end);
    mlx_hook(scene.window.win_ptr, 17, 0, ft_exit, &scene.window);
    mlx_key_hook(scene.window.win_ptr, ft_handle_keyboard, &scene);
    mlx_mouse_hook(scene.window.win_ptr, ft_handle_mouse, &scene);
    //hacer gestión de error para carga textura!!
    scene.texture.img = (int *)mlx_png_file_to_image(scene.window.mlx_ptr, "textures/milkyway.png"
            , &scene.texture.width, &scene.texture.height);
    scene.texture.val = (int *)mlx_get_data_addr(scene.texture.img, &scene.texture.bitpixl,
            &scene.texture.len, &scene.texture.end);
    ft_scene_to_screen(&scene);
    mlx_loop(scene.window.mlx_ptr);
} 
