#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
#include <assert.h>
#include <stdio.h>

#include "sort_bus_lines.h"

/**
 * TODO add documentation
 */
int is_sorted_by_distance (const BusLine *start, const BusLine *end);

/**
 * TODO add documentation
 */
int is_sorted_by_duration (const BusLine *start, const BusLine *end);

/**
 * TODO add documentation
 */
int is_sorted_by_name (const BusLine *start, const BusLine *end);

/**
 * TODO add documentation
 */
void run_test();
int is_equal (const BusLine *start_sorted,
              const BusLine *end_sorted,
              const BusLine *start_original,
              const BusLine *end_original);
#endif //EX2_REPO_TESTBUSLINES_H
