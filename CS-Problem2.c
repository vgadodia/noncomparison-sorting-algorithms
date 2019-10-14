// Programming Language: C 4.2.1
// Development Framework: Sublime Text
// Platform: Mac

// Command in terminal to compile and run this program:
// gcc CS-Problem2.c
// ./a.out

/* 
Input instructions: 
Enter input file name (containing the data) in first prompt
Enter output file name in second prompt
*/

/*
Special Instructions:
Uncomment/comment the radixSort and countingsort3 
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

// Structure for storing lastname, firstname, gpa, and graduation year respectively
struct student_record{
    char lastname[31];
    char firstname[31];
    int gpa;
    int gradyear;
};

void create_records(struct student_record *records, int num_records, FILE* inp_ptr);
void countingsort(struct student_record *records, struct student_record *sorted_records, int n);
void divider(struct student_record *records, struct student_record *sorted_records, int n);
void radixSort(struct student_record *records, struct student_record *sorted_records, int start, int end);
void countingsort2(struct student_record *records, struct student_record *sorted_records, int start, int end, int digit);
void countingsort3(struct student_record *records, struct student_record *sorted_records, int start, int end);


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

    // Calls divider function which finds groups in structure sorted_records with the same graduation year and calls counting sort on them to sort them by GPA
    // The data sorted by GPA is outputted back into structure records
    divider(records, sorted_records, num_records);

    // Ends timer
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Outputs data from structure records into output file
    for (int i = 0; i<num_records; i++)
    {
        fprintf(out_ptr, "%s, %s %d.%.2d %d\n", records[i].lastname, records[i].firstname, records[i].gpa/100, records[i].gpa%100, records[i].gradyear);
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
        int gpa = 0;
        while((c=fgetc(inp_ptr))==' ')
        {
            ;
        }
        ungetc(c, inp_ptr);

        // Ignores decimal point and reads GPA as a 3 digit integer
        while((c=fgetc(inp_ptr))!=' ')
        {
            if (c=='.')
            {
                continue;
            }
            int digit = c - '0';
            gpa = (gpa*10)+digit;
        }
        records[i].gpa = gpa;

        // Reads graduation year
        fscanf(inp_ptr, "%d", &records[i].gradyear);
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

// Divider function calls the countingsort3 function with indexes of groups with the same graduation year to sort by GPA
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
            Uncomment and comment the countingsort3 and radixSort 
            functions below in order to run each separately.

            The countingsort3 approach is uncommented because I chose it
            as my main sorting method for this problem.

            Only one function should be uncommented.
            */

            // Uncomment for counting sort approach
            countingsort3(records, sorted_records, start, end);

            // Uncomment for radix sort approach
            //radixSort(records, sorted_records, start, end);
        }
    }
}

// Radix sort approach that sends 3 passes through the GPA and calls countingsort to sort each group of digits
void radixSort(struct student_record *records, struct student_record *sorted_records, int start, int end)
{

    for (int digit = 0; digit < 3; digit++)
    {
        countingsort2(records, sorted_records, start, end, digit);
        struct student_record *temp = sorted_records;
        sorted_records = records;
        records = temp;
    }
}

// Counting sort function to sort each group of digits from radix sort
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
        int temp2 = sorted_records[i].gpa;
        int temp = (temp2/((int) pow(10, digit)))%10;
        countarr[temp] = countarr[temp] + 1;
    }

    // Cumulative Counting Array
    for (int i = range-2; i >= 0; i = i-1)
    {
        countarr[i] = countarr[i] + countarr[i+1];
    }

    // Add sorted data to structure records
    for (int i = end-1; i >= start; i = i - 1)
    {
        int temp2 = sorted_records[i].gpa;
        int temp = (temp2/((int) pow(10, digit)))%10;
        records[countarr[temp]+start-1] = sorted_records[i];
        countarr[temp] = countarr[temp] - 1;
    } 
    free(countarr);
}

// Counting sort approach sorts groups with the same graduation year by GPA with one pass
void countingsort3(struct student_record *records, struct student_record *sorted_records, int start, int end) 
{
    int *countarr;

    // Less than 400 possible values of GPA (0.01-3.99 inclusive)
    int range = 400;

    // Create a count array of size k
    countarr = (int*) malloc(range * sizeof(int));

    // Initializes values in count array to 0
    for (int i = 0; i < range; i++)
    {
        countarr[i] = 0;
    }

    // Increments values in count array depending on value of GPA
    for (int i = start; i < end; i++)
    {
        int temp = sorted_records[i].gpa;
        countarr[temp] = countarr[temp] + 1;
    }
    // Cumulative Counting Array
    for (int i = range-2; i >= 0; i = i-1)
    {
        countarr[i] = countarr[i] + countarr[i+1];
    }

    // Adds sorted data to structure records
    for (int i = end-1; i >= start; i = i - 1)
    {
        int temp = sorted_records[i].gpa;
        records[countarr[temp]+start-1] = sorted_records[i];
        countarr[temp] = countarr[temp] - 1;
    } 
    free(countarr);
}
