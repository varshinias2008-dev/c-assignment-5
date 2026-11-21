#include <stdio.h>
#include <string.h>

typedef struct {
    char group[4];
    int units;
} Stock;

int update_units(FILE *fp, int record, int new_units)
{
    Stock item;

    if (record < 0 || new_units < 0)
        return 0;

    if (fseek(fp, (long)record * (long)sizeof(Stock), SEEK_SET) != 0)
        return 0;

    if (fread(&item, sizeof item, 1, fp) != 1)
        return 0;

    item.units = new_units;

    if (fseek(fp, (long)record * (long)sizeof(Stock), SEEK_SET) != 0)
        return 0;

    return fwrite(&item, sizeof item, 1, fp) == 1;
}

int main(void)
{
    Stock stock[5] = {
        {"A+", 10}, {"A-", 8}, {"B+", 15}, {"B-", 6}, {"AB+", 12}
    };

    FILE *fp = fopen("stock.dat", "wb");
    if (fp == NULL) {
        perror("stock.dat");
        return 1;
    }
    fwrite(stock, sizeof(Stock), 5, fp);
    fclose(fp);

    fp = fopen("stock.dat", "rb+");
    if (fp == NULL) {
        perror("stock.dat");
        return 1;
    }

    printf("update record 3: %s\n",
           update_units(fp, 2, 20) ? "done" : "failed");
    printf("update record 9: %s\n",
           update_units(fp, 8, 20) ? "done" : "failed");

    rewind(fp);
    Stock item;
    while (fread(&item, sizeof item, 1, fp) == 1)
        printf("%s: %d\n", item.group, item.units);

    fclose(fp);
    return 0;
}

SAMPLE OUTPUT:
update record 3: done
update record 9: failed
A+: 10
A-: 8
B+: 20
B-: 6
AB+: 12
