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

char ** fill_map(t_game *game, t_cub_lines *cub_lines_list)
{
    char *line;
    // int line_len = -1;
    int map_width = -1;
    int map_height = 0;
    extract_width_height(cub_lines_list, &map_width, &map_height);
    char **map = malloc(sizeof(char *) * map_height);
    int i = 0;

    while(i < map_height)
    {
        map[i] = ft_strjoin(cub_lines_list->line, n_space(map_width, ft_strlen(cub_lines_list->line)));
        cub_lines_list = cub_lines_list->next;
        i++;
    }
    return (map);
}
