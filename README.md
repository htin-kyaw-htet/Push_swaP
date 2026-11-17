*This project has been created as part of the 42 curriculum by mmyat, htkyaw.*

# push_swap

## Description

**Goal:** sort a list of integers using two stacks (`a` and `b`) and only 11 allowed
operations, while printing the shortest list of operations we can.

The program `push_swap` reads integers as arguments, then prints one operation per line
on standard output. Applying those operations to stack `a` sorts it in ascending order
(smallest number on top) with `b` empty at the end.

**The 11 operations**

| Operation | Effect |
|---|---|
| `sa` / `sb` / `ss` | swap the top two elements of a / b / both |
| `pa` / `pb` | push the top of b onto a / the top of a onto b |
| `ra` / `rb` / `rr` | rotate: the top element goes to the bottom |
| `rra` / `rrb` / `rrr` | reverse rotate: the bottom element goes to the top |

**Overview of the project**

- Stacks are stored as **linked lists** (`t_stack`: `value`, `index`, `next`).
- The program contains **four strategies** and chooses one at runtime:
  simple, medium, complex and adaptive.
- The **disorder** of the input is measured before any move.
- An optional `--bench` mode prints statistics on stderr.

## Instructions

### Compilation

```bash
make        # builds ./push_swap
make clean  # removes object files
make fclean # removes object files and the binary
make re     # fclean + all
```

Flags used: `cc -Wall -Wextra -Werror`.

### Execution

```bash
./push_swap [strategy] [--bench] <list of integers>
```

| Option | Meaning |
|---|---|
| `--simple` | force the O(n²) algorithm |
| `--medium` | force the O(n√n) algorithm |
| `--complex` | force the O(n log n) algorithm |
| `--adaptive` | choose by disorder (**default**) |
| `--bench` | print statistics on **stderr** after sorting |

Rules: the first number is the top of stack `a`; no duplicates; every value must fit in a
C `int`. On any error the program prints `Error` on stderr. With no arguments it prints
nothing.

### Examples

```bash
./push_swap 2 1 3 6 5 8
./push_swap --simple 5 4 3 2 1
./push_swap --bench 4 67 3 87 23 2> bench.txt
```

Example of `--bench` output (on stderr):

```
[bench] disorder: 40.00%
[bench] strategy: Adaptive / O(n√n)
[bench] total_ops: 13
[bench] sa: 0 sb: 0 ss: 0 pa: 5 pb: 5
[bench] ra: 2 rb: 1 rr: 0 rra: 0 rrb: 0 rrr: 0
```

## Algorithms

All complexities are measured in **number of push_swap operations generated**, not in
CPU time. `n` is the number of integers.

### Disorder metric

Disorder is a number between 0 and 1: for every pair (i < j) in the starting stack, a pair
is a "mistake" if `a[i] > a[j]`. Then `disorder = mistakes / total_pairs`.
A sorted list gives 0 and a reversed list gives 1. A random list gives about 0.5.
It is computed once, before any move (it does not cost any operation).
With 0 or 1 numbers there are no pairs, so we return 0 to avoid dividing by zero.

### 1. Simple: selection sort: O(n²)

1. Find the smallest number in `a`.
2. Rotate `a` until it is on top (`ra` if it is in the top half, `rra` otherwise).
3. `pb` it.
4. Repeat until `a` is empty (or already sorted), then `pa` everything back.

Because the smallest numbers are pushed first, they come back in the right order.
**Why O(n²):** each of the `n` numbers needs at most about `n/2` rotations, plus one `pb`
and one `pa`.

### 2. Medium: chunk sort: O(n√n)

1. Replace every value by its **rank** (`index`: 0 = smallest, n-1 = biggest).
2. Push numbers to `b` chunk by chunk. A chunk is a window of ranks of size about `2√n`.
   Numbers outside the current window are skipped with `ra`. Smaller numbers of the
   window are sent to the bottom of `b` with `rb`, so `b` ends up roughly ordered.
3. Bring the biggest rank of `b` to the top (`rb` or `rrb`, whichever is shorter) and
   `pa` it. Biggest first means `a` ends up ascending.

**Why O(n√n) (upper-bound argument):** there are about `√n` chunks. For each chunk, `a`
is rotated at most once around (`O(n)`), which gives `O(n√n)` for phase 1. In phase 2,
the next biggest number is always within about one chunk of the top of `b`, so each of
the `n` `pa` needs `O(√n)` rotations: `O(n√n)` again.

### 3. Complex: radix sort (LSD, on ranks): O(n log n)

1. Replace every value by its rank (`index`).
2. For each bit from the least significant one: `pb` the numbers whose bit is 0, `ra` the
   ones whose bit is 1, then `pa` everything back.

**Why O(n log n):** the ranks go from 0 to n-1, so there are `⌈log₂ n⌉` bits. Each pass
costs at most `2n` operations (`n` for the `pb`/`ra` and `n` for the `pa`).

### 4. Adaptive (default)

The program measures the disorder first, then picks:

| Disorder | Strategy used | Class |
|---|---|---|
| `< 0.2` | selection sort | O(n²) |
| `0.2 ≤ d < 0.5` | chunk sort | O(n√n) |
| `≥ 0.5` | radix sort | O(n log n) |

**Rationale for the thresholds:** a random list has a disorder of about 0.5, so `0.5` and
above is the "really messy" case (random or close to reversed), where only the
O(n log n) method gives a guaranteed good bound. Between 0.2 and 0.5 the list is partly
ordered, so the O(n√n) chunk method is a middle ground. Below 0.2 the list is almost
sorted, and the simple method is enough (and it stops immediately if the list is
already sorted).

**Complexity of the adaptive strategy:** it is the worst of the three branches inside its
own range, so it respects the targets of the subject (O(n²), O(n√n), O(n log n)).

**Space:** O(n) in total: the two stacks (at most `n` nodes together), plus a temporary
array of `n` integers during parsing, which is freed right after. The strategies
themselves only use O(1) extra variables.

## Technical choices

- **Linked lists** for the stacks: `pa`, `pb` and `sa` only change a few pointers.
- **Basic moves are separated from printing** (`swap_top`, `push_top`, `rotate_up`,
  `rotate_down` do the move; `sa`, `pb`, ... also print and count). This makes it easy
  to reuse the moves, for example in a checker.
- **No global variables.** The `--bench` counters live in a `t_stats` struct that is
  passed to every operation.
- `--bench` output goes to **stderr**, so the operations on stdout can still be piped to
  the checker.

## Testing

All commands are meant to be copy-pasted from the project folder (they work in bash and
zsh). `checker_linux` is the checker provided with the subject. The numbers are stored
in an **array** `ARG` so that each number is passed as a separate argument.

```bash
make
```

**1. Correctness with each strategy**

```bash
ARG=(4 67 3 87 23)
./push_swap --simple "${ARG[@]}" | ./checker_linux "${ARG[@]}"     # expected: OK
./push_swap --medium "${ARG[@]}" | ./checker_linux "${ARG[@]}"     # expected: OK
./push_swap --complex "${ARG[@]}" | ./checker_linux "${ARG[@]}"    # expected: OK
./push_swap --adaptive "${ARG[@]}" | ./checker_linux "${ARG[@]}"   # expected: OK
./push_swap "${ARG[@]}" | ./checker_linux "${ARG[@]}"              # expected: OK (default = adaptive)
```

**2. Performance, 100 random numbers**

```bash
ARG=($(shuf -i 0-9999 -n 100))
./push_swap "${ARG[@]}" | ./checker_linux "${ARG[@]}"   # expected: OK
./push_swap "${ARG[@]}" | wc -l                         # target: < 700 excellent, < 1500 good, < 2000 pass
```

**3. Performance, 500 random numbers**

```bash
ARG=($(shuf -i 0-9999 -n 500))
./push_swap "${ARG[@]}" | ./checker_linux "${ARG[@]}"   # expected: OK
./push_swap "${ARG[@]}" | wc -l                         # target: < 5500 excellent, < 8000 good, < 12000 pass
```

**4. Each strategy on 100 numbers**

```bash
ARG=($(shuf -i 0-9999 -n 100))
for f in --simple --medium --complex --adaptive; do
  echo "$f: $(./push_swap $f "${ARG[@]}" | wc -l) operations"
  ./push_swap $f "${ARG[@]}" | ./checker_linux "${ARG[@]}"
done
```

**5. Benchmark mode**

```bash
ARG=(4 67 3 87 23)
./push_swap --bench "${ARG[@]}" 2> bench.txt | ./checker_linux "${ARG[@]}"   # expected: OK
cat bench.txt
```

**6. Edge cases**

```bash
./push_swap                          # prints nothing
./push_swap 5                        # prints nothing (one number)
./push_swap 1 2 3                    # prints nothing (already sorted)
./push_swap 2 1 | ./checker_linux 2 1                      # expected: OK
./push_swap 3 2 1 | ./checker_linux 3 2 1                  # expected: OK
./push_swap -5 3 -100 0 2147483647 -2147483648 | ./checker_linux -5 3 -100 0 2147483647 -2147483648   # expected: OK
```

**7. Error management (each must print `Error` on stderr)**

```bash
./push_swap 1 1            # duplicate
./push_swap 1 a 3          # not a number
./push_swap 2147483648     # bigger than INT_MAX
./push_swap -2147483649    # smaller than INT_MIN
./push_swap ""             # empty argument
```

**8. Memory**

```bash
ARG=($(shuf -i 0-9999 -n 100))
valgrind --leak-check=full ./push_swap "${ARG[@]}" > /dev/null
```

**9. Norm**

```bash
norminette *.c *.h
```

## Contributions

| Part | Author |
|---|---|
| Argument parsing, error handling, linked-list stack, the 11 operations | htkyaw |
| Radix sort (complex strategy) | htkyaw |
| Disorder metric | mmyat |
| Simple (selection) and medium (chunk) strategies | mmyat |
| Adaptive strategy and `--bench` mode | mmyat |
| Makefile, README, testing | htkyaw |

## Resources

**References**

- Subject of the project: *push_swap* (42 curriculum, version 1.2)
- Big-O notation: https://en.wikipedia.org/wiki/Big_O_notation
- Stack (data structure): https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
- Linked list: https://en.wikipedia.org/wiki/Linked_list
- Selection sort: https://en.wikipedia.org/wiki/Selection_sort
- Radix sort: https://en.wikipedia.org/wiki/Radix_sort

### Use of AI

AI tools were used in this project only as a learning and research assistant, never to write code. All the C code (parsing, stacks, operations, sorting strategies, disorder metric and `--bench` mode) was written, tested and debugged by the authors, and we can explain every part of it. We used AI to get plain-language explanations of the push_swap rules, to research how selection sort, chunk sort and radix sort work with two stacks, to understand Big-O notation and write the justification in the Algorithms section, to learn concepts we did not know (linked lists, rank indexing, bitwise operations), to discuss ideas for the disorder metric before choosing the formula and thresholds ourselves, to get ideas for edge cases and error cases to test. We checked what AI told us against the subject, the references above and our own tests, and we tested everything with the provided checker.
