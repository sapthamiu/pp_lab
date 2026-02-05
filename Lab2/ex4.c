//std send: root reads n, sends n+1 to process 1, process sends n+2 to process 2 and so on,
//process p sends n+p to root
//Sapthami Upadhya 
//16 Jan 2026
#include<mpi.h>
#include<stdio.h>
int main(int argc, char* argv[]){
	int rank, size, num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0){
		printf("Enter a number: ");
		fflush(stdout);
		scanf("%d", &num);
		MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Process 0: Sent %d to process 1\n", num);
		fflush(stdout);
		MPI_Recv(&num, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process 0: Received %d from process %d\n", num, size-1);	
		fflush(stdout);

	}
	else if(rank > 0 && rank < size-1){
		MPI_Recv(&num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d: Received %d from process %d\n", rank, num, rank-1);	
		fflush(stdout);
		num++;
		MPI_Send(&num, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
		printf("Process %d: Sent %d to process %d\n", rank, num, rank+1);	
		fflush(stdout);
	}
	else{
		MPI_Recv(&num, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d: Received %d from process %d\n", rank, num, rank-1);	
		fflush(stdout);
		num++;
		MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("Process %d: Sent %d to process 0\n", rank, num);	
		fflush(stdout);

	}
	MPI_Finalize();
	return 0;
}