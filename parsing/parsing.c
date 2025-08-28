#include "../cub3d.h"

void init_game_cub(t_game *game)
{
    game->cub = malloc(sizeof(t_cub));

    game->cub->map = NULL;
    game->cub->map_height = -1;
    game->cub->map_width = -1;
    game->cub->state_mask = 0;
    game->cub->color_c = (t_rgb){ 0, 0, 0 };
    game->cub->color_f = (t_rgb){ 0, 0, 0 };
}

void parsing(t_game *game, char *fileName)
{
    t_cub_lines *cub_lines_list;

    cub_lines_list = read_cube_file(game, fileName);
    init_game_cub(game);
    read_map(game, cub_lines_list);
    // check_map(game);
}