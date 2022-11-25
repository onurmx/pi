#include "chudnovsky.h"

/*Constructor*/
Chudnovsky::Chudnovsky()
{
	// Constants
	DIGITS = 100000000; /*one million: 1000000, ten million: 10000000, hundred million: 100000000*/
	A = 13591409;
	B = 545140134;
	C = 640320;
	D = 426880;
	E = 10005;
	DIGITS_PER_TERM = 14.1816474627254776555;  // = log(53360^3) / log(10)
	C3_24 = C * C * C / 24;
	N = DIGITS / DIGITS_PER_TERM;
	PREC = DIGITS * log2(10);
}

/*Compute PQT (by Binary Splitting Algorithm)*/
PQT Chudnovsky::compPQT(int n1, int n2)
{
	int m;
	PQT res;

	if (n1 + 1 == n2) {
		res.P = (2 * n2 - 1);
		res.P *= (6 * n2 - 1);
		res.P *= (6 * n2 - 5);
		res.Q = C3_24 * n2 * n2 * n2;
		res.T = (A + B * n2) * res.P;
		if ((n2 & 1) == 1) res.T = -res.T;
	}
	else {
		m = (n1 + n2) / 2;
		PQT res1 = compPQT(n1, m);
		PQT res2 = compPQT(m, n2);
		res.P = res1.P * res2.P;
		res.Q = res1.Q * res2.Q;
		res.T = res1.T * res2.Q + res1.P * res2.T;
	}

	return res;
}

/*Compute PI*/
void Chudnovsky::compPi()
{
	std::cout << "**** PI Computation ( " << DIGITS << " digits )" << std::endl;

	// Time (start)
	t0 = clock();

	// Compute Pi
	PQT PQT = compPQT(0, N);
	mpf_class pi(0, PREC);
	pi = D * sqrt((mpf_class)E) * PQT.Q;
	pi /= (A * PQT.Q + PQT.T);

	// Time (end of computation)
	t1 = clock();
	std::cout << "TIME (COMPUTE): " << (double)(t1 - t0) / CLOCKS_PER_SEC << " seconds." << std::endl;
}