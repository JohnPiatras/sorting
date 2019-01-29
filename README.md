Here I play with some sorting algorithms.

Usage: sorting <num>

Where <num> is an integer greater than 0.

If no integer is supplied the default of 25 will be used.

The program generates an array of <num> random integers from 1 to 100
and sorts them using bubble sort, selection sort, insertion sort and merge sort.

Intermediate steps are printed along with total time to sort for each algorithm
as long as the array size is 40 or less. For larger values the intermediate output
is suppressed.

Note - each algorithm is actually run twice - once to print intermediate output
and a second time with no printed output during which it is timed.

= Why? =

I wanted to practice writing these algorithms and writing some C as it's been some
time since I did so.

Also, it shows off just how powerful a merge sort is compared to the others:

    Sort test
    Array size is 50000

    Bubble Sort
    Time elapsed = 39768.949219ms

    Selection Sort
    Time elapsed = 15173.847656ms

    Insertion Sort
    Time elapsed = 11755.546875ms

    Merge Sort
    Time elapsed = 44.090271ms

= Sample Output =
    Sort test
    Array size is 10

    Bubble Sort
    034 012 037 041 029 041 049 086 024 051
    012 034 037 041 029 041 049 086 024 051
    012 034 037 029 041 041 049 086 024 051
    012 034 037 029 041 041 049 024 086 051
    012 034 037 029 041 041 049 024 051 086
    012 034 029 037 041 041 049 024 051 086
    012 034 029 037 041 041 024 049 051 086
    012 029 034 037 041 041 024 049 051 086
    012 029 034 037 041 024 041 049 051 086
    012 029 034 037 024 041 041 049 051 086
    012 029 034 024 037 041 041 049 051 086
    012 029 024 034 037 041 041 049 051 086
    012 024 029 034 037 041 041 049 051 086
    Swaps:       12
    Comparisons: 72
    Time elapsed = 0.004000ms

    Selection Sort
    034 012 037 041 029 041 049 086 024 051
    034 012 037 041 029 041 049 086 024 051
    012 034 037 041 029 041 049 086 024 051
    012 034 037 041 029 041 049 086 024 051
    012 024 037 041 029 041 049 086 034 051
    012 024 037 041 029 041 049 086 034 051
    012 024 029 041 037 041 049 086 034 051
    012 024 029 041 037 041 049 086 034 051
    012 024 029 034 037 041 049 086 041 051
    012 024 029 034 037 041 049 086 041 051
    012 024 029 034 037 041 049 086 041 051
    012 024 029 034 037 041 049 086 041 051
    012 024 029 034 037 041 049 086 041 051
    012 024 029 034 037 041 049 086 041 051
    012 024 029 034 037 041 041 086 049 051
    012 024 029 034 037 041 041 086 049 051
    012 024 029 034 037 041 041 049 086 051
    012 024 029 034 037 041 041 049 086 051
    012 024 029 034 037 041 041 049 051 086
    Swaps:       9
    Comparisons: 45
    Time elapsed = 0.002000ms

    Insertion Sort
    034 012 037 041 029 041 049 086 024 051
    034 012 037 041 029 041 049 086 024 051
    012 034 037 041 029 041 049 086 024 051
    012 034 037 041 029 041 049 086 024 051
    012 029 034 037 041 041 049 086 024 051
    012 029 034 037 041 041 049 086 024 051
    012 024 029 034 037 041 041 049 086 051
    012 024 029 034 037 041 041 049 086 051
    012 024 029 034 037 041 041 049 051 086
    012 024 029 034 037 041 041 049 051 086
    Insertions:  4
    Comparisons: 21
    Time elapsed = 0.002000ms

    Merge Sort
    034 012 037 041 029 041 049 086 024 051
    034 012
    012 034
    012 034 037
    012 034 037
                041 029
                029 041
    012 034 037 029 041
    012 029 034 037 041
                        041 049
                        041 049
                        041 049 086
                        041 049 086
                                    024 051
                                    024 051
                        041 049 086 024 051
                        024 041 049 051 086
    012 029 034 037 041 024 041 049 051 086
    012 024 029 034 037 041 041 049 051 086
    Time elapsed = 0.004000ms


