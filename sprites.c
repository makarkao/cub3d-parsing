#include "cub3d.h"

//-------------------distance between points-----------------------

double distancepoints(double x0, double y0, double x1, double y1)
{
    return(sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2)));
}

//--------------------
t_sprites_list *create_sprite_node(int sp_num, int x_pos, int y_pos)
{
    t_sprites_list *sp_new_node = malloc(sizeof(t_sprites_list));

    sp_new_node->sprite_data.sprite_n = sp_num;
    if(sp_num == 2)
        sp_new_node->sprite_data.tex_index = 4;
    else if (sp_num == 3)
        sp_new_node->sprite_data.tex_index = 5;
    else if (sp_num == 4)
        sp_new_node->sprite_data.tex_index = 6;
    else
        sp_new_node->sprite_data.tex_index = 0;
    sp_new_node->sprite_data.x_pos = (double)x_pos;
    sp_new_node->sprite_data.y_pos = (double)y_pos;
    sp_new_node->sprite_data.distance = -1.0;
    sp_new_node->sprite_data.angle = 1.5 * M_PI;
    sp_new_node->sprite_data.visible = false;
    sp_new_node->next = NULL;
    return (sp_new_node);
}

//////////


void addback_sprites(t_game *game, int sp_num, int i, int j)
{
    int x_pos = i * game->map->tile;
    int y_pos = j * game->map->tile;
    t_sprites_list *sp_node = create_sprite_node(sp_num, x_pos, y_pos);
    if(!sp_node || !game)
        return ;
    if (!game->sprites)
    {
        game->sprites = sp_node;
        return;
    }
    t_sprites_list *node = game->sprites;
    while(node->next)
        node = node->next;
    node->next = sp_node;
}

///////////

void addback_sprite_sorted(t_sprites_list **head, t_sprites_list *sp_node)
{
    if(!sp_node || !head)
        return ;
    if (!*head)
    {
        *head = sp_node;
        return;
    }
    t_sprites_list *node = *head;
    t_sprites_list *prev = NULL;
    while(node->next)
    {
        if(node->sprite_data.distance < sp_node->sprite_data.distance)
        {
            if(!prev)
                *head = sp_node;
            else
                prev->next = sp_node;
            sp_node->next = node;
            return;
        }
        prev = node;
        node = node->next;
    }
    if(node->sprite_data.distance < sp_node->sprite_data.distance)
    {
        if(!prev)
            *head = sp_node;
        else
            prev->next = sp_node;
        sp_node->next = node;
        return;
    }
    else
        node->next = sp_node;
}

//////////

//////////

void free_sprites_list(t_sprites_list *head)
{
    t_sprites_list *tmp;

    while(head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

/////////

//-------------------------------------------------------------------------------------------------------------------


void fill_sprites_list(t_game *game)
{
    int i;
    int j = 0;
    t_map *map = game->map;

    while(j < map->h)
    {
        i = 0;
        while(i < map->w)
        {
            if(map->map[j][i] >= 2 && map->map[j][i] <= 4)
            {
                game->sprites_count++;
                addback_sprites(game, map->map[j][i], i, j);
            }
            i++;
        }
        j++;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------


unsigned int extract_sprites_color(t_game *game, t_sprites_list  *visible_spnode, int x, int y)
{
    t_texture tex = game->textures[visible_spnode->sprite_data.tex_index];
    int bytes = tex.bpp / 8; // 3 or 4
     unsigned char *p;

     if(x < 0 || x >= tex.texture_w || y < 0 || y >= tex.texture_h)
        return (0x00000000);

    p = ( unsigned char *)tex.texture_s + y * tex.texture_len + x * bytes;

    unsigned char r=0, g=0, b=0, a=0xFF;


    b = p[0]; g = p[1]; r = p[2]; a = p[3];
    return ((unsigned)a << 24) | ((unsigned)r << 16)
         | ((unsigned)g << 8)  |  (unsigned)b;  // AARRGGBB
}

void draw_sprites(t_game *game)
{
    t_sprites_list  *visible_sp = NULL;
    t_sprites_list  *visible_spnode;
    t_sprites_list  *all_sps = game->sprites;
    t_player    *player = game->player;
    double          anglePlayerSprite;
    double          arctanPSprite;

    while(all_sps)
    {
        arctanPSprite = atan2(all_sps->sprite_data.y_pos - player->y_p - 8, all_sps->sprite_data.x_pos - player->x_p - 8);
        //** */
        if(arctanPSprite > 2 * M_PI)
            arctanPSprite -= 2 * M_PI;
        else if (arctanPSprite < 0)
            arctanPSprite += 2 * M_PI;
        //** */
        anglePlayerSprite = arctanPSprite - player->angle;
        //--
        if(anglePlayerSprite >  M_PI)
            anglePlayerSprite -= 2 * M_PI;
        else if (anglePlayerSprite <  -M_PI)
            anglePlayerSprite += 2 * M_PI;
        //--
        // anglePlayerSprite = fabs(anglePlayerSprite);
        if(fabs(anglePlayerSprite) < (FOV / 2) + 0.2)
        {
            visible_spnode = create_sprite_node(all_sps->sprite_data.sprite_n, all_sps->sprite_data.x_pos, all_sps->sprite_data.y_pos);
            visible_spnode->sprite_data.visible = true;//don't need it
            visible_spnode->sprite_data.distance = distancepoints(player->x_p + 8, player->y_p + 8, visible_spnode->sprite_data.x_pos, visible_spnode->sprite_data.y_pos);
            visible_spnode->sprite_data.angle = anglePlayerSprite;
            addback_sprite_sorted(&visible_sp, visible_spnode);
        }
        all_sps = all_sps->next;
    }
    // sort_visible_sprites_list(&visible_sp);
    visible_spnode = visible_sp;
    // int i = 0;
    // printf("-----------------------------------------\n");
    // printf("-----------------------------------------\n");



    ////
    //////

    double  spriteHegit;
    double  spriteWidth;

    double spriteTopY;
    double spriteBottomY;

    double  distanceProjPlane;

    int     win_height;
    int     win_width;
    win_width = game->map->w_p;
    win_height = game->map->h_p;

    double spriteAngle;
    // double spriteScreenPx;
    double spriteLeftX;
    double spriteRightX;

    unsigned int color;
    // int i = 0;

    while(visible_spnode)
    {
        distanceProjPlane = (win_width / 2) / tan(FOV / 2);
        spriteHegit = ((game->map->tile) / visible_spnode->sprite_data.distance) *  distanceProjPlane;
        spriteWidth = spriteHegit;

        spriteTopY = (win_height / 2) - (spriteHegit / 2);
        if(spriteTopY < 0)
            spriteTopY = 0;
        
        spriteBottomY = (win_height / 2) + (spriteHegit / 2);
        if(spriteBottomY > win_height)
            spriteBottomY = win_height;
        
        
        spriteAngle = visible_spnode->sprite_data.angle;
    
        spriteLeftX = (win_width / 2) + (tan(spriteAngle) * distanceProjPlane) - 32;
        spriteRightX = spriteLeftX + spriteWidth;

        int x = (int)spriteLeftX;
        int y;

        double xcol;
        double ycol;
        while(x < (int)spriteRightX)
        {
            y = (int)spriteTopY;
            while(y < (int)spriteBottomY)
            {
                xcol = floor(((double)x - spriteLeftX) * 64 / spriteWidth);
                ycol = ((double)y - ((win_height / 2) - (spriteHegit / 2))) * 64 / spriteHegit;

                color = extract_sprites_color(game, visible_spnode, (int)xcol, (int)ycol);
                // if(x < 0)
                //     printf("x == %d\n", x);
                if (x >= 0 && y >= 0 && x < game->map->w_p && y < game->map->h_p && color != 0x00000000 && game->ray[x].distance > visible_spnode->sprite_data.distance)
                    set_color(game->image, x, y, color);
                y++;
            }
            x++;
        }

        visible_spnode = visible_spnode->next;
    }

    free_sprites_list(visible_sp); 
}