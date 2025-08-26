#include "../cub3d.h"

void fill_map(t_game *game, char *line)
{
    int line_len = -1;
    int map_width = -1;
    int map_height = 0;
    while(line)
    {
        map_height++;
        line_len = ft_strlen(line);
        if(map_width < line_len)
            map_width = line_len;
        if(line[0] != '1' && line[0] != ' ')
            exit((free(line), printf("ERROR\n"), 1));
        addback_line(game, maplines_list, line);
        line = get_next_line(fd, map);
    }
}