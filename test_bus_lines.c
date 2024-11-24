#include "test_bus_lines.h"
#include "sort_bus_lines.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

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
        if (current->name > (current + 1)->name)
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
    for (const BusLine* current = start_sorted;
        current < end_sorted; current++){
        int found_flag = 0;
        for (const BusLine* current_original = start_original;
            current_original < end_original; current_original++)
        {
            if (current->distance == current_original->distance &&
                strcmp(current->name, current_original->name) == 0 &&
                is_sorted_by_duration(current, current_original))
            {
                found_flag = 1;
            }
        }
        if (!found_flag)
        {
            return 0;
        }
    }
    return 1;
}

void run_test()
{
    BusLine lines[] = {
        {"c3", 5.0, 30}, {"a1", 10.0, 15},
        {"b2", 20.0, 10}
    };
    BusLine sorted_by_distance[] = {
        {"c3", 5.0, 30}, {
            "a1", 10.0,
            15
        },
        {"b2", 20.0, 10}
    };
    BusLine sorted_by_duration[] = {
        {"b2", 20.0, 10}, {
            "a1", 10.0,
            15
        },
        {"c3", 5.0, 30}
    };
    BusLine sorted_by_name[] = {
        {"a1", 10.0, 15}, {
            "b2", 20.0,
            10
        },
        {"c3", 5.0, 30}
    };
    assert(is_sorted_by_distance(sorted_by_distance, sorted_by_distance + 3));
    assert(is_sorted_by_duration(sorted_by_duration, sorted_by_duration + 3));
    assert(is_sorted_by_name(sorted_by_name, sorted_by_name + 3));

    assert(!is_sorted_by_distance(lines, lines + 3));
    assert(!is_sorted_by_duration(lines, lines + 3));
    assert(!is_sorted_by_name(lines, lines + 3));

    printf("All tests passed successfully!\n");
}
