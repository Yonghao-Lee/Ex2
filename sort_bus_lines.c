#include "sort_bus_lines.h"
#include <stdbool.h>

void swap(BusLine *a, BusLine *b) {
    BusLine temp = *a;
    *a = *b;
    *b = temp;
}

BusLine *partition(BusLine *start, BusLine *end, SortType sort_type) {
    BusLine *pivot = end - 1; // Last element as pivot
    BusLine *i = start - 1;   // Pointer to smaller element

    for (BusLine *j = start; j < end - 1; j++) { // Iterate until the pivot
        bool condition = false;
        if (sort_type == DISTANCE) {
            condition = (j->distance < pivot->distance);
        } else if (sort_type == DURATION) {
            condition = (j->duration < pivot->duration);
        }

        if (condition) {
            i++;
            swap(i, j);
        }
    }

    // Place pivot in its correct position
    swap(i + 1, pivot);
    return i + 1;
}

void quick_sort(BusLine *start, BusLine *end, SortType sort_type) {
    if (start < end - 1) { // Ensure there are at least two elements
        BusLine *pivot = partition(start, end, sort_type);
        quick_sort(start, pivot, sort_type);    // Sort left of pivot
        quick_sort(pivot + 1, end, sort_type); // Sort right of pivot
    }
}
void bubble_sort(BusLine *start, BusLine *end) {
    BusLine *i, *j;
    bool swapped = false;
    for (i = start; i < end - 1; i++) {
        swapped = false;
        for (j = start; j < end - 1 - (i - start); j++) {
            if (strcmp(j->name, (j + 1)->name) > 0) {
                swap(j, j + 1);
                swapped = true;
            }
        }
        if (!swapped) {
            break; // Stop early if no swaps
        }
    }
}