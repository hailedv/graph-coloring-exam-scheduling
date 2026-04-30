/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : coloring.cpp
 *  Purpose: Backtracking graph-coloring implementation
 * ============================================================
 */

#include "coloring.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

// ── Constructor ──────────────────────────────────────────────
GraphColoring::GraphColoring(const Graph& g)
    : graph(g), n(g.getNumVertices()),
      color(g.getNumVertices(), 0),
      colorsUsed(0), callCount(0) {}

// ── isSafe ───────────────────────────────────────────────────
// Returns true if assigning color c to 'vertex' violates no
// adjacency constraint (no neighbour already has color c).
bool GraphColoring::isSafe(int vertex, int c) const {
    for (int i = 0; i < n; ++i)
        if (graph.hasEdge(vertex, i) && color[i] == c)
            return false;
    return true;
}

// ── backtrack ────────────────────────────────────────────────
// Recursively assigns colors to vertices 0..n-1.
// Returns true when a complete valid coloring is found.
bool GraphColoring::backtrack(int vertex, int m) {
    ++callCount;

    // Base case: all vertices colored successfully
    if (vertex == n) return true;

    // Try each color 1..m
    for (int c = 1; c <= m; ++c) {
        if (isSafe(vertex, c)) {
            color[vertex] = c;

            if (backtrack(vertex + 1, m))
                return true;

            // Backtrack
            color[vertex] = 0;
        }
    }
    return false;   // No valid color found → trigger backtrack
}

// ── greedyUpperBound ─────────────────────────────────────────
// Welsh-Powell greedy coloring: sort vertices by degree (desc),
// assign the smallest available color. Gives a fast upper bound
// so the chromatic-number search starts close to the answer.
int GraphColoring::greedyUpperBound() const {
    // Compute degrees
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        int da = 0, db = 0;
        for (int i = 0; i < n; ++i) {
            da += graph.hasEdge(a, i) ? 1 : 0;
            db += graph.hasEdge(b, i) ? 1 : 0;
        }
        return da > db;
    });

    std::vector<int> tempColor(n, 0);
    int maxColor = 0;

    for (int idx = 0; idx < n; ++idx) {
        int v = order[idx];
        // Find smallest color not used by neighbours
        std::vector<bool> used(n + 2, false);
        for (int i = 0; i < n; ++i)
            if (graph.hasEdge(v, i) && tempColor[i] > 0)
                used[tempColor[i]] = true;

        int c = 1;
        while (used[c]) ++c;
        tempColor[v] = c;
        maxColor = std::max(maxColor, c);
    }
    return maxColor;
}

// ── findChromaticNumber ──────────────────────────────────────
// Searches for the minimum m such that colorWithM(m) succeeds.
// Starts from a lower bound (max clique lower bound ≈ max degree
// of any vertex + 1 is too loose; we use 1) up to the greedy
// upper bound.
int GraphColoring::findChromaticNumber() {
    callCount = 0;

    int upper = greedyUpperBound();

    // Lower bound: at least 1 color; at least 2 if any edge exists
    int lower = (graph.getNumEdges() > 0) ? 2 : 1;

    int chromatic = upper;

    std::cout << "\n  [Chromatic Search] Greedy upper bound = "
              << upper << " colors\n";
    std::cout << "  [Chromatic Search] Trying m = ";

    for (int m = lower; m <= upper; ++m) {
        std::cout << m << " ... " << std::flush;

        // Reset colors
        std::fill(color.begin(), color.end(), 0);
        callCount = 0;

        if (backtrack(0, m)) {
            chromatic  = m;
            colorsUsed = m;
            std::cout << "SUCCESS\n";
            break;
        }
        std::cout << "fail  ";
    }
    return chromatic;
}

// ── colorWithM ───────────────────────────────────────────────
bool GraphColoring::colorWithM(int m) {
    std::fill(color.begin(), color.end(), 0);
    callCount  = 0;
    colorsUsed = 0;

    bool result = backtrack(0, m);
    if (result) colorsUsed = m;
    return result;
}

// ── printColorAssignments ────────────────────────────────────
void GraphColoring::printColorAssignments() const {
    // Column widths
    const int W_NO   = 5;
    const int W_NAME = 32;
    const int W_SLOT = 12;
    const int W_CLR  = 8;
    const int TOTAL  = W_NO + W_NAME + W_SLOT + W_CLR + 4; // 4 = separators

    std::string bar(TOTAL, '-');

    std::cout << "\n  +" << bar << "+\n";
    std::cout <<   "  |" << std::setw((TOTAL + 34) / 2) << std::left
              << "  COLOR ASSIGNMENTS (per course)" << std::setw(TOTAL - 30)
              << " " << "|\n";
    std::cout << "  +" << bar << "+\n";

    // Header row
    std::cout << "  | "
              << std::left << std::setw(W_NO)   << "No."  << " | "
              << std::left << std::setw(W_NAME)  << "Course Name" << " | "
              << std::left << std::setw(W_SLOT)  << "Time Slot"   << " | "
              << std::left << std::setw(W_CLR)   << "Color"       << "|\n";
    std::cout << "  +" << bar << "+\n";

    for (int i = 0; i < n; ++i) {
        // Truncate name if too long
        std::string name = graph.getCourseName(i);
        if ((int)name.size() > W_NAME)
            name = name.substr(0, W_NAME - 2) + "..";

        std::string slot = "Slot-" + std::to_string(color[i]);
        std::string clr  = "Color-" + std::to_string(color[i]);

        std::cout << "  | "
                  << std::left << std::setw(W_NO)   << (i + 1) << " | "
                  << std::left << std::setw(W_NAME)  << name    << " | "
                  << std::left << std::setw(W_SLOT)  << slot    << " | "
                  << std::left << std::setw(W_CLR)   << clr     << "|\n";
    }
    std::cout << "  +" << bar << "+\n";
}

// ── printSchedule ────────────────────────────────────────────
void GraphColoring::printSchedule() const {
    std::string bar(54, '=');
    std::cout << "\n  +" << bar << "+\n";
    std::cout <<   "  |          FINAL EXAM SCHEDULE                         |\n";
    std::cout <<   "  |  (Each slot = one exam period, no student conflict)  |\n";
    std::cout <<   "  +" << bar << "+\n";

    for (int slot = 1; slot <= colorsUsed; ++slot) {
        // Count courses in this slot
        int count = 0;
        for (int i = 0; i < n; ++i)
            if (color[i] == slot) ++count;

        std::cout << "\n  +-- TIME SLOT " << std::setw(2) << slot
                  << " (" << count << " exam(s)) "
                  << std::string(34, '-') << "+\n";

        for (int i = 0; i < n; ++i)
            if (color[i] == slot)
                std::cout << "  |  [" << std::setw(2) << (i+1) << "]  "
                          << std::left << std::setw(40)
                          << graph.getCourseName(i) << "|\n";
    }
    std::cout << "  +" << bar << "+\n";
}

// ── printStats ───────────────────────────────────────────────
void GraphColoring::printStats() const {
    std::string bar(50, '-');
    std::cout << "\n  +" << bar << "+\n";
    std::cout <<   "  |           ALGORITHM STATISTICS                   |\n";
    std::cout <<   "  +" << bar << "+\n";
    std::cout << "  |  Graph                                            |\n";
    std::cout << "  |    Vertices (courses)   : " << std::left
              << std::setw(24) << n                   << "|\n";
    std::cout << "  |    Edges (conflicts)    : " << std::left
              << std::setw(24) << graph.getNumEdges() << "|\n";
    std::cout << "  +" << bar << "+\n";
    std::cout << "  |  Result                                           |\n";
    std::cout << "  |    Chromatic number (X) : " << std::left
              << std::setw(24) << colorsUsed          << "|\n";
    std::cout << "  |    Meaning              : " << std::left
              << std::setw(24) << (std::to_string(colorsUsed) + " time slots needed")
              << "|\n";
    std::cout << "  +" << bar << "+\n";
    std::cout << "  |  Backtracking Performance                         |\n";
    std::cout << "  |    Recursive calls made : " << std::left
              << std::setw(24) << callCount           << "|\n";
    std::cout << "  |    Worst-case (theory)  : " << std::left
              << std::setw(24) << "O(m^n)"           << "|\n";
    std::cout << "  |    Actual O(m^n) value  : O(" << colorsUsed
              << "^" << n << ")                  |\n";
    std::cout << "  |    Pruning saved calls  : enormous (see above)   |\n";
    std::cout << "  +" << bar << "+\n";
    std::cout << "  |  Real-World Meaning                               |\n";
    std::cout << "  |    Only " << std::left << std::setw(2) << colorsUsed
              << " exam periods needed for " << std::setw(2) << n
              << " courses.        |\n";
    std::cout << "  |    No student has 2 exams at the same time.      |\n";
    std::cout << "  +" << bar << "+\n";
}

// ── getters ──────────────────────────────────────────────────
int  GraphColoring::getColorsUsed()          const { return colorsUsed; }
int  GraphColoring::getCallCount()           const { return (int)callCount; }
const std::vector<int>& GraphColoring::getColors() const { return color; }
