#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <fstream>

#define CHUNK 10
#define ROOT 0

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

int main (int argc, char **argv) {
    int rank, proc, a, x;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc);

    signed long *A = NULL, *B = NULL;
    int n = 0, m = 0;

    ifstream fin(argv[1]);

    if (rank == ROOT) {
        while(n < proc) {
            fin>>n;
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    A = (signed long *) calloc(n, sizeof(signed long));

    if (rank == ROOT) {
        for (int i = 0; i < n; i++) {
            fin>>A[i];
        }
        fin>>m;
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    B = (signed long *) calloc(m, sizeof(signed long));

    if (rank == ROOT) {
        for (int i = 0; i < m; i++) {
            fin>>B[i];
        }

        // cout << "First ";
        // printPoly(A, n);
        // cout << "\nSecond ";
        // printPoly(B, m);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int i, j;

    double start = MPI_Wtime();

    MPI_Bcast(B, m, MPI_LONG, 0, MPI_COMM_WORLD);

    int parts_size = n / proc;
    signed long *A_parts = (signed long *) calloc(parts_size, sizeof(signed long));

    MPI_Scatter(A, parts_size, MPI_LONG, A_parts, parts_size, MPI_LONG, 0, MPI_COMM_WORLD);

    signed long *C_parts = (signed long *)calloc((n+m-1), sizeof(signed long));
    #pragma omp parallel for shared(A, B, C_parts) private(i, j) collapse(2)
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < parts_size; j++)
            {
                C_parts[i+j+rank] += B[i]*A_parts[j];
            }
        }

    if (rank == ROOT) {
        signed long *C = (signed long *)calloc((n+m-1), sizeof(signed long));
        #pragma omp parallel for shared(C_parts, C) private(i, j)
            for (i = 1; i < proc; i++)
            {
                MPI_Recv(C, n+m-1, MPI_LONG, i, 0, MPI_COMM_WORLD, NULL);
                #pragma omp parallel for shared(C_parts, C) private(i, j)
                for (j = 0; j < n+m-1; j++)
                {
                    C_parts[j] += C[j];
                }
            }
        free(C);
    } else {
        MPI_Send(C_parts, n+m-1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }

    free(A_parts);
    A_parts = NULL;

    if (rank == ROOT) {
        // cout<<"\nProduct \n";
        // printPoly(C_parts, n+m-1);
        // cout<<"\n";
    }


    // polynom eval
    if (rank == ROOT) {
        fin>>x;
    }
    MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

    parts_size = (n + m - 1) / proc;
    A_parts = (signed long *) calloc(parts_size, sizeof(signed long));
    MPI_Scatter(C_parts, parts_size, MPI_LONG, A_parts, parts_size, MPI_LONG, 0, MPI_COMM_WORLD);
    
    long result = 0;
    #pragma omp parallel for shared(A_parts, result, x) private(i)
        for (i = 0; i < parts_size; i++)
        {
            #pragma omp critical
            result += A_parts[i] * pow(x, i + rank*2);
        }

    long final_result = 0;
    MPI_Reduce(&result, &final_result, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == ROOT) {
        printf("mpi: %f s\n", end - start);
        // cout<<"Eval: "<<final_result<<endl;
    }

    free(A);
    free(B);
    free(A_parts);
    free(C_parts);

    MPI_Finalize();
    return 0;
}