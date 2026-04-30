/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : graph.cpp
 *  Purpose: Graph class implementation
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <iomanip>

// ── Constructor ──────────────────────────────────────────────
Graph::Graph(int numVertices) : n(numVertices), edgeCount(0) {
    // Zero-initialise adjacency matrix
    for (int i = 0; i < MAX_VERTICES; ++i)
        for (int j = 0; j < MAX_VERTICES; ++j)
            adj[i][j] = false;

    // Default course names
    for (int i = 0; i < n; ++i)
        courseNames[i] = "Course_" + std::to_string(i + 1);
}

// ── addEdge ──────────────────────────────────────────────────
void Graph::addEdge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n || u == v) return;
    if (!adj[u][v]) {
        adj[u][v] = adj[v][u] = true;
        ++edgeCount;
    }
}

// ── setCourseName ────────────────────────────────────────────
void Graph::setCourseName(int vertex, const std::string& name) {
    if (vertex >= 0 && vertex < n)
        courseNames[vertex] = name;
}

// ── Accessors ────────────────────────────────────────────────
int Graph::getNumVertices() const { return n; }
int Graph::getNumEdges()    const { return edgeCount; }

bool Graph::hasEdge(int u, int v) const {
    if (u < 0 || u >= n || v < 0 || v >= n) return false;
    return adj[u][v];
}

const std::string& Graph::getCourseName(int v) const {
    return courseNames[v];
}

// ── printAdjacencyMatrix ─────────────────────────────────────
void Graph::printAdjacencyMatrix() const {
    std::cout << "\n  Adjacency Matrix (" << n << " x " << n << "):\n";
    std::cout << "     ";
    for (int j = 0; j < n; ++j)
        std::cout << std::setw(3) << (j + 1);
    std::cout << "\n     ";
    for (int j = 0; j < n; ++j) std::cout << "---";
    std::cout << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(3) << (i + 1) << " |";
        for (int j = 0; j < n; ++j)
            std::cout << std::setw(3) << (adj[i][j] ? 1 : 0);
        std::cout << "\n";
    }
}

// ── printEdgeList ────────────────────────────────────────────
void Graph::printEdgeList() const {
    std::cout << "\n  Edge List (student-overlap conflicts):\n";
    int count = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (adj[i][j]) {
                std::cout << "    " << courseNames[i]
                          << "  <-->  " << courseNames[j] << "\n";
                ++count;
            }
    std::cout << "  Total edges: " << count << "\n";
}
