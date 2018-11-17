#include "widget6.h"

using namespace std;

int hex2Dec(int x) {
	int s = 0;
	for (int i = 0; i < 2; i++) {
		s = s * 16;
		if (D[x][i] >= 'a')
			s += D[x][i] - 'a' + 10;
		else if (D[x][i] >= 'A')
			s += D[x][i] - 'A' + 10;
		else
			s += D[x][i] - '0';
	}
	return s;
}

extern void Oppo_AWB( int awbStart, int e , ofstream *f) {

	

	e = awbStart;
	fout << "AWB_R :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "AWB_Gr :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "AWB_Gb :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "AWB_B :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "Golden_R :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "Golden_Gr :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "Golden_Gb :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;
	fout << "Golden_B :	" << (float)(hex2Dec(e + 0) + hex2Dec(e + 1) * 256) / 1024 << endl;
	e = e + 2;





}