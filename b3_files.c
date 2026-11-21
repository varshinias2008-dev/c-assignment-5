#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    char group[4];
} Donor;

int main(void)
{
    Donor donors[10], readback[10];

    for (int i = 0; i < 10; i++) {
        donors[i].id = 101 + i;
        snprintf(donors[i].name, sizeof donors[i].name, "Donor%d", i + 1);
        strcpy(donors[i].group, (i % 2 == 0) ? "A+" : "O+");
    }

    FILE *tf = fopen("donors.txt", "w");
    if (tf == NULL) {
        perror("donors.txt");
        return 1;
    }

    for (int i = 0; i < 10; i++)
        fprintf(tf, "%d,%s,%s\n",
                donors[i].id, donors[i].name, donors[i].group);
    fclose(tf);

    tf = fopen("donors.txt", "r");
    if (tf == NULL) {
        perror("donors.txt");
        return 1;
    }

    int text_count = 0;
    char line[100];
    while (fgets(line, sizeof line, tf) != NULL)
        text_count++;
    fclose(tf);

    FILE *bf = fopen("donors.dat", "wb");
    if (bf == NULL) {
        perror("donors.dat");
        return 1;
    }
    if (fwrite(donors, sizeof(Donor), 10, bf) != 10) {
        printf("Binary write failed.\n");
        fclose(bf);
        return 1;
    }
    fclose(bf);

    bf = fopen("donors.dat", "rb");
    if (bf == NULL) {
        perror("donors.dat");
        return 1;
    }
    size_t count = fread(readback, sizeof(Donor), 10, bf);
    fclose(bf);

    int correct = (count == 10);
    for (int i = 0; i < 10 && correct; i++) {
        if (donors[i].id != readback[i].id ||
            strcmp(donors[i].name, readback[i].name) != 0 ||
            strcmp(donors[i].group, readback[i].group) != 0)
            correct = 0;
    }

    printf("Text file verification: %s\n",
           text_count == 10 ? "SUCCESS" : "FAILED");
    printf("Binary file verification: %s\n",
           correct ? "SUCCESS" : "FAILED");

    return 0;
}

SAMPLE OUTPUT:
Text file verification: SUCCESS
Binary file verification: SUCCESS
