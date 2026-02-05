//std send: sender sends number, receivers receive and print the number
//Sapthami Upadhya 
//16 Jan 2026
#include<mpi.h>
#include<stdio.h>
int main(int argc, char* argv[]){
	int rank, size, num1;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0){
		printf("Enter the number to send: ");
		scanf("%d", &num1);
		for(int i = 1; i < size; i++){
			MPI_Send(&num1, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Process 0: Sent the number %d to process %d\n", num1, i);
		}
	}
	else{
		int num2;
		MPI_Recv(&num2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d: Received the number %d\n", rank, num2);
	}
	MPI_Finalize();
	return 0;
}