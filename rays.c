#include "cub3d.h"

int min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}



//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------




void set_ray_direction(t_ray *ray)
{

    if(ray->angle > 0 && ray->angle < M_PI)
    {
        ray->facing_down = 1;
        ray->facing_up = 0;
    }
    else if(ray->angle > M_PI && ray->angle < 2 * M_PI)
    {
        ray->facing_down = 0;
        ray->facing_up = 1;
    }
    else
    {
        ray->facing_down = -1;
        ray->facing_up = -1;
    }
    if(ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
    {
        ray->facing_left = 1;
        ray->facing_right = 0;
    }
    else if((ray->angle > 0 && ray->angle < M_PI / 2) || (ray->angle > 3 * M_PI / 2 && ray->angle < M_PI * 2))
    {
        ray->facing_left = 0;
        ray->facing_right = 1;
    }
    else
    {
        ray->facing_left = -1;
        ray->facing_right = -1;
    }
}




//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------




int check_If_Wall_touched(t_map *map, double x, double y)
{
    int i;
    int j;

    i = (int)floor(x / map->tile);
    j = (int)floor(y / map->tile);
    if((i >= 0 && i < map->w) && (j >= 0 && j < map->h))
    {
        if(map->map[j][i] == 1)
            return (1);
    }
    return (0);
}



//--------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------




void calculate_V_d(t_game *game, t_ray *ray, t_raydata *vertical)
{
    int error;
    int error1;
    int error2;

    error = 0;
    error1 = 0;
    error2 = 0;

    if(ray->facing_right)
        error1 = game->map->tile;

    vertical->xintersect = error1 + floor((game->player->x_p + 8) / game->map->tile) * (game->map->tile);
    vertical->yintersect = game->player->y_p + 8 + (vertical->xintersect - game->player->x_p - 8) * tan(vertical->angle);

    vertical->xstep = game->map->tile;
    vertical->ystep = game->map->tile * tan(vertical->angle);

    if(ray->facing_left == 1)
        vertical->xstep *= -1;

    if((ray->facing_up == 1 && vertical->ystep > 0) || (ray->facing_down == 1 && vertical->ystep < 0))
        vertical->ystep *= -1;

    vertical->nextouchx = vertical->xintersect;
    vertical->nextouchy = vertical->yintersect;

    if(ray->facing_left == 1)
        error++;
    // if(ray->facing_up == 1)
    //     error2++;

    while(vertical->nextouchx >= 0 && vertical->nextouchx < game->map->w_p && vertical->nextouchy >= 0 && vertical->nextouchy < game->map->h_p && !check_If_Wall_touched(game->map, vertical->nextouchx - error, vertical->nextouchy - error2))
    {
        vertical->nextouchx += vertical->xstep;
        vertical->nextouchy += vertical->ystep;
    }

    vertical->distance = sqrt(pow(game->player->x_p + 8 - vertical->nextouchx, 2) + pow(game->player->y_p + 8 - vertical->nextouchy, 2));
}




//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------




void calculate_H_d(t_game *game, t_ray *ray, t_raydata *horizantal)
{
    int error;
    int error1;
    int error2;

    error = 0;
    error1 = 0;
    error2 = 0;
    if(ray->facing_down)
        error1 = game->map->tile;

    horizantal->yintersect = error1 + floor((game->player->y_p + 8) / game->map->tile) * (game->map->tile);
    horizantal->xintersect = game->player->x_p + 8 + (horizantal->yintersect - game->player->y_p - 8) / tan(horizantal->angle);

    horizantal->ystep = game->map->tile;
    horizantal->xstep = game->map->tile / tan(horizantal->angle);

    if(ray->facing_up == 1)
        horizantal->ystep *= -1;

    if((ray->facing_left == 1 && horizantal->xstep > 0) || (ray->facing_right == 1 && horizantal->xstep < 0))
        horizantal->xstep *= -1;

    horizantal->nextouchx = horizantal->xintersect;
    horizantal->nextouchy = horizantal->yintersect;

    if(ray->facing_up == 1)
        error++;
    // if(ray->facing_left == 1)
    //     error2++;

    while(horizantal->nextouchx >= 0 && horizantal->nextouchx < game->map->w_p && horizantal->nextouchy >= 0 && horizantal->nextouchy < game->map->h_p && !check_If_Wall_touched(game->map, horizantal->nextouchx - error2, horizantal->nextouchy - error))
    {
        horizantal->nextouchx += horizantal->xstep;
        horizantal->nextouchy += horizantal->ystep;
    }

    horizantal->distance = sqrt(pow(game->player->x_p + 8 - horizantal->nextouchx, 2.0) + pow(game->player->y_p + 8 - horizantal->nextouchy, 2.0));
}




//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------




void calculate_dda(t_game *game, t_ray *ray)
{
    // t_ray *ray = game->ray;
    t_raydata horizantal;
    t_raydata vertical;

    // ray->angle = game->player->angle - FOV 199/ 2;

    horizantal.angle = ray->angle;
    vertical.angle = ray->angle;
    set_ray_direction(ray);
    calculate_H_d(game, ray, &horizantal);
    calculate_V_d(game, ray, &vertical);
    if(fmin(horizantal.distance, vertical.distance) == horizantal.distance)
    {
        ray->distance = horizantal.distance;
        ray->xtouch = horizantal.nextouchx;
        ray->ytouch = horizantal.nextouchy;
        ray->is_h_or_v = IS_H;

    }
    else
    {
        ray->distance = vertical.distance;
        ray->xtouch = vertical.nextouchx;
        ray->ytouch = vertical.nextouchy;
        ray->is_h_or_v = IS_V;
    }
    // draw_line(game->map, game->image, game->player->x_p + 8, game->player->y_p + 8, ray->xtouch, ray->ytouch);
}




//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------




void fill_rays_list(t_game *game)
{
    int win_width = game->map->w_p;
    int i;
    double distanceProjPlane = ((double)win_width / 2) / tan(FOV / 2);

    i = 0;
    double teta = game->player->angle - FOV / 2;
    // double alpha = FOV / game->map->w_p;
    while(i < game->map->w_p)
    {
        teta = game->player->angle + atan((i - game->map->w_p / 2) / distanceProjPlane);
        if(teta < 0)
            teta += (2 * M_PI);
        else if(teta > (2 * M_PI))
            teta -= (2 * M_PI);
        game->ray[i].angle = teta; 
        calculate_dda(game, &game->ray[i]);
        // teta += alpha;
        i++;
    }
}




//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------




void draw_rays(t_game *game)
{
    int i;

    i = 0;
    while(i < game->map->w_p)
    {
        // printf("player angles ---  =   %lf\n", game->player->angle);
        // printf("ray angles ---  =   %lf\n", game->ray[i].angle);
        draw_line(game->map, game->image, game->player->x_p + 8, game->player->y_p + 8, game->ray[i].xtouch, game->ray[i].ytouch);
        i++;
    }
}




//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------





int calculate_color_b_distance(double rayDisFishCorrect, int is_h_or_v, double angle)
{
    unsigned int color = 0x00000000;

    if(is_h_or_v == IS_H)
    {
        if(angle > M_PI && angle < 2 * M_PI)
            color = (unsigned int)255 << 8;
        else
            color = (unsigned int)105 << 8 | (unsigned int)105 << 16;
    }
    else
    {
        if(angle > M_PI / 2 && angle < 3 * M_PI / 2)
            color = (unsigned int)255;
        else
            color = (unsigned int)255 | (unsigned int)205 << 16;
        
    }
    double percentage = 350 / rayDisFishCorrect;

    if(percentage > 1.0)
        percentage = 1.0;
    
    double dopacity = 255 * percentage;

    if((unsigned char)dopacity < 10)
        dopacity = 10;
    
    unsigned int t = ((unsigned char)dopacity) << 24;
    color |= t;
    return ((int)color);
}




//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------





unsigned int extract_color(t_texture *tex, t_ray *ray, int x, int y)
{
    int bytes = tex->bpp / 8; // 3 or 4
     unsigned char *p;
    if(x < 0 || y < 0 && y >= 64 || x >= 64)
        return 0;
    if(ray->is_h_or_v == IS_H)
    {
        if(ray->angle > M_PI && ray->angle < 2 * M_PI)
            p = ( unsigned char *)tex->texture_s + y * tex->texture_len + x * bytes;
        else
            p = ( unsigned char *)(tex + 1)->texture_s + y * tex->texture_len + x * bytes;

    }
    else
    {
        if(ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
            p = ( unsigned char *)(tex + 2)->texture_s + y * tex->texture_len + x * bytes;
        else
            p = ( unsigned char *)(tex + 3)->texture_s + y * tex->texture_len + x * bytes;
    }
    unsigned char r=0, g=0, b=0, a=0xFF;
            // little-endian (Linux): BGRA in memory
    b = p[0]; g = p[1]; r = p[2]; a = p[3];
    return ((unsigned)a << 24) | ((unsigned)r << 16)
         | ((unsigned)g << 8)  |  (unsigned)b;  // AARRGGBB
}




//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------




unsigned int extract_color_ftexture(t_game *game, t_ray *ray, int y)
{
    int x_t;
    int y_t;
    if(ray->is_h_or_v == IS_H)
        x_t = (int)floor(fmod(ray->xtouch, game->map->tile) * (double)game->textures[0].texture_w / game->map->tile);
    else
        x_t = (int)floor(fmod(ray->ytouch, game->map->tile) * (double)game->textures[0].texture_w / game->map->tile);
    y_t = y;
    return (extract_color(game->textures, ray, x_t, y_t));
}




//--------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------




void draw_to_projection_plan(t_game *game)
{
    int     x;
    int     y;
    double  wallstripHegit;
    t_ray   *ray = game->ray;
    double  distanceProjPlane;


    int     wall_top_y;
    int     wall_bottom_y;
    double texture_offset_y;



    int     win_height;
    int     win_width;
    double  rayDisFishCorrect;


    x = 0;
    win_width = game->map->w_p;
    win_height = game->map->h_p;
    wallstripHegit = 0;
    distanceProjPlane = 0;
    unsigned int color;
    while(x < win_width)
    {  
        rayDisFishCorrect = ray[x].distance * cos(ray[x].angle - game->player->angle);
        distanceProjPlane = ((double)win_width / 2) / tan(FOV / 2);
        wallstripHegit = (TILE / rayDisFishCorrect) *  distanceProjPlane;
        // if(wallstripHegit > win_height)
        //     wallstripHegit = win_height;



        wall_top_y = (win_height / 2) - ((int)wallstripHegit / 2);
        if(wall_top_y < 0)
            wall_top_y = 0;

        wall_bottom_y = (win_height / 2) + (wallstripHegit / 2);
        if(wall_bottom_y > win_height)
            wall_bottom_y = win_height;

        y = 0;
        while(y < wall_top_y)
        {
            set_color(game->image, x, y, 0xFFB0EFFF);
            y++;
        }
        y = wall_top_y;
        while(y < wall_bottom_y)
        {
            texture_offset_y = ((double)y - (win_height / 2) + (wallstripHegit / 2)) * (64.0 / wallstripHegit);
            color = extract_color_ftexture(game, &ray[x], (int)texture_offset_y);
            set_color(game->image, x, y, color);
            y++;
        }
        y = wall_bottom_y;
        while(y < win_height)
        {
            set_color(game->image, x, y, 0x11808080);
            y++;
        }
        x++;
    }
}


