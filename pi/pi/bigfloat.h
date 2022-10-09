#pragma once

#include <algorithm>
#include "fft.h"
#include <memory>
#include <string>
#include <vector>

class BigFloat {
public:
    BigFloat(BigFloat&& x);
    BigFloat& operator=(BigFloat&& x);

    BigFloat();
    BigFloat(uint32_t x, bool sign = true);

    std::string to_string(size_t digits = 0) const;
    std::string to_string_sci(size_t digits = 0) const;
    size_t get_precision() const;
    int64_t get_exponent() const;
    uint32_t word_at(int64_t mag) const;

    void negate();
    BigFloat mul(uint32_t x) const;
    BigFloat add(const BigFloat& x, size_t p = 0) const;
    BigFloat sub(const BigFloat& x, size_t p = 0) const;
    BigFloat mul(std::vector<std::vector<my_complex>>& twiddle_table, const BigFloat& x, size_t p = 0, int threads = 0) const;
    BigFloat rcp(std::vector<std::vector<my_complex>>& twiddle_table, size_t p, int threads = 0) const;
    BigFloat div(std::vector<std::vector<my_complex>>& twiddle_table, const BigFloat& x, size_t p, int threads = 0) const;

private:
    bool sign;      //  true = positive or zero, false = negative
    int64_t exp;    //  Exponent
    size_t L;       //  Length
    std::unique_ptr<uint32_t[]> T;

    //  Internal helpers
    int64_t to_string_trimmed(size_t digits, std::string& str) const;
    int ucmp(const BigFloat& x) const;
    BigFloat uadd(const BigFloat& x, size_t p) const;
    BigFloat usub(const BigFloat& x, size_t p) const;

    friend BigFloat invsqrt(std::vector<std::vector<my_complex>>& twiddle_table, uint32_t x, size_t p, int threads);
};

BigFloat invsqrt(std::vector<std::vector<my_complex>>& twiddle_table, uint32_t x, size_t p, int threads);