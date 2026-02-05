//Write  a  MPI  program  using  synchronous  send.  
//The  sender  process  sends  a  word  to  the receiver. 
//The second process receives the word, toggles each letter of the word and sends it back to the first process. 
//Both process use synchronous send operations.

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
int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char word[100];
    if(!rank){
        printf("Enter a word:\n");
        fflush(stdout);
        scanf("%s", word);
        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("P0: Sent %s to P1\n", word);
        fflush(stdout);
        MPI_Recv(word, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("P0: Received %s from P1\n", word);
        fflush(stdout);
    }
    else if(rank){
        MPI_Recv(word, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("P1: Received %s from P0\n", word);
        fflush(stdout);
        toggle(word);
        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("P1: Sent %s to P0\n", word);
    }
    MPI_Finalize();
    return 0;
}