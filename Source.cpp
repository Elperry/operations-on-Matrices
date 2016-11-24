#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>
using namespace std;
string mat, sstemp, stemp,real,combl;
float matrix[100][100], matrix1[100][100], dete[100][100], te[100][100], result[100][100],comb1[100][100],comb[100][100],resultcomb[100][100], ftemp, fina = 0;
int error = 0, power, x, i, y = 0, ch[100], row = 0, row1 = 0, ncol1 = 9999, ncol = 9999;//
char op;

int entermat(float zz[100][100],float co[100][100], int & r , int & c) {
	int col = 0, index = 1;
	r = 0; c = 9999;
	int x = mat.length();
	if (mat.substr(0, 1) == "[" && mat.substr(x - 1, 1) == "]") { error = 0; }
	else { error = 1; }

	for (int i = 1; i < x; i++) {
		stemp = mat.substr(i, 1);
		if (!((stemp[0] > 47 && stemp[0] < 58) || (stemp == "-") || (stemp == "i") || (stemp == ".") || (stemp == " ") || (stemp == ";") || (stemp == "+") || (stemp == "]"))) { error = 1;/* cout << "ERROR"; */ break; }// cheking for num and - and .and " " and ";" and "]" if error break ;
																																							  // cut mat into pecies and convert it to matrix elements
		if ((stemp == " ") || (stemp == "]") || (stemp == ";")) {// new col and store in matrix
			sstemp = mat.substr(index, i - index); // cut mat into pecies and convert pecies into element
				if ((i - index > 0)) { // do not store empty values
					if (sstemp[sstemp.length()-1]='i') {
						for (int g=0; g <sstemp.length(); g++) {
							if (sstemp[g] == '+' || sstemp[g] == '-') { real = sstemp.substr(0, g); combl = sstemp.substr(g, sstemp.length() - 2); }
						}
						
					}
					zz[r][col] = atof(real.c_str());  // convert string into float
					co[r][col] = atof(combl.c_str());							 // store values in matrix

										  
				col++;
			}
			index = i + 1;
		}
		//storing num of col and check data if mat
		if ((stemp == ";") || (stemp == "]")) { //new row mean we found ; or ] 
			if (c == 9999) { c = col; /*cout << endl << "num of col is: " << ncol;*/ } // storing num of col in ncol 
			else if (c != col) { error = 1;/* cout << "ERROR";*/ break; }//num of cols donot equal
			else { /*cout << endl << ncol;*/ }
			r++; col = 0; //New row	and make col=0 if ; found
		}

		if (stemp == "]") { break; }
	}
	//cout << r << "VS" << c << endl;
	return error;
}

int pluss(float mat1[100][100],float mat2[100][100]) {
	for (i = 0; i < row; i++) {
		for (x = 0; x < ncol; x++) {
			result[i][x] = mat1[i][x] + mat2[i][x];
		}
	}
	return 0;
}

int substract(float mat1[100][100],float mat2[100][100]) {
	for (int i = 0; i < row; i++) {
		for (int x = 0; x < ncol; x++) {
			result[i][x] = mat1[i][x] - mat2[i][x];
		}
	}
	return 0;
}

int multiply(float mm1[100][100], float mm2[100][100], int r, int r1, int c) {
	for (int i = 0; i < r; i++) {
		for (int x = 0; x < c; x++) {
			result[i][x] = 0;
			for (int y = 0; y < r1; y++) {
				result[i][x] = result[i][x] + mm1[i][y] * mm2[y][x];
			}
		}
	}
	return 0;
}

int poww() {
	for (i = 0; i < row; i++) {
		for (x = 0; x < ncol; x++) {
			matrix1[i][x] = matrix[i][x];

		}
	}
	ncol1 = ncol;
	row1 = row;
	for (y = 1; y < power; y++) {
		error = multiply(matrix, matrix1, row, row, ncol);
		for (i = 0; i < row; i++) {
			for (x = 0; x < ncol; x++) {
				matrix1[i][x] = result[i][x];

			}

		}
	}
	return 0;

}

int transpose(float matri[100][100], int r, int c) {
	for (i = 0; i < r; i++) {
		for (x = 0; x < c; x++) {
			result[x][i] = matri[i][x];

		}
	}
	int x = c;
	c = r;
	r = x;
	return r;
}

float towd(float dd[100][100], int r1, int r2, int c1, int c2) {
	float h = dd[r1][c1] * dd[r2][c2] - dd[r1][c2] * dd[r2][c1];
	return h;

}

float thrd(float ddd[100][100], int r1, int r2, int r3, int c1, int c2, int c3) {
	int x1, x2; float hh = 0;
	for (i = 0; i < 3; i++) {
		if (i == 0) { x = c1; x1 = c2; x2 = c3; }
		else if (i == 1) { x = c2;  x1 = c1; x2 = c3; }
		else if (i == 2) { x = c3;  x1 = c1; x2 = c2; }
		hh = hh + (ddd[r1][x] * towd(ddd, r2, r3, x1, x2)*pow(-1, i));

	}

	return hh;
}

int comat(float mtr[100][100], float mtr2[100][100]) {

	for (i = 0; i < 100; i++) {
		for (x = 0; x < 100; x++) {
			mtr2[i][x] = mtr[i][x];
		}
	}

	return 0;
}

float forth(float deto[100][100], int r1, int r2, int r3, int r4, int c1, int c2, int c3, int c4) { // A*[] -B*[]+c*[]-D*[]+E*[]
	int x, i, x1, x2, x3; float hhh = 0;
	for (i = 0; i < 4; i++) {
		if (i == 0) { x = c1;  x1 = c2; x2 = c3; x3 = c4; }
		else if (i == 1) { x = c2;  x1 = c1; x2 = c3; x3 = c4; }
		else if (i == 2) { x = c3;  x1 = c1; x2 = c2; x3 = c4; }
		else if (i == 3) { x = c4;  x1 = c1; x2 = c2; x3 = c3; }
		hhh = hhh + (deto[r1][x] * thrd(deto, r2, r3, r4, x1, x2, x3)* pow(-1, i));

	}

	return hhh;
}

float determ(float det[100][100], int r) { // A*[] -B*[]+c*[]-D*[]+E*[]
	if (r == 1) { fina = matrix[0][0]; }
	else if (r == 2) { fina = towd(det, 0, 1, 0, 1); }
	else if (r == 3) { fina = thrd(det, 0, 1, 2, 0, 1, 2); }
	else if (r == 4) { fina = forth(det, 0, 1, 2, 3, 0, 1, 2, 3); }

	else { fina = 0; }
	return fina;
}

int inverse(float inv[100][100], int dim) {
	float ftemp = determ(inv, dim);
	ftemp = 1 / ftemp;
	int col = 0;
	if (dim == 2) {
		for (int i = 0; i < 2; i++) {
			for (int x = 0; x < 2; x++) {
				result[i][x] = (ftemp * inv[1 - x][1 - i] * pow(-1, i + x));
			}
		}
	}

	else if (dim == 3) {
		for (int i = 0; i < 3; i++) {
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) { if (y == i) {} else { ch[col] = y; col++; } }
				for (y = 0; y < 3; y++) { if (y == x) {} else { ch[col] = y; col++; } }
				result[i][x] = ftemp * towd(inv, ch[0], ch[1], ch[2], ch[3])*pow(-1, i + x);

				col = 0;
			}

		}error = comat(result, dete);
		error = transpose(dete, dim, dim);
	}

	else if (dim == 4) {

		for (int ii = 0; ii < 4; ii++) {
			if (determ(inv, dim) == 0) { cout << "ERROR"; break; }

			for (int xx = 0; xx < 4; xx++) {
				for (y = 0; y < 4; y++) { if (y == ii) {} else { ch[col] = y; col++; } }
				for (y = 0; y < 4; y++) { if (y == xx) {} else { ch[col] = y; col++; } }
				result[ii][xx] = (ftemp * thrd(inv, ch[0], ch[1], ch[2], ch[3], ch[4], ch[5])*pow(-1, ii + xx));
				col = 0;
			}
		}comat(result, dete);
		error = transpose(dete, dim, dim);
	}

	else if (dim == 5) {
		for (int i = 0; i < dim; i++) {
			if (determ(inv, dim) == 0) { cout << "ERROR"; break; }

			for (int x = 0; x < dim; x++) {
				for (int y = 0; y < dim; y++) { if (y == i) {} else { ch[col] = y; col++; } }
				for (y = 0; y < dim; y++) { if (y == x) {} else { ch[col] = y; col++; } }
				result[i][x] = ftemp * forth(inv, ch[0], ch[1], ch[2], ch[3], ch[4], ch[5], ch[6], ch[7])*pow(-1, i + x);
				//cout << result[i][x] << " ";
				col = 0;
			}
		}comat(result, dete);
		error = transpose(dete, dim, dim);
	}

	return error;
}

int combmout(float mo[100][100],float im[100][100]) {
	ostringstream re;
	re<<'[';
	for (int i = 0; i < row; i++) {//rows
		for (int x = 0; x < ncol; x++) {// cols
			re << mo[i][x];
			if (im[i][x]>=0) { re << '+'; }
			else {}
			re << im[i][x];
			re << 'i';
			if (x != ncol - 1) { re << ' '; }
						
		}
		if (i != row - 1)re << ";";
	}
	re << "]";
	cout << re.str();
	return 0;
}

int mout(float mo[100][100]) {
	cout << "[";
	for (i = 0; i < row; i++) {
		for (x = 0; x < ncol; x++) {

			if (x == ncol - 1) { cout << mo[i][x]; }
			else { cout << mo[i][x] << " "; }
		}
		if (i != row - 1)cout << ";";
	}
	cout << "]";
	return 0;
}

int main() {

	getline(cin, mat); // getting mat as [1.2 3 5;4 5 6; 7 8 9]
	x = mat.length();
	error = entermat(matrix,comb,row,ncol);
	//mout(matrix);
	//mout(comb);
	if (error) { cout << "ERROR"; }// there is an Error in entering the matrix
	else {
		cin >> op;
		//cheking for operator
		if (op == '+') {
			// + entring another matrix 
			getline(cin, mat);
			getline(cin, mat);
			x = mat.length();
			error = entermat(matrix1,comb1,row1,ncol1);
			if (error) { cout << "ERROR"; }
			else {
				if ((ncol == ncol1) && (row == row1)) { error = pluss(comb, comb1); comat(result, resultcomb); pluss(matrix, matrix1); error = combmout(result,resultcomb); }// make adding op
				else { cout << "ERROR"; }

			}
		}

		else if (op == '-') {
			// + entring another matrix 
			getline(cin, mat);
			getline(cin, mat);
			x = mat.length();
			error = entermat(matrix1,comb1,row1,ncol1);
			if (error) { cout << "ERROR"; }
			else {
				if ((ncol == ncol1) && (row == row1)) { error = substract(comb, comb1); comat(result, resultcomb); substract(matrix, matrix1); error = combmout(result, resultcomb); }// make adding op
				else { cout << "ERROR"; }

			}
		}

		else if (op == '*') {
			// + entring another matrix 
			getline(cin, mat);
			getline(cin, mat);
			x = mat.length();
			error = entermat(matrix1,comb1,row1,ncol1);
			if (error) { cout << "ERROR"; }
			else {
				if (ncol == row1) { 
					error = multiply(matrix, comb1, row, row1, ncol1);
				    comat(result,resultcomb);
				    multiply(comb, matrix1, row, row1, ncol1);
				    comat(result, te);
				    pluss(resultcomb, te);
				    comat(result, resultcomb);
					error = multiply(comb, comb1, row, row1, ncol1);
					comat(result, te);
					multiply(matrix, matrix1, row, row1, ncol1);
					
					substract(result, te);
					
				ncol = ncol1; error = combmout(result,resultcomb); }// make adding op
				else { cout << "ERROR"; }

			}
		}

		else if (op == '^') {
			// + entring another matrix 
			cin >> power;

			if (0) { cout << "ERROR"; }
			else {
				if (ncol == row) { error = poww(); error = mout(result); }// make adding op
				else { cout << "ERROR"; }

			}
		}

		else if (op == 'T') {
			error = row;
			row = transpose(matrix, row, ncol); ncol = error; error = mout(result);

		}

		else if (op == 'D') {
			if (row != ncol) { cout << "ERROR"; }
			else { fina = determ(matrix, row); cout << fina; }

		}

		else if (op == 'I') {
			if (row != ncol || determ(matrix, row) == 0) { cout << "ERROR"; }
			else { inverse(matrix, row); mout(result); }

		}

		else if (op == '/') {
			// + entring another matrix 
			getline(cin, mat);
			getline(cin, mat);
			x = mat.length();
			error = entermat(matrix1,comb1,row1,ncol1);

			if (error) { cout << "ERROR"; }
			else {
				float foo = determ(matrix1, row1);
				if ((ncol == ncol1) && (row1 == ncol1)) {
					if (foo) {
						inverse(matrix1, row1);
						error = comat(result, matrix1);
						multiply(matrix, matrix1, row, row1, row1);
						error = mout(result);
					}
					else { cout << "ERROR"; }
				}

				else { cout << "ERROR"; }

			}
		}

		else { cout << "ERROR"; }//not operator



	}

	cin >> x;
	cin >> x;
	return 0;
}

