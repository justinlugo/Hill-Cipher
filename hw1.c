#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
Name: Justin Lugo
Class: CIS 3360
Teacher: McAlpin
Assignment: HW1
*/

void encrypt(int[][9], char[10000], int);

int main(int argc, char *argv[3]){

	int key[9][9], keySize;
	char inTxt[10000];
	char outTxt[10000];
	int i, j, k=0, rem, extra;
	int inputSize=0;
	char c;
	char character;

	FILE *matrix, *plain;

	matrix = fopen(argv[1], "r");
	plain = fopen(argv[2], "r");

	if(matrix == NULL)
		printf("Could not open key file.");
	if(plain==NULL)
		printf("Could not open plaintext file.");

	else
		fscanf(matrix, "%d", &keySize);

	for(i=0;i<keySize;i++){								//creates a 2d array
		for(j=0;j<keySize;j++){
			key[i][j] = 0;
		}
	}
	printf("Key Matrix:\n\n");

	for(i=0;i<keySize;i++){								//puts the values into the array
		for(j=0;j<keySize;j++){
			fscanf(matrix, "%d", &key[i][j]);
			printf("%d ", key[i][j]);
		}
		printf("\n");
	}
	printf("\nPlaintext:\n\n");

	while(!feof(plain)){									//scans input file for characters
		character = (char)getc(plain);

		if(character >= 'A' && character <= 'Z')       //if character is capital, convert them to lowercase
			character = tolower(character);

		if(character>= 'a' && character <='z')         //if character is lowercase, add them to the input array
			inTxt[inputSize++] = character;

	}

	int len = strlen(plain);
	for (int i = 0; i < len; i++)
	{
		printf("%c", plain[i]);
		if ((i + 1) % 80 == 0 & i != 0)
		{
			printf("\n");
		}
	}

	//puts(inTxt);

	rem = strlen(inTxt)%keySize;

	extra = strlen(inTxt);

    for(i=0;i<rem;i++){
        inTxt[extra+i] = 'x';       //if the plaintext array is not divisible by length, pad with x
		}


	fclose(matrix);
	fclose(plain);

	printf("\n");

	encrypt(key,inTxt, keySize);						//uses the key and plaintext array to encrypt the file

	printf("\n");

	return 0;
}


void encrypt(int key[][9], char inTxt[], int size){

	int i=0;
	int len = strlen(inTxt);
	char outTxt[10000];
	int temp =0;
	printf("Ciphertext:\n\n");
	while(i < len){

		int j,k,l;

		for (j=0; j<size; j++) {
        	int temp = 0;
            for (k=0; k<size; k++){
                temp = (temp + key[j][k]*(inTxt[i+k] - 'a'))%26;			//add calculated values of position in key times 1d value of plaintext array
            }																//subtract ASCII value of 'a' to get correct ASCII value for plaintext calculation
        outTxt[j] = (char)('a' + temp);    									//added back
        }

        i += size;															//plaintext index increased by size so no duplicates

		for (int i = 0; i < len; i++)
		{
			printf("%c", inTxt[i]);
			if ((i + 1) % 80 == 0 & i != 0)
			{
				printf("\n");
			}
		}
	}
}
