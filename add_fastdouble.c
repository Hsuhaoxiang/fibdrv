#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


static long long fib_fast_doub(long long k)
{
    int bin_k[10];
    int count = 0;
    while (k) {
        bin_k[count] = k % 2;
        k = k >> 1;
        count++;
    }
    long long int a = 0, b = 1;
    for (int i = count - 1; i >= 0; i--) {
        a = a * ((2 * b) - a);
        b = b * b + a * a;

        if (bin_k[i] == 1) {
            long long tmp;
            tmp = a + b;
            a = b;
            b = tmp;
        }
    }
    return a;
}

unsigned long long fib_add(int n)
{
    unsigned long long series[92];
    series[0] = 0;
    series[1] = 1;
    for (int i = 2; i < n + 1; i++) {
        series[i] = series[i - 1] + series[i - 2];
    }
    return series[n];
}
long diff_ns(struct timespec t1, struct timespec t2)
{
    return ((long) 1.0e+9 * t2.tv_sec + t2.tv_nsec) -
           ((long) 1.0e+9 * t1.tv_sec + t1.tv_nsec);
}
int main()
{
    FILE *diff = fopen("diff_ns.txt", "w");
    struct timespec t1, t2;
    for (int i = 2; i < 93; i++) {
        clock_gettime(CLOCK_REALTIME, &t1);
        fib_add(i);
        clock_gettime(CLOCK_REALTIME, &t2);
        fprintf(diff, "%d ", i);
        fprintf(diff, "%ld ", diff_ns(t1, t2));
        clock_gettime(CLOCK_REALTIME, &t1);
        fib_fast_doub(i);
        clock_gettime(CLOCK_REALTIME, &t2);
        fprintf(diff, "%ld\n", diff_ns(t1, t2));
    }
    fclose(diff);
    return 0;
}