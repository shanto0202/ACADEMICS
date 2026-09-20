CSE 208 Offline 4 - Binomial Heap

Files:
1. offline_heap.cpp
2. README.txt

This single cpp file contains both Part A and Part B.
No separate header file is needed.

Compile:
g++ -std=c++17 offline_heap.cpp -o offline_heap

Run:
Keep input.txt in the same folder, then run:
./offline_heap

The program writes every output line to both:
1. console
2. output.txt

Part A commands:
I h x       Insert x into heap h
F h         Find minimum
E h         Extract minimum
D h x y     Decrease key x to y
R h x       Remove key x
U h1 h2     Union Hh2 into Hh1 and empty Hh2
P h         Print in the required checking format

Part B extra commands:
V h         Visualize heap h with actual parent-child relationships
VU h1 h2    Visualize Hh1 and Hh2 before union, show every link step,
            perform the union, then visualize the final Hh1

Extra structural feature in visualization:
- Shows heap size in binary form. The 1-bits indicate which Binomial Trees
  are present. Example: size 5 = binary 101, so B0 and B2 are present.
- Each displayed node also shows its degree.

Example Part B input:
I 1 20
I 1 5
I 1 30
I 2 12
I 2 7
V 1
VU 1 2

Note:
Use U for normal Part A union because U produces no output.
Use V and VU only when manually demonstrating Part B.
