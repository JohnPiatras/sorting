#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// colour codes courtesy of https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c/3219471
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

void print_array(int a[], const int n, const int i_red, const int i_green);
void copy_array(const int source[], int dest[], const int n);
int rand_range(const int m, const int n);

void test_sort_function(char name[], void (*f)(int a[], const int n, bool print_output), const int a[], const int n );

void bubble_sort(int a[], const int n, bool print_output);
void selection_sort(int a[], const int n, bool print_output);
void insertion_sort(int a[], const int n, bool print_output);
void merge_sort(int a[], const int n, bool print_output);

int main(int argc,  char* argv[])
{    
    int array_size;
    if(argc == 2){
        array_size = atoi(argv[1]);
        if (array_size <= 0)
        {
            array_size = 25;
        }
    }

    int original_array[array_size];
    int working_array[array_size];

    srand(time(NULL));
    for (int i= 0 ; i < array_size; i++)
    {
        original_array[i] = rand_range(100, 1);        
    }

    float dT;
    
    printf("Sort test\n");
    printf("Array size is %i\n\n", array_size);

    test_sort_function("Bubble Sort", bubble_sort, original_array, array_size);    
    test_sort_function("Selection Sort", selection_sort, original_array, array_size);   
    test_sort_function("Insertion Sort", insertion_sort, original_array, array_size);   
    test_sort_function("Merge Sort", merge_sort, original_array, array_size);   
}

int rand_range(const int m, const int n)
{
    return m + rand() / (RAND_MAX / (n - m + 1) + 1);
}

// i_red and i_green are indices of values that can be colored red or green to indicate swaps
void print_array(int a[], const int n, const int i_red, const int i_green)
{
    
    for (int i= 0 ; i < n; i++)
    {
        if(i == i_red)
        {
            printf(ANSI_COLOR_RED);
        }
        else if(i == i_green)
        {
            printf(ANSI_COLOR_GREEN);
        }
        printf("%03i ", a[i]);
        printf(ANSI_COLOR_RESET);
    }
    printf("\n");
}

void copy_array(const int source[], int dest[], int n)
{
    for(int i = 0; i < n; i++)
    {
        dest[i] = source[i];
    }
}

// This helper function runs a sort function and times it
// char name[] - function name (eg 'Bubble Sort')
// void(*f)... - pointer to the sorting function
// const int a[] - array of integers to be sorted
// const int n - the size of the above array
// The original integer array will not be modified. A copy is used.
void test_sort_function(char name[], void (*f)(int a[], const int n, bool print_output), const int a[], const int n)
{
    int working_array[n];

    copy_array(a, working_array, n);

    printf("%s\n", name);
    if(n <= 40)f(working_array, n, true);

    copy_array(a, working_array, n);    

    float startTime, endTime, dT;
    startTime = (float)clock()/CLOCKS_PER_SEC;
    f(working_array, n, false);
    endTime = (float)clock()/CLOCKS_PER_SEC;
    dT = 1000.0 * (endTime - startTime);
    printf("Time elapsed = %fms\n\n", dT);
    
}

void bubble_sort(int a[], const int n, bool print_output)
{
    bool did_swap;
    int swaps = 0;
    int comparisons = 0;
    
    if(print_output)print_array(a, n, -1, -1);
    do
    {                
        did_swap = false;
        for(int i = 0; i < n - 1; i++)
        {
            if(a[i] > a[i + 1])
            {
                int t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
                did_swap = true;
                swaps++;
                if(print_output)print_array(a, n, i + 1, i);                
            }
            comparisons++;
        }
    }
    while(did_swap);
    if (print_output)
    {
        printf("Swaps:       %d\n", swaps);
        printf("Comparisons: %d\n", comparisons);
    }        
    
}

void selection_sort(int a[], const int n, bool print_output)
{
    int swaps = 0;
    int comparisons = 0;    
    int smallest = 0;
    
    if(print_output)print_array(a, n, -1, -1);
    for(int i = 0; i < n - 1; i++)
    {
        smallest = i;                
       
        for(int j = i + 1; j < n; j++)
        {
            if(a[j] < a[smallest])
            {
                smallest = j;
            }
            comparisons++;
        }
        if(print_output)print_array(a, n, i, smallest);
        int t = a[i];
        a[i] = a[smallest];
        a[smallest] = t;

        swaps++;
        if(print_output)print_array(a, n, smallest, i);
    }
    if(print_output)
    {
        printf("Swaps:       %d\n", swaps);
        printf("Comparisons: %d\n", comparisons);
    }
    
    
}

void insertion_sort(int a[], const int n, bool print_output)
{
    int sorted_index = 0;
    int comparisons = 0;
    int insertions = 0; 

    if(print_output)print_array(a, n, -1, -1);
    for(int i = 1; i < n; i++)
    {
        comparisons++;            
        if (a[i] < a[sorted_index])
        {      
            if(print_output)print_array(a, n, i, -1);      
            int new_index = sorted_index;
            //find first sorted element that is less than current element, a[i]
            comparisons++;
            while(new_index > 0 && a[i] < a[new_index - 1])
            {
                comparisons++;
                new_index--;
            }                      
            //first sorted element that is smaller than a[i] is at index j

            int cur_element = a[i];
            //shift all elements from j to sorted_index right by one
            for(int j = sorted_index; j >= new_index; j--)
            {
                a[j + 1] = a[j];                
            }
            a[new_index] = cur_element;
            insertions++;
            if(print_output)print_array(a, n, -1, new_index);
        }
        
        sorted_index++;
    }    
    if(print_output)
    {
        print_array(a, n, -1, -1);
        printf("Insertions:  %d\n", insertions);
        printf("Comparisons: %d\n", comparisons);
    }        
}


void print_intermediate_merge_array(int a[], const int start, const int end, const bool show_halves)
{
    
    int mid = (start + end) / 2;
    for (int i = 0 ; i <= end; i++)
    {      
        if(show_halves)
        {
            if(i >= start && i <= mid)
            {
                printf(ANSI_COLOR_RED);
            }
            else if(i > mid && i <= end)
            {
                printf(ANSI_COLOR_GREEN);
            }
        }     

        if(i >= start)
        {
            printf("%03i ", a[i]);
        }
        else
        {
            printf("    ");
        }

        printf(ANSI_COLOR_RESET);
    }
    printf("\n");
}

void _merge_sort(int a[], int inter[], const int start, const int end, bool print_output)
{    
    if(end <= start)
    {
        return;
    }    
    int middle = (start + end) / 2;    
    _merge_sort(a, inter, start, middle, print_output);
    _merge_sort(a, inter, middle + 1, end, print_output);

    int left = start;
    int right = middle + 1;    

    if(print_output)print_intermediate_merge_array(a, start, end, true);
    for(int i = start; i <= end; i++)
    {
        if(left == middle + 1)
        {
            inter[i] = a[right];
            right++;
        }
        else if(right == end + 1)
        {
            inter[i] = a[left];
            left++;
        }
        else if (a[left] < a[right])
        {
            inter[i] = a[left];
            left++;
        }
        else
        {
            inter[i] = a[right];
            right++;
        }
    }

    for(int i = start; i <= end; i++)
    {
        a[i] = inter[i];
    }

    if(print_output)print_intermediate_merge_array(a, start, end, false);
}

void merge_sort(int a[], const int n, bool print_output)
{
    int inter[n];
    
    if(print_output)print_intermediate_merge_array(a, 0, n - 1, false);

    _merge_sort(a, inter, 0, n - 1, print_output);

}