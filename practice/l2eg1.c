//Write a MPI program using standard send. 
//The sender process sends a number to the receiver. 
//The second process receives the number and prints it. 

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n;
    if(rank==0){
        printf("Enter a number:\n");
        fflush(stdout);
        scanf("%d", &n);
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("P0: Sent %d to P1\n", n);
        fflush(stdout);
    }
    else if(rank == 1){
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("P1: Received %d from P0\n", n);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}