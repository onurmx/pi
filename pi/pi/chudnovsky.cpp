#include "chudnovsky.h"

/* Constructor */
Chudnovsky::Chudnovsky(int digits)
{
	/* Constants */
	DIGITS = digits;
	A = 13591409;
	B = 545140134;
	C = 640320;
	D = 426880;
	E = 10005;
	DIGITS_PER_TERM = 14.1816474627254776555; /* log(53360^3) / log(10) */
	C3_24 = C * C * C / 24;
	N = DIGITS / DIGITS_PER_TERM;
	PREC = DIGITS * log2(10);
}

/* Binary Splitting Recursion for the Chudnovsky Formula */
PQT Chudnovsky::bsr(int n1, int n2)
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
		PQT res1 = bsr(n1, m);
		PQT res2 = bsr(m, n2);
		res.P = res1.P * res2.P;
		res.Q = res1.Q * res2.Q;
		res.T = res1.T * res2.Q + res1.P * res2.T;
	}

	return res;
}

/* Compute PI */
std::string Chudnovsky::computePi()
{
	std::cout << "Computing " << DIGITS << " digits of pi." << std::endl;
	std::cout << "Calculation has been started..." << std::endl;

	t0 = clock(); /* Calculation start time */

	/* Calculation procedure */
	/* ********Start******** */
	PQT PQT = bsr(0, N);
	mpf_class pi(0, PREC);
	pi = D * sqrt((mpf_class)E) * PQT.Q;
	pi /= (A * PQT.Q + PQT.T);
	/* *********End********* */

	t1 = clock(); /* Calculation end time */
	std::cout << "Computed in " << (double)(t1 - t0) / CLOCKS_PER_SEC << " seconds." << std::endl;

	mp_exp_t exp;
	std::string str = pi.get_str(exp, 10, 0);

	return str.substr(0, DIGITS);
}