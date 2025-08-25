#ifndef CUB3D_H
#define CUB3D_H

#include "mlx_linux/mlx.h"
// #include "MLX/.MLX42.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <./libft/libft.h>
#include <sys/time.h>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FOV  (7 * M_PI / 18) 	
#define IS_H  1 	
#define IS_V  2

#define ESC_KEY     65307
#define UP_KEY      119
#define DOWN_KEY    115
#define RIGHT_KEY   100
#define LEFT_KEY    97

#define R_RIGHT_KEY 65363
#define R_LEFT_KEY  65361


typedef struct s_sprites
{
    int             sprite_n;
    int             tex_index;
    double          x_pos;
    double          y_pos;
    double          distance;
    double          angle;
    bool            visible;
}   t_sprites;


typedef struct s_sprites_list
{
    t_sprites  sprite_data;
    struct  s_sprites_list   *next;
    
}   t_sprites_list;


typedef struct s_texture
{
    int             bpp;
    int             endian;
    int             texture_len;
    int             texture_h;
    int             texture_w;
    void            *texture_p;
    unsigned int    *texture_s;
}   t_texture;


// typedef struct s_map 
// {
//     int             map[15][20];
//     int             tile;
//     int             h;
//     int             h_p;
//     int             w;
//     int             w_p;
// }   t_map;

typedef struct s_map 
{
    char            **map;
    // int             tile;
    int             h;
    // int             h_p;
    int             w;
    // int             w_p;
}   t_map;


typedef struct s_raydata
{
    double          xstep;
    double          ystep;

    double          xintersect;
    double          yintersect;

    double          nextouchx;
    double          nextouchy;

    double          distance;
    double          angle;
}   t_raydata;


typedef struct s_ray
{
    double          distance;
    double          angle;
    double          xtouch;
    double          ytouch;
    int             is_h_or_v;
    int             facing_down;     
    int             facing_up;     
    int             facing_right;     
    int             facing_left;
}   t_ray;


typedef struct s_player
{
    double          x_p;
    double          y_p;
    double          angle;
    double          angle_speed;
    char            up;
    char            down;
    char            right;
    char            left;
    char            r_right;
    char            r_left;
}   t_player;


typedef struct s_image
{
    int             bpp;
    int             size_len;
    int             endian;
    int             image_width;
    int             image_height;
    void            *image_p;
    unsigned char   *image_s;
}   t_image;

typedef struct s_rgb
{
    int r;
    int g; 
    int b; 

} t_rgb;


typedef struct s_cub
{
    t_texture       tex_no;
    t_texture       tex_so;
    t_texture       tex_we;
    t_texture       tex_ea;
    char            **map;
    int             map_height;
    int             map_width;
    unsigned char   state_mask;
    t_rgb           color_c;
    t_rgb           color_f;
}   t_cub;


typedef struct s_game
{
    void            *mlx;
    void            *win;
    t_image         *image;
    t_player        *player;
    t_cub           *cub;
    t_map           *map;
    t_ray           *ray;
    t_texture       *textures;
    t_sprites_list  *sprites;
    int             sprites_count;
}   t_game;


int    draw_in_screen(t_game *m);
int     player_mv(t_game *m);
void    calculate_dda(t_game *game, t_ray *ray);
void    draw_line(t_map *map, t_image *image, int x0, int y0, int x1, int y1);
void    fill_rays_list(t_game *game);
void    draw_rays(t_game *game);
void    draw_to_projection_plan(t_game *game);
void    set_color(t_image *image, int x, int y, unsigned int color);
void    fill_sprites_list(t_game *game);
void    draw_sprites(t_game *game);

int     key_press(int key, t_game *m);
int     key_release(int key, t_game *m);
int     handle_close(t_game *m);
int     cursor_func(int xpos, int ypos, t_game *game);

#endif