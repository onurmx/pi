#include "bigfloat.h"
#include "fft.h"
#include <iostream>
#include <omp.h>
#include "pi.h"

int main()
{
    omp_set_nested(1);
    int threads = omp_get_max_threads();
    size_t digits = 100;
    std::vector<std::vector<my_complex>> twiddle_table;

    //  Figure out how large to make the table:
    //  Determine minimum FFT size.
    size_t p = 2 * digits / 9 + 10;
    int k = 0;
    size_t length = 1;
    while (length < 3 * p) {
        length <<= 1;
        k++;
    }
    fft_ensure_table(twiddle_table,k);

    Pi(twiddle_table,digits, threads);
}
