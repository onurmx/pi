#pragma once

#include "gmp.h"
#include "gmpxx.h"
#include <iostream>

struct PQT
{
	mpz_class P, Q, T;
};

class Chudnovsky
{
	mpz_class A, B, C, D, E, C3_24; // GMP Integer
	int DIGITS, PREC, N; // Integer
	double DIGITS_PER_TERM; // Long
	clock_t t0, t1, t2; // Time
	PQT compPQT(int n1, int n2); // Computer PQT (by BSA)

public:
	Chudnovsky(); // Constructor
	void compPi(); // Compute PI
};