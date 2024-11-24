#include "test_bus_lines.h"
#include "sort_bus_lines.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//TODO add implementation here
int is_sorted_by_distance(const BusLine* start, const BusLine* end)
{
    for (const BusLine* current = start; current < end - 1; current++)
    {
        if (current->distance > ((current + 1)->distance))
        {
            return 0;
        }
    }
    return 1;
}

int is_sorted_by_duration(const BusLine* start, const BusLine* end)
{
    for (const BusLine* current = start; current < end - 1; current++)
    {
        if (current->duration > ((current + 1)->duration))
        {
            return 0;
        }
    }
    return 1;
}


int is_sorted_by_name(const BusLine* start, const BusLine* end)
{
    for (const BusLine* current = start; current < end - 1; ++current)
    {
        if (strcmp(current->name, (current + 1)->name) > 0)
        {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}


int is_equal(const BusLine* start_sorted,
             const BusLine* end_sorted,
             const BusLine* start_original,
             const BusLine* end_original)
{
    const long n_sorted = end_sorted - start_sorted;
    const long n_original = end_original - start_original;

    if (n_sorted != n_original)
    {
        return 0;
    }

    for (const BusLine* current = start_sorted; current < end_sorted; current++)
    {
        int found_flag = 0;
        for (const BusLine* current_original = start_original;
             current_original < end_original; current_original++)
        {
            if (current->distance == current_original->distance &&
                current->duration == current_original->duration &&
                strcmp(current->name, current_original->name) == 0)
            {
                found_flag = 1;
                break;
            }
        }
        if (!found_flag)
        {
            return 0; // An element in the sorted array doesn't exist in the original
        }
    }
    return 1; // All elements match
}

void run_test(const BusLine* lines, const BusLine* end) {
    size_t size = end - lines;

    // Create temporary arrays for sorting
    BusLine* sorted_by_distance = calloc(size, sizeof(BusLine));
    BusLine* sorted_by_duration = calloc(size, sizeof(BusLine));
    BusLine* sorted_by_name = calloc(size, sizeof(BusLine));

    if (!sorted_by_distance || !sorted_by_duration || !sorted_by_name) {
        fprintf(stderr, "Error: Memory allocation failed during testing.\n");
        free(sorted_by_distance);
        free(sorted_by_duration);
        free(sorted_by_name);
        return;
    }

    // Copy original array into each for sorting
    memcpy(sorted_by_distance, lines, size * sizeof(BusLine));
    memcpy(sorted_by_duration, lines, size * sizeof(BusLine));
    memcpy(sorted_by_name, lines, size * sizeof(BusLine));

    // Sort each array
    quick_sort(sorted_by_distance, sorted_by_distance + size, DISTANCE);
    quick_sort(sorted_by_duration, sorted_by_duration + size, DURATION);
    bubble_sort(sorted_by_name, sorted_by_name + size);

    // Tests for distance sorting
    if (is_sorted_by_distance(sorted_by_distance, sorted_by_distance + size))
        printf("TEST 1 PASSED: The array is sorted by distance\n");
    else
        printf("TEST 1 FAILED: The array is not sorted by distance\n");

    if (is_equal(sorted_by_distance, sorted_by_distance + size, lines, end))
        printf("TEST 2 PASSED: The array has the same items after sorting\n");
    else
        printf("TEST 2 FAILED: The array does not have the same items after sorting\n");

    // Tests for duration sorting
    if (is_sorted_by_duration(sorted_by_duration, sorted_by_duration + size))
        printf("TEST 3 PASSED: The array is sorted by duration\n");
    else
        printf("TEST 3 FAILED: The array is not sorted by duration\n");

    if (is_equal(sorted_by_duration, sorted_by_duration + size, lines, end))
        printf("TEST 4 PASSED: The array has the same items after sorting\n");
    else
        printf("TEST 4 FAILED: The array does not have the same items after sorting\n");

    // Tests for name sorting
    if (is_sorted_by_name(sorted_by_name, sorted_by_name + size))
        printf("TEST 5 PASSED: The array is sorted by name\n");
    else
        printf("TEST 5 FAILED: The array is not sorted by name\n");

    if (is_equal(sorted_by_name, sorted_by_name + size, lines, end))
        printf("TEST 6 PASSED: The array has the same items after sorting\n");
    else
        printf("TEST 6 FAILED: The array does not have the same items after sorting\n");

    // Free allocated memory
    free(sorted_by_distance);
    free(sorted_by_duration);
    free(sorted_by_name);
}