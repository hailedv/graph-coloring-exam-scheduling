#ifndef DATASET_H
#define DATASET_H

/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : dataset.h
 *  Purpose: Build the 50-course university dataset
 * ============================================================
 */

#include "graph.h"

// Builds and returns a Graph representing 50 university courses
// with realistic student-overlap conflicts.
Graph buildUniversityDataset();

#endif // DATASET_H
