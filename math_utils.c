#include <stdio.h>
#include <string.h>
#include "math_utils.h"

long long gcd_ll(long long a, long long b) {
    long long temp;

    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}
static long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    long long x1, y1;
    long long gcd;
    
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    gcd = extended_gcd(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}
long long mod_inverse(long long a, long long m, int *has_inverse) {
    long long x, y;
    long long gcd;
    long long answer;

    gcd = extended_gcd(a, m, &x, &y);

    if (gcd != 1) {
        *has_inverse = 0;
        return 0;
    }

    answer = (x % m + m) % m;
    *has_inverse = 1;

    return answer;
}


long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;

    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}





int is_prime(long long n) {
    long long i;

    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

long long phi_value(long long n) {
    long long result = n;
    long long p;

    for (p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n = n / p;
            }

            result = result - (result / p);
        }
    }

    if (n > 1) {
        result = result - (result / n);
    }

    return result;
}
