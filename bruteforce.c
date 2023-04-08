/*
 * Password Cracking using Brute Force Algorithm
 * We will be generating words, and checking them with the user input to see if it is correct 
 * Created on 22.03.2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	printf("Enter your password:\n");
	char target[20]; 
	scanf("%s",target);
	char word[10]="-----";
	for (word[0]='a'; word[0]<'z';word[0]++){
	   for(word[1]='a';word[1]<'z';word[1]++){
	      for (word[2]='a';word[2]<'z';word[2]++){
	        for (word[3]='a';word[3]<'z';word[3]++){
		  for (word[4]='a';word[4]<'z';word[4]++){
			  //to check the passwords
			  //see if target matches the hash 
			  if (strcmp(word, target)==0){
			  	printf("Found it! %s\n", word);
				exit(0);
			  }
		  }
		}
	      }
	   }
printf("%s\n",word);
	}
return 0;
}
