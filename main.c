#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 20
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100
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

int get_bus_line_info(BusLine* bus_line, int line_number) {
    while (1) {
        char buffer[64];
        printf("Enter bus line info (name, distance, duration): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Error reading input. Please try again.\n");
            continue;
        }

        char name[MAX_NAME_LENGTH + 1];
        int distance, duration;
        if (sscanf(buffer, " %20[^,],%d,%d", name, &distance, &duration) != 3) {
            printf("Error: Invalid input format. Expected: name,distance,duration.\n");
            continue;
        }

        for (int i = 0; name[i] != '\0'; i++) {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= '0' && name[i] <= '9'))) {
                printf("Error: Name must contain only lowercase letters and digits.\n");
                continue;
            }
        }

        if (distance < 0 || distance > MAX_DISTANCE) {
            printf("Error: Distance should be between 0 and %d.\n", MAX_DISTANCE);
            continue;
        }
        if (duration < MIN_DURATION || duration > MAX_DURATION) {
            printf("Error: Duration should be between %d and %d.\n", MIN_DURATION, MAX_DURATION);
            continue;
        }

        strncpy(bus_line[line_number].name, name, MAX_NAME_LENGTH);
        bus_line[line_number].name[MAX_NAME_LENGTH] = '\0';
        bus_line[line_number].distance = distance;
        bus_line[line_number].duration = duration;
        return 1; // Success
    }
}
