# How to Run — Graph Coloring Exam Scheduling

## For Windows (PowerShell)

### Step 1 — Navigate to Project Folder
```powershell
cd D:\DAA@2\graph-coloring-exam-scheduling
```

### Step 2 — Compile
```powershell
g++ -std=c++17 -O2 -Isrc src/graph.cpp src/coloring.cpp src/dataset.cpp src/display.cpp src/main.cpp -o exam_scheduler.exe
```

### Step 3 — Run
```powershell
./exam_scheduler.exe
```

---

## Interactive Menu Options

Once the program starts, you will see a menu with 9 options.

### Recommended Demo Sequence

Type these numbers one at a time:

```
1    → Find Chromatic Number (shows X = 10)
5    → Show Exam Schedule (all 10 time slots)
6    → Show Color Assignments (all 50 courses)
7    → Verify Solution (checks all 228 edges)
8    → Show Algorithm Statistics (complexity analysis)
0    → Exit
```

---

## What Each Option Does

| Option | Description | What It Shows |
|---|---|---|
| **1** | Find Chromatic Number | Tries m=2,3,4...10, finds minimum = 10 |
| **2** | Color with custom m | User enters m, algorithm tries to color |
| **3** | Show Adjacency Matrix | 50x50 matrix of conflicts |
| **4** | Show Edge List | All 228 conflict pairs |
| **5** | Show Exam Schedule | Courses grouped by time slot |
| **6** | Show Color Assignments | Table of all 50 courses |
| **7** | Verify Solution | Checks all edges, confirms valid |
| **8** | Show Statistics | Complexity, recursive calls |
| **0** | Exit | Closes the program |

---

## Testing Different Values (Option 2)

To demonstrate the algorithm rejects invalid colorings:

```
Choose option: 2
Enter m: 1     → FAILED (impossible)
Enter m: 9     → FAILED (one less than minimum)
Enter m: 10    → SUCCESS (exact minimum)
Enter m: 12    → SUCCESS (valid but not optimal)
```

---

## Expected Results

- **Chromatic Number:** 10
- **Total Courses:** 50
- **Total Conflicts:** 228
- **Recursive Calls:** 52
- **Verification:** PASS (zero violations)

---

## System Requirements

- **Compiler:** g++ with C++17 support
- **OS:** Windows, Linux, or macOS
- **RAM:** Minimal (< 10 MB)
- **Time:** < 1 second to find chromatic number

---

## Troubleshooting

**If compilation fails:**
```powershell
# Check g++ is installed
g++ --version

# If not installed, install MinGW or MSYS2
```

**If "command not found":**
```powershell
# Use full path
D:\DAA@2\graph-coloring-exam-scheduling\exam_scheduler.exe
```

---

## Contact

Student: [Your Name]  
ID: [Your Student ID]  
Course: Algorithm Design & Analysis  
University: Aksum University
