#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    char *name = NULL;
    size_t size = 0;

    printf("Enter donor name: ");
    if (getline(&name, &size, stdin) != -1) {
        printf("Donor name: %s", name);
    }

    free(name);
    return 0;
}

SAMPLE OUTPUT:
Enter donor name: GOPINATH
Donor name: GOPINATH
