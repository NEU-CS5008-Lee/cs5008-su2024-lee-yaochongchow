// name: Yao Chong Chow
// email: chow.ya@northeastern.edu

#include<stdio.h>
#include<string.h>

int compression(char arr[], int n, char res[]){
    int res_index = 0;
    int count = 1;

    for (int i = 0; i < n; i++) {
        if (i + 1 < n && arr[i] == arr[i + 1]) {
            count++;
        } else {
            res[res_index++] = arr[i];
            if (count > 1) {
                char count_str[10];
                sprintf(count_str, "%d", count);
                for (int j = 0; count_str[j] != '\0'; j++) {
                    res[res_index++] = count_str[j];
                }
            }
            count = 1;
        }
    }
    res[res_index] = '\0';
    return res_index;

}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r,n=strlen(a);//n is the size of input array
    r=compression(a,n,res);
    printf("length of the compressed string:%d\n",r);
    return 0;
}
