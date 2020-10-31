#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void substring(char input[56], char output[28], int position, int length) 
{
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

void round_key(char key[])
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
    
    // 1. Compressing the key using the PC1 table
	char perm_key[56] = ""; 
	for(int i = 0; i < 56; i++)
    {
        char temp =  key[pc1[i]-1];
		strncat(perm_key, &temp, 1); 
	}
    printf("Step 1:\t%s\n",perm_key);

	// 2. Dividing the result into two equal halves
    char left[28] = ""; 
    char right[28] = "";
    substring(perm_key,left,1,28);
    substring(perm_key,right,29,28);
    printf("Step 2 Left:\t%s\n",left);
    printf("Step 2 Right:\t%s\n",right);
    
    //Generating 16 keys
    for(int i = 0; i<16; i++)
    {
        //For rounds 1, 2, 9, 16 the key_chunks are shifted by one.
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
        printf("\nRound %d Left Shifted:\t%s\n",i,left);
        printf("Round %d Right Shifted:\t%s\n",i,right);
        
        // 4. The chunks are combined
        char combined_key[56] = "";
        strcat(combined_key,left);
        strcat(combined_key,right);
        printf("Combined Key:\t%s\n",combined_key);
        
        // 5. Finally, the PC2 table is used to transpose the key bits
        char round_key[] = ""; 
        for(int i = 0; i < 48; i++)
        { 
            char temp = combined_key[pc2[i]-1];
            strncat(round_key,&temp,1); 
        }   
        printf("Round Key:\t%s\n",round_key);
    }
}

int main()
{
    char key[] = "1010101010111011000010010001100000100111001101101100110011011101";
    round_key(key);
    return 0;
}