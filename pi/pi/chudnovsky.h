#pragma once

#include <iostream>
#include <mpirxx.h>

struct PQT
{
	mpz_class P, Q, T;
};

class Chudnovsky
{
private:
	mpz_class A, B, C, D, E, C3_24; // GMP Integer
	int DIGITS, PREC, N; // Integer
	double DIGITS_PER_TERM; // Long
	clock_t t0, t1, t2; // Time
	PQT bsr(int n1, int n2); // Computer PQT

public:
	Chudnovsky(int digits); // Constructor
	std::string computePi(); // Compute PI
};