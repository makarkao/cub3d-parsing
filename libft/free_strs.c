#include "libft.h"

void free_strs(char **strs)
{
    int i;

    i = 0;
    while(strs[i])
        free(strs[i++]);
    free(strs);
}