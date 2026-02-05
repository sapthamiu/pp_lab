//Write a MPI program where the master process (process 0) sends a number to each of the slaves and the slave processes receives the number and prints it. Use standard send. 
#include<stdio.h>
#include<mpi.h>
int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n;
    if(!rank){
        printf("Enter the number:\n");
        fflush(stdout);
        scanf("%d", &n);
        for(int i = 0; i < size; i++)
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        printf("P0: Sent %d\n", n);
        fflush(stdout);
    }
    else{
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("P%d: Received %d\n", rank, n);
    }
    MPI_Finalize();
    return 0;
}