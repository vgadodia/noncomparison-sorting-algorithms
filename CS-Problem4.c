// Programming Language: C 4.2.1
// Development Framework: Sublime Text
// Platform: Mac 

// Command in terminal to compile and run this program:
// gcc CS-Problem4.c
// ./a.out

/* 
Input instructions: 
Enter input file name (containing the data) in first prompt (first line)
Enter output file name in second prompt (second line)
*/

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

// Structure for storing string, most frequent letter, and its frequency respectively
struct data{
    char *s;
    char freq_let;
    int freq;
};

// Structure for a queue that takes 3 integers for each node
struct queueNode
{
    int start;
    int end;
    int index;
    struct queueNode *next;
};

void create_strings(struct data *str_data, int num_records, FILE *inp_ptr);
void frequency(struct data *str_data, int num_records);
void countingsort(struct data *str_data, struct data *sorted_records, int num_records);
void divider(struct data *str_data, struct data *sorted_records, int num_records);
void countingsort2(struct data *str_data, struct data *sorted_records, int start, int end);
void divider2(struct data **str_data, struct data **sorted_records, int num_records);
void radixSort(struct data **str_data, struct data **sorted_records, int start, int end);
void countingsort3(struct data *str_data, struct data *sorted_records, int start, int end, int index);
struct queueNode *createNode(int start, int end, int index);
struct queueNode *pop(struct queueNode **head, struct queueNode **tail);
void push(struct queueNode **head, struct queueNode **tail, struct queueNode *node);

// Main function
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
	char c = fgetc(inp_ptr);

    if (num_records == 0){
        return 0;
    }
    if (num_records < 0){
        printf("Error: number of num_data is negative\n");
        return -1;
    }

    // Declares structures to store data
    struct data *str_data;
    struct data *sorted_records;

    // Creates empty structure str_data
	str_data = (struct data *)malloc(num_records * sizeof(struct data));

    // Checks if memory was allocated
    if(str_data == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    // Calls create_strings function to read data from input file and fill into structure data_str
    create_strings(str_data, num_records, inp_ptr);

    // Creates empty structure sorted_records
    sorted_records = (struct data *)malloc(num_records * sizeof(struct data));

    // Starts timer
    start = clock();

    // Function to store the letter with the greatest frequency and the greatest frequency
	frequency(str_data, num_records);

    // Counting sort function to sort the data by occurences of most frequent letter
	countingsort(str_data, sorted_records, num_records);
	
    // Divider finds indexes of groups with same frequency and calls counting sort to sort the groups alphabetically my most frequent letter
    divider(str_data, sorted_records, num_records);

    // Divider 2 finds indexes of groups that meet the first 2 criteria and then calls radix sort to compare the strings alphabetically from left to right
	divider2(&str_data, &sorted_records, num_records);

    // Ends timer
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	for (int i = 0; i < num_records; i++)
	{
		fprintf(out_ptr, "%s\n", str_data[i].s);
	}

    // Prints sorting time
    fprintf(out_ptr, "%f", cpu_time_used*1000);

    // Closes files
    fclose(inp_ptr);
    fclose(out_ptr);

    free(sorted_records);
    free(str_data);
}

// Function to read data and fill structure records with the data
void create_strings(struct data *str_data, int num_records, FILE *inp_ptr)
{
    char temp[41];
    // Loops through each line in the input file
    for(int i = 0; i < num_records; i++)
    {   
        // Reads strings
        char c = fgetc(inp_ptr);
        int j = 0;
        while (c != '\n' && c != EOF)
        {
            temp[j] = c;
            j++;
            c = fgetc(inp_ptr);
        }
        temp[j] = '\0';
        j++;
        // Only allocate memory as needed
        str_data[i].s = (char *)malloc(j * sizeof(char));

        // Copies each letter from temp into str_data[i].s
        for(int k = 0; k<j;k++)
        {
            str_data[i].s[k] = temp[k];
        }
        // Adds NULL character at the end of the string
        str_data[i].s[j] = '\0';
    }
}

// Function stores most frequent letter and the value of its frequency in structure str_data
void frequency(struct data *str_data, int num_records)
{
	for(int i = 0; i < num_records; i++)
	{
        // Declare array freq_counter
		int freq_counter[26];

        // Initialize values in freq_counter to 0
		for (int j = 0; j<26;j++)
		{
			freq_counter[j] = 0;
		}
		int j = 0;

        // Stores the different frequencies of each letter in the string
		while(str_data[i].s[j] != '\0')
		{
			freq_counter[str_data[i].s[j] - 'A'] = freq_counter[str_data[i].s[j] - 'A'] + 1 ;
			j++;
		}

        // Finds index of most frequent letter
		int index_max = 0;
		for (int j = 1;j<26;j++)
		{
			if (freq_counter[j] > freq_counter[index_max])
			{
				index_max = j;
			}
		}

		char letter = index_max + 65;

        // Stores most frequent letter in structure str_data
		str_data[i].freq_let = letter;

        // Store the frequency of the most frequent letter in structure str_data
		str_data[i].freq = freq_counter[index_max];
	}
}

// Counting sort function to sort the data by occurences of most frequent letter
void countingsort(struct data *str_data, struct data *sorted_records, int num_records) 
{
    int *countarr;

    // 40 possible letters in each string (1-40 inclusive)
    int range = 40;

    // Creates a count array of size k
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

    // Increments values in count array depending on value of frequency
    for (int i = 0; i < num_records; i++)
    {
    	countarr[str_data[i].freq-1] = countarr[str_data[i].freq-1] + 1;
    }

    // Cumulative Counting Array
    for (int i = range-2; i >= 0; i = i-1)
    {

        countarr[i] = countarr[i] + countarr[i+1];
    }

    // Adds sorted data to structure sorted_records
    for (int i = num_records-1; i >= 0; i = i - 1)
    {
        sorted_records[countarr[str_data[i].freq-1]-1] = str_data[i];
        countarr[str_data[i].freq-1] = countarr[str_data[i].freq-1] - 1;
    } 
    free(countarr);
}

// Divider function finds start and end indexes of groups with same frequency and calls counting sort with those indexes
void divider(struct data *str_data, struct data *sorted_records, int num_records)
{
	int end = 0;
    while (end<num_records)
	{
	    int start = end;
        while (sorted_records[end].freq == sorted_records[end+1].freq && end<(num_records-1))
        {
            end++;
        }
        end++;
        if (start<end && end<=num_records)
        {
            countingsort2(str_data, sorted_records, start, end);
        }
    }
}

// Counting sort function to sort data by alphabetical order of most frequent letter
void countingsort2(struct data *str_data, struct data *sorted_records, int start, int end) 
{
    int *countarr;

    // Only 26 letters
    int range = 26;

    // Create a count array of size k
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

    // Increments values in count array depending on most frequent letter
    for (int i = start; i < end; i++)
    {
    	countarr[sorted_records[i].freq_let-'A'] = countarr[sorted_records[i].freq_let-'A'] + 1;
    }

    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {
        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure str_data
    for (int i = end-1; i >= start; i = i - 1)
    {
        str_data[start+countarr[sorted_records[i].freq_let-'A']-1] = sorted_records[i];
        countarr[sorted_records[i].freq_let-'A'] = countarr[sorted_records[i].freq_let-'A'] - 1;
    } 
}


// Divider function that finds start and end indexes of groups with same frequency and most frequent letter and calls radix sort with those indexes
void divider2(struct data **str_data, struct data **sorted_records, int num_records)
{
	int end = 0;
    while (end<num_records)
    {
        int start = end;
        while (end<(num_records-1) && (*str_data)[end].freq == (*str_data)[end+1].freq && (*str_data)[end].freq_let == (*str_data)[end+1].freq_let)
        {
            end++;
        }
        end++;
        if (start<(end-1) && end<=num_records)
        { 
        	radixSort(str_data, sorted_records, start, end);
        }
    }
}

// Function to push items to a queue
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

// Function to pop items from a queue
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

// Function to create a node (with start, end, and index) that can be pushed to a queue
struct queueNode *createNode(int start, int end, int index)
{
    struct queueNode *node = (struct queueNode*)malloc(sizeof(struct queueNode));
    node->start = start;
    node->end = end;
    node->index = index;
    node->next = NULL;
    return node;
}

// Left to right radix sort function to sort data by comparing strings alphabetically
void radixSort(struct data **str_data, struct data **sorted_records, int start, int end)
{
	int index = 0;

    // Initialize head and tail of queue
	struct queueNode *head, *tail;
	head = NULL;
	tail = NULL;

    // Create a node with start, end, and index values
	struct queueNode *newnode = createNode(start, end, index);

    // Push the created node to the queue
	push(&head, &tail, newnode);

    // Repeats until the queue is empty
	while (head != NULL)
	{
        // Pops node from the front of the queue
		struct queueNode *node = pop(&head, &tail);
		int index = node->index;
        int start = node->start;
        int end = node->end;

        // Checks if a letter exists in the string at the index in the node
        // If it doesn't exist, it means the string has ended and so it will be moved to the top as it is a prefix 
        for (int i = start; i < end; ++i)
        {
            if ((*str_data)[i].s[index] == '\0')
            {
                char *temp = (*str_data)[start].s;
                (*str_data)[start].s = (*str_data)[i].s;
                (*str_data)[i].s = temp;
                start = start + 1;
            }
        }

        // Checks to make sure group of strings is greater than 1
		if(end-start > 1)
		{
            // Calls counting sort to sort strings with same frequency and frequent letter by letters in a certain index
			countingsort3(*str_data, *sorted_records, start, end, index);
			
            // Swaps str_data with sorted_records
            for (int i = start; i < end; i++)
			{
				struct data temp = (*str_data)[i];
    			(*str_data)[i] = (*sorted_records)[i];
    			(*sorted_records)[i] = temp;
			}
            
            // The while loop makes groups of strings that share the same letters up to a certain index determined by variable index
    		// After making these new groups of strings, it creates a node with the new start, end, and index values and pushed it to the queue
            while (start<end)
    		{
        		int k = start;
        		while (start<(end-1) && (*str_data)[start].s[index] == (*str_data)[start+1].s[index])
        		{
        			start++;
        		}
        		start++;
        		if (k<start && start<=end)
        		{
        			newnode = createNode(k, start, index+1);
        			push(&head, &tail, newnode);
        		}
    		}
		}
		free(node);
	}
}  

// Counting sort function that sorts the strings with the same frequency and frequent letter by a certain index determined by the index
void countingsort3(struct data *str_data, struct data *sorted_records, int start, int end, int index) 
{ 
    int *countarr;

    // Only 26 letters
    int range = 26;
    
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

    // Increments values in count array depending on letter at certain index
    for (int i = start; i < end; i++)
    {
    	countarr[str_data[i].s[index]-'A'] = countarr[str_data[i].s[index]-'A'] + 1;
    }

    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {
        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure sorted_records
    for (int i = end-1; i >= start; i = i - 1)
    {
        sorted_records[start+countarr[str_data[i].s[index]-'A']-1] = str_data[i];
        countarr[str_data[i].s[index]-'A'] = countarr[str_data[i].s[index]-'A'] - 1;
    } 
}












