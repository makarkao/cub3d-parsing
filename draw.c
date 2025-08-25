#include "cub3d.h"


void set_color(t_image *im, int x, int y, unsigned int argb)
{
    if (x < 0 || y < 0 || x >= im->image_width || y >= im->image_height)
        return;

    int bytes = im->bpp / 8;
    unsigned char *p = im->image_s + y * im->size_len + x * bytes;
          // little-endian (Linux): BGRA in memory
            p[0] =  argb        & 0xFF;  // B
            p[1] = (argb >>  8) & 0xFF;  // G
            p[2] = (argb >> 16) & 0xFF;  // R
            p[3] = (argb >> 24) & 0xFF;  // A
}



void draw_line(t_map *map, t_image *image, int x0, int y0, int x1, int y1)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int error;
    int e2;

    dx = abs(x1 - x0);
    dy = -abs(y1 - y0);
    error = dx + dy;
    if(x1 > x0)
        sx = 1;
    else
        sx = -1;
    if(y1 > y0)
        sy = 1;
    else
        sy = -1;
    while(x0 >= 0 && x0 < map->w_p && y0 >= 0 && y0 < map->h_p)
    {
        set_color(image, x0, y0, 0x00ff0000);
        e2 = 2 * error;
        if(e2 >= dy)
        {

            if(x0 == x1)
                break;
            error += dy;
            x0 += sx;
        }
        if(e2 <= dx)
        {
            if(y0 == y1)
                break;
            error += dx;
            y0 += sy;
        }
    }
}

void draw_player_line(t_map *map, t_image *image, int x0, int y0, int x1, int y1)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int error;
    int e2;

    dx = abs(x1 - x0);
    dy = -abs(y1 - y0);
    error = dx + dy;
    if(x1 > x0)
        sx = 1;
    else
        sx = -1;
    if(y1 > y0)
        sy = 1;
    else
        sy = -1;
    while(x0 >= 0 && x0 < map->w_p && y0 >= 0 && y0 < map->h_p)
    {
        set_color(image, x0, y0, 0x0000ff00);
        e2 = 2 * error;
        if(e2 >= dy)
        {

            if(x0 == x1)
                break;
            error += dy;
            x0 += sx;
        }
        if(e2 <= dx)
        {
            if(y0 == y1)
                break;
            error += dx;
            y0 += sy;
        }
    }
}

void draw_square(t_image *image, t_player *player, t_map *map)
{
    int x;
    int y;

    y = player->y_p;
    while(y < player->y_p + 16)
    {
        x = player->x_p;
        while(x < player->x_p + 16)
        {
            set_color(image, x, y, 0xffff0000);
            x++;
        }
        y++;
    }
    draw_player_line(map, image, player->x_p + 8, player->y_p + 8, player->x_p + 8 + 16 * cos(player->angle), player->y_p + 8 + 16 * sin(player->angle));

}



void    clean_image(t_image    *image)
{
    int x;
    int y;

    y = 0;
    while(y < 960)
    {
        x = 0;
        while(x < 1280)
        {
            set_color(image, x, y, 0);
            x++;
        }
        y++;
    }
}

void draw_tile(t_image *image, int x_s, int y_s, int color)
{
    int x;
    int y;

    y = y_s;
    while(y < y_s + 64)
    {
        x = x_s;
        while(x < x_s + 64)
        {
            set_color(image, x, y, color);
            x++;
        }
        y++;
    }
}

void    draw_map(t_map *map, t_image *image)
{
    int i;
    int j;

    j = 0;
    while(j < map->h)
    {
        i = 0;
        while(i < map->w)
        {
            if(map->map[j][i] == 1)
                draw_tile(image, i * 64, j * 64, 0xffffffff);
            else if(map->map[j][i] == 0)
                draw_tile(image, i * 64, j * 64, 0x00000000);
            i++;
        }
        j++;
    }
}

void	ft_usleep(unsigned int microseconds)
{
	struct timeval	start;
	struct timeval	current;
	double			elapsed;
	double			target_seconds;

	elapsed = 0.0;
	target_seconds = microseconds / 1000000.0;
	gettimeofday(&start, NULL);
	while (elapsed < target_seconds)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec)
			+ (current.tv_usec - start.tv_usec) / 1000000.0;
	}
}


int draw_in_screen(t_game *m)
{
    clean_image(m->image);

    
    // draw_map(m->map, m->image);
    player_mv(m);
    fill_rays_list(m);
    // draw_rays(m);
    // draw_square(m->image, m->player, m->map);
    
    draw_to_projection_plan(m);
    draw_sprites(m);

    mlx_put_image_to_window(m->mlx, m->win, m->image->image_p, 0, 0);

    ft_usleep(20000);
    return (0);
}
