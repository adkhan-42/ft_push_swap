_This project has been created as part of the 42 curriculum by adkhan._

# push_swap

A 42 School project that sorts a stack of integers using a limited set of operations, outputting the sequence of moves to `stdout`. This implementation uses the **Turk Sort** algorithm — a cost-optimized strategy that minimizes total operations by calculating the cheapest element to move at each step.

---

## Table of Contents

- [Data Structure](#data-structure)
- [Core Algorithm — Turk Sort](#core-algorithm--turk-sort)
- [File-by-File Function Reference](#file-by-file-function-reference)
- [Allowed Operations](#allowed-operations)
- [Recommendations for Improvement](#recommendations-for-improvement)

---

## Data Structure

The program uses a **doubly-linked list** to represent each stack. Each node (`t_stack`) contains:

| Field        | Type       | Purpose                                                                 |
|--------------|------------|-------------------------------------------------------------------------|
| `value`      | `int`      | The original integer value                                              |
| `index`      | `int`      | Rank (0-indexed position in the sorted order). Used instead of raw values for comparisons |
| `pos`        | `int`      | Current position in the stack (0 = top). Recalculated before each move  |
| `target_pos` | `int`      | The position in stack A where this node should be inserted              |
| `cost_a`     | `int`      | Number of rotations needed on A. Negative = reverse rotate              |
| `cost_b`     | `int`      | Number of rotations needed on B. Negative = reverse rotate              |
| `next`       | `t_stack*` | Pointer to the next node                                                |
| `prev`       | `t_stack*` | Pointer to the previous node                                           |

---

## Core Algorithm — Turk Sort

The algorithm works in 4 phases:

### Phase 1 — Push to B (`push_init`)
Push roughly half the elements from A to B. Elements with index ≤ median are pushed first for a rough split, then the remainder (except the last 3) are pushed unconditionally. This leaves exactly **3 elements in A**.

### Phase 2 — Sort the 3 (`sort_three`)
Sort the remaining 3 elements in A using at most 2 operations by comparing their ranks.

### Phase 3 — Cost-Optimized Insertions (the "Turk" loop)
While B is not empty, repeat:
1. **`set_current_pos`** — Assign each node its current position index in both stacks.
2. **`set_target_pos`** — For each node in B, find its optimal insertion point in A (the smallest element in A whose rank is greater than B's rank; wraps around to the minimum if none exists).
3. **`get_cost`** — Calculate the cost to bring each B node to the top of B and its target position to the top of A. Positive cost = `ra`/`rb`, negative = `rra`/`rrb`.
4. **`get_cheapest_cost`** — Select the B node with the lowest combined cost, accounting for overlapping rotations (`rr`/`rrr`).
5. **`optimize` + `do_move`** — Execute the move using combined rotations where possible, then `pa`.

### Phase 4 — Final Rotation (`min_on_top`)
Rotate A so the smallest element is on top, completing the sort.

---

## File-by-File Function Reference

### `main.c`

| Function | Description |
|----------|-------------|
| `push_swap(t_stack **a, t_stack **b)` | Entry point for sorting. Dispatches to `sa` (2 elements), `sort_three` (3 elements), or `sort` (4+ elements). |
| `main(int ac, char **av)` | Parses arguments, initializes stack A, checks if already sorted, calls `push_swap`, and frees memory. |

---

### `init_stack_a.c`

| Function | Description |
|----------|-------------|
| `copy_array(int *source, int size)` | *(static)* Allocates and returns a copy of an integer array. Used to create a sortable copy for ranking. |
| `get_rank(int *sorted_arr, int target, int size)` | *(static)* Returns the index (rank) of `target` in the sorted array. This converts raw values to 0-indexed ranks. |
| `get_input_data(int ac, char **av, int *size)` | *(static)* Parses command-line arguments into a raw integer array and sets the total count via `size`. |
| `create_sorted_check(int *raw, int size)` | *(static)* Copies the raw array, sorts it, and checks for duplicates. Returns `NULL` if duplicates are found. |
| `init_stack_a(t_stack **a, int ac, char **av)` | Orchestrates initialization: parses input → validates → ranks each number → builds the linked list for stack A. Each node stores both the raw `value` and its `index` (rank). |

---

### `sort.c`

| Function | Description |
|----------|-------------|
| `push_init(t_stack **a, t_stack **b)` | Pushes elements from A to B in two phases: first the lower-ranked half (index ≤ median), then remaining elements until only 3 are left in A. |
| `get_min_node(t_stack *stack)` | Returns a pointer to the node with the smallest `value` in the stack. |
| `move_to_top(t_stack **stack, t_stack *target_node, char stack_name)` | Rotates or reverse-rotates a stack until `target_node` is on top. Chooses direction based on whether the node is in the first or second half. |
| `min_on_top(t_stack **a)` | Moves the minimum-value node to the top of A. Used as the final step to complete the sort. |
| `init_nodes(t_stack *a, t_stack *b)` | Recalculates all metadata for the current state: positions, target positions, and costs. Called before every move. |

---

### `sort_tiny.c`

| Function | Description |
|----------|-------------|
| `sort(t_stack **a, t_stack **b)` | Main sort driver for 4+ elements. Calls `push_init`, `sort_three`, then repeatedly calls `init_nodes` + `do_move` until B is empty, and finishes with `min_on_top`. |
| `sort_three(t_stack **a)` | Sorts exactly 3 elements using at most 2 operations (`ra`/`rra` + optional `sa`) by comparing rank values. |

---

### `turk_utils.c`

| Function | Description |
|----------|-------------|
| `set_current_pos(t_stack *stack)` | Walks the stack and assigns each node its position (0 = top). Must be called before cost calculations. |
| `get_min_index_pos(t_stack *a)` | Returns the `pos` of the node with the smallest `index` (rank) in the stack. Used as the wrap-around target. |
| `set_target_pos(t_stack **a, t_stack **b)` | For each node in B, finds the closest larger-ranked node in A and sets `target_pos` to that node's position. If no larger rank exists, targets the minimum-rank position (wrap-around). |
| `get_cost(t_stack **a, t_stack **b)` | Calculates `cost_a` and `cost_b` for each node in B. Positive = rotate, negative = reverse rotate. Direction depends on whether the node/target is in the upper or lower half of its stack. |

---

### `execute_move.c`

| Function | Description |
|----------|-------------|
| `optimize(t_stack **a, t_stack **b, int cost_a, int cost_b)` | *(static)* Executes the cheapest move. Uses `rr` when both costs are positive, `rrr` when both are negative, then finishes any remaining single-stack rotations. |
| `do_move(t_stack **a, t_stack **b)` | Finds the cheapest node in B via `get_cheapest_cost`, executes `optimize` to position both stacks, then calls `pa` to push it to A. |

---

### `finder_utils.c`

| Function | Description |
|----------|-------------|
| `abs_val(long nb)` | *(static)* Returns the absolute value of a number. |
| `calc_combined_cost(long a, long b)` | *(static)* Calculates the true cost of a move. When costs have the same sign (both rotate or both reverse-rotate), the combined cost is `max(|a|, |b|)` since they overlap. Otherwise it's `|a| + |b|`. |
| `get_cheapest_cost(t_stack *b)` | Iterates through B and returns the node with the lowest combined cost (the optimal move). |
| `get_lowest_index_pos(t_stack **a)` | Returns the position of the node with the lowest index (rank) in A. |
| `is_sorted(t_stack *stack)` | Returns `1` if the stack values are in ascending order, `0` otherwise. Used to skip sorting when input is already sorted. |

---

### `linked_list.c`

| Function | Description |
|----------|-------------|
| `stack_new(int value, int index)` | Allocates a new node with the given value and rank index. All other fields are initialized to `-1` / `NULL`. |
| `stack_add_back(t_stack **stack, t_stack *new_node)` | Appends a node to the end of the doubly-linked list. |
| `free_stack(t_stack **stack)` | Frees all nodes in the stack and sets the head pointer to `NULL`. |
| `get_stack_size(t_stack *stack)` | Returns the number of nodes in the stack. |

---

### `input_utils.c`

| Function | Description |
|----------|-------------|
| `free_array(char **arr, int count)` | Frees a null-terminated string array and its elements. |
| `parse_input(int ac, char **av)` | Handles both input formats: a single quoted string (`"3 2 1"`) via `ft_split`, or multiple arguments (`3 2 1`) via `ft_strdup`. Returns a string array. |
| `arr_len(char **arr)` | Returns the length of a null-terminated string array. |
| `get_numbers(char **str_nums)` | Converts the string array to integers. Validates syntax and checks for integer overflow (`INT_MIN` to `INT_MAX`). |
| `pre_sort_int_arr(int *arr, int size)` | Sorts an integer array in-place using **selection sort**. Used to create the sorted copy for rank assignment. |

---

### `input2_utils.c`

| Function | Description |
|----------|-------------|
| `is_valid_syntax(char *str)` | Validates that a string is a valid integer: optional `+`/`-` prefix followed by digits only. |
| `ft_atol(const char *str)` | Converts a string to `long`. Similar to `atoi` but returns `long` to detect overflow before casting to `int`. |
| `check_duplicates(int *arr, int size)` | Checks a **sorted** array for adjacent duplicates. Returns `1` if duplicates exist. |

---

### `error_utils.c`

| Function | Description |
|----------|-------------|
| `exit_error(t_stack **a, char **str_nums)` | Frees any allocated resources, writes `"Error\n"` to stderr, and exits with code `1`. |

---

### Operation Files

#### `swap_ops.c`
| Function | Description |
|----------|-------------|
| `swap(t_stack **stack)` | Swaps the first two elements of a stack by relinking pointers. |
| `sa` / `sb` / `ss` | Swap wrappers that call `swap` and print the operation name. `ss` swaps both stacks. |

#### `push_ops.c`
| Function | Description |
|----------|-------------|
| `push(t_stack **src, t_stack **dest)` | Removes the top element from `src` and pushes it onto `dest`. |
| `pa` / `pb` | Push wrappers: `pa` pushes B→A, `pb` pushes A→B. Each prints its operation name. |

#### `rotate_ops.c`
| Function | Description |
|----------|-------------|
| `rotate(t_stack **stack)` | Moves the top element to the bottom (shift up). |
| `ra` / `rb` / `rr` | Rotate wrappers. `rr` rotates both stacks simultaneously. |

#### `rev_rotate_ops.c`
| Function | Description |
|----------|-------------|
| `reverse_rotate(t_stack **stack)` | Moves the bottom element to the top (shift down). |
| `rra` / `rrb` / `rrr` | Reverse rotate wrappers. `rrr` reverse-rotates both stacks simultaneously. |

---

## Allowed Operations

| Op    | Effect                                       |
|-------|----------------------------------------------|
| `sa`  | Swap first 2 elements of A                   |
| `sb`  | Swap first 2 elements of B                   |
| `ss`  | `sa` + `sb` simultaneously                   |
| `pa`  | Push top of B onto A                          |
| `pb`  | Push top of A onto B                          |
| `ra`  | Rotate A up (top → bottom)                    |
| `rb`  | Rotate B up (top → bottom)                    |
| `rr`  | `ra` + `rb` simultaneously                   |
| `rra` | Reverse rotate A (bottom → top)               |
| `rrb` | Reverse rotate B (bottom → top)               |
| `rrr` | `rra` + `rrb` simultaneously                 |

---

## 2. Run the Program

Execute push_swap by passing a list of integers. It accepts numbers as separate arguments or as a single quoted string. It will output the calculated sequence of operations to stdout.
Makefile Targets

    make / make all — Compile the executable.

    make clean — Remove object files.

    make fclean — Remove object files and the executable.

    make re — Rebuild the project from scratch.

## Recommendations for Improvement

### Current Performance Estimate (500 elements)

Based on the current Turk Sort implementation with a simple median split, the expected move count is roughly **~6,500–8,000 operations** for 500 random elements. The 42 grading benchmarks are:

| Moves (500 elements) | Grade             |
|-----------------------|-------------------|
| ≤ 5,500              | ✅ Full marks      |
| ≤ 7,000              | ⚠️ Partial marks   |
| > 7,000              | ❌ Failing          |

### Recommended Improvements

#### 1. Chunk-Based Pushing (High Impact)
Instead of splitting A into just two halves, divide the indices into **multiple chunks** (e.g., 5–8 chunks for 500 elements). Push elements chunk-by-chunk into B, placing smaller-index elements at the bottom of B and larger ones at the top. This pre-sorts B into rough descending order, dramatically reducing the cost of later insertions.

**Target: ~5,000–5,500 moves** for 500 elements.

#### 2. Dynamic Chunk Sizing
The optimal number of chunks varies with input size. A good heuristic is `chunks = sqrt(size) * 0.65`. For 500 elements, that's roughly **14–15 chunks**. Experiment with this multiplier to find the sweet spot.

**Target: ~4,500–5,200 moves** for 500 elements.

#### 3. Greedy Best-of-Two-Ends
When pushing from A to B, check both the top and bottom of A for which element is cheaper to push. This can save 10–15% of moves by sometimes using `rra` + `pb` instead of iterating through the entire stack with `ra`.

**Target: Additional ~5–10% reduction.**

#### 4. Improved `push_init` Strategy
The current `push_init` pushes the lower half first, then everything else. A smarter approach would:
- Push elements that are **closest to the top or bottom** of A first (minimizing rotations).
- Consider `rrr`/`rr` opportunities during the initial push phase itself.

#### 5. Pre-Sort B During Pushes
When pushing to B, use `rb` to maintain B in rough descending order. This means during Phase 3, each element in B is already close to its correct position, reducing costs.

#### 6. Better `sort_three` Integration
Instead of always reducing A to exactly 3, consider reducing to **5** and implementing an optimized `sort_five` that uses the same Turk logic but with fewer wasted operations.

### Summary of Achievable Targets

| Strategy                          | Expected Moves (500 elements) |
|-----------------------------------|-------------------------------|
| Current implementation            | ~6,500–8,000                  |
| + Chunk-based pushing             | ~5,000–5,500                  |
| + Dynamic chunk sizing            | ~4,500–5,200                  |
| + Greedy best-of-two-ends         | ~4,200–4,800                  |
| All optimizations combined        | **~4,000–4,500**              |


##AI Usage Statement

AI was used to support brainstorming, gather ideas, structure concepts, and generate test scripts for this project. No core logic coding was completed with the assistance of AI, maintaining strict adherence to the 42 school academic integrity policies.

##Resources

push_swap visualizer [Link](https://github.com/o-reo/push_swap_visualizer)
linked list [Link](https://visualgo.net/en/list)
push_swap [Game](https://vscza.itch.io/push-swap)
sorting algo [Selection Sort](https://www.geeksforgeeks.org/c/c-program-for-selection-sort/)
push_swap [Sample](https://github.com/arommers/push_swap)
Sorting Algorithms [Cheatsheet](https://www.bigocheatsheet.com/)
Sorting Algorithms [Animations](https://www.toptal.com/developers/sorting-algorithms)
Turk Sort1 [Explained](https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0)
Turk Sort2 [Explained](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
Grrokking Algorithims [Link](https://www.manning.com/books/grokking-algorithms?source=post_page-----4c6650a458c0---------------------------------------)

