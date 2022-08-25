    Tema 1 & 2 & 3 SM

# Problema

    Inmultirea de polinoame si evaluarea rezultatului inmultirii

    Paralelizarea s-a facut strict pe operatiile care ne intereseaza pentru a nu aduce un overhead mare

# Compilare

    SECVENTIAL: g++ seq.cpp -o seq
    
    PTHREAD: g++ pthreads.cpp -o pthreads -Wall -lpthread -lm
    
    OpenMP: g++ openmp.cpp -o openmp -fopenmp -lm
    
    MPI: mpiCC mpi.cpp -o mpi ; mpirun -np 4 mpi
    
    HIBRID: mpiCC hibrid.cpp -o hibrid -fopenmp -lm ; mpirun -np 4 hibrid

# Precizare

    Toate implementarile paralele s-au rulat cu 4 thread-uri.
    Pentru a testa exercitiile au fost folosite inputuri speciale.
    Motivul a fost evaluarea si functionarea corecta a implementarii in MPI si cea Hibrida.

    Exemplul din fisierul input.in:
    4 - numar coeficienti primului polinom (TREBUIE sa fie multiplu de numar de thread-uri)
    1 0 -1 0 - coeficientii
    5 - numar coeficienti al doilea polinom (TREBUIE sa fie multiplu de numar de thread-uri + 1)
    1 2 3 4 5 - coeficienti
    1 - valoarea pentru evaluarea rezultatului inmultirii

Measurements (Time / SpeedUp):

    Local:
        input_500_505.in:
            seq:        0.00087 s
            pthreads:   0.05820 s / s = 0.01494
            openmp:     0.00144 s / s = 0.60416
            mpi:        0.00055 s / s = 1.58181
            hibrid:     0.03810 s / s = 0.02283

        input_1240_1357.in:
            seq:        0.00562 s
            pthreads:   0.34856 s / s = 0.01612
            openmp:     0.01250 s / s = 0.4496
            mpi:        0.00240 s / s = 2.34166
            hibrid:     0.04369 s / s = 0.12863

        input_10204_10113.in
            seq:        0.28626 s
            pthreads:  20.73774 s / s = 0.01380
            openmp:     1.00000 s / s = 0.28626
            mpi:        0.12301 s / s = 2.32712
            hibrid:     0.14095 s / s = 2.03093

        input_50228_50281.in
            seq:        7.62521 s
            pthreads: 512.00000 s / s = 0.01489
            openmp:    23.09023 s / s = 0.33023
            mpi:        2.67816 s / s = 2.84718
            hibrid:     2.52593 s / s = 3.01877

        input_100292_100197.in
            seq:       28.42041 s
            pthreads:2168.40000 s / s = 0.01310
            openmp:    13.58076 s / s = 2.09269
            mpi:       10.33391 s / s = 2.75020
            hibrid:     9.84712 s / s = 2.88616     

    Solaris:
    	input_500_505.in:
            seq:        0.014 s
            pthreads:   1.799 s / s = 0.007
            openmp:     0.005 s / s = 2.8
            mpi:        1.884 s / s = 0.007
            hibrid:     1.633 s / s = 0.007

        input_1240_1357.in:
            seq:        0.022 s
            pthreads:   0.197 s / s = 0.111
            openmp:     0.008 s / s = 2.75
            mpi:        2.142 s / s = 0.010
            hibrid:     1.736 s / s = 0.012

        input_10204_10113.in
            seq:        0.723 s
            pthreads:  10.997 s / s = 0.065
            openmp:     0.267 s / s = 2.707
            mpi:        2.556 s / s = 0.282
            hibrid:     0.096 s / s = 7.531

        input_50228_50281.in
            seq:       16.969 s
            pthreads: > 111.0 s / s < 0
            openmp:     4.991 s / s = 3.4
            mpi:        5.802 s / s = 2.924
            hibrid:     1.850 s / s = 9.172

        input_100292_100197.in
            seq:       67.580 s
            pthreads: > 350.0 s / s < 0
            openmp:     3.071 s / s = 22.005
            mpi:       18.121 s / s = 3.729
            hibrid:     2.730 s / s = 24.754
            
            
            
            
            
            
