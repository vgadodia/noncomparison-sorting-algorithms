// Programming Language: C 4.2.1
// Development Framework: Sublime Text
// Platform: Mac

// Command in terminal to compile and run this program:
// gcc CS-Problem1.c
// ./a.out

/* 
Input instructions: 
Enter input file name (containing the data) in first prompt
Enter output file name in second prompt
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

// Structure for storing lastname, firstname, gpa, and graduation year respectively
struct student_record{
    char lastname[31];
    char firstname[31];
    float gpa;
    int gradyear;
};

void create_records(struct student_record *records, int num_records, FILE *inp_ptr);
void countingsort(struct student_record *records, struct student_record *sorted_records, int num_records);

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
        return 0;
    }

    // Declares structures to store data
    struct student_record *records;
    struct student_record *sorted_records;

    // Creates empty structure records according to number of data items in input
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

    // Start timer
    start = clock();

    // Calls counting sort function to sort records by graduation year and output into structure sorted_records
    countingsort(records, sorted_records, num_records);

    // End timer
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Outputs data from sorted_records into output file
    for (int i = 0; i<num_records; i++)
    {
        fprintf(out_ptr, "%s, %s %.2f %d\n", sorted_records[i].lastname, sorted_records[i].firstname, sorted_records[i].gpa, sorted_records[i].gradyear);
    }

    // Prints sorting time
    fprintf(out_ptr, "%f", cpu_time_used*1000);

    // Closes files
    fclose(inp_ptr);
    fclose(out_ptr);

    free(sorted_records);
    free(records);
}

// Function to read data and fill structure records with the data
void create_records(struct student_record *records, int num_records, FILE *inp_ptr)
{
    // Loops through each line in the input file
    for (int i = 0; i<num_records; i++)
    {
        // Reads lastname
        char c = fgetc(inp_ptr);
        int j = 0;
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

    // Adds sorted data to structure sorted_records
    for (int i = num_records-1; i >= 0; i = i - 1)
    {
        sorted_records[countarr[records[i].gradyear-2018]-1] = records[i];
        countarr[records[i].gradyear-2018] = countarr[records[i].gradyear-2018] - 1;
    } 
    free(countarr);
} 

