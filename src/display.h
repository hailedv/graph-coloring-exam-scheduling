#ifndef DISPLAY_H
#define DISPLAY_H

/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : display.h
 *  Purpose: Console UI / banner helpers
 * ============================================================
 */

#include "graph.h"
#include "coloring.h"

void printBanner();
void printSectionHeader(const std::string& title);
void printGraphSummary(const Graph& g);
void printVerification(const Graph& g, const GraphColoring& gc);

#endif // DISPLAY_H
