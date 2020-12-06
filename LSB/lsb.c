#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define k 3

// Global variables
int binary_counter = 0;
int buffer_counter = 0;
char finalarr[(335*187)*3];
int clustercount[k];
int clustercounter=0;
char cipherarr[(335*187)*3];

struct Pixel
{
	int red, green, blue, cluster;
};

/*
sorting_clusters : Dividing the clusters.txt file into different files.
*/
void sorting_clusters() {
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

void lsb_insert(char filename[], char binary_array[], int frame) {
    
    //Opening each cluster file to hide data.
    FILE *file, *fl;
    file = fopen(filename, "r+");

    int total_pixels=0;
    // Counting total number of lines to declare total pixels
    for (char c = getc(file); c != EOF; c = getc(file)) {
        if(c == '\n') {
            total_pixels+=1;
        }
    }
    printf("Total pixels in %s is %d\n", filename, total_pixels);
    fclose(file);

    clustercount[clustercounter]=total_pixels;
    clustercounter++;

    // Creating flagged binary array
    int len=frame*8;
    char flagged_binary_array[len+8];
 

    for(int i=0;i<len;i++) {
        flagged_binary_array[i]=binary_array[binary_counter];
        binary_counter++;
    }
    for(int i=len;i<(len+8); i++) {
        flagged_binary_array[i]='0';
    }

    printf("Flagged binary array for file %s is\n", filename);

    for(int i=0;i<len+8;i++) {
        printf("%c", flagged_binary_array[i]);
    }

    printf("\n");


    // LSB process.. 
    int pixel_counter = 0;
    int r,g,b,cluster;
    file = fopen(filename, "r+");
    fl = fopen("clusters_lsb.txt", "a+");
    for(int j = 0; j < (len+8);j++) {
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
    fclose(file);
    fclose(fl);
}


/* LSB fetch function will be used to fetch a bit from the 
   least significant bit position of every colour in a pixel. */

void lsb_fetch(char filename[], int total_pixels) {
    FILE *file;
    file = fopen(filename, "r+");
    int r,g,b,cluster, lsb_r, lsb_g, lsb_b;
    int buffer[8];
    for(int i=0;i<total_pixels;i++) {
        fscanf(file, "%d %d %d", &r, &g, &b);
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
    printf("Final array - %s\n", finalarr);
    buffer_counter = 0; 
    for(int i=0;i<(strlen(finalarr)-8);i++) {
        if(finalarr[i]=='0') {
            strcat(cipherarr, "0");
        }
        else {
            strcat(cipherarr, "1");
        }    
    }
    printf("Cipher array - %s\n", cipherarr);
    strcpy(finalarr, "");
}


void lsb_stegnography() {

    // binary_array = data recieved from the DES program.

/*     char binary_array[100];
    FILE *file2;                     
	file2 = fopen("cipher.txt", "r");
	fscanf(file2, "%s", binary_array);
	fclose(file2); */

    char binary_array[] = "0010111110110101111110011101110100000011111001101100011100000100";
    printf("Binary array \n");
    printf("%s\n", binary_array);

    //Dividing data into parts
    int frame_size = 8;
    int noofframes =  strlen(binary_array) / frame_size;
    int framepercluster = noofframes / k;
    int reminder = noofframes % k;

    printf("No of frames - %d\n", noofframes);

    // Running the lsb_insert function to insert bits at lsb.
    printf("\nRunning lsb\n\n");
    for(int i=0;i<k;i++) {
        char filename[10];
        snprintf(filename, sizeof(filename), "%d.txt", i);
        if(i<(k-1)) {
            lsb_insert(filename, binary_array, framepercluster);
        }
        else {
            lsb_insert(filename, binary_array, (framepercluster+reminder));
        }
    }

    // Converting pixel to images.
    FILE *file;
    file = fopen("clusters_lsb.txt", "r");
    struct Pixel pixels[335*187];
	int width = 335, height = 187;
    for(int i = 0; i < width * height; i++)
		fscanf(file, "%d %d %d %d", &pixels[i].red, &pixels[i].green, &pixels[i].blue, &pixels[i].cluster);

    unsigned char *images[k];
  
    for(int i = 0; i < k; i++)
  	    images[i] = malloc(3 * (int)sqrt(clustercount[i]) * (int)sqrt(clustercount[i]) * sizeof(uint8_t));

	for(int c = 0; c < k; c++)
	{
		int counter = 0;
		for(int i = 0; i < width * height; i++)
		{
			if(pixels[i].cluster == c && counter < 3 * (int)sqrt(clustercount[c]) * (int)sqrt(clustercount[c]))
    	{
		    *(images[c] + counter++) = (uint8_t)pixels[i].red;
		    *(images[c] + counter++) = (uint8_t)pixels[i].green;
		    *(images[c] + counter++) = (uint8_t)pixels[i].blue;
    	}
		}
	}

	printf("\n");
    int desired_no_channels = 3;
  
    char name[30];
    for(int c = 0; c < k; c++)
    {
	    sprintf(name, "cluster-%d.png", c);
  	    printf("%s saved in same directory\n", name);
  	    stbi_write_png(name, (int)sqrt(clustercount[c]), (int)sqrt(clustercount[c]), desired_no_channels, images[c], (int)sqrt(clustercount[c]) * desired_no_channels);
    }   
}

void lsb_stegnography_d() {
    for(int i;i<k;i++) {
        char name[30];
        sprintf(name, "cluster-%d.png", i);
        int width, height, channels;
        unsigned char *img = stbi_load(name, &width, &height, &channels, 3);
  
        if(img == NULL) {
            printf("Error in loading the image\n");
  	        exit(1);
        }
  
        //Saving it to a file
	    FILE *fp;
        char pixfile[30];
        sprintf(pixfile, "cluster-%d.txt", i);
	    fp = fopen(pixfile, "w");
	    for(int i = 0; i < 3 * width * height; i+= 3)
            fprintf(fp, "%d %d %d\n", *(img + i), *(img + i + 1), *(img + i + 2));
        fclose(fp);

        lsb_fetch(pixfile, (width*height));
    }

    //printing finalarr
    printf("Final Array :\n");
    printf("%s\n", cipherarr);

    FILE *file;                     
	file = fopen("cipher_afterlsb.txt", "w");
	fprintf(file, "%s", cipherarr);
	fclose(file);
}

int main() {
    sorting_clusters();
    lsb_stegnography();
    lsb_stegnography_d();

    return 0;    
}
