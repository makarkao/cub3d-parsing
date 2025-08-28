#include "../cub3d.h"

void extract_width_height(t_cub_lines *cub_lines_list, int *m_w, int *m_h)
{
    int line_len;
    char *line;

    while(cub_lines_list)
    {
        (*m_h)++;
        line = cub_lines_list->line;
        line_len = ft_strlen(line);
        if(*m_w < line_len)
            *m_w = line_len;
        cub_lines_list = cub_lines_list->next;
    }
}


char *add_spaces_to_len(char *str, int len)
{
    int i;
    char *ret_str;

    i = -1;
    ret_str = malloc(sizeof(char)  * (len + 1));
    if(!ret_str)
        return (NULL);
    while(str[++i])
        ret_str[i] = str[i];
    while(i < len);
        ret_str[i++] = ' ';
    ret_str[i] = '\0';
    return (ret_str);
}

char ** fill_map(t_game *game, t_cub_lines *cub_lines_list)
{
    int map_width;
    int map_height;
    char **map;
    int i;

    i = 0;
    map_width = -1;
    map_height = 0;
    extract_width_height(cub_lines_list, &map_width, &map_height);
    game->cub->map_height = map_height;
    game->cub->map_width = map_width;
    map = malloc(sizeof(char *) * map_height);
    while(i < map_height)

    {
        map[i] =  add_spaces_to_len(cub_lines_list->line, map_width);
        if(!map[i])
            return (NULL);
        cub_lines_list = cub_lines_list->next;
        i++;
    }
    return (map);
}
