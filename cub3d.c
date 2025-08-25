#include "cub3d.h"

void init_textures(t_game *m)
{
    m->textures = malloc(sizeof(t_texture) * 7);


    //---------------------------------------------------------------


    m->textures[0].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/blue_stone.xpm", &m->textures[0].texture_w, &m->textures[0].texture_h);
    m->textures[0].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[0].texture_p, &m->textures[0].bpp, &m->textures[0].texture_len, &m->textures[0].endian);

    m->textures[1].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/grey_stone.xpm", &m->textures[1].texture_w, &m->textures[1].texture_h);
    m->textures[1].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[1].texture_p, &m->textures[1].bpp, &m->textures[1].texture_len, &m->textures[1].endian);

    m->textures[2].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/mossy.xpm", &m->textures[2].texture_w, &m->textures[2].texture_h);
    m->textures[2].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[2].texture_p, &m->textures[2].bpp, &m->textures[2].texture_len, &m->textures[2].endian);

    m->textures[3].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/red_brick.xpm", &m->textures[3].texture_w, &m->textures[3].texture_h);
    m->textures[3].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[3].texture_p, &m->textures[3].bpp, &m->textures[3].texture_len, &m->textures[3].endian);


    //---------------------------------------------------------------

    m->textures[4].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/pillar.xpm", &m->textures[4].texture_w, &m->textures[4].texture_h);
    m->textures[4].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[4].texture_p, &m->textures[4].bpp, &m->textures[4].texture_len, &m->textures[4].endian);

    m->textures[5].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/sprite_1.xpm", &m->textures[5].texture_w, &m->textures[5].texture_h);
    m->textures[5].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[5].texture_p, &m->textures[5].bpp, &m->textures[5].texture_len, &m->textures[5].endian);

    m->textures[6].texture_p = mlx_xpm_file_to_image(m->mlx, "./textures/sprite_2.xpm", &m->textures[6].texture_w, &m->textures[6].texture_h);
    m->textures[6].texture_s = (unsigned int *)mlx_get_data_addr(m->textures[6].texture_p, &m->textures[6].bpp, &m->textures[6].texture_len, &m->textures[6].endian);
}


void init_player(t_player *player)
{
    player->x_p = 400;
    player->y_p = 400;
    player->angle = 0;
    player->angle_speed = 0.09;
    player->up = 0;
    player->down = 0;
    player->right = 0;
    player->left = 0;
    player->r_right = 0;
    player->r_left = 0;
}


int main()
{
    t_game m;
    t_image image;
    t_player player;
    t_ray ray;

    //---------------------------------------------------------------

    t_map map = {.map = 
    {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1},
    {1, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    },
    .h = 15,
    .w = 20,
    .tile = 64
    };


    map.h_p = 1080;
    map.w_p = 1920;

    //---------------------------------------------------------------

    m.mlx = mlx_init();
    m.win = mlx_new_window(m.mlx, 1920, 1080, "cub3d");
    m.image = &image;
    m.player = &player;
    m.map = &map;
    m.ray = &ray;

    //---------------------------------------------------------------

    image.image_width =  1920;
    image.image_height = 1080;
    image.image_p = mlx_new_image(m.mlx, image.image_width, image.image_height);
    image.image_s = (unsigned char *)mlx_get_data_addr(image.image_p, &image.bpp, &image.size_len, &image.endian);

    printf("size_len == %d\n", image.size_len);
    printf("bpp == %d\n", image.bpp);
    printf("endian == %d\n", image.endian);

    //---------------------------------------------------------------

    init_player(m.player);

    //---------------------------------------------------------------

    m.ray = malloc(sizeof(t_ray) * m.map->w_p);

    //---------------------------------------------------------------

    init_textures(&m);

    //---------------------------------------------------------------

    m.sprites_count = 0;
    m.sprites = NULL;
    fill_sprites_list(&m);
    
    //---------------------------------------------------------------


	mlx_mouse_hide(m.mlx, m.win);
    mlx_hook(m.win, 17, 0, handle_close, &m);
    mlx_hook(m.win, 2, 1L<<0, key_press, &m);
    mlx_hook(m.win, 3, 1L<<1, key_release, &m);
    mlx_loop_hook(m.mlx, draw_in_screen, &m);
	// mlx_set_cursor_mode(m.mlx, 0x00034003);
	mlx_hook(m.win, 6, 1L<<6, cursor_func, &m);

    //---------------------------------------------------------------

    mlx_loop(m.mlx);
}