/**/

//headers
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string>
#include<cmath>
using namespace std;

//read
void read(float ** result, int& row, int& col) {
	char arr[10010];
	cin.getline(arr, 10010);
	string cur_fl = "";
	int cur_row = 0, cur_col = 0;
	for (int i = 1; i < (int)sizeof(arr); i++) {
		if (arr[i] == ';') {
			if (cur_fl != "")
				result[cur_row][cur_col] = atof(cur_fl.c_str());
			cur_fl = "";
			cur_col = 0;
			cur_row++;
		}
		else if (arr[i] == ' ') {
			if (cur_fl != "")
				result[cur_row][cur_col++] = atof(cur_fl.c_str());
			cur_fl = "";
		}
		else if (arr[i] == ']') {
			if (!cur_fl.empty())
				result[cur_row][cur_col] = atof(cur_fl.c_str());
			break;
		}
		else {
			cur_fl += arr[i];
		}
	}
	row = cur_row;
	col = cur_col;
}


//output
void print(float ** arr, int row, int col) {
	cout << "[";
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			cout << arr[i][j];
			if (j != col)cout << " ";
		}
		if (i != row)cout << ';';
	}
	cout << "]";
}

//plus
float ** add(float ** arr1, float ** arr2, int row, int col) {
	float ** result = new float*[row + 1];
	for (int i = 0; i <= row; i++) {
		result[i] = new float[col + 1];
		for (int j = 0; j <= col; j++) {
			result[i][j] = arr1[i][j] + arr2[i][j];
		}
	}
	return result;
}

//minus
float ** subtract(float ** arr1, float ** arr2, int row, int col)
{
	float **result = new float*[row + 1];
	for (int i = 0; i <= row; i++) {
		result[i] = new float[col + 1];
		for (int j = 0; j <= col; j++) {
			result[i][j] = arr1[i][j] - arr2[i][j];
		}
	}
	return result;
}

//multiply
float ** mul(float ** arr1, float ** arr2, int row1, int row2, int col1, int col2) {
	float ** result = new float*[row1 + 1];
	for (int i = 0; i <= row1; i++) {
		result[i] = new float[col2 + 1];
		for (int j = 0; j <= col2; j++) {
			result[i][j] = 0.f;
			for (int k = 0; k <= col1; k++) {
				result[i][j] += arr1[i][k] * arr2[k][j];
			}
		}
	}
	return result;
}

//transpose
float ** trans(float ** arr, int row, int col) {
	float ** result = new float*[row + 1];
	for (int i = 0; i <= col; i++) {
		result[i] = new float[col + 1];
		for (int j = 0; j <= row; j++) {
			result[i][j] = arr[j][i];
		}
	}

	return result;
}

//power - binary exponent
float ** fastpower(float ** arr, int row, int col, int power) {
	float ** result = new float*[row + 1];
	for (int i = 0; i <= row + 1; i++) {
		result[i] = new float[col + 1];
		for (int j = 0; j <= col; j++)
			result[i][j] = 0;
		result[i][i] = 1; //identity
	}
	while (power > 0) {
		if (power % 2 == 1) {
			power -= 1;
			result = mul(result, arr, row, row, col, col);
		}
		else {
			power /= 2;
			arr = mul(arr, arr, row, row, col, col);
		}
	}
	return result;
}

//////////determinate
float det(float ** arr, int row) {
	float result = 1.0;
	// eleminat under 1st col eleminate under 1st row
	for (int e = 0; e < row; e++) {
		for (int i = e + 1; i <= row; i++) {
			float f = arr[i][e] / arr[e][e];
			for (int j = 0; j <= row; j++) {
				arr[i][j] = arr[i][j] - f*arr[e][j];
			}
		}
	}
	// eleminat under 2nd col
	/*	for (int i = 2; i <= row; i++) {
	float f = arr[i][1] / arr[1][1];
	for (int j = 0; j <= row; j++) {
	arr[i][j] = arr[i][j] - f*arr[1][j];
	}
	}
	*/
	for (int i = 0; i <= row; i++) {
		result = result * arr[i][i];
	}


	return result;
}
//////////inverse
int i, j, k;
float  d;
float ** inv(float ** arr, int row, int col) {
	float ** result = new float*[row + 1];
	float ** a = new float*[row + 1];
	float f = 1.000001;
	// I matrix
	for (i = 0; i <= row; i++)
	{
			a[i] = new float[row + 1];
		for (j = 0; j <= row; j++)
		{
			a[i][j] = arr[i][j];
		}
	}
	
	if (!det(a, row)) { cout << "ERROR"; return NULL; }
	for (i = 0; i <= row; i++)
	{
		result[i] = new float[col + 1];
		for (j = 0; j <= row; j++)
		{
			if (i == j) { result[i][j] = 1; }
			else result[i][j] = 0;
		}
	}

////	
	for (int e = 0; e < row; e++) {
		for (int i = e + 1; i <= row; i++) {
					f = arr[i][e] / arr[e][e];
					for (int j = 0; j <= row; j++) {
						result[i][j] -= result[e][j] * f;
						arr[i][j] = arr[i][j] - f*arr[e][j];

					}
				}
}



	
	for (int e = row; e >0; e--) {
		for (int i = e - 1; i >= 0; i--) {
			f = arr[i][e] / arr[e][e];
			for (int j = 0; j <= row; j++) {
				arr[i][j] = arr[i][j] - f*arr[e][j];
				result[i][j] = result[i][j] - f*result[e][j];
			}
		}
	}
	//////////
	for (int i = 0; i <= row; i++) {
		f = arr[i][i];
		for (int j = 0; j <= row; j++) {
			arr[i][j] = arr[i][j] / f;
			result[i][j] = result[i][j] / f;
		}
	}
	
	////////

	return result;
}
////////divide
float ** div(float ** arr1, float ** arr2, int row1, int row2, int col1, int col2) {
	float ** result = new float*[row1 + 1];
	result = mul(arr1, inv(arr2, row2, col2), row1, row2, col1, col2);
	return result;
}





//main
int main() {
	float **arr1, **arr2;
	float ** result;
	arr1 = new float *[100];
	arr2 = new float *[100];
	for (int i = 0; i < 100; i++) {
		arr1[i] = new float[100];
		arr2[i] = new float[100];
	}
	int arr1_rows = 0, arr1_col = 0;
	int arr2_rows = 0, arr2_col = 0;
	char op;
	//cout<<"Please enter the first matrix: ";
	read(arr1, arr1_rows, arr1_col);
	/*cout<<"Enter:\n"<<
	"1. * to multiply to two matrices.\n"<<
	"2. + to add the two matrices.\n"<<
	"3. - to subtract.\n" <<
	"4. T for transpose.\n"<<
	"5. ^ for exponent.\n" <<
	"6. any other key to exit.\n";*/

	cin >> op;
	cin.ignore();
	int row, col;

	if (op == '+') {
		//cout<<"Please enter the second matrix: ";
		read(arr2, arr2_rows, arr2_col);
		if (arr1_rows == arr2_rows && arr1_col == arr2_col)
			result = add(arr1, arr2, arr1_rows, arr1_col); else { cout << "ERROR"; return 0; }
		row = arr1_rows;
		col = arr2_col;
		print(result, row, col);
	}

	if (op == '-') {
		//cout<<"Please enter the second matrix: ";
		read(arr2, arr2_rows, arr2_col);
		if (arr1_rows == arr2_rows && arr1_col == arr2_col)
			result = subtract(arr1, arr2, arr1_rows, arr1_col); else { cout << "ERROR"; return 0; }
		row = arr2_rows;
		col = arr2_col;
		print(result, row, col);
	}

	else if (op == '*') {
		//cout<<"Please enter the second matrix: ";
		read(arr2, arr2_rows, arr2_col);
		if (arr1_col == arr2_rows)
			result = mul(arr1, arr2, arr1_rows, arr2_rows, arr1_col, arr2_col); else { cout << "ERROR"; return 0; }
		row = arr1_rows;
		col = arr2_col;
		print(result, row, col);
	}

	if (op == 'T') {
		result = trans(arr1, arr1_rows, arr1_col);
		row = arr1_col;
		col = arr1_rows;
		print(result, row, col);
	}

	if (op == '^') {
		int power;
		cin >> power;
		if (power < 0 || arr1_rows != arr1_col) {
			cout << "ERROR";
		}
		else {
			result = fastpower(arr1, arr1_rows, arr1_col, power);
			row = arr1_rows;
			col = arr1_col;
			print(result, row, col);
		}
	}

	if (op == 'D') {
		if (arr1_col == arr1_rows)
		{
			float de = det(arr1, arr1_rows); cout << de;
		}
		else { cout << "ERROR"; return 0; }
		row = arr1_rows;
		col = arr1_col;
	}
	if (op == 'I') {
		result = inv(arr1, arr1_rows, arr1_col);
		row = arr1_col;
		col = arr1_rows;
		print(result, row, col);
	}
	if (op == '/') {
		read(arr2, arr2_rows, arr2_col);
		if (arr1_col == arr2_rows)
			result = div(arr1, arr2, arr1_rows, arr2_rows, arr1_col, arr2_col); else { cout << "ERROR"; return 0; }
		row = arr1_rows;
		col = arr2_col;
		print(result, row, col);
	}


	cin >> col;
	cin >> col;
	return 0;
}
