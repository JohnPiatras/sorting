#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

// colour codes courtesy of https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c/3219471
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_array(int a[], const int n, const int i_red, const int i_green);
void copy_array(const int source[], int dest[], const int n);
int rand_range(const int m, const int n);

void test_sort_function(char name[], void (*f)(int a[], const int n, bool print_output), const int a[], const int n );

void bubble_sort(int a[], const int n, bool print_output);
void selection_sort(int a[], const int n, bool print_output);
void insertion_sort(int a[], const int n, bool print_output);
void merge_sort(int a[], const int n, bool print_output);
void heap_sort(int a[], const int n, bool print_output);

int main(int argc,  char* argv[])
{    
    int array_size = 25;
    if(argc == 2){
        array_size = atoi(argv[1]);
        if (array_size <= 0)
        {
            array_size = 25;
        }
    }

    int original_array[array_size];
    
    srand(time(NULL));
    for (int i= 0 ; i < array_size; i++)
    {
        original_array[i] = rand_range(999, 1);        
    }

    float dT;
    
    printf("Sort test\n");
    printf("Array size is %i\n\n", array_size);

    test_sort_function("Bubble Sort", bubble_sort, original_array, array_size);    
    test_sort_function("Selection Sort", selection_sort, original_array, array_size);   
    test_sort_function("Insertion Sort", insertion_sort, original_array, array_size);      
    test_sort_function("Merge Sort", merge_sort, original_array, array_size);      
    test_sort_function("Heap Sort", heap_sort, original_array, array_size);      
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
        int extracted = a[i];
        int j = i - 1; //we will campare extracted to the last sorted element        
        //shifts every sorted element that is greater than a[j] to the right by one
        if(print_output)print_array(a, n, i, -1);
        while( extracted < a[j] && j >= 0)
        {                  
            comparisons++;
            a[j + 1] = a[j];
            if(print_output)print_array(a, n, j , j + 1);
            j--;
        }
        //we exited the while loop because extracted > a[j] or j < 0
        a[j + 1] = extracted;
        insertions++;
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



void _merge_sort(int a[], int temp[], const int start, const int end, bool print_output)
{    
    if(end <= start)
    {
        return;
    }    
    int middle = (start + end) / 2;    
    _merge_sort(a, temp, start, middle, print_output);
    _merge_sort(a, temp, middle + 1, end, print_output);

    int left = start;   //current index of left array
    int right = middle + 1; //current index of right array
    int i = start;  //current index in our main array
    if(print_output)print_intermediate_merge_array(a, start, end, true);

    //place elements from either left, or right array into 
    //our intermediate array in correct order until one of
    //the left or right arrays has no elements left
    while ( left < (middle + 1) && right < (end + 1) )
    {
        if(a[left] < a[right])
        {
            temp[i] = a[left];
            left++;
        }
        else
        {
            temp[i] = a[right];
            right++;
        }
        i++;
    }

    //these two loops copy the remainder of which ever of the left or right
    //arrays has elements left into the remainder of our intermediate array
    while( left < (middle + 1) )
    {
        temp[i] = a[left];
        left++;
        i++;
    }

    while( right < (end + 1) )
    {
        temp[i] = a[right];
        right++;
        i++;
    }

    //copy our now sorted elements from the intermediate array into the main array
    for(int i = start; i <= end; i++)
    {
        a[i] = temp[i];
    }

    if(print_output)print_intermediate_merge_array(a, start, end, false);
}

void merge_sort(int a[], const int n, bool print_output)
{
    int temp[n];
    
    if(print_output)print_intermediate_merge_array(a, 0, n - 1, false);

    _merge_sort(a, temp, 0, n - 1, print_output);

}

#define PARENT(i) ((i - 1) / 2)
#define LINE_WIDTH 100
void print_binary_tree(int tree[], int n)
{
    int print_pos[n];
    int i, j, k, pos, x=1, level=0;

    print_pos[0] = 0;
    for(i=0,j=1; i<n; i++,j++) {
        pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);

        for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':'-');
        printf("%d",tree[i]);

        print_pos[i] = x = pos+1;
        if (j==pow(2,level)) {
            printf("\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    printf("\n\n\n");
}



/*              
                                             000
                       _______________________|_______________________
                      |                                               |
                     000                                             000
           ___________|___________                         ___________|___________
          |                       |                       |                       |
         000                     000                     000                     000       
     _____|_____             _____|_____             _____|_____             _____|_____
    |           |           |           |           |           |           |           |
   000         000         000         000         000         000         000         000
  __|__       __|__       __|__       __|__       __|__       __|__       __|__       __|__
 |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
001   002   003   004   005   006   007   008   001   002   003   004   005   006   007   008
*/

#define NODE_WIDTH 3
void print_chars(int n, char c)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}

void print_connectors(int spacing, int indent, int nodes)
{
    for(int i = 0; i < nodes / 2; i++)
    {
        print_chars(1 + indent + NODE_WIDTH / 2, ' ');
        print_chars(1 + indent + NODE_WIDTH / 2, '_');
        printf("|");
        print_chars(1 + indent + NODE_WIDTH / 2, '_');
        print_chars(1 + NODE_WIDTH + spacing / 2, ' ');
    }
    printf("\n");

    print_chars(indent + NODE_WIDTH / 2,' ');
    for(int i = 0; i < nodes; i++)
    {
        printf("|");
        print_chars(spacing + 2 * (NODE_WIDTH / 2), ' ');
    
    }
    printf("\n");

}

void print_heap(int a[], int n, int i_green, int i_red)
{
    int h = log2(n);
    //loop from levels of tree, starting at root
    int i = 0; //index of current node
    for(int l = 0; l <=h; l++)
    {
        int d = h - l; //distance from leaf node level
        
        int spacing = (pow(2,d + 1) - 1) * NODE_WIDTH;
        int indent = (pow(2, d) - 1) * NODE_WIDTH;
        int nodes = pow(2, l); //number of nodes at this level
        if(l > 0)print_connectors(spacing, indent, nodes);

        
        print_chars(indent, ' ');        
        for(int j = 0; j < nodes && i < n; j++)
        {
            if(i == i_red)
                printf(ANSI_COLOR_RED);
            else if( i == i_green)
                printf(ANSI_COLOR_GREEN);                
                
            printf("%03i", a[i]);
            printf(ANSI_COLOR_RESET);
            print_chars(spacing, ' ');
            i++;
        }
        printf("\n");        
    }
    printf("\n");

}
//in a heap sort we start by treating our array as a 'complete binary tree'
//This has the special properties of being a binary tree and of having its
//leaf elements leaning to the left. The last leaf element does not need to
//have a right sibling so this the complete tree does not have to be a full 
//binary tree.
//The complete binary tree has this relationship between array indices and 
//tree elements:
//for a given array index i, its left child is 2i+1 and the right child is 
//2i+2.
//The parent of any given element at i is (i - 1) / 2 rounded down.
//In a heap the largest element is at the root and its children are smaller
//than their parent - this relationship continues down the tree.
//This is a max-heap. A min heap has the opposite relationship.

//this function heapify this sub-tree whose root is at array index i
//We then recursively 
void heapify(int a[], int n, int i, bool print_output)
{
    int largest = i; //will store index of largest amoung heap root, left child and right child
    int left = 2 * i + 1;   //left child index
    int right = 2 * i + 2;  //right child index

    //now determine which is largest
    if(left < n && a[left] > a[largest])
        largest = left;
    if(right < n && a[right] > a[largest])
        largest = right;
    
    //if largest is not root (i) then swap them
    if(print_output)printf("Called heapify with root node index %i...", i);    
    if(largest != i)
    {
        
        if(print_output)
        {
            printf("\nSwapping node at %i and node at %i\n", i, largest);
            print_heap(a, n, largest, i);
        }
        int t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        if(print_output)print_heap(a, n, i, -1);
        //as we have swapped these elements there is no garauntee that
        //the subtree whose root is index give by 'largest' is currently
        //heapified, so heapify it        
        heapify(a, n, largest, print_output);
    }else{
        if(print_output)printf("no swaps.\n");
    }
    
}

void heap_sort(int a[], const int n, bool print_output)
{
    //we start heapifying our tree from the last non-leaf node.
    //In our complete tree this node has index n/2 - 1
    if(print_output)
    {
        printf("Heapifying...\n");
        printf("-------------\n\n");
    }

    for(int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i, print_output);
    }
    if(print_output)print_heap(a, n, -1, -1);

    //We have a max heap, therefore the largest element in the 
    //array is the root element at i = 0
    //So, we swap this to the end of the array then re-heapify the
    //root but with the array length n now given as 1 shorter.    
    if(print_output)
    {
        printf("\nSorting\n");
        printf("---------\n\n");
    }

    int iteration = 0;
    for(int i = n - 1; i >= 0; i--)
    {   
        if(print_output)
        {        
            printf("-------------------------------------------------------\n");    
            printf("///////////////////////////////////////////////////////\n"); 
            printf("-------------------------------------------------------\n"); 
            printf("Iteration %i - Swapping root and node at index %i\n", iteration, i);
            if(print_output)print_heap(a, n, i, 0);
        }
        
        int t = a[0];
        a[0] = a[i];
        a[i] = t;

        if(print_output)print_heap(a, n, i, -1);

        if(print_output)
        {            
            printf("Heapifying from root to node at %i\n", i - 1);
            print_heap(a, n, 0, i - 1);
        }
        heapify(a, i, 0, print_output);
        if(print_output)print_heap(a, n, 0, i-1);
        if(print_output)printf("\n");  
        iteration++;      
    }

    if(print_output)
    {
        
        print_array(a, n, -1, -1);
    }

}



