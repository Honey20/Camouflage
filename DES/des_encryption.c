#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

char encryption_keys[16][49];
char key[64] = "";

// Function to convert alphabetical string to binary string
void str_to_bin(char string_input[], char bin_output[])
{
    strcpy(bin_output,"");
    int i,j,c;
    for(i=0; string_input[i]!='\0';i++)
    {
        c = string_input[i];
        for(j=7;j+1>0;j--)
        {
            if(c>=(1<<j))
            {
                c = c - (1<<j);
                strcat(bin_output,"1");
            }
            else
            {
                strcat(bin_output,"0");
            }
        }
    }
}

// Function to convert binary string to decimal
int bin_to_dec(char binary[])
{
    int decimal = 0;
	int counter = 0;
	int size = strlen(binary);
	for(int i = size-1; i >= 0; i--)
	{
    	if(binary[i] == '1')
        	decimal += pow(2, counter);
    counter++;
	}
	return decimal;
}

// Function to convert decimal to binary string
void dec_to_bin(int decimal, char binary[4])
{
    while(decimal != 0)
    {
        if(decimal%2 == 0)
        {
            char temp[] = "";
    	    strcpy(temp,binary);
    	    strcpy(binary,"0");
    	    strcat(binary,temp);
        }
        else
        {
            char temp[] = "";
    	    strcpy(temp,binary);
    	    strcpy(binary,"1");
    	    strcat(binary,temp);
        }
		decimal = decimal/2;
	}
	
	while(strlen(binary) < 4)
	{
	    char temp[4] = "";
	    strcpy(temp,binary);
	    strcpy(binary,"0");
	    strcat(binary,temp);
	}
}

// Function to compute substring of a string from given position and of given length
void substring(char input[], char output[], int position, int length) 
{
    strcpy(output,"");
    int c = 0;
    while (c < length) 
    {
        output[c] = input[position+c-1];
        c++;
    }
    output[c] = '\0';
}

// Function to shift the string to left by one position
void shift_left_one(char input[], char output[28])
{
    for(int i = 1; i < 28; i++)
    {
        output[i-1] = input[i];
    }
    strncat(output,&input[0],1); 
}

// Function to shift the string to left by two positions
void shift_left_two(char input[], char output[28])
{
    for(int i = 2; i < 28; i++)
    {
        output[i-2] = input[i];
    }
    strncat(output,&input[0],1); 
    strncat(output,&input[1],1); 
}

// Function to perform XOR operation on two strings
void xor(char a[], char b[], char output[], int size)
{
	for(int i = 0; i < size; i++)
    { 
		if(a[i] != b[i])
			strcat(output,"1");
		else
			strcat(output,"0");
    }
}

// Function to generate 16 round keys and store them in a 2D character array
void generate_round_keys(char key[])
{
    // The PC1 table 
	int pc1[56] = {
                    57,49,41,33,25,17,9, 
                    1,58,50,42,34,26,18, 
                    10,2,59,51,43,35,27, 
                    19,11,3,60,52,44,36,		 
                    63,55,47,39,31,23,15, 
                    7,62,54,46,38,30,22, 
                    14,6,61,53,45,37,29, 
                    21,13,5,28,20,12,4 
                  };

	// The PC2 table
	int pc2[48] = { 
                    14,17,11,24,1,5, 
                    3,28,15,6,21,10, 
                    23,19,12,4,26,8, 
                    16,7,27,20,13,2, 
                    41,52,31,37,47,55, 
                    30,40,51,45,33,48, 
                    44,49,39,56,34,53, 
                    46,42,50,36,29,32 
                  }; 
    
    // Compressing the key using the PC1 table
	char perm_key[56] = ""; 
	for(int i = 0; i < 56; i++)
    {
		strncat(perm_key, &key[pc1[i]-1], 1); 
	}

	// Dividing the result into two equal halves
    char left[29] = ""; 
    char right[29] = "";
    substring(perm_key,left,1,28);
    substring(perm_key,right,29,28);
    
    // Generating 16 keys
    for(int i = 0; i<16; i++)
    {
        // For rounds 1, 2, 9, 16 the key_chunks are shifted by one; for other rounds: its two left shifts
        char left_shifted[28] = "";
        char right_shifted[28] = "";
        if(i == 0 || i == 1 || i==8 || i==15 )
        {
			shift_left_one(left,left_shifted);
            strcpy(left,left_shifted);
			shift_left_one(right,right_shifted);
            strcpy(right,right_shifted);
        }
        else
        {
			shift_left_two(left,left_shifted);  
            strcpy(left,left_shifted);  
			shift_left_two(right,right_shifted);
            strcpy(right,right_shifted);
        }
        
        // The chunks are combined
        char combined_key[56] = "";
        strcat(combined_key,left);
        strcat(combined_key,right);
        
        // Finally, the PC2 table is used to transpose the key bits
        char round_key[48] = ""; 
        for(int i = 0; i < 48; i++)
        { 
            strncat(round_key,&combined_key[pc2[i]-1],1); 
        }
        strcpy(encryption_keys[i],round_key);
        strcat(encryption_keys[i],"\0");
    }
}

// Function to perform DES encryption
void des_encryption(char plain_text[64],char round_keys[16][49])
{
    // The initial permutation table 
	int initial_permutation[64] = { 
                                    58,50,42,34,26,18,10,2, 
                                    60,52,44,36,28,20,12,4, 
                                    62,54,46,38,30,22,14,6, 
                                    64,56,48,40,32,24,16,8, 
                                    57,49,41,33,25,17,9,1, 
                                    59,51,43,35,27,19,11,3, 
                                    61,53,45,37,29,21,13,5, 
                                    63,55,47,39,31,23,15,7 
                                  }; 

	// The expansion table
	int expansion_table[48] = { 
                                32,1,2,3,4,5,4,5, 
                                6,7,8,9,8,9,10,11, 
                                12,13,12,13,14,15,16,17, 
                                16,17,18,19,20,21,20,21, 
                                22,23,24,25,24,25,26,27, 
                                28,29,28,29,30,31,32,1 
                              }; 

	// The substitution boxes.
	int substition_boxes[8][4][16]=  
	{   { 
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
        }, 
        { 
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
        }, 
        { 
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
        }, 
        { 
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
        }, 
        { 
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
        }, 
        { 
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
        }, 
        { 
            4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
        }, 
        {
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
        }
    };

	// The permutation table
	int permutation_tab[32] = { 
                                16,7,20,21,29,12,28,17, 
                                1,15,23,26,5,18,31,10, 
                                2,8,24,14,32,27,3,9,
                                19,13,30,6,22,11,4,25 
                              }; 

	// The inverse permutation table
	int inverse_permutation[64]= { 
                                    40,8,48,16,56,24,64,32, 
                                    39,7,47,15,55,23,63,31, 
                                    38,6,46,14,54,22,62,30, 
                                    37,5,45,13,53,21,61,29, 
                                    36,4,44,12,52,20,60,28, 
                                    35,3,43,11,51,19,59,27, 
                                    34,2,42,10,50,18,58,26, 
                                    33,1,41,9,49,17,57,25 
                                 };

    // Applying the initial permutation
  	char perm[64] = ""; 
	for(int i = 0; i < 64; i++)
    {
		strncat(perm, &plain_text[initial_permutation[i]-1],1); 
	}
    
    // Dividing the result into two equal halves 
    char left[33] = ""; 
    char right[33] = "";    
    substring(perm,left,1,32);
    substring(perm,right,33,32);

  	// The plain text is encrypted 16 times 
    for(int i = 0; i<16; i++)
    {
        char right_expanded[48] = "";
		
        // The right half of the plain text is expanded
    	for(int i = 0; i < 48; i++) 
        { 
      		strncat(right_expanded,&right[expansion_table[i]-1],1); 
        }

        // The result is xored with a key
        char xored[48] = "";
        xor(round_keys[i], right_expanded, xored, 48);

        // The result is divided into 8 equal parts and passed through 8 substitution boxes. After passing through a substitution box, each box is reduced from 6 to 4 bits.
        char res[32] = "";
        char copy[33] = "";
        strcpy(copy,left);

		for(int i=0; i<8; i++)
		{ 
			// Finding row and column indices to lookup the substituition box
            char row1[] = "";
            char xored_substring1[2] = "";
            char xored_substring2[2] = "";
            substring(xored,xored_substring1,(i*6)+1,1);
            substring(xored,xored_substring2,(i*6+5)+1,1);
            strcat(row1,xored_substring1);
            strcat(row1,xored_substring2);
      		int row = bin_to_dec(row1);

            char col1[] = "";
            char xored_substring3[2] = "";
            char xored_substring4[2] = "";
            char xored_substring5[2] = "";
            char xored_substring6[2] = "";
            substring(xored,xored_substring3,(i*6+1)+1,1);
            substring(xored,xored_substring4,(i*6+2)+1,1);
            substring(xored,xored_substring5,(i*6+3)+1,1);
            substring(xored,xored_substring6,(i*6+4)+1,1);
            strcat(col1,xored_substring3);
            strcat(col1,xored_substring4);
            strcat(col1,xored_substring5);
            strcat(col1,xored_substring6);
            
			int col = bin_to_dec(col1);

			int val = substition_boxes[i][row][col];
            char value1[] = "";
            dec_to_bin(val,value1);
			strcat(res,value1);
		}
        
        char perm2[33] = "";
        char xored1[33] = "";

        for(int i = 0; i < 32; i++)
		{
			strncat(perm2, &res[permutation_tab[i]-1], 1);
		}

        // The result is xored with the left half
		xor(perm2, copy, xored1, 32);
        strcat(xored1,"\0");

		// The left and the right parts of the plain text are swapped 
        strcpy(left,xored1);
        if(i < 15)
		{
            char temp[] = "";
			strcpy(temp,right);
			strcpy(right,xored1);
			strcpy(left,temp);
		}
    }
    // The halves of the plain text are combined
    char combined_text[] = "";
    strcat(combined_text,left);
    strcat(combined_text, right);
	char ciphertext[64] = ""; 

	// The inverse of the initial permutation is applied
	for(int i = 0; i < 64; i++)
    {
        strncat(ciphertext, &combined_text[inverse_permutation[i]-1], 1); 
    }
    
    // File pointer
    FILE *file;                     
	file = fopen("cipher.txt", "w");
	fprintf(file, "%s", ciphertext);
	fclose(file);
}

int main()
{
    char string_pt[9];
    char plain_text[64] = "";
    char string_key[9];
    
    printf("\nEnter the message to be encrypted: ");
    scanf("%[^\n]%*c",string_pt);
    str_to_bin(string_pt,plain_text);

    printf("Enter the key to be used for encryption (8 Characters only): ");
    scanf("%[^\n]%*c",string_key);
    str_to_bin(string_key,key);

    FILE *file;
    file = fopen("key.txt", "w");
	fprintf(file, "%s\n", key);
	fclose(file);

    generate_round_keys(key);
    des_encryption(plain_text,encryption_keys);
    
    printf("\n---------------------Text Encrypted Successfully!---------------------\n\n");
    return 0;
}
