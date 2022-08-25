#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

// A utility function to print a polynomial
void printPoly(signed long poly[], int n) {
	for (int i = 0; i < n; ++i)	{
		if (poly[i] != 0) {
			cout << static_cast<int>(poly[i]);
			if (i != 0)
				cout << "x^" << i;
            if (i < n - 1) {
                if (poly[i + 1] > 0) {
				    cout << " + ";
                } else {
                    cout<< " ";
                }
            }
		}
	}
}

int main(int argc, char** argv) {
	omp_set_num_threads(4);
	clock_t start, end;
	int i, j, x;
	ifstream fin(argv[1]);

    signed long *A;
	int n;

	fin>>n;
	A = (signed long *) malloc(n*sizeof(signed long));
	for (i = 0; i < n; ++i) {
		fin>>A[i];
	}

	signed long *B;
	int m;
	
	fin>>m;
	B = (signed long *) malloc(m*sizeof(signed long));
	for (i = 0; i < m; ++i) {
		fin>>B[i];
	}

	// cout << "First ";
	// printPoly(A, n);
	// cout << "\nSecond ";
	// printPoly(B, m);

    signed long *C = new signed long[m + n - 1];

	start = clock();

    #pragma omp parallel for shared(A, B, C) private(i, j) collapse(2)
        for (i = 0; i < m; ++i)
        {
            for (j = 0; j < n; ++j)
            {
				#pragma omp atomic
                C[i+j] += B[i] * A[j];
            }
        }

    // cout << "\nProduct \n";
    // printPoly(C, n + m -1);

	signed long result = 0;
	fin>>x;

	#pragma omp parallel for shared(C, result, x) private(i)
		for (i = n + m - 2; i >= 0; --i)
		{
			#pragma omp critical
        	result += C[i] * pow(x, i);
		}

	end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "\nTime taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;

	// cout<<"\nEval: "<<result<<endl;

	free(A);
	free(B);
	free(C);
    
    return 0;
}