//Yao Chong Chow
//chow.ya@northeastern.edu

/*C Program to read and print the n employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;

/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    // Add your code here

    
    printf("Enter the employeeID, Name, Designation and Department of Employee %d:",n+1);
    scanf("%d",&s->empId);
    scanf("%s",s->Name);
    scanf("%s",s->Designation);
    scanf("%s",s->Dept);
    


}
/* Function to print the employee details*/
void display(int n, employee_t* s)
{
    
    printf("The details of Employee %d :\n",n);
    printf("empId: %d\n ", s->empId);
    printf("Name: %s\n ", s->Name);
    printf("Designation: %s\n ", s->Designation);
    printf("Dept: %s\n ", s->Dept);
    printf("\n");
    
}

/*----------Main Program--------*/
int main()

{
    // Main Function to print the employee details
    // Add your code here


        int i;
        int n;

        printf("Enter the number of employees: ");
        scanf("%d",&n);

        employee_t *employee_company = (employee_t*)malloc(n * sizeof(employee_t));

        for (i = 0; i < n; ++i)
        {
        readData(i, &employee_company[i]);
        }

        for (i = 0; i < n; ++i)
        {
        display(i, &employee_company[i]);
        }

        free(employee_company);
        return 0;

}

