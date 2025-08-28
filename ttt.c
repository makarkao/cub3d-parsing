#include "cub3d.h"


// int mouse_hook(int button, int x, int y, void *param)
// {
//     if (button == 1) // left click
//         printf("Left click at (%d, %d)\n", x, y);
//     else if (button == 3) // left click
//         printf("right click at (%d, %d)\n", x, y);
//     else if (button == 2) // left click
//         printf("middle click at (%d, %d)\n", x, y);
//     else if (button == 4) // scroll up
//         printf("Scroll up at (%d, %d)\n", x, y);
//     else if (button == 5) // scroll up
//         printf("Scroll down at (%d, %d)\n", x, y);
//     else if (button == 6) // scroll left
//         printf("Scroll left\n");
//     else if (button == 7) // scroll right
//         printf("Scroll right\n");

//     return (0);
// }




// typedef struct s_rgb
// {
//     int r;
//     int g;
//     int b;
// } t_rgb;

int check_numeric(char c)
{
    return (c >= '0' && c <= '9');
}

void extract_color(t_rgb *rgbb, char **sp_line)
{
	int i;
	int j;
	int *rgb;
	int number;
	int comma_flag;
	int count_comma;
	int count_digits;

	i = 1;
	number = 0;
	comma_flag = 1;
	count_comma = 0;
	count_digits = 0;
	rgb = (int[3]){-1, -1, -1};
	while (sp_line[i])
	{
		j = 0;
		while (sp_line[i][j])
		{
			if (check_numeric(sp_line[i][j]))
			{
				count_digits++;
				if(count_digits > 3)
					exit((printf("ERROR 1\n"), 1));
				number = (number * 10) + (sp_line[i][j] - 48);
				if (number > 255)
					exit((printf("ERROR 2\n"), 1));
				if (comma_flag)
					comma_flag = 0;
			}
			else if (sp_line[i][j] == ',' && !comma_flag)
			{
				rgb[count_comma++] = number;
				if (count_comma > 2)
					exit((printf("ERROR 3\n"), 1));
				comma_flag = 1;
				count_digits = 0;
                number = 0;
			}
			else
				exit((printf("ERROR 4\n"), 1));
			j++;
		}
		i++;
	}
	if(count_comma == 2)
		rgb[count_comma] = number;
	else
		exit((printf("ERROR 5\n"), 1));
	*rgbb = (t_rgb){rgb[0], rgb[1], rgb[2]};
}

// void assign(t_rgb *rgb)
// {
//     *rgb = (t_rgb){88, 99 , 77};
// }

int main(void)
{
    t_rgb rgb = {-1, -1, -1};
    printf("before ->  r = %d, g = %d, b = %d  \n", rgb.r, rgb.g, rgb.b);
    char *str = "F 187, 88,           98      ";
    char **sp_line = ft_split(str, ' ');
    extract_color(&rgb, sp_line);
    // assign(&rgb);
    printf("after   ->  r = %d, g = %d, b = %d  \n", rgb.r, rgb.g, rgb.b);
}

    // void *mlx;
    // void *win;

    // mlx = mlx_init();
    // win = mlx_new_window(mlx, 800, 600, "Mouse Hook Example");

    // mlx_mouse_hook(win, mouse_hook, NULL);
    // mlx_loop(mlx);