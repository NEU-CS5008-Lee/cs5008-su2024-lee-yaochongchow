// name: Yao Chong Chow
// email: chow.ya@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here

    if (n == 0) {
        return 1;  
    }
    if (n == 2) {
        return 3;  
    }
    if (n%2!=0){
        return 0;
    }

    d[0] = 1;
    d[2] = 3;

    for (int i = 4; i <= n; i += 2) {
        d[i] = 3 * d[i-2];
        for (int j = i - 4; j >= 0; j -= 2) {
            d[i] += 2 * d[j];
        }
    }

    return d[n];
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
