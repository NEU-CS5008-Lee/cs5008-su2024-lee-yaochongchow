//Yao Chong Chow
//chow.ya@northeastern.edu

#include<stdio.h>
int main()
{
    int a,b,c, choice;
    
    printf("Enter your choice\n");
    printf(" 1. Addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
    
    printf("Enter a and b values ");
    scanf("%d %d", &a, &b);
    
    switch (choice) {
        case 1:
            c=a+b;
            printf("Result: %d", c);
            break;

        case 2:
            c=a-b;
            printf("Result: %d\n", c);
            break;

        case 3:
            c=a*b;
            printf("Result: %d\n", c);
            break;

        default:
            c=a/b;
            printf("Result: %d\n", c);
            break;
    }

           
    return 0;
}
