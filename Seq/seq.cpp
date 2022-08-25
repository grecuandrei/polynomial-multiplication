#include <iostream>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

signed long *multiply(signed long A[], signed long B[], int n, int m) {
	signed long *prod = new signed long[m+n-1];

	for (int i = 0; i<m+n-1; ++i)
		prod[i] = 0;

	for (int i=0; i<m; ++i) {
		for (int j=0; j<n; ++j)
			prod[i+j] += B[i]*A[j];
	}
	
	return prod;
}

void printPoly(signed long poly[], int n) {
	for (int i=0; i<n; ++i) {
		if (poly[i] != 0) {
			cout << static_cast<long>(poly[i]);
			if (i != 0)
				cout << "x^" << i ;
            if (i != n-1) {
                if (poly[i+1] > 0) {
				    cout << " + ";
                } else {
                    cout<< " ";
                }
            }
		}
	}
}

signed long horner(signed long poly[], int n, signed long x) {
    signed long result = 0;
 
    for (int i=n-1; i>=0; --i)
        result += poly[i] * pow(x, i);
 
    return result;
}

int main(int argc, char *argv[]) {
	clock_t start, end;
	signed long *A;
	int n;
	ifstream fin(argv[1]);

	fin>>n;
	A = (signed long *) malloc(n*sizeof(signed long));
	for (int i = 0; i < n; i++) {
		fin>>A[i];
	}

	signed long *B;
	int m;
	fin>>m;
	B = (signed long *) malloc(m*sizeof(signed long));
	for (int i = 0; i < m; i++) {
		fin>>B[i];
	}

	// cout << "First ";
	// printPoly(A, n);
	// cout << "\nSecond ";
	// printPoly(B, m);

	start = clock();

	signed long *prod = multiply(A, B, n, m);

	// cout << "\nProduct \n";
	// printPoly(prod, m+n-1);

	signed long x;
	fin>>x;

	horner(prod, n+m-1, x);
	// cout<<"\nEval: "<<horner(prod, n+m-1, x)<<endl;

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;

	free(A);
	free(B);

	return 0;
}