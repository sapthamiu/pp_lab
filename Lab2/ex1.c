//synch send: sender sends word, receiver receives, toggles each letter, sends back
//Sapthami Upadhya 
//16 Jan 2026
#include<mpi.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
void toggle(char* word){
	for(int i = 0; i < strlen(word); i++){
		if(islower(word[i])) word[i] = toupper(word[i]);
		else if(isupper(word[i])) word[i] = tolower(word[i]);
	}
}
int main(int argc, char* argv[]){
	int rank, size;
	char word[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank == 0){
		printf("Enter a word to send: ");
		scanf("%s", word);
		MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
		printf("Process 0: Sent the word '%s'\n", word);
		fflush(stdout);
		MPI_Recv(word, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process 0: Received the toggled word '%s'\n", word);
		fflush(stdout);
	}
	else{
		MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process 1: Received the word '%s'\n", word);
		fflush(stdout);
		toggle(word);
		MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		printf("Process 1: Sent the toggled word '%s'\n", word);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}