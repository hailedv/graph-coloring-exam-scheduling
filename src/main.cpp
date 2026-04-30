/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : main.cpp
 *  Author : Haile DV
 *  University : Aksum University, Ethiopia
 *  Course : Algorithm Design & Analysis
 *
 *  Problem:
 *    Schedule university final exams so that no student sits
 *    two exams simultaneously.  Courses with shared students
 *    must be placed in different time slots.
 *
 *  Modelling:
 *    Vertices  = courses (50)
 *    Edges     = student-overlap conflicts
 *    Colors    = time slots
 *    Goal      = minimum colors (chromatic number χ)
 *
 *  Algorithm:
 *    Backtracking with constraint pruning (isSafe check).
 *    Greedy Welsh-Powell heuristic provides an upper bound
 *    so the chromatic search converges quickly.
 *
 *  Complexity: O(m^n) worst case; pruning reduces exploration.
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

#include "graph.h"
#include "coloring.h"
#include "dataset.h"
#include "display.h"

// ── Interactive menu ─────────────────────────────────────────
static void showMenu() {
    std::cout << "\n";
    std::cout << "  +-------------------------------------------+\n";
    std::cout << "  |               MAIN MENU                   |\n";
    std::cout << "  +-------------------------------------------+\n";
    std::cout << "  |  [1]  Find Chromatic Number (auto)        |\n";
    std::cout << "  |  [2]  Color with custom m colors          |\n";
    std::cout << "  |  [3]  Show Adjacency Matrix               |\n";
    std::cout << "  |  [4]  Show Edge List (conflict pairs)     |\n";
    std::cout << "  |  [5]  Show Exam Schedule (by time slot)   |\n";
    std::cout << "  |  [6]  Show Color Assignments (per course) |\n";
    std::cout << "  |  [7]  Verify Solution                     |\n";
    std::cout << "  |  [8]  Show Algorithm Statistics           |\n";
    std::cout << "  |  [0]  Exit                                |\n";
    std::cout << "  +-------------------------------------------+\n";
    std::cout << "  Choice: ";
}

// ── main ─────────────────────────────────────────────────────
int main() {
    printBanner();

    // Build the 50-course dataset
    Graph g = buildUniversityDataset();
    printGraphSummary(g);

    GraphColoring gc(g);
    bool hasSolution = false;

    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;

        // Guard against bad input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {

        case 1: {
            printSectionHeader("FINDING CHROMATIC NUMBER");
            int chi = gc.findChromaticNumber();
            std::cout << "\n";
            std::cout << "  +------------------------------------------+\n";
            std::cout << "  |  RESULT: Chromatic Number X = " << std::left
                      << std::setw(12) << chi << "|\n";
            std::cout << "  |  Meaning: Need exactly " << chi
                      << " exam time slots.  |\n";
            std::cout << "  |  No student will have 2 exams at once.   |\n";
            std::cout << "  +------------------------------------------+\n";
            hasSolution = true;
            break;
        }

        case 2: {
            int m;
            std::cout << "  Enter number of colors (time slots) m: ";
            std::cin >> m;
            if (m < 1) { std::cout << "  m must be ≥ 1.\n"; break; }

            printSectionHeader("COLORING WITH m = " + std::to_string(m));
            if (gc.colorWithM(m)) {
                std::cout << "\n  [SUCCESS] Valid coloring found with " << m << " colors.\n";
                std::cout << "  Use option [5] to see the schedule.\n";
                hasSolution = true;
            } else {
                std::cout << "\n  [FAILED]  No valid coloring exists with only " << m << " colors.\n";
                std::cout << "  The graph needs more colors (time slots).\n";
                std::cout << "  Try option [1] to find the minimum automatically.\n";
                hasSolution = false;
            }
            break;
        }

        case 3:
            printSectionHeader("ADJACENCY MATRIX");
            g.printAdjacencyMatrix();
            break;

        case 4:
            printSectionHeader("EDGE LIST");
            g.printEdgeList();
            break;

        case 5:
            if (!hasSolution) {
                std::cout << "  No solution yet. Run option 1 or 2 first.\n";
            } else {
                gc.printSchedule();
            }
            break;

        case 6:
            if (!hasSolution) {
                std::cout << "  No solution yet. Run option 1 or 2 first.\n";
            } else {
                gc.printColorAssignments();
            }
            break;

        case 7:
            if (!hasSolution) {
                std::cout << "  No solution yet. Run option 1 or 2 first.\n";
            } else {
                printVerification(g, gc);
            }
            break;

        case 8:
            gc.printStats();
            break;

        case 0:
            std::cout << "\n  Goodbye!\n\n";
            break;

        default:
            std::cout << "  Unknown option. Try again.\n";
        }
    }

    return 0;
}
