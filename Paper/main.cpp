﻿#include <iostream>
//struct IUnknown;// Workaround for "combaseapi.h(229): error C2187: syntax error: 'identifier' was unexpected here" when using /permissive-

extern "C" {
#include "miracl.h"
	FILE _iob[] = { *stdin, *stdout, *stderr };
	extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
}
using namespace std;

//#include "Ellipse.h"
//#include "Test.h"
#include "PrintTest.h"

int main()
{
	srand(time(NULL));
	miracl *M = mirsys(100, 0);
	M->IOBASE = 16;
	csprng Rng; InitStrongRNG(&Rng);
	big a = mirvar(1), x = mirvar(1), y = mirvar(1), n = mirvar(1);
	big b = mirvar(0xe);
	EC_CONSTANTS_F2m_POLY EC[NUM_OF_EC] = {};

	pepoint P = epoint_init();
	big k = mirvar(1);
	int m[NUM_OF_EC + 1] = { 0 };// { 163, 233, 283, 409, 571, 0 };
	
	Result testBin[NUM_OF_EC];
	string msg;
	int len = 0;
	readFile("DSTU4145TablePrameters.txt", EC);
	/*printf("%d\n\t%s\n%d %d %d %d %d\n\t%s\n\t%s\n\t%s\n\n",
		EC.a, EC.b, EC.m, EC.k1, EC.k2,
		EC.k3, EC.h, EC.n, EC.Gx, EC.Gy);*/
	//GetConstainsEC(EC, m[0]);
	//for (int i = 0; i < NUM_OF_EC; i++) {
	//	for (int i = 0; i < NUM_OF_EC; i++) {
	//		printf("%4d: %13.3f %13.3f %13.3f %13.3f\n",
	//			0, testBin[i].c[0], testBin[i].c[1], testBin[i].c[2], testBin[i].c[LIB]);
	//	}
	//}
	
	for (int i = 0; i < NUM_OF_EC; i++) {
		m[i] = EC[i].m;
		//GetConstainsEC(EC, m[i]);
		if (!GenEC(EC[i], a, b, P, x, y, n)) 
			return 1;
		//TestBin(Rng, P, n, testBin[i]);
		//TestSclBin(Rng, P, n, testBin[i]);
		Test(Rng, P, n, testBin[i], msg);
		//TestShrMul_Bin(Rng, P, n, msg);
	}
	cout << endl << msg << endl;
	
	printBinOption(m, testBin);
	
	cout << endl << "\a\a\a\a\a\a\a\a\a\a\a" << endl;

	epoint_free(P);
	mirkill(a); mirkill(b); mirkill(k);
	mirexit();
	system("pause");
	return 0;
}

//__________________________________________________

