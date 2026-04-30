#ifndef GRAPH_H
#define GRAPH_H

/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : graph.h
 *  Purpose: Adjacency-matrix graph + backtracking coloring
 * ============================================================
 */

#include <string>
#include <vector>

// Maximum number of vertices supported
static const int MAX_VERTICES = 100;

// ─────────────────────────────────────────────────────────────
//  Graph class
//  Represents courses as vertices and student-overlap as edges.
//  Uses a 2-D boolean adjacency matrix.
// ─────────────────────────────────────────────────────────────
class Graph {
public:
    // ── Construction ─────────────────────────────────────────
    explicit Graph(int numVertices);

    // ── Mutators ─────────────────────────────────────────────
    void addEdge(int u, int v);
    void setCourseName(int vertex, const std::string& name);

    // ── Accessors ────────────────────────────────────────────
    int  getNumVertices()                    const;
    int  getNumEdges()                       const;
    bool hasEdge(int u, int v)               const;
    const std::string& getCourseName(int v)  const;

    // ── Display ──────────────────────────────────────────────
    void printAdjacencyMatrix()              const;
    void printEdgeList()                     const;

private:
    int  n;                          // number of vertices
    int  edgeCount;
    bool adj[MAX_VERTICES][MAX_VERTICES];
    std::string courseNames[MAX_VERTICES];
};

#endif // GRAPH_H
