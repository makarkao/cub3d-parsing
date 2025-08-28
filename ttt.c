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
void assign(t_rgb *rgb)
{
    *rgb = (t_rgb){88, 99 , 77};
}

int main(void)
{
    t_rgb rgb = {10, 23, 57};

    printf("before ->  r = %d, g = %d, b = %d  \n", rgb.r, rgb.r, rgb.b);
    assign(&rgb);
    printf("after   ->  r = %d, g = %d, b = %d  \n", rgb.r, rgb.r, rgb.b);
}

    // void *mlx;
    // void *win;

    // mlx = mlx_init();
    // win = mlx_new_window(mlx, 800, 600, "Mouse Hook Example");

    // mlx_mouse_hook(win, mouse_hook, NULL);
    // mlx_loop(mlx);