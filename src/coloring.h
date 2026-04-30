#ifndef COLORING_H
#define COLORING_H

/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : coloring.h
 *  Purpose: Backtracking graph-coloring algorithm interface
 * ============================================================
 */

#include "graph.h"
#include <string>
#include <vector>

// ─────────────────────────────────────────────────────────────
//  GraphColoring class
//
//  Algorithm : Backtracking with constraint propagation
//  Complexity : O(m^n) worst case  (m = colors, n = vertices)
//               Pruning via isSafe() reduces actual exploration
//
//  Usage:
//    GraphColoring gc(graph);
//    int chromatic = gc.findChromaticNumber();
//    gc.colorWithM(chromatic);
//    gc.printSchedule();
// ─────────────────────────────────────────────────────────────
class GraphColoring {
public:
    explicit GraphColoring(const Graph& g);

    // Find the minimum number of colors needed (chromatic number)
    int  findChromaticNumber();

    // Try to color the graph with exactly m colors
    // Returns true if a valid coloring was found
    bool colorWithM(int m);

    // Print the exam schedule (color → time slot mapping)
    void printSchedule()          const;

    // Print detailed color assignments
    void printColorAssignments()  const;

    // Print algorithm statistics
    void printStats()             const;

    // Export current coloring as Graphviz DOT file
    bool exportDot(const std::string& filename) const;

    // Getters
    int  getColorsUsed()          const;
    int  getCallCount()           const;
    const std::vector<int>& getColors() const;

private:
    const Graph&     graph;
    int              n;
    std::vector<int> color;      // color[v] = assigned color (1-based), 0 = uncolored
    int              colorsUsed;
    long long        callCount;  // recursive calls made (for complexity demo)

    // Core backtracking function
    bool backtrack(int vertex, int m);

    // Constraint check: can we assign color c to vertex v?
    bool isSafe(int vertex, int c) const;

    // Greedy upper-bound heuristic (Welsh-Powell) for faster chromatic search
    int  greedyUpperBound() const;
};

#endif // COLORING_H
