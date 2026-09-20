README - Binomial Heap Assignment Student ID: 2405168
1. Compilation Instruction

Compile the program using g++ compiler:

g++ 2405168.cpp -o 2405168

2. Running Instruction

Run the executable:

./2405168

The program takes commands from input.txt and generates output.txt
automatically.
3. input.txt and output.txt
Usage

input.txt: - Contains the sequence of Binomial Heap commands. - Each
command should be written in a separate line.

output.txt: - The program writes all operation results into this file. -
It is generated automatically after execution.

4. Heap Visualization Command

Command format:

V h

where h is the heap number.

Example:

V 1

This displays the structure of heap H1 including: - Binomial tree
hierarchy - Node keys - Degree of each node - Minimum node information

5. Visualized Union Command

Command format:

W h1 h2

where h1 and h2 are two heap numbers.

Example:

W 1 2

This performs union of heap H1 and H2 and displays the resulting
binomial heap structure.

6. Extra Visualization Feature

Additional visualization features implemented:

-   Displays the degree of every node.
-   Marks the minimum node clearly.
-   Shows the hierarchical structure of binomial trees during
    visualization.
-   Helps to understand the shape and properties of the binomial heap
    after operations.

Implemented Operations

The program supports:

1.  Insert
2.  Find Minimum
3.  Extract Minimum
4.  Union of Binomial Heaps
5.  Decrease Key
6.  Delete Key
7.  Heap Visualization