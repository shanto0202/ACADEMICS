# AVL Tree Assignment

## Files

- `AVLTree.cpp` - Ordinary AVL Tree
- `IntervalScheduler.cpp` - Interval Scheduler using AVL Tree
- `README.txt` - Basic information

## 1. AVLTree.cpp

Supported input commands:

- `I x` = insert x
- `D x` = delete x
- `F x` = find x
- `T` = inorder traversal

The program takes two command-line arguments:

```text
AVLTree input.txt output.txt
```

Example:

```text
./AVLTree testcase_avl.txt output.txt
```

The normal assignment output is written to the output file.

Timing information is printed to the terminal after all commands finish.

## 2. IntervalScheduler.cpp

Supported commands:

- `ADD start end`
- `REMOVE id`
- `UPDATE id start end`
- `CONFLICT start end`
- `OVERLAPS start end`
- `AT time`
- `NEXT time`

Example:

```text
./IntervalScheduler testcase_basic_interval.txt output.txt
```

Event IDs start from 1 and increase whenever a new event is added.

The tree is ordered by:

```text
(start, id)
```

Each node also stores `maxEnd`, which is used for faster interval queries.

Intervals are treated as:

```text
[start, end)
```

So an event is active at time `t` when:

```text
start <= t < end
```

Two intervals overlap when:

```text
start1 < end2 && start2 < end1
```

## 3. Compilation

Use C++17:

```text
g++ -std=c++17 AVLTree.cpp -o AVLTree
g++ -std=c++17 IntervalScheduler.cpp -o IntervalScheduler
```

## 4. Running

AVL:

```text
./AVLTree testcase_avl.txt output.txt
```

Interval Scheduler:

```text
./IntervalScheduler testcase_basic_interval.txt output.txt
```

The program follows the input/output command format used by the assignment test cases.

## 5. Timing

The programs measure the required operations separately.

AVL:

- insert
- delete
- find
- traverse

Interval Scheduler:

- add
- remove
- update
- conflict
- overlaps
- at
- next

Timing values depend on the computer and the particular run, so they should not be expected to be identical on different machines.
