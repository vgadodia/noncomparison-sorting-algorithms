// Programming Language: C 4.2.1
// Development Framework: Sublime Text
// Platform: Mac 

// Command in terminal to compile and run this program:
// gcc CS-Problem3.c
// ./a.out

/* 
Input instructions: 
Enter input file name (containing the data) in first prompt
Enter output file name in second prompt
*/

/*
Special Instructions:
Uncomment and comment the radixSort, countingsort3, or radixSort2 
functions in the divider function in order to run each one individually. 
Only one function should be uncommented.
See the divider function for further instructions.
*/

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

// Structure for storing id, lastname, firstname, gpa, and graduation year respectively
struct student_record{
    unsigned long int id;
    char lastname[31];
    char firstname[31];
    float gpa;
    int gradyear;
};

void create_records(struct student_record *records, int num_records, FILE *inp_ptr);
void countingsort(struct student_record *records, struct student_record *sorted_records, int n);
void divider(struct student_record *records, struct student_record *sorted_records, int n);
void countingsort2(struct student_record *records, struct student_record *sorted_records, int start, int end, int digit);
void radixSort_9pass(struct student_record *records, struct student_record *sorted_records, int start, int end);
void countingsort3(struct student_record *records, struct student_record *sorted_records, int start, int end); 
void radixSort_3pass(struct student_record *records, struct student_record *sorted_records, int start, int end);
void countingsort4(struct student_record *records, struct student_record *sorted_records, int start, int end, int digit);

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

    // Testing if number of records is 0 or negative
    if (num_records == 0){
        return 0;
    }
    if (num_records<0){
        printf("Error: number of records is negative\n");
        return -1;
    }

    // Declares structures to store data
    struct student_record *records;
    struct student_record *sorted_records;

    // Creates empty structure records 
    records = (struct student_record*) malloc(num_records * sizeof(struct student_record));
    
    // Checks to see if memory was allocated
    if(records == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    // Calls create_records function to read data from input file and fill into structure records
    create_records(records, num_records, inp_ptr);

    // Creates empty structure sorted_records
    sorted_records = (struct student_record*) malloc(num_records * sizeof(struct student_record));

    // Starts timer
    start = clock();

    // Calls counting sort function to sort records by graduation year and output into structure sorted_records
    countingsort(records, sorted_records, num_records);
    
    // Calls divider function which finds groups in structure sorted_records with the same graduation year and calls a 3 pass radix sort on them to sort them by ID
    // The data sorted by ID is outputted back into structure records 
    divider(records, sorted_records, num_records);

    // Ends timer
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // Outputs data from structure records into output file
    for (int i = 0; i<num_records; i++)
    {
        fprintf(out_ptr, "%lu %s, %s %.2f %d\n", records[i].id, records[i].lastname, records[i].firstname, records[i].gpa, records[i].gradyear);
    }

    // Prints sorting time
    fprintf(out_ptr, "%f", cpu_time_used*1000);

    // Closes files
    fclose(inp_ptr);
    fclose(out_ptr);

    free(records);
    free(sorted_records);
}

// Function to read data and fill structure records with the data
void create_records(struct student_record *records, int num_records, FILE *inp_ptr)
{
    // Loops through each line in the input file
    for (int i = 0; i<num_records; i++)
    {
        // Reads ID
        fscanf(inp_ptr, "%lu", &records[i].id);
        char c = fgetc(inp_ptr);
        c = fgetc(inp_ptr);
        int j = 0;

        // Reads lastname
        while (c != ',')
        {
            records[i].lastname[j]=c;
            j++;
            c = fgetc(inp_ptr);
        }  
        // Adds NULL character to end of string
        records[i].lastname[j] = '\0';
        c = fgetc(inp_ptr);
        c = fgetc(inp_ptr);
        j = 0;

        // Reads firstname
        while (c < '0' || c > '9')
        {
            records[i].firstname[j]=c;
            j++;
            c = fgetc(inp_ptr);
        }
        // Adds NULL character to end of string
        records[i].firstname[j-1] = '\0';
        ungetc(c, inp_ptr);

        // Reads gpa and graduation year data
        fscanf(inp_ptr, "%f %d", &records[i].gpa, &records[i].gradyear);
        c = fgetc(inp_ptr);
    }
}

// Counting sort function to sort data in records by graduation year and output it into sorted_records
void countingsort(struct student_record *records, struct student_record *sorted_records, int num_records) 
{
    int *countarr;

    // 5 possible graduation years (2018-2022 inclusive)
    int range = 5;

    // Create a count array of size k
    countarr = (int*) malloc(range * sizeof(int));

    // Initializes values in count array to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on gradyear
    for (int i = 0; i < num_records; i++)
    {
        countarr[records[i].gradyear-2018] = countarr[records[i].gradyear-2018] + 1;
    }

    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {
        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds data to structure sorted_records
    for (int i = num_records-1; i >= 0; i = i - 1)
    {
        sorted_records[countarr[records[i].gradyear-2018]-1] = records[i];
        countarr[records[i].gradyear-2018] = countarr[records[i].gradyear-2018] - 1;
    } 
    free(countarr);
} 

// Divider function calls the 3 pass radix sort function with indexes of groups with the same graduation year to sort by ID
void divider(struct student_record *records, struct student_record *sorted_records, int num_records)
{
    int end = 0;
    for (int j = 0; j < 5; j++)
    {
        // k is the start index of the group with the same graduation year
        int start = end;
        while (sorted_records[end].gradyear-2018 == j && end<num_records)
        {
            end++;
        }
        // i is end index of the group with the same graduation year
        if (start<end && end<=num_records)
        {
            /*
            Uncomment and comment the functions below to run
            the 9 pass radix sort, counting sort, and 3 pass 
            radix sort approaches. 

            The radixSort_3pass approach is uncommented because I chose it
            as my main sorting method for this problem.
            
            Only one function should be uncommented.

            Keep in mind, the countingsort3 requires a large amount of memory.
            */

            // Uncomment below for 9 pass radix sort approach
            //radixSort_9pass(records, sorted_records, start, end);
            
            // Uncomment below for counting sort approach
            //countingsort3(records, sorted_records, start, end);

            // Uncomment below for 3 pass radix sort approach
            radixSort_3pass(records, sorted_records, start, end);
        }
    }
}

// Radix sort approach that sends 9 passes through the IDs to sort them
void radixSort_9pass(struct student_record *records, struct student_record *sorted_records, int start, int end)
{

    for (int digit = 0; digit < 9; digit++)
    {
        // Calls counting sort with a 1 digit number
        countingsort2(records, sorted_records, start, end, digit);
        struct student_record *temp = sorted_records;
        sorted_records = records;
        records = temp;
    }
}

// Counting sort called by the 9 pass radix sort to sort the 9 groups of digits
void countingsort2(struct student_record *records, struct student_record *sorted_records, int start, int end, int digit) 
{  
    int *countarr;

    // 10 possible digits (0-9 inclusive)
    int range = 10;

    // Create a count array of size k
    countarr = (int*) malloc(range * sizeof(int));

    // Initializes values in count array to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on value of digit
    for (int i = start; i < end; i++)
    {
        unsigned long int temp2 = sorted_records[i].id;
        int temp = (temp2/((int) pow(10, digit)))%10;
        countarr[temp] = countarr[temp] + 1;
    }
    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {

        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure records
    for (int i = end-1; i >= start; i = i - 1)
    {
        unsigned long int temp2 = (sorted_records[i].id);
        int temp = (temp2/((int) pow(10, digit)))%10;
        records[countarr[temp]+start-1] = sorted_records[i];
        countarr[temp] = countarr[temp] - 1;
    } 
    free(countarr);
}

// Radix sort approach that sends 3 passes through the IDs to sort them
void radixSort_3pass(struct student_record *records, struct student_record *sorted_records, int start, int end)
{

    for (int digit = 3; digit <= 9; digit=digit+3)
    {
        // Calls counting sort with a 3 digit number
        countingsort4(records, sorted_records, start, end, digit);
        struct student_record *temp = sorted_records;
        sorted_records = records;
        records = temp;
    }
}

// Counting sort called by the 3 pass radix sort to sort the 3 groups of digits
void countingsort4(struct student_record *records, struct student_record *sorted_records, int start, int end, int digit) 
{ 
    int *countarr;

    // 1000 possible 3 digit numbers (0-999 inclusive)
    int range = 1000;

    // Create a count array of size k
    countarr = (int*) malloc(range * sizeof(int));

    // Initializes values in count array to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on value of 3 digit number
    for (int i = start; i < end; i++)
    {
        unsigned long int temp2 = sorted_records[i].id;
        int temp5 = ((temp2/((int) pow(10, digit-1)))%10)*100;
        int temp3 = ((temp2/((int) pow(10, digit-2)))%10)*10;
        int temp4 = ((temp2/((int) pow(10, digit-3)))%10);
        int temp = temp5 + temp3 + temp4;
        countarr[temp] = countarr[temp] + 1;
    }
    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {

        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure records
    for (int i = end-1; i >= start; i = i - 1)
    {
        unsigned long int temp2 = sorted_records[i].id;
        int temp5 = ((temp2/((int) pow(10, digit-1)))%10)*100;
        int temp3 = ((temp2/((int) pow(10, digit-2)))%10)*10;
        int temp4 = ((temp2/((int) pow(10, digit-3)))%10);
        int temp = temp5 + temp3 + temp4;
        records[countarr[temp]+start-1] = sorted_records[i];
        countarr[temp] = countarr[temp] - 1;
    } 
    free(countarr);
}

// Final counting sort approach which sorts all the IDs with same graduation year in one pass
void countingsort3(struct student_record *records, struct student_record *sorted_records, int start, int end) 
{ 
    int *countarr;

    // 1000000000 possible values of ID (0-999999999 inclusive)
    unsigned long int range = 1000000000;

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

    // Increments values in count array depending on value of ID
    for (int i = start; i < end; i++)
    {
        countarr[sorted_records[i].id] = countarr[sorted_records[i].id] + 1;
    }

    // Cumulative Counting Array
    for (int i = 1; i < range; i++)
    {

        countarr[i] = countarr[i] + countarr[i-1];
    }

    // Adds sorted data to structure records
    for (int i = end-1; i >= start; i = i - 1)
    {
        records[countarr[sorted_records[i].id]-1] = sorted_records[i];
        countarr[sorted_records[i].id] = countarr[sorted_records[i].id] - 1;
    } 
    free(countarr);
}

