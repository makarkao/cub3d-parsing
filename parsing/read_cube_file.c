#include "../cub3d.h"

void free_lines_list(t_cub_lines *cub_lines)
{
    t_cub_lines *tmp;

    while(cub_lines)
    {
        tmp = cub_lines->next;
        free(cub_lines->line);
        free(cub_lines);
        cub_lines = tmp;
    }
}

t_cub_lines *create_line_node(char *line)
{
    t_cub_lines *line_node = malloc(sizeof(t_cub_lines));

    if(!line_node)
        return NULL;
    line_node->line = line;
    line_node->next = NULL;
    return (line_node);
}

void    addback_line(t_cub_lines **cub_lines, char *line)
{
    t_cub_lines *line_node = create_line_node(line);
    t_cub_lines *node;
    
    if(!cub_lines)
        return ;
    if(!*cub_lines)
    {
        *cub_lines = line_node;
        return;
    }
    node = *cub_lines;
    while(node->next)
        node = node->next;
    node->next = line_node;
}

t_cub_lines *read_cube_file(t_game *game, char *filename)
{
    int         fd;
    char        *line;
    t_cub_lines *cub_lines;

    fd = open(filename, O_RDONLY);
	if (fd < 0)
		return((perror("Error opening file"), NULL));
    line = get_next_line(fd);
    if(!line && errno == ENOMEM)
        exit(1);
    else if (!line)
        exit((printf("ERROR Empty file\n"), 1));
    cub_lines = NULL;
    while(line)
    {
        addback_line(&cub_lines, line);
       
        line = get_next_line(fd);
        if(!line && errno == ENOMEM)
            exit((free_lines_list(cub_lines), 1));
    }
    return (cub_lines);
}