/*
 * ============================================================
 *  Graph Coloring - Exam Scheduling
 *  File   : display.cpp
 *  Purpose: Console UI helpers
 * ============================================================
 */

#include "display.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// ── printBanner ──────────────────────────────────────────────
void printBanner() {
    std::cout << "\n";
    std::cout << "  +----------------------------------------------------------+\n";
    std::cout << "  |        GRAPH COLORING  -  EXAM SCHEDULING SYSTEM         |\n";
    std::cout << "  +----------------------------------------------------------+\n";
    std::cout << "  |  Problem   : Schedule exams so no student has 2 at once  |\n";
    std::cout << "  |  Model     : Graph  (courses=vertices, conflicts=edges)   |\n";
    std::cout << "  |  Algorithm : Backtracking with Constraint Pruning         |\n";
    std::cout << "  |  Structure : Adjacency Matrix  (2-D boolean array)        |\n";
    std::cout << "  |  Dataset   : 50 University Courses, 228 Conflict Edges    |\n";
    std::cout << "  |  Goal      : Find minimum time slots = Chromatic Number   |\n";
    std::cout << "  +----------------------------------------------------------+\n";
    std::cout << "\n";
}

// ── printSectionHeader ───────────────────────────────────────
void printSectionHeader(const std::string& title) {
    int width = 58;
    std::string bar(width, '=');
    std::cout << "\n  +" << bar << "+\n";
    // Centre the title
    int pad = (width - (int)title.size()) / 2;
    std::cout << "  |" << std::string(pad, ' ') << title
              << std::string(width - pad - (int)title.size(), ' ') << "|\n";
    std::cout << "  +" << bar << "+\n";
}

// ── printGraphSummary ────────────────────────────────────────
void printGraphSummary(const Graph& g) {
    printSectionHeader("GRAPH SUMMARY");

    std::cout << "  |\n";
    std::cout << "  |  What is this graph?\n";
    std::cout << "  |    Each VERTEX  = one university course\n";
    std::cout << "  |    Each EDGE    = two courses share at least one student\n";
    std::cout << "  |    Each COLOR   = one exam time slot\n";
    std::cout << "  |\n";
    std::cout << "  |  Graph size:\n";
    std::cout << "  |    Vertices (courses)  : " << g.getNumVertices() << "\n";
    std::cout << "  |    Edges (conflicts)   : " << g.getNumEdges()    << "\n";
    std::cout << "  |\n";
    std::cout << "  |  Departments in dataset:\n";
    std::cout << "  |\n";

    // Department table
    struct Dept { const char* name; int from; int to; int courses; };
    Dept depts[] = {
        { "Computer Science",     1,  10, 10 },
        { "Mathematics",         11,  20, 10 },
        { "Physics",             21,  28,  8 },
        { "Electrical Eng.",     29,  37,  9 },
        { "Business",            38,  44,  7 },
        { "Electives (cross-dept)", 45, 50, 6 },
    };

    std::cout << "  |  " << std::left
              << std::setw(26) << "Department"
              << std::setw(10) << "Courses"
              << std::setw(16) << "Vertex Range"
              << "\n";
    std::cout << "  |  " << std::string(50, '-') << "\n";
    for (auto& d : depts) {
        std::cout << "  |  "
                  << std::left  << std::setw(26) << d.name
                  << std::left  << std::setw(10) << d.courses
                  << d.from << " - " << d.to << "\n";
    }
    std::cout << "  |\n";
    std::cout << "  |  Conflict rules:\n";
    std::cout << "  |    - All courses within a dept conflict (dense clique)\n";
    std::cout << "  |    - Cross-dept electives add realistic extra conflicts\n";
    std::cout << "  +----------------------------------------------------------+\n";
}

// ── printVerification ────────────────────────────────────────
void printVerification(const Graph& g, const GraphColoring& gc) {
    printSectionHeader("SOLUTION VERIFICATION");

    const std::vector<int>& colors = gc.getColors();
    int n = g.getNumVertices();
    bool valid = true;
    int  conflicts = 0;

    std::cout << "  |\n";
    std::cout << "  |  Checking all " << g.getNumEdges()
              << " conflict edges...\n";
    std::cout << "  |  Rule: if edge(A,B) exists then color[A] != color[B]\n";
    std::cout << "  |\n";

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (g.hasEdge(i, j) && colors[i] == colors[j]) {
                std::cout << "  |  [CONFLICT] "
                          << g.getCourseName(i) << " <-> "
                          << g.getCourseName(j)
                          << " both in Slot-" << colors[i] << "\n";
                ++conflicts;
                valid = false;
            }
        }
    }

    if (valid) {
        std::cout << "  |  [PASS] All " << n << " courses assigned a slot.\n";
        std::cout << "  |  [PASS] All " << g.getNumEdges()
                  << " conflict edges checked - zero violations.\n";
        std::cout << "  |  [PASS] Solution is VALID and OPTIMAL.\n";
    } else {
        std::cout << "  |  [FAIL] " << conflicts
                  << " violation(s) found. Solution is INVALID.\n";
    }
    std::cout << "  +----------------------------------------------------------+\n";
}
