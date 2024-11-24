#include <assert.h>

#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * TODO add documentation
*/

// Function prototypes
int get_number_of_lines();
int get_bus_line_info(BusLine* bus_line, int line_number);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mode>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* mode = argv[1];
    if (strcmp(mode, "test") != 0 && strcmp(mode, "by_name") != 0 &&
        strcmp(mode, "by_distance") != 0 && strcmp(mode, "by_duration") != 0) {
        fprintf(stderr, "Invalid mode: %s\n", mode);
        return EXIT_FAILURE;
        }

    if (strcmp(mode, "test") == 0) {
        run_test();
        return EXIT_SUCCESS;
    }

    int num_lines = get_number_of_lines();
    BusLine* lines = calloc(num_lines, sizeof(BusLine));
    if (!lines) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_lines; i++) {
        if (!get_bus_line_info(lines, i)) {
            fprintf(stderr, "Error: Failed to get line info for line %d.\n", i);
            free(lines);
            return EXIT_FAILURE;
        }
    }

    if (strcmp(mode, "by_name") == 0) {
        bubble_sort(lines, lines + num_lines);
    } else if (strcmp(mode, "by_distance") == 0) {
        quick_sort(lines, lines + num_lines, DISTANCE);
    } else if (strcmp(mode, "by_duration") == 0) {
        quick_sort(lines, lines + num_lines, DURATION);
    }

    for (int i = 0; i < num_lines; i++) {
        printf("%s, %d, %d\n", lines[i].name, lines[i].distance, lines[i].duration);
    }

    free(lines);
    return EXIT_SUCCESS;
}


int get_number_of_lines()
{
    char* end_pointer = NULL;

    while (1)
    {
        char buffer[64];
        printf("Enter number of lines: ");
        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        const long num_lines = strtol(buffer, &end_pointer, 10);
        if ((*end_pointer == '\n' || *end_pointer == '\0') && num_lines > 0)
        {
            return (int)num_lines;
        }
        printf("Invalid input. Please enter a valid number.\n");
    }
}

int get_bus_line_info(BusLine* bus_line, int line_number)
{
    while (1)
    {
        char buffer[64];
        printf("Enter bus line info (name, distance, duration): ");
        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        char name[21];
        int distance, duration;
        if (sscanf(buffer, "%20[^,],%d,%d", name, &distance, &duration) != 3)
        {
            printf("Error: Invalid input format.\n");
            continue;
        }
        for (int i = 0; name[i] != '\0'; i++)
        {
            if (!(name[i] >= 'a' && name[i] <= 'z')
                && !(name[i] >= '0' && name[i] <= '9'))
            {
                printf("Error: Only digits and small letters.\n");
                return 0; // Skip invalid entry
            }
        }
        if (distance < 0 || distance > 1000)
        {
            printf("Error: Distance should be an integer between 0 and 1000.\n");
            return 0; // Skip invalid entry
        }
        if (duration < 10 || duration > 100)
        {
            printf("Error: Duration should be an integer between 10 and 100.\n");
            return 0; // Skip invalid entry
        }
        strncpy(bus_line[line_number].name,
            name, sizeof(bus_line[line_number].name) - 1);
        bus_line[line_number].name[sizeof(bus_line[line_number].name) - 1] = '\0';
        bus_line[line_number].distance = distance;
        bus_line[line_number].duration = duration;
        return 1; // Success
    }
}
