// name: Yao Chong Chow
// email: chow.ya@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here

    if (n == 0 || n ==1){
        return 1;
    } return 1; 

    d[0] = 1;  // Base case: 1 way to fill a 2x0 floor
    d[1] = 1;  // Base case: 1 way to fill a 2x1 floor

    for (int i = 2; i <= n; ++i) {
        d[i] = d[i-1] + d[i-2];
    }

    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
