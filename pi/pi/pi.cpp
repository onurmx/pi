#include "bigfloat.h"
#include "helpers.h"
#include <iostream>
#include <omp.h>

using std::cout;
using std::endl;

void Pi_BSR(std::vector<std::vector<my_complex>>& twiddle_table, BigFloat& P, BigFloat& Q, BigFloat& R, uint32_t a, uint32_t b, size_t p, int tds = 1) {
	//  Binary Splitting recursion for the Chudnovsky Formula.

	if (b - a == 1) {
		//  P = (13591409 + 545140134 b)(2b-1)(6b-5)(6b-1) (-1)^b
		P = BigFloat(b).mul(545140134);
		P = P.add(BigFloat(13591409));
		P = P.mul(2 * b - 1);
		P = P.mul(6 * b - 5);
		P = P.mul(6 * b - 1);
		if (b % 2 == 1)
			P.negate();

		//  Q = 10939058860032000 * b^3
		Q = BigFloat(b);
		Q = Q.mul(twiddle_table, Q).mul(twiddle_table, Q).mul(26726400).mul(409297880);

		//  R = (2b-1)(6b-5)(6b-1)
		R = BigFloat(2 * b - 1);
		R = R.mul(6 * b - 5);
		R = R.mul(6 * b - 1);

		return;
	}

	uint32_t m = (a + b) / 2;

	BigFloat P0, Q0, R0, P1, Q1, R1;

	if (b - a < 1000 || tds < 2) {
		//  No more threads.
		Pi_BSR(twiddle_table, P0, Q0, R0, a, m, p);
		Pi_BSR(twiddle_table, P1, Q1, R1, m, b, p);
	}
	else {
		//  Run sub-recursions in parallel.
		int tds0 = tds / 2;
		int tds1 = tds - tds0;
#pragma omp parallel num_threads(2)
		{
			int tid = omp_get_thread_num();
			if (tid == 0) {
				Pi_BSR(twiddle_table, P0, Q0, R0, a, m, p, tds0);
			}
			if (tid != 0 || omp_get_num_threads() < 2) {
				Pi_BSR(twiddle_table, P1, Q1, R1, m, b, p, tds1);
			}
		}
	}

	P = P0.mul(twiddle_table, Q1, p, tds).add(P1.mul(twiddle_table, R0, p, tds), p);
	Q = Q0.mul(twiddle_table, Q1, p, tds);
	R = R0.mul(twiddle_table, R1, p, tds);
}

void Pi(std::vector<std::vector<my_complex>>& twiddle_table, size_t digits, int tds) {
	//  The leading 3 doesn't count.
	digits++;

	size_t p = (digits + 8) / 9;
	size_t terms = (size_t)(p * 0.6346230241342037371474889163921741077188431452678) + 1;

	//  Limit Exceeded
	if ((uint32_t)terms != terms)
		throw "Limit Exceeded";

	cout << "Computing Pi..." << endl;
	cout << "Algorithm: Chudnovsky Formula" << endl << endl;

	double time0 = wall_clock();

	cout << "Summing Series... " << terms << " terms" << endl;
	BigFloat P, Q, R;
	Pi_BSR(twiddle_table, P, Q, R, 0, (uint32_t)terms, p, tds);
	P = Q.mul(13591409).add(P, p);
	Q = Q.mul(4270934400);
	double time1 = wall_clock();
	cout << "Time: " << time1 - time0 << endl;

	cout << "Division... " << endl;
	P = Q.div(twiddle_table, P, p, tds);
	double time2 = wall_clock();
	cout << "Time: " << time2 - time1 << endl;

	cout << "InvSqrt... " << endl;
	Q = invsqrt(twiddle_table, 10005, p, tds);
	double time3 = wall_clock();
	cout << "Time: " << time3 - time2 << endl;

	cout << "Final Multiply... " << endl;
	P = P.mul(twiddle_table, Q, p, tds);
	double time4 = wall_clock();
	cout << "Time: " << time4 - time3 << endl;

	cout << "Total Time = " << time4 - time0 << endl << endl;

	dump_to_file("pi.txt", P.to_string(digits));
}