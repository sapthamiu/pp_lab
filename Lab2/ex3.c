//buf send: sender reads an array, sends one element each to receivers, 
//even receiver finds square of the number, odd receiver finds cube of the number
//Sapthami Upadhya 
//16 Jan 2026
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int data[5];	
	int buf_size = MPI_BSEND_OVERHEAD + sizeof(int);
	void* buf = malloc(buf_size);
	MPI_Buffer_attach(buf, buf_size);

	if(rank == 0){
		printf("Enter the %d array elements: ", size);
		fflush(stdout);

		for(int i = 0; i < size; i++)
			scanf("%d", &data[i]);
		for(int i = 1; i < size; i++){
			MPI_Bsend(&data[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Process 0: Sent %d to process %d\n", data[i], i);
			fflush(stdout);
		}
		printf("Process 0: Square of %d = %d\n", data[0], data[0]*data[0]);
		fflush(stdout);

	}
	else{
		int num;
		MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d: Received %d\n", rank, num);
		fflush(stdout);

		if(rank % 2)//odd
			printf("Process %d: Cube of %d = %d\n", rank, num, num*num*num);
		else 
			printf("Process %d: Square of %d = %d\n", rank, num, num*num);
		fflush(stdout);
	}
		
	MPI_Buffer_detach(&buf, buf_size);
	free(buf);
	MPI_Finalize();
	return 0;
}