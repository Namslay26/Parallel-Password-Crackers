/*
 * Password Cracking using Brute Force Algorithm, Parallelised Code
 * We will be generating words, and checking them with the user input to see if it is correct 
 * Created on 22.03.2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>


int main(){
	printf("Enter your password:\n");
	char target[20]; 
	scanf("%s",target);
	#pragma omp parallel for schedule(static)
	for (int i=0; i<26;i++){

	for(int j=0;j<26;j++){

	for (int k=0;k<26;k++){

	for (int l=0;l<26;l++){
		 
	for (int m=0;m<26;m++){
		//to check the passwords
		//see if target matches the hash
		char word[10] ={0};
		word[0]='a'+i;
		word[1]='a'+j;
		word[2]='a'+k;
		word[3]='a'+l;
		word[4]='a'+m;
		if (strcmp(word, target)==0){
			printf("Found it! %s\n", word);
			exit(0);
		}
	}
	}
	}
	}
	}		
return 0;
}
