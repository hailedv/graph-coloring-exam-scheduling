/*
 * ============================================================
 *  Graph Coloring – Exam Scheduling
 *  File   : dataset.cpp
 *  Purpose: 50-course university dataset with student overlaps
 *
 *  Design rationale
 *  ─────────────────
 *  Courses are grouped into 6 academic departments.
 *  Within a department, courses share many students → dense
 *  intra-department edges.
 *  Cross-department electives create sparser inter-department
 *  edges, producing a realistic conflict graph.
 * ============================================================
 */

#include "dataset.h"
#include <vector>
#include <string>

Graph buildUniversityDataset() {
    // ── 50 courses ───────────────────────────────────────────
    const int N = 50;
    Graph g(N);

    // Course names (index 0-based)
    const std::string names[N] = {
        // CS Department  (0-9)
        "CS101-Intro_Programming",   "CS201-Data_Structures",
        "CS301-Algorithms",          "CS302-OS",
        "CS401-Compilers",           "CS402-Networks",
        "CS403-AI",                  "CS404-ML",
        "CS405-Database",            "CS406-Security",

        // Math Department (10-19)
        "MATH101-Calculus_I",        "MATH102-Calculus_II",
        "MATH201-Linear_Algebra",    "MATH202-Discrete_Math",
        "MATH301-Probability",       "MATH302-Statistics",
        "MATH401-Numerical_Methods", "MATH402-Graph_Theory",
        "MATH403-Optimization",      "MATH404-Cryptography",

        // Physics Department (20-27)
        "PHY101-Mechanics",          "PHY102-Electromagnetism",
        "PHY201-Thermodynamics",     "PHY202-Quantum_Mechanics",
        "PHY301-Optics",             "PHY302-Relativity",
        "PHY401-Particle_Physics",   "PHY402-Astrophysics",

        // EE Department (28-36)
        "EE101-Circuit_Theory",      "EE201-Electronics",
        "EE202-Digital_Logic",       "EE301-Signal_Processing",
        "EE302-Control_Systems",     "EE401-VLSI",
        "EE402-Embedded_Systems",    "EE403-Power_Systems",
        "EE404-Communications",

        // Business Department (37-43)
        "BUS101-Accounting",         "BUS102-Economics",
        "BUS201-Finance",            "BUS202-Marketing",
        "BUS301-Management",         "BUS302-Operations",
        "BUS401-Strategy",

        // Interdisciplinary / Electives (44-49)
        "ELEC-Data_Science",         "ELEC-Robotics",
        "ELEC-Cybersecurity",        "ELEC-Bioinformatics",
        "ELEC-Game_Theory",          "ELEC-Quantum_Computing"
    };

    for (int i = 0; i < N; ++i)
        g.setCourseName(i, names[i]);

    // ── Helper: add all edges within a department group ──────
    auto addGroupEdges = [&](const std::vector<int>& group) {
        for (int i = 0; i < (int)group.size(); ++i)
            for (int j = i + 1; j < (int)group.size(); ++j)
                g.addEdge(group[i], group[j]);
    };

    // ── Intra-department conflicts ───────────────────────────
    // CS: all 10 courses share a large student pool
    addGroupEdges({0,1,2,3,4,5,6,7,8,9});

    // Math: all 10 courses
    addGroupEdges({10,11,12,13,14,15,16,17,18,19});

    // Physics: 8 courses
    addGroupEdges({20,21,22,23,24,25,26,27});

    // EE: 9 courses
    addGroupEdges({28,29,30,31,32,33,34,35,36});

    // Business: 7 courses
    addGroupEdges({37,38,39,40,41,42,43});

    // ── Inter-department conflicts (shared elective students) ─

    // CS ↔ Math (algorithms, discrete math, numerical methods)
    g.addEdge(2,  13);   // Algorithms ↔ Discrete Math
    g.addEdge(2,  17);   // Algorithms ↔ Graph Theory
    g.addEdge(7,  14);   // ML         ↔ Probability
    g.addEdge(7,  15);   // ML         ↔ Statistics
    g.addEdge(7,  18);   // ML         ↔ Optimization
    g.addEdge(8,  15);   // Database   ↔ Statistics
    g.addEdge(9,  19);   // Security   ↔ Cryptography
    g.addEdge(6,  14);   // AI         ↔ Probability
    g.addEdge(16, 2);    // Numerical  ↔ Algorithms

    // CS ↔ EE (digital systems, networks, embedded)
    g.addEdge(3,  30);   // OS         ↔ Digital Logic
    g.addEdge(5,  36);   // Networks   ↔ Communications
    g.addEdge(5,  31);   // Networks   ↔ Signal Processing
    g.addEdge(4,  33);   // Compilers  ↔ VLSI
    g.addEdge(4,  34);   // Compilers  ↔ Embedded Systems

    // Math ↔ Physics
    g.addEdge(10, 20);   // Calculus I  ↔ Mechanics
    g.addEdge(11, 21);   // Calculus II ↔ Electromagnetism
    g.addEdge(12, 22);   // Lin Algebra ↔ Thermodynamics
    g.addEdge(14, 23);   // Probability ↔ Quantum Mechanics
    g.addEdge(16, 24);   // Numerical   ↔ Optics

    // Math ↔ EE
    g.addEdge(12, 31);   // Lin Algebra ↔ Signal Processing
    g.addEdge(18, 32);   // Optimization↔ Control Systems
    g.addEdge(15, 31);   // Statistics  ↔ Signal Processing

    // Physics ↔ EE
    g.addEdge(21, 28);   // Electromag  ↔ Circuit Theory
    g.addEdge(22, 35);   // Thermodynamics↔ Power Systems
    g.addEdge(23, 31);   // Quantum     ↔ Signal Processing

    // CS ↔ Business
    g.addEdge(8,  37);   // Database    ↔ Accounting
    g.addEdge(7,  39);   // ML          ↔ Finance
    g.addEdge(6,  41);   // AI          ↔ Management

    // Math ↔ Business
    g.addEdge(15, 38);   // Statistics  ↔ Economics
    g.addEdge(18, 42);   // Optimization↔ Operations
    g.addEdge(19, 39);   // Cryptography↔ Finance

    // ── Elective conflicts ───────────────────────────────────
    // Data Science (44) – CS + Math + Stats
    g.addEdge(44, 7);    // Data Science ↔ ML
    g.addEdge(44, 8);    // Data Science ↔ Database
    g.addEdge(44, 15);   // Data Science ↔ Statistics
    g.addEdge(44, 18);   // Data Science ↔ Optimization

    // Robotics (45) – CS + EE + Physics
    g.addEdge(45, 6);    // Robotics ↔ AI
    g.addEdge(45, 32);   // Robotics ↔ Control Systems
    g.addEdge(45, 34);   // Robotics ↔ Embedded Systems
    g.addEdge(45, 20);   // Robotics ↔ Mechanics

    // Cybersecurity (46) – CS + Math
    g.addEdge(46, 9);    // Cybersecurity ↔ Security
    g.addEdge(46, 19);   // Cybersecurity ↔ Cryptography
    g.addEdge(46, 5);    // Cybersecurity ↔ Networks

    // Bioinformatics (47) – CS + Math + Physics
    g.addEdge(47, 7);    // Bioinformatics ↔ ML
    g.addEdge(47, 14);   // Bioinformatics ↔ Probability
    g.addEdge(47, 15);   // Bioinformatics ↔ Statistics

    // Game Theory (48) – Math + Business
    g.addEdge(48, 17);   // Game Theory ↔ Graph Theory
    g.addEdge(48, 14);   // Game Theory ↔ Probability
    g.addEdge(48, 38);   // Game Theory ↔ Economics
    g.addEdge(48, 43);   // Game Theory ↔ Strategy

    // Quantum Computing (49) – CS + Math + Physics
    g.addEdge(49, 6);    // Quantum Comp ↔ AI
    g.addEdge(49, 19);   // Quantum Comp ↔ Cryptography
    g.addEdge(49, 23);   // Quantum Comp ↔ Quantum Mechanics
    g.addEdge(49, 9);    // Quantum Comp ↔ Security

    return g;
}
