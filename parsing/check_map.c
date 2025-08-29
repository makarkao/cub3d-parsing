#include "../cub3d.h"

void    check_map(char  **map)
{
    int i;
    int j;

    i = 0;
    while(map[i][j])
    {
        j = 0;
        while(map[i][j])
        {


            j++;
        }
        i++;
    }
}
