#include "cub3d.h"

int player_mv(t_game *m)
{
    double n_x;
    double n_y;

    n_x = 0;
    n_y = 0;

    if(m->player->r_right)
    {
        m->player->angle = m->player->angle + m->player->angle_speed;
        if(m->player->angle > (2 * M_PI))
            m->player->angle -= (2 * M_PI);
    }
    else if (m->player->r_left)
    {
        m->player->angle = m->player->angle - m->player->angle_speed;
        if(m->player->angle < 0)
            m->player->angle += (2 * M_PI);
    }
    else if(m->player->right)
    {
        n_x -= 16 * sin(m->player->angle);
        n_y += 16 * cos(m->player->angle);
    }
    else if(m->player->left)
    {
        n_x += 16 * sin(m->player->angle);
        n_y -= 16 * cos(m->player->angle);
    }
    else if(m->player->up)
    {
        n_x += 16 * cos(m->player->angle);
        n_y += 16 * sin(m->player->angle);
    }
    else if(m->player->down)
    {
        n_x -= 16 * cos(m->player->angle);
        n_y -= 16 * sin(m->player->angle);
    }
    else
        return (1);
    if(!n_x && !n_y)
        return (0);
    if(m->map->map[(int)floor((m->player->y_p + 16 + n_y)/64)][(int)((m->player->x_p + 16 + n_x)/64)] == 1
        || m->map->map[(int)floor((m->player->y_p + 16 + n_y)/64)][(int)((m->player->x_p + n_x)/64)] == 1
        || m->map->map[(int)floor((m->player->y_p + n_y)/64)][(int)((m->player->x_p + 16 + n_x)/64)] == 1
        || m->map->map[(int)floor((m->player->y_p + n_y)/64)][(int)((m->player->x_p + n_x)/64)] == 1)
        return (1);
    m->player->x_p += n_x;
    m->player->y_p += n_y;
    return (0);
}