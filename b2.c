#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[10];

    printf("Enter donor name: ");
    if (fgets(name, sizeof(name), stdin) == NULL)
        return 1;

    name[strcspn(name, "\n")] = '\0';
    printf("Donor name: %s\n", name);

    return 0;
}

SAMPLE OUTPUT:
Enter donor name: GOPINATH
Donor name: GOPINATH
