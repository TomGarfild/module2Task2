#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

struct complex {
	//x = a*i+b;
	double a=0, b=0;
};
complex addC(complex x, complex y) {
	complex z;
	z.a = x.a + y.a;
	z.b = x.b + y.b;
	return z;
}
complex mulC(complex x, complex y) {
	complex z;
	z.a = x.a * y.b + y.a * x.b;
	z.b = x.b * y.b - x.a * y.a;
	return z;
}
complex mulCConst(complex x, int y) {
	return {x.a*y, x.b*y};
}
complex powC(complex x, int c) {
	complex z;
	if (c == 0) { z.a = 0; z.b = 1; }
	else {
		z.a = 0; z.b = 1;
		for (int i = 0; i < c; ++i) {
			z = mulC(z, x);
		}
	}
	return z;
}
void printC(complex x) {
	if (x.a != 0) {
		if (abs(x.a - 1) > 0.00000001) cout << x.a;
		cout << "i";
		if (x.b < 0) cout << x.b;
		else if (x.b > 0) cout << "+" << x.b;
	}
	else {
		cout << x.b << " ";
	}
	cout << " ";
}
int main() {
	const int MAX_LENGTH = 2000;
	complex x;
	cin >> x.a >> x.b;	
	FILE* fr;
	if ((fr = fopen("input.txt", "r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	char str[2000];
	vector<vector<complex>> m;
	vector<string> parse;
	while (fgets(str, MAX_LENGTH, fr) != NULL) {
		parse.push_back(str);
		int p = 0;
		for (int i = 0; i < strlen(str); ++i) {
			if (str[i] == 'x') {
				if (i + 1 != strlen(str)) {
					if (str[i + 1] != '^') {
						p = 1; break;
					}
					i += 2;
					while (i < strlen(str) && str[i]>='0' && str[i] <= '9') {
						p *= 10; p += (int)(str[i] - '0'); ++i;
					}
				}
				else p = 1;
				break;
			}
		}
		m.push_back(vector<complex>(p+1));
	}
	for (int k = 0; k < parse.size(); ++k) {
		string str = parse[k];
		complex n;
		bool signBefore = false;
		for (int i = 0; i < str.size(); ++i) {
			double num = 0, d = 0; bool sign = false;
			if (str[i] == '-') {
				if (str[i + 1] == '(') {
					signBefore = true;
				}
				else {
					sign = true;
				}
				++i;
			}
			else if (str[i] == '+')  i ++;
			while (str[i] <= '9' && str[i] >= '0') {
				num *= 10;
				num += (int)(str[i] - '0');
				++i;
			}
			if (str[i] == '.') {
				++i;
				while (str[i] <= '9' && str[i] >= '0') {
					d++;
					num *= 10;
					num += (int)(str[i] - '0');
					++i;
				}
				num /= pow(10, d);
			}
			if (str[i] == 'i') {
				if (num == 0) num = 1;
				n.a =  num * (sign ? -1 : 1) * (signBefore ? -1 : 1); i++;
			}
			else {
				n.b = num * (sign ? -1 : 1) * (signBefore ? -1 : 1);
			}
			if (str[i] != ')') continue;
			i += 2;
			if (i >= str.size()) {
				m[k][0] = n;
			}
			else if (i + 1 == str.size()) {
				m[k][1] = n;
			}
			else {
				int p = 0;
				i += 2;
				while (i < str.size() && str[i] >= '0' && str[i] <= '9') {
					p *= 10; p += (int)(str[i] - '0'); ++i;
				}
				if (p == 0) {
					p = 1; i--;
				}
				m[k][p] = n;
				i--;
			}
			signBefore = false;
			n.a = 0; n.b = 0;
		}
	}
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			complex k;
			vector<complex> temp(m[j]);
			for (int l = 0; l < temp.size(); ++l) {
				if (l - i >= 0) {
					k = addC(k, mulC(temp[l], powC(x, l - i)));
					m[j][l] = mulCConst(temp[l], l-i);
				}
			}
			printC(k);
		}
		cout << "\n";
	}
	return 0;
}