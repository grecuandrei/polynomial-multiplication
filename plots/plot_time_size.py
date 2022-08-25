import matplotlib.pyplot as plt

def plot_all(x, y_secv_l, y_secv_f, y_mpi_l, y_mpi_f, y_openmp_l, y_openmp_f, y_pthreads_l, y_pthreads_f, y_hibrid_l, y_hibrid_f):
    if y_secv_l: plt.plot(x, y_secv_l, label="secv_l")
    if y_mpi_l: plt.plot(x, y_mpi_l, label="mpi_l")
    if y_openmp_l: plt.plot(x, y_openmp_l, label="openmp_l")
    if y_pthreads_l: plt.plot(x, y_pthreads_l, label="pthreads_l")
    if y_hibrid_l: plt.plot(x, y_hibrid_l, label="hibrid_l")
    if y_secv_f: plt.plot(x, y_secv_f, label="secv_f")
    if y_mpi_f: plt.plot(x, y_mpi_f, label="mpi_f")
    if y_openmp_f: plt.plot(x, y_openmp_f, label="openmp_f")
    if y_pthreads_f: plt.plot(x, y_pthreads_f, label="pthreads_f")
    if y_hibrid_f: plt.plot(x, y_hibrid_f, label="hibrid_f")
    plt.legend(loc="upper left")
    plt.xlabel('size of input')
    plt.ylabel('time (s)')
    plt.savefig('Comparison_all_time_size.png')
    plt.clf()

def plot_comp(x, y_secv, y_mpi, y_openmp, y_pthreads, y_hibrid, name):
    if y_secv: plt.plot(x, y_secv, label="secv")
    if y_mpi: plt.plot(x, y_mpi, label="mpi")
    if y_openmp: plt.plot(x, y_openmp, label="openmp")
    if y_pthreads: plt.plot(x, y_pthreads, label="pthreads")
    if y_hibrid: plt.plot(x, y_hibrid, label="hibrid")
    plt.legend(loc="upper left")
    plt.xlabel('size of input')
    plt.ylabel('time (s)')
    plt.savefig(name + '_comparison_time_size.png')
    plt.clf()

def plot_fig(x, y_l, y_f, name):
    plt.plot(x, y_l, "-b", label="local")
    plt.plot(x, y_f, "-r", label="fep")
    plt.legend(loc="upper left")
    plt.xlabel('size of input')
    plt.ylabel('time (s)')
    plt.savefig(name + '_time_size.png')
    plt.clf()

def main():
    x = [500, 1240, 10204, 50228, 100292]
    y_secv_l, y_secv_f, y_mpi_l, y_mpi_f, y_openmp_l, y_openmp_f, y_pthreads_l, y_pthreads_f, y_hibrid_l, y_hibrid_f = ([] for i in range(10))

    file_name = "input_time.in"
    f = open(file_name, "r")

    for line in f:
        if line == 'SECV\n':
            for i in range(5):
                y_secv_l.append(float(f.readline().rstrip()))
                y_secv_f.append(float(f.readline().rstrip()))
                f.readline()
            plot_fig(x, y_secv_l, y_secv_f, line.rstrip())
        if line == 'MPI\n':
            for i in range(5):
                y_mpi_l.append(float(f.readline().rstrip()))
                y_mpi_f.append(float(f.readline().rstrip()))
                f.readline()
            plot_fig(x, y_mpi_l, y_mpi_f, line.rstrip())
        if line == 'OPENMP\n':
            for i in range(5):
                y_openmp_l.append(float(f.readline().rstrip()))
                y_openmp_f.append(float(f.readline().rstrip()))
                f.readline()
            plot_fig(x, y_openmp_l, y_openmp_f, line.rstrip())
        if line == 'PTHREADS\n':
            for i in range(5):
                y_pthreads_l.append(float(f.readline().rstrip()))
                y_pthreads_f.append(float(f.readline().rstrip()))
                f.readline()
            plot_fig(x, y_pthreads_l, y_pthreads_f, line.rstrip())
        if line == 'HIBRID\n':
            for i in range(5):
                y_hibrid_l.append(float(f.readline().rstrip()))
                y_hibrid_f.append(float(f.readline().rstrip()))
                f.readline()
            plot_fig(x, y_hibrid_l, y_hibrid_f, line.rstrip())

    plot_comp(x, y_secv_l, y_mpi_l, y_openmp_l, y_pthreads_l, y_hibrid_l, 'local')
    plot_comp(x, y_secv_f, y_mpi_f, y_openmp_f, y_pthreads_f, y_hibrid_f, 'fep')

    plot_all(x, y_secv_l, y_secv_f, y_mpi_l, y_mpi_f, y_openmp_l, y_openmp_f, y_pthreads_l, y_pthreads_f, y_hibrid_l, y_hibrid_f)

    f.close()

main()