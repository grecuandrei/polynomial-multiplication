#include <iostream>
#include <pthread.h>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>

#define MAX_THREAD 4
  
using namespace std;
  
signed long *a, *b, *c;
signed long result = 0;
pthread_mutex_t lockk;
pthread_barrier_t barrier;

struct Args {
    int n, m, id, x;
};
  
void* prod(void* arg)
{
    struct Args *thread_arg = (struct Args*)arg;

    int start = thread_arg->id * (double)thread_arg->n / MAX_THREAD;
    int end = min((thread_arg->id + 1) * (double)thread_arg->n / MAX_THREAD, (double)thread_arg->n);
  
    for (int i = start; i < end; i++)
        for (int j = 0; j < thread_arg->m; j++) {
            pthread_mutex_lock(&lockk);
            c[i+j] += a[i]*b[j];
            pthread_mutex_unlock(&lockk);
        }

    start = thread_arg->id * (double)(thread_arg->n + thread_arg->m - 1) / MAX_THREAD;
    end = min((thread_arg->id + 1) * (double)(thread_arg->n + thread_arg->m - 1) / MAX_THREAD, (double)(thread_arg->n + thread_arg->m - 1));
    pthread_barrier_wait (&barrier);

    for (int i = start; i < end; i++) {
        pthread_mutex_lock(&lockk);
        result += c[i] * pow(thread_arg->x, i);
        pthread_mutex_unlock(&lockk);
    }
    
    return NULL;
}
  
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


int main(int argc, char *argv[])
{
    clock_t start, end;
    int n, m, x;
    ifstream fin(argv[1]);
    
    fin>>n;
    a = new signed long[n];
	for (int i = 0; i < n; i++) {
		fin>>a[i];
	}
    
    fin>>m;
    b = new signed long[m];
	for (int i = 0; i < m; i++) {
		fin>>b[i];
	}

    if (pthread_mutex_init(&lockk, NULL) != 0 || pthread_barrier_init (&barrier, NULL, MAX_THREAD) != 0) {
        printf("\n mutex or barrier init has failed\n");
        return 1;
    }

    pthread_t threads[MAX_THREAD];
    Args *thread_arg;
    thread_arg = (Args*) malloc(MAX_THREAD*sizeof(Args));

    // cout << "First ";
    // printPoly(a, n);
    // cout << "\nSecond ";
    // printPoly(b, m);

    fin>>x;

    c = new signed long[m+n-1];

    start = clock();
  
    for (int i = 0; i < MAX_THREAD; i++) {
        (thread_arg + i)->id = i;
        (thread_arg + i)->x = x;
        (thread_arg + i)->m = m;
        (thread_arg + i)->n = n;
        pthread_create(&threads[i], NULL, prod, (void*)(thread_arg+i));
    }

    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "\nTime taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    
    // cout<<"\nProduct \n";
    // printPoly(c, m + n - 1);
    // cout<<endl<<"Eval: "<<result<<endl;
    
    pthread_mutex_destroy(&lockk);

    free(a);
    free(b);
    free(c);
    free(thread_arg);
  
    return 0;
}