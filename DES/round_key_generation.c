#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

char encryption_keys[16][49];
char key[64] = "";

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

void shift_left_one(char input[], char output[28])
{
    for(int i = 1; i < 28; i++)
    {
        output[i-1] = input[i];
    }
    strncat(output,&input[0],1); 
}

void shift_left_two(char input[], char output[28])
{
    for(int i = 2; i < 28; i++)
    {
        output[i-2] = input[i];
    }
    strncat(output,&input[0],1); 
    strncat(output,&input[1],1); 
}

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

int main()
{
    char string_key[9];

    printf("Enter the key to be used for encryption (8 Characters only): ");
    scanf("%[^\n]%*c",string_key);
    str_to_bin(string_key,key);

    generate_round_keys(key);
    printf("\n------------------------Printing 16 Round Keys------------------------\n\n");
    for(int i=0; i<16; i++)
    {
        printf("Key %d: %s\n",i+1,encryption_keys[i]);
    }
    
    printf("\n---------------------Keys Generated Successfully!---------------------\n\n");
    return 0;
}
