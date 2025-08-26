/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:20:19 by makarkao          #+#    #+#             */
/*   Updated: 2025/08/26 15:56:39 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void file_to_image(t_game *game, char **sp_line, char *line, t_texture *tex)
{
	tex->texture_p = mlx_xpm_file_to_image(game->mlx, sp_line[1], &tex->texture_w, &tex->texture_h);
	if(!tex->texture_p)
		exit((free(line), free_strs(sp_line), printf("ERROR\n"), 1));
	tex->texture_s = (unsigned int *)mlx_get_data_addr(tex->texture_p, &tex->bpp, &tex->texture_len, &tex->endian);
	if(!tex->texture_s)
		exit((free(line), free_strs(sp_line), printf("ERROR\n"), 1));
}


void fill_texture(t_game *game, char **sp_line, char *line, int flag)
{
	if(flag == EA)
		file_to_image(game, sp_line, line, &game->cub->tex_ea);
	else if(flag == WE)
		file_to_image(game, sp_line, line, &game->cub->tex_we);
	else if(flag == SO)
		file_to_image(game, sp_line, line, &game->cub->tex_so);
	else if(flag == NO)
		file_to_image(game, sp_line, line, &game->cub->tex_no);
	else if(flag == EA)
		file_to_image(game, sp_line, line, &game->cub->tex_ea);
	// else if (flag == F)
	// 	extract_color(game, sp_line, line, &game->cub->color_f);
	// else
	// 	extract_color(game, sp_line, line, &game->cub->color_f);
}


void fill_texture_tt(t_game *game, char **sp_line, char *line, int flag)
{
	if(game->cub->state_mask & flag)
		exit((printf("ERROR\n"), 1));
	else
	{
		game->cub->state_mask |= flag;
		fill_texture(game, sp_line, line, flag);
	}
}


void check_line(t_game *game, char **sp_line, char *line)
{
	if(!ft_strcmp(sp_line[0], "EA"))
		fill_texture_tt(game, sp_line, line, EA);
	else if (!ft_strcmp(sp_line[0], "SO"))
		fill_texture_tt(game, sp_line, line, SO);
	else if (!ft_strcmp(sp_line[0], "NO"))
		fill_texture_tt(game, sp_line, line, NO);
	else if (!ft_strcmp(sp_line[0], "WE"))
		fill_texture_tt(game, sp_line, line, WE);
	else if (!ft_strcmp(sp_line[0], "C"))
		fill_texture_tt(game, sp_line, line, C);
	else
		fill_texture_tt(game, sp_line, line, F);
}


int ft_check(char *str)
{
	return (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO") 
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "EA") 
		|| !ft_strcmp(str, "F") || !ft_strcmp(str, "C"));
}


char**	read_map(t_game *game, char *filename)
{
	int		fd;
	char	*line = NULL;
	char	**map;
	char	**sp_line = NULL;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ((perror("Error opening file"), NULL));
	map = NULL;
	line = get_next_line(fd, map);
	while (line)
	{
		sp_line = ft_split(line, ' ');
		if(!sp_line)
			return(printf("Error\n"), NULL);
		if(sp_line[0] && (!sp_line[1] || (sp_line[1] && sp_line[2])))
			return(printf("Error\n"), NULL);
		if(sp_line[0][0])
		{		
			if(ft_check(sp_line[0]))
				check_line(game, sp_line, line);
			else
				break;
		}
		(free(line), line = NULL);
		(free_strs(sp_line), sp_line = NULL);
		line = get_next_line(fd, map);
	}
	if(sp_line)
		(free_strs(sp_line), sp_line = NULL);
	if(game->cub->state_mask != (NO | SO | EA | WE | F | C))
		exit((free(line), printf("ERROR\n"), 1));
	// fill_map(game);
	printf("nadi\n");
	return (NULL);
}
