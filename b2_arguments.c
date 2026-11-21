#include <stdio.h>
#include <string.h>

int valid_group(const char *g)
{
    const char *groups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    for (int i = 0; i < 8; i++)
        if (strcmp(g, groups[i]) == 0)
            return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "find") != 0) {
        printf("Usage: program find BLOOD_GROUP\n");
        return 1;
    }

    if (!valid_group(argv[2])) {
        printf("Invalid blood group.\n");
        return 1;
    }

    printf("Command accepted.\n");
    printf("Searching for blood group: %s\n", argv[2]);
    return 0;
}

SAMPLE COMMANDS AND OUTPUTS:
Command: program
Output: Usage: program find BLOOD_GROUP

Command: program find O+ extra
Output: Usage: program find BLOOD_GROUP

Command: program find X+
Output: Invalid blood group.

Command: program find O+
Output:
Command accepted.
Searching for blood group: O+
