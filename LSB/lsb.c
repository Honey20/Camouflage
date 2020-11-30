#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Global variables
int lsb_counter = 0;
int buffer_counter = 0;
char finalarr[(335*187)*3];

/*
sorting_clusters : Dividing the clusters.txt file into different files.
*/
void sorting_clusters() {
    int k=3;
    int total_pixels = 335*187;   
    int r,g,b,cluster;
    FILE  *file;
    FILE  *f[k];
    for(int i=0; i < k; i++) {
        file = fopen("clusters.txt", "r");
        char filename[10];
        snprintf(filename, sizeof(filename), "%d.txt", i);
        f[i] = fopen(filename, "w");
        for(int j = 0; j < total_pixels; j++) {
            fscanf(file, "%d %d %d %d", &r, &g, &b, &cluster);
            if(cluster==i) {
                fprintf(f[i], "%d %d %d %d\n", r, g, b, cluster);
            }
        }   
        fclose(f[i]);  
        fclose(file);
    }
    printf("\nSuccesfully sorted all the clusters\n");
}

/* LSB Insert function will be used to insert a bit at the 
   least significant bit of every colour in a pixel.     */

void lsb_insert(char flagged_binary_array[], int len) {
    FILE *file, *fl;
    file = fopen("clusters_copy.txt", "r");
    int total_pixels = 335*187; 
    int pixel_counter = 0;
    int r,g,b,cluster;
    fl = fopen("clusters_lsb.txt", "w+");
    for(int j = 0; j < len;j++) {
        fscanf(file, "%d %d %d %d", &r, &g, &b, &cluster);
        if(flagged_binary_array[j]=='0') {
            if(r%2==0) 
                r=r;
            else
                r=r-1;
        }
        else if (flagged_binary_array[j]=='1') {
            if(r%2==1)
                r=r;
            else
                r=r+1;
        }
        else {
            break;
        }
        j++;
        if(flagged_binary_array[j]=='0') {
            if(g%2==0) 
                g=g;
            else
                g=g-1;
        }
        else if (flagged_binary_array[j]=='1') {
            if(g%2==1)
                g=g;
            else
                g=g+1;
        }
        else {
            break;
        }
        j++;
        if(flagged_binary_array[j]=='0') {
            if(b%2==0) 
                b=b;
            else
                b=b-1;
        }
        else if (flagged_binary_array[j]=='1') {
            if(b%2==1)
                b=b;
            else
                b=b+1;
        }
        else {
            break;
        }
        fprintf(fl, "%d %d %d %d\n", r, g, b, cluster);
        pixel_counter++;
    }
    for(int i=pixel_counter;i<total_pixels;i++) {
        fscanf(file, "%d %d %d %d", &r, &g, &b, &cluster);
        fprintf(fl, "%d %d %d %d\n", r, g, b, cluster);
    }
}


/* LSB fetch function will be used to fetch a bit from the 
   least significant bit position of every colour in a pixel. */

void lsb_fetch() {
    FILE *file;
    int total_pixels = 335*187;
    file = fopen("clusters_lsb.txt", "r+");
    int r,g,b,cluster, lsb_r, lsb_g, lsb_b;
    int buffer[8];
    for(int i=0;i<total_pixels;i++) {
        fscanf(file, "%d %d %d %d", &r, &g, &b, &cluster);
        lsb_r = r % 2;
        if (lsb_r==0){
            strcat(finalarr, "0");
        }
        else {
            strcat(finalarr, "1");
        }
        buffer[buffer_counter] = lsb_r;
        buffer_counter++;
        if(buffer_counter==8) {
            int temp = 0 ;
            for(int i=0; i<8;i++) {
                if(buffer[i]==0) {
                    temp++;
                }
            }
            if(temp==8) {
                break;
            }
            temp = 0;
            buffer_counter = buffer_counter % 8;
        }
        lsb_g = g % 2;
        if (lsb_g==0){
            strcat(finalarr, "0");
        }
        else {
            strcat(finalarr, "1");
        }
        buffer[buffer_counter] = lsb_g;
        buffer_counter++;
        if(buffer_counter==8) {
            int temp = 0 ;
            for(int i=0; i<8;i++) {
                if(buffer[i]==0) {
                    temp++;
                }
            }
            if(temp==8) {
                break;
            }
            temp = 0;
            buffer_counter = buffer_counter % 8;
        }
        lsb_b = b % 2;
        if (lsb_b==0){
            strcat(finalarr, "0");
        }
        else {
            strcat(finalarr, "1");
        }
        buffer[buffer_counter] = lsb_b;
        buffer_counter++;
                if(buffer_counter==8) {
            int temp = 0 ;
            for(int i=0; i<8;i++) {
                if(buffer[i]==0) {
                    temp++;
                }
            }
            if(temp==8) {
                break;
            }
            temp = 0;
            buffer_counter = buffer_counter % 8;
        }
    }
}


int main() {

    // sorting_clusters();

    // binary_array = data recieved from the DES program.
    char binary_array[] = "0010111110110101111110011101110100000011111001101100011100000100";
    printf("Binary array \n");
    printf("%s", binary_array);

    // Declaring Flagged array.
    char flagged_binary_array[strlen(binary_array)+8];
        
    // flagging array = binary_array + "00000000" 
    for(int i=0;i<strlen(binary_array);i++) {
        flagged_binary_array[i]=binary_array[i];
    } 
    for(int i=strlen(binary_array);i<(strlen(binary_array)+8); i++) {
        flagged_binary_array[i]='0';
    }

    // Printing the flagged array.
    printf("\nFlagged binary array\n");
    for(int i;i<(strlen(binary_array)+8);i++) {
        printf("%c", flagged_binary_array[i]);
    }
    printf("\n");

    // Running the lsb_insert function to insert bits at lsb.
    printf("\nRunning lsb\n\n");
    lsb_insert(flagged_binary_array, (strlen(binary_array)+8));

    lsb_fetch();

    // printing finalarr
    printf("Final Array :\n");
    printf("%s\n", finalarr);
    return 0;    
}
