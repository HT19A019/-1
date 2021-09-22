#include <iostream>
#include <NTL/ZZ.h>
#include <random>
#include <ctime>
#include <time.h>
#include <limits.h>
#include <stdio.h>

using namespace std;
using namespace NTL;

void Create_Prime(ZZ &p, ZZ &q);
int Miller_Rabin(ZZ &num);
void Division(ZZ &p, ZZ &q);
void MR_MR(ZZ & p, ZZ &q);

ZZ Q2 = (ZZ)2;
ZZ P2 = (ZZ)2;

static clock_t start_t, end_t;
unsigned int success_count = 0;//Prime
unsigned long miss_count = 0;//MIssing
unsigned long Division_miss_count = 0;
unsigned long Q_MR_miss_count = 0;
unsigned long P_MR_miss_count = 0;
unsigned long EEL_miss_count = 0;

int Prime[] = { 2,3,5,7,11,13,17,19,23,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,281,283,293,307,311,313,317,331,337,347,349,353,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541 };

void main() {
	ZZ q, p;
	cout << "Start" << endl;
	while (success_count < 100) {
	Restart:

		Create_Prime(q, p);
		//試行割算法なしならコメントアウト↓
		for (int i = 0; i < 100; i++) {
			if ((q % Prime[i]) == 0 && (p % Prime[i]) == 0) {
				Division_miss_count++;
				goto Restart;
			}
		}
		//ここまで↑

		if (Miller_Rabin(p) == 0) {
		}
		P_MR_miss_count++;
		goto Restart;
	}

	P2 = p % 4;

	if (P2 == 1) {
		for (ZZ a = (ZZ)0; a < p; a++) {
			Q2 *= 2;
		}
		if (((Q2 + 1) % q) != 0) {
			EEL_miss_count++;
			goto Restart;
		}
		success_count++;
	}
	if (P2 == 3) {
		for (ZZ a = (ZZ)0; a < p; a++) {
			Q2 *= 2;
		}
		if (((Q2 - 1) % q) != 0) {
			EEL_miss_count++;
			goto Restart;
		}
		success_count++;
	}
	else {
		EEL_miss_count++;
		goto Restart;
	}

cout << "Success: " << success_count << endl;
cout << "Division_Miss:" << Division_miss_count << endl;
