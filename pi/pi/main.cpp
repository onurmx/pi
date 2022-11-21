#include "bigfloat.h"
#include "findpattern.h"
#include "helpers.h"
#include <iostream>
#include <omp.h>
#include "pi.h"

int main()
{
	/********EXAMPLE USAGE OF PI CALCULATION *****************************************/
	//omp_set_nested(1);
	//int threads = omp_get_max_threads();
	//size_t digits = 1000000;
	//std::vector<std::vector<my_complex>> twiddle_table;

	////  Figure out how large to make the table:
	////  Determine minimum FFT size.
	//size_t p = 2 * digits / 9 + 10;
	//int k = 0;
	//size_t length = 1;
	//while (length < 3 * p) {
	//	length <<= 1;
	//	k++;
	//}
	//fft_ensure_table(twiddle_table, k);

	//dump_to_file("pi_output.txt", Pi(twiddle_table, digits, threads, false));
	/*******************************************************************************/

	/***************EXAMPLE USAGE OF KMP ALGORITHM******************/
	//std::string text = "gcatcgcagagagtatacagtacg";
	//std::string pattern = "gagag";
	//std::cout << std::to_string(KMP_search(text, pattern));
	/***************************************************************/
}
