#include "cub3d.h"

int handle_close(t_game *m)
{
    exit((free(m->textures), free(m->ray), 0));
}


int key_press(int key, t_game *m)
{
    if(key == ESC_KEY)
        exit((free(m->textures), free(m->ray), 0));
    else if(key == UP_KEY)
        m->player->up = 1;
    else if(key == DOWN_KEY)
        m->player->down = 1;
    else if(key == RIGHT_KEY)
        m->player->right = 1;
    else if(key == LEFT_KEY)
        m->player->left = 1;
    else if(key == R_RIGHT_KEY)
        m->player->r_right = 1;
    else if(key == R_LEFT_KEY)   
        m->player->r_left = 1;
}

int key_release(int key, t_game *m)
{
    if(key == UP_KEY)
        m->player->up = 0;
    else if(key == DOWN_KEY)
        m->player->down = 0;
    else if(key == RIGHT_KEY)
        m->player->right = 0;
    else if(key == LEFT_KEY)
        m->player->left = 0;
    else if(key == R_RIGHT_KEY)
        m->player->r_right = 0;
    else if(key == R_LEFT_KEY)   
        m->player->r_left = 0;
}


int cursor_func(int xpos, int ypos, t_game *game)
{
    (void)ypos;
    static int last_x = -1;

    if (last_x == -1)
    {
        last_x = xpos; 
        return 0;
    }    

    double delta = xpos - last_x;
    game->player->angle += delta * 0.005;
    if (game->player->angle > 2 * M_PI) game->player->angle -= 2*M_PI;
    if (game->player->angle < 0)       game->player->angle += 2*M_PI;
    last_x = xpos;
    return 0;
}
