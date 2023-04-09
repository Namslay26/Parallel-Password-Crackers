#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 50
#define MAX_PASSWORD_LENGTH 100

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char password[MAX_PASSWORD_LENGTH];
    char word[MAX_WORD_LENGTH];
    bool password_found = false;
    int i, j;
    char slen [16];
    int length = 0;
    char buf[512];

    // Rank 0 reads the password from the command line
    if (rank == 0) {
        if (argc < 2) {
            printf("Usage: %s <password>\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        strncpy(password, argv[1], MAX_PASSWORD_LENGTH);
        password[MAX_PASSWORD_LENGTH-1] = '\0';
    }

    // Broadcast the password to all processes
    MPI_Bcast(password, MAX_PASSWORD_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);

    char dictname[255];
    sprintf (dictname, "dictionary_%d.txt", (int) strlen(password));

    // Open the dictionary file
    FILE* dictionary_file = fopen(dictname, "r");
    if (dictionary_file == NULL) {
       // if that length dictionary doesnt exist
       sprintf (buf, "cat dictionary.txt | awk \'length==%d\' > dictionary_%d.txt", (int) strlen(password));
       system (buf);
       FILE* dictionary_file = fopen(dictname, "r");
       if (dictionary_file == NULL) {
          printf("Error: could not open dictionary file\n");
          MPI_Abort(MPI_COMM_WORLD, 1);
       }
    }

    // compute the number of lines in the dictionary
    sprintf (buf, "wc -l dictionary_%d.txt", (int) strlen(password));
    FILE *pcmd = popen (buf, "r");
    fscanf (pcmd,"%s", slen);
    printf ("%d: dict length:%s\n", rank, slen);
    fclose (pcmd);
    length = atoi (slen);

 
    printf ("rank %d seeking %s\n", rank, dictname);

    // compute the offset from the start of the dictionary file in bytes
    // compute the iterations to perform from that offset
    // offset is based on rank,
    // rank 0 -> first chunk, rank 1> second ..
    // iteration is number of lines in chunk
    int startloc =rank * (strlen (password) + 2) *(length / size);
    int iteration =  length / size; 

    // Each process reads and compares a chunk of words from the dictionary
    fseek(dictionary_file, startloc, SEEK_SET);
    for (i = 0; i < iteration; i++) {
        fgets(word, MAX_WORD_LENGTH, dictionary_file);
        word[strcspn(word, "\r\n")] = '\0';  // Remove newline characters
        if (strcmp(password, word) == 0) {
            password_found = true;
	    printf ("found by %d/%d\n", rank, size);
            break;
        }
    }

    // Reduce the results to rank 0
    bool global_password_found;
    MPI_Reduce(&password_found, &global_password_found, 1, MPI_C_BOOL, MPI_LOR, 0, MPI_COMM_WORLD);

    // Print the result
    if (rank == 0) {
        if (global_password_found) {
            printf("Password found: %s\n", password);
        } else {
            printf("Password not found in dictionary\n");
        }
    }

    MPI_Finalize();
    return 0;
}
