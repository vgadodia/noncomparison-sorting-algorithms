// Programming Language: C 4.2.1
// Development Framework: Sublime Text
// Platform: Mac 

// Command in terminal to compile and run this program:
// gcc CS-Problem5.c
// ./a.out

/* 
Input instructions: 
Enter input file name (containing the data) in first prompt (first line)
Enter output file name in second prompt (second line)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

// Structure to store the 5 numbers and the position of the prime number respectively
struct num_set{
    unsigned long long data[5];
    int position;
};

// Structure for a queue that takes 3 integers for each node
struct queueNode 
{ 
    int start;
    int end;
    int index; 
    struct queueNode *next; 
};

int is_Prime(unsigned long long num);
void prime_position(struct num_set *num_data, int num_records);
void countingsort(struct num_set *num_data, struct num_set *sorted_data, int num_records);
void divider(struct num_set *num_data, struct num_set *sorted_data, int num_records);
void radixSort(struct num_set *num_data, struct num_set *sorted_data, int start, int end);
void countingsort2(struct num_set *num_data, struct num_set *sorted_data, int start, int end, int digit);
void divider2(struct num_set *num_data, struct num_set *sorted_data, int num_records);
void radixSort2(struct num_set *num_data, struct num_set *sorted_data, int start, int end);
void countingsort3(struct num_set *num_data, struct num_set *sorted_data, int start, int end, int index, int digit);
struct queueNode *createNode(int start, int end, int position);
struct queueNode *pop(struct queueNode **head, struct queueNode **tail);
void push(struct queueNode **head, struct queueNode **tail, struct queueNode *node);

int main()
{
    // Declaring characters for input and output filenames
    char input[100];
    char output[100];

    // Reads input and output filenames
    printf("Enter input file name: ");
    scanf("%s", input);
    printf("Enter output file name: ");
    scanf("%s", output);

    FILE *inp_ptr;
    FILE *out_ptr;

    // Reads data from input file
    inp_ptr = fopen(input, "r");

    // Writes data into output file
    out_ptr = fopen(output, "w");

    // Declaring variable for number of records
    int num_records;

    // Reads number of records
    fscanf(inp_ptr, "%d", &num_records);

    if (num_records == 0){
        return 0;
    }
    if (num_records < 0){
        printf("Error: number of num_data is negative\n");
        return -1;
    }

    // Declares structures to store data
    struct num_set *num_data;
    struct num_set *sorted_data;

    // Creates empty structure num_data
    num_data = (struct num_set *) malloc(num_records * sizeof(struct num_set));

    // Checks if memory was allocated
    if(num_data == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    
    // Reads the five integers on each line
    for (int i = 0; i < num_records; ++i)
    {
        fscanf(inp_ptr, "%llu %llu %llu %llu %llu", &num_data[i].data[0], &num_data[i].data[1], &num_data[i].data[2], &num_data[i].data[3], &num_data[i].data[4]);
    }

    // Creates empty structure sorted_data
    sorted_data = (struct num_set *)malloc(num_records * sizeof(struct num_set));

    // Starts timer
    start = clock();

    // Function to find the index of the prime number within the 5 numbers on each line
    prime_position(num_data, num_records);

    // Counting sort to sort data by position of prime number
    countingsort(num_data, sorted_data, num_records);

    // Divider function finds indexes of groups with same position of prime number and sorts them by value of prime number
    divider(num_data, sorted_data, num_records);

    // Divider 2 finds indexes of groups that meet the first 2 criteria and calls another radix sort to compare each number and sort by the first difference
    divider2(num_data, sorted_data, num_records);

    // Ends timer
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    for(int i = 0; i < num_records; i++)
    {
        fprintf(out_ptr, "%llu %llu %llu %llu %llu\n", sorted_data[i].data[0], sorted_data[i].data[1], sorted_data[i].data[2], sorted_data[i].data[3], sorted_data[i].data[4]);
    }

    // Prints sorting time
    fprintf(out_ptr, "%f", cpu_time_used*1000);

    // Closes files
    fclose(inp_ptr);
    fclose(out_ptr);

    free(num_data);
    free(sorted_data);
}

// Function to test if a number is prime
int is_Prime(unsigned long long num)
{
    if(num <= 1)
    {
        return 0;
    }
    else if(num <= 3)
    {
        return 1;
    }
    else if(num%2 == 0 || num%3 == 0)
    {
        return 0;
    }
    int i = 5;
    while(i*i <= num)
    {
        if(num%i==0 || num%(i+2) == 0)
        {
            return 0;
        }
        i = i + 6;
    }
    return 1;
}

// This function goes through each number and calls the is_Prime function until it finds the position of the prime number
void prime_position(struct num_set *num_data, int num_records)
{
    for(int i = 0; i < num_records; i++)
    {
        for(int j = 0; j<5;j++)
        {
            if(is_Prime(num_data[i].data[j]) == 1)
            {
                num_data[i].position = j;
                break;
            }
        }
    }
}

// Counting sort function to sort the data by position of the prime number
void countingsort(struct num_set *num_data, struct num_set *sorted_data, int num_records)
{
    int countarr[5];

    // Only 5 possible positions
    int range = 5;
    
    // Initializes values in countarr to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on position
    for (int i = 0; i < num_records; i++)
    {
        countarr[num_data[i].position] = countarr[num_data[i].position] + 1;
    }
    // Cumulative Counting Array
    for (int i = 1; i <= range; i++)
    {
        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure sorted_data
    for (int i = num_records-1; i >= 0; i = i - 1)
    {
        sorted_data[countarr[num_data[i].position]-1] = num_data[i];
        countarr[num_data[i].position] = countarr[num_data[i].position] - 1;
    } 
}

// Divider finds indexes of groups with same position and calls radix sort to sort the data by value of prime number
void divider(struct num_set *num_data, struct num_set *sorted_data, int num_records)
{
    int end = 0;
    while (end<num_records)
    {
        int start = end;
        // Increments end if position is the same
        while (sorted_data[end].position == sorted_data[end+1].position && end<(num_records-1))
        {
            end++;
        }
        end++;
        if (start<end-1 && end<=num_records)
        {
            radixSort(num_data, sorted_data, start, end);
        }
    }
}

// Radix sort sends 6 passes to sort by prime number
void radixSort(struct num_set *num_data, struct num_set *sorted_data, int start, int end)
{

    for (int digit = 3; digit <= 18; digit=digit+3)
    {
        countingsort2(num_data, sorted_data, start, end, digit);

        // Swaps sorted_data and num_data in order to store the output in sorted_data
        struct num_set *temp = sorted_data;
        sorted_data = num_data;
        num_data = temp;
    }
}

// Counting sort function that sorts the data according to each pass of 3 digit numbers
void countingsort2(struct num_set *num_data, struct num_set *sorted_data, int start, int end, int digit)
{ 
    int *countarr;
    int range = 1000;

    // Creates a count array of size range
    countarr = (int*) malloc(range * sizeof(int));

    // Checks if memory was allocated
    if(countarr == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    // Initializes values in count array to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on value of 3 digit number
    for (int i = start; i < end; i++)
    {
        unsigned long long temp2 = sorted_data[i].data[sorted_data[i].position];
        int temp = (temp2/((unsigned long long) pow(10, digit-3)))%1000;
        countarr[temp] = countarr[temp] + 1;
    }
    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {
        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure num_data
    for (int i = end-1; i >= start; i = i - 1)
    {
        unsigned long long temp2 = sorted_data[i].data[sorted_data[i].position];
        int temp = (temp2/((unsigned long long) pow(10, digit-3)))%1000;
        num_data[countarr[temp]+start-1] = sorted_data[i];
        countarr[temp] = countarr[temp] - 1;
    } 
    free(countarr);
}

void push(struct queueNode **head, struct queueNode **tail, struct queueNode *node) 
{ 
    // If queue is empty, then new node is front and rear both 
    if (*head == NULL) 
    { 
        *head = *tail = node; 
        return; 
    } 
  
    // Add the new node at the end of queue and change rear 
    (*tail)->next = node; 
    *tail = node; 
} 

struct queueNode *pop(struct queueNode **head, struct queueNode **tail) 
{ 
    // If queue is empty, return NULL. 
    if (*head == NULL) 
       return NULL; 
  
    // Store previous front and move front one node ahead 
    struct queueNode *temp = *head; 
    *head = (*head)->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (*head == NULL)
    {
        *tail = NULL; 
    } 
    return temp; 
}

struct queueNode *createNode(int start, int end, int index)
{
    struct queueNode *node = (struct queueNode*)malloc(sizeof(struct queueNode));
    node->start = start;
    node->end = end;
    node->index =index;
    node->next = NULL;
    return node;
}

// Divider 2 finds indexes of groups with same position and prime number and calls radix sort
void divider2(struct num_set *num_data, struct num_set *sorted_data, int num_records)
{
    int end = 0;
    while (end<num_records)
    {
        int start = end;
        // Increments end when position and prime number are the same
        while (end<(num_records-1) && sorted_data[end].position == sorted_data[end+1].position && sorted_data[end].data[sorted_data[end].position] == sorted_data[end+1].data[sorted_data[end+1].position])
        {
            end++;
        }
        end++;
        if (start<end-1 && end<=num_records)
        {
            radixSort2(num_data, sorted_data, start, end);
        }
    }
}

// Radix sort 2 compares each number in the set of 5 numbers and sorts based on the first difference
void radixSort2(struct num_set *num_data, struct num_set *sorted_data, int start, int end)
{
    int index = 0;

    // Initialize head and tail of queue
    struct queueNode *head, *tail;
    head = NULL;
    tail = NULL;

    // Creates a node with values of start, end, and index
    struct queueNode *newnode = createNode(start, end, index);

    // Pushes created node to queue
    push(&head, &tail, newnode);

    // Repeats until queue is empty
    while (head != NULL)
    {
        // Pops node from front of the queue
        struct queueNode *node = pop(&head, &tail);

        // Sets temporary values to those popped from the queue
        int index = node->index;
        int start = node->start;
        int end = node->end;
        if(end-start > 1)
        {
            // Performs 6 passes through the numbers at position index and sorts them 
            for (int digit = 3; digit <= 18; digit=digit+3)
            {
                countingsort3(num_data, sorted_data, start, end, index, digit);
                for (int i = start; i < end; i++)
                {
                    struct num_set temp = sorted_data[i];
                    sorted_data[i] = num_data[i];
                    num_data[i] = temp;
                }
            }   

            // Makes new groups with data items that have same numbers up to a certain position determined by index
            // Then, it creates a node with the values and pushes it to the queue
            while (start<end)
            {
                int k = start;
                while (start<(end-1) && sorted_data[start].data[index] == sorted_data[start+1].data[index])
                {
                    start++;
                }
                start++;
                if (k<start && start<=end && index < 4)
                {
                    newnode = createNode(k, start, index+1);
                    push(&head, &tail, newnode);
                }
            }
        }
        free(node);
    }
}

void countingsort3(struct num_set *num_data, struct num_set *sorted_data, int start, int end, int index, int digit)
{ 
    int *countarr;
    int range = 1000;

    // Creates a count array of size range
    countarr = (int*) malloc(range * sizeof(int));

    // Checks if memory was allocated
    if(countarr == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    // Initializes values in count array to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on 3 digit number 
    for (int i = start; i < end; i++)
    {
        unsigned long long temp2 = sorted_data[i].data[index];
        int temp = (temp2/((unsigned long long) pow(10, digit-3)))%1000;
        countarr[temp] = countarr[temp] + 1;
    }

    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {
        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure num_data
    for (int i = end-1; i >= start; i = i - 1)
    {
        unsigned long long temp2 = sorted_data[i].data[index];
        int temp = (temp2/((unsigned long long) pow(10, digit-3)))%1000;
        num_data[countarr[temp]+start-1] = sorted_data[i];
        countarr[temp] = countarr[temp] - 1;
    } 
    free(countarr);
}





