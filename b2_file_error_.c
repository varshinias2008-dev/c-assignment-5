#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("donors.txt", "r");

    if (fp == NULL) {
        perror("Error opening donors.txt");
        return 1;
    }

    printf("File opened successfully.\n");
    fclose(fp);
    return 0;
}

SAMPLE OUTPUT WHEN donors.txt IS NOT PRESENT:
Error opening donors.txt: No such file or directory
