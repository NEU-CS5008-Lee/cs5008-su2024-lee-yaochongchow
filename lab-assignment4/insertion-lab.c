//Yao Chong Chow
//chow.ya@northeastern.edu
//To perform insertion sort of integers stored in a file and display the output and store it in another file.
#include <stdio.h>
#include<stdlib.h>
int main()
{
    FILE *fp;
    int arr[10],temp;
    int count=0,i,j;
    /*count will have the total number of elements in the array*/

    /*read the file*/
    fp=fopen("Input1.txt","r");
    if(fp==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot open the file \n");
        exit(0);
    }
    
    //insert your code here
    while (fscanf(fp, "%d", &arr[count]) == 1) {
        count++;
    }

    fclose(fp);
    
    //Insertion Sort
    for (i=1; i<count; i++){
        temp=arr[i];
        for(j=i-1; (j>=0 && arr[j]>temp); j--){
            arr[j+1] = arr[j];
        }
        arr[j+1]=temp;
    }

    //Output file

    FILE *op;
    op=fopen("Output1.txt","w");

    if(op==NULL){
        //if file returns NULL then can't open the file
        printf("\n Cannot write the file \n");
        exit(0);
    }

    for (i=1; i<count; i++){
        fprintf(op,"%d\n",arr[i]);
    }
    
    fclose(op);
    
    return 0;
}
