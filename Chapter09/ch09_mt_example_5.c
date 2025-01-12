#include <stdio.h>
#include <openmpi/mpi.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int numprocs, rank, len;
    char procname[MPI_MAX_PROCESSOR_NAME];
    int tnum = 0, tc = 1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(procname, &len);

    #pragma omp parallel default(shared) private(tnum, tc) 
    {
        int np;                        // 변수 선언
        np = omp_get_num_threads();    // 초기화
        tnum = omp_get_thread_num();   // 이후 사용
        printf("Thread %d out of %d from process %d out of %d on %s\n",
               tnum, np, rank, numprocs, procname);  // 출력에서 np 사용
    }

   MPI_Finalize();
}

/*┌──(kali㉿kali)-[~/Documents/C-programming/Multithreading_CPP/Chapter09]
└─$ mpicc -fopenmp ch09_mt_example_5.c -o ch09_5
*/