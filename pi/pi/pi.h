#pragma once

void Pi_BSR(std::vector<std::vector<my_complex>>& twiddle_table, BigFloat& P, BigFloat& Q, BigFloat& R, uint32_t a, uint32_t b, size_t p, int tds = 1);
std::string Pi(std::vector<std::vector<my_complex>>& twiddle_table, size_t digits, int tds, bool silent_mode);