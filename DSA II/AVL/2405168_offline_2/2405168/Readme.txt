Assignment 2: AVL Trees and Interval Scheduling

COMPILATION
-----------

AVL Tree:
g++ -std=c++17 AVLTree.cpp -o avl_tree

Interval Scheduler:
g++ -std=c++17 IntervalScheduler.cpp -o interval_scheduler


EXECUTION
---------

AVL Tree:
./avl_tree testcase_avl.txt output_avl.txt

Interval Scheduler:
./interval_scheduler testcase_basic_interval.txt output_basic_interval.txt
./interval_scheduler testcase_edge_interval.txt output_edge_interval.txt
./interval_scheduler testcase_large_interval.txt output_large_interval.txt


OUTPUT AND TIMING
-----------------

"AVL" | Set-Content timing_report.txt
.\avl_tree.exe testcase_avl.txt output_avl.txt | Add-Content timing_report.txt

"" | Add-Content timing_report.txt
"Interval Scheduler" | Add-Content timing_report.txt
.\interval_scheduler.exe testcase_large_interval.txt output_large_interval.txt | Add-Content timing_report.txt

Get-Content timing_report.txt

IMPLEMENTATION SUMMARY
----------------------

AVLTree.cpp:
- Implements AVL insertion, deletion, search, and traversal.
- Performs LL, RR, LR, and RL rotations when rebalancing is needed.
- Search, insertion, and deletion take O(log n) worst-case time.
- Traversal takes O(n) time.

IntervalScheduler.cpp:
- Implements an AVL-based interval scheduler.
- Each node stores maxEnd in addition to its height.
- Supports ADD, REMOVE, UPDATE, CONFLICT, OVERLAPS, AT, and NEXT.
- maxEnd is maintained after insertion, deletion, update, and rotation.
- OVERLAPS and AT use maxEnd-based pruning.