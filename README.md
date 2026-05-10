# Array, Linked List, and Binary Tree

Benchmarks comparing Array, SortedArray, LinkedList, and BST across common operations.

## Requirements

- C++23 compiler (`g++`)
- Python 3

## Build

```bash
make
```

## Run benchmark and generate graph

```bash
make graph
```

Runs benchmarks across multiple values of N, writes `results.csv`, and saves `results.png`.

## Other targets

```bash
make run        # build and run once (single N=varies output to results.csv)
make benchmark  # run benchmark only
make venv       # set up Python venv only
make clean      # remove binary, results.csv, results.png
```
