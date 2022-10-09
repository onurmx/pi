#pragma once

#include "fft.h"
#include <omp.h>
#include <pmmintrin.h>
#include <vector>

struct SIMD_delete {
    void operator()(__m128d* p) {
        _mm_free(p);
    }
};
struct my_complex {
    double r;
    double i;
    my_complex(double _r, double _i) : r(_r), i(_i) {};
};
//std::vector<std::vector<my_complex>> twiddle_table;
void fft_ensure_table(std::vector<std::vector<my_complex>>& twiddle_table,int k);
void fft_forward(std::vector<std::vector<my_complex>>& twiddle_table,__m128d* T, int k, int tds = 1);
void fft_inverse(std::vector<std::vector<my_complex>>& twiddle_table,__m128d* T, int k, int tds = 1);
void fft_pointwise(__m128d* T, __m128d* A, int k);
void int_to_fft(__m128d* T, int k, const uint32_t* A, size_t AL);
void fft_to_int(__m128d* T, int k, uint32_t* A, size_t AL);