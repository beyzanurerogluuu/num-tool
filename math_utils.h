#ifndef MATH_UTILS_H
#define MATH_UTILS_H

long long gcd_ll(long long a, long long b);
long long mod_pow(long long base, long long exp, long long mod);
int is_prime(long long n);
long long mod_inverse(long long a, long long m, int *has_inverse);
long long phi_value(long long n);

#endif
