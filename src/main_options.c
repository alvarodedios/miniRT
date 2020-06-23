#include "miniRT.h"

void            ft_initialize_options(t_scene *scene)
{
    int i;

    i = -1;
    while (++i < 14)
        scene->option[i] = 0; 
}

void            ft_save_option(char *argv, t_scene *scene)
{
    if (!ft_strncmp(argv, "--save", ft_strlen(argv) + 1))
    {
        if (scene->option[0])
            ft_error_handler(DOUBLE_FLAG);
        scene->option[0] = 1;
    }
    else
    {
#ifdef BONUS
        ft_bonus_options(argv, scene);
#else
        ft_error_handler(BAD_FLAG);
#endif
    }
}

void             ft_check_options(int argc, char **argv, t_scene *scene)
{
    int i;

    i = 1;
    while (++i < argc)
        ft_save_option(argv[i], scene);
}
