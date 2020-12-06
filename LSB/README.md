# LSB - Least Significant Bit 

The least significant bit is the bit which is farthest to the right and holds the least value in a multi-bit binary number.

## Calculating the LSB of a Number.


## Tradition Method

In tradition method first we calculate the binary conversion of the number and then find the right most bit.

for eg, Calculating the LSB of `163`

    ----------------------------------
           | Number         Remainder
    -------|------------    ---------
        2  |  163               1          /^\
    --------------------                    |
        2  |  81                1           |
    --------------------                    |
        2  |  40                0           |
    --------------------                    |
        2  |  20                0           |
    --------------------                    |
        2  |  10                0           |
    --------------------                    |
        2  |   5                1           |
    --------------------                    |
        2  |   2                0           |
    --------------------                    |
        2  |   1                1           |
    --------------------    ---------

Hence binary converstion of 163 => 10100011
And LSB is the right most bit, that is 1 for 10100011

## Standard Way [Used in the Code]

LSB can be simply calculated by the formula `N % 2`
where `N` is the number,

for eg, LSB of 163 using the standard formula : 163 % 2 => 1

## Algorithm of Hiding the Data in Image using LSB.

### LSB Stegnography Encryption.

1. First we sort the `cluster.txt` file we got after `K-means` into seprate files, where each file contain the RGB colour value information of pixels in a cluster.
    ```
    void sorting_clusters() {
        int total_pixels = width_of_image * height_of_image ;   
        for(int i=0; i < number_of_clusters; i++) {
            file = fopen("clusters.txt", "r");
            char filename[10];
            snprintf(filename, sizeof(filename), "%d.txt", i);
            f[i] = fopen(filename, "w");
            for(int j = 0; j < total_pixels; j++) {
                Reading r, g, b, cluster value from clusters.txt
                if(cluster==i) {
                    Printing Value in f[i]
                }
            }   
            close f[i]  
            close file
        }
        print Succesfully sorted all the clusters
    }
    ```

2. Reading the Encrypted data from `cipher.txt` and dividing the data into frames to hide almost equivalent data in each cluster.
    ```
    frame_size = 8;
    no_of_frames =  length(Encrypted_data) / frame_size;
    frame_per_cluster = no_of_frames / no_of_clusters;
    reminder = no_of_frames % no_of_clusters;

    // lsb_insert() is the function to hide data in LSB.
    // for < k
    lsb_insert(filename, Encrypted_data, frame_per_cluster); 
    // for k
    lsb_insert(filename, Encrypted_data, frame_per_cluster + reminder );
    ```

3. Inserting Data in Images
    - Changing each frame to proper length.
    - Adding a flag `00000000`, that will be useful to tell when our encrypted data ended while fetching LSB data at receiver side.
    - Modifying data in LSB and saving it.
    - saving the remaining pixels.
    ```
    //function call
    lsb_insert(filename, Encrypted_data, frame_per_cluster); 

    void lsb_insert(char filename[], char binary_array[], int frame) {
    
        Opening each cluster file to hide data.
        file = fopen(filename, "r+");

        int total_pixels=0;
        // Counting total number of lines to declare total pixels
        for (char c = getc(file); c != EOF; c = getc(file)) {
            if(c == '\n') {
                total_pixels+=1;
            }
        }
        fclose(file);

        // Cluster counter is a global array that contains value of pixels in each cluster. 
        clustercount[clustercounter]=total_pixels;
        clustercounter++;

        // Creating flagged binary array
        len=frame*8;
        flagged_binary_array[len+8]; // Flagged Array.
    
        for(int i=0;i<len;i++) {
            flagged_binary_array[i]=binary_array[binary_counter];
            binary_counter++;
        }
        for(int i=len;i<(len+8); i++) {
            flagged_binary_array[i]='0';
        }

        // LSB process.. 
        pixel_counter = 0;
        file = fopen(filename, "r+");
        fl = fopen("clusters_lsb.txt", "a+");
        for(int j = 0; j < (len+8);j++) {
            fscanf(file, "%d %d %d %d", &r, &g, &b, &cluster); // Reading data from cluster file.

            // FOR EACH PIXEL colour, Red, Green, Blue we will repeat same process.
            // If input data is same as LSB 
            //      Data remain unchanged
            // else for 0, pixel_colour = pixel_colour - 1 and else for 1, pixel_colour = pixel_colour + 1

            if(flagged_binary_array[j]=='0') {
                if( pixel_colour % 2 == 0) 
                    pixel_colour = pixel_colour;
                else
                    pixel_colour = pixel_colour - 1;
            }
            else if (flagged_binary_array[j]=='1') {
                if( pixel_colour % 2 == 1)
                    pixel_colour = pixel_colour;
                else
                    pixel_colour = pixel_colour + 1;
            }
            else {
                break;
            }
            // repeat for each cluster
            // Adding LSB inserted data to new pixel file
            fprintf(fl, "%d %d %d %d\n", r, g, b, cluster);
            pixel_counter++;
        } 
        // Adding remaing pixels from cluster.
        for(int i=pixel_counter;i<total_pixels;i++) {         
            fscanf(file, "%d %d %d %d", &r, &g, &b, &cluster);
            fprintf(fl, "%d %d %d %d\n", r, g, b, cluster);
        }  
        fclose(file);
        fclose(fl);
    }
    ```

4. Converting newly generated pixel data to images.
    ```
        file = fopen("clusters_lsb.txt", "r");
        struct Pixel pixels[ width_of_image * height_of_image ];

        // Reading pixel information and storing it in a structure
        for(int i = 0; i < width * height; i++)
            fscanf(file, "%d %d %d %d", &pixels[i].red, &pixels[i].green, &pixels[i].blue, &pixels[i].cluster);

        unsigned char *images[no_of_clusters];
    
        // create a image memory allocation for each cluster
        for(int i = 0; i < no_of_clusters; i++)
            images[i] = malloc(3 * (int)sqrt(clustercount[i]) * (int)sqrt(clustercount[i]) * sizeof(uint8_t));

        // Creating the images from Pixel data
        for(int c = 0; c < no_of_clusters; c++) {
            int counter = 0;
            for(int i = 0; i < width * height; i++) {
                if(pixels[i].cluster == c && counter < 3 * (int)sqrt(clustercount[c]) * (int)sqrt(clustercount[c])) {
                *(images[c] + counter++) = (uint8_t)pixels[i].red;
                *(images[c] + counter++) = (uint8_t)pixels[i].green;
                *(images[c] + counter++) = (uint8_t)pixels[i].blue;
                }
            }
        }
        int desired_no_channels = 3;
        char name[30];
        for(int c = 0; c < no_of_clusters; c++) {
            sprintf(name, "cluster-%d.png", c);
            printf("%s saved in same directory\n", name);
            stbi_write_png(name, (int)sqrt(clustercount[c]), (int)sqrt(clustercount[c]), desired_no_channels, images[c], (int)sqrt(clustercount[c]) * desired_no_channels);
        }   
    }
    ```

### LSB Stegnography Decryption.

1. Creating the Pixels information file again from the images.
    ```
    // no_of_clusters is also equal to the number of images that will be formed.
    for(int i; i < no_of_clusters ; i++) {
        //Opening an images data into *img.
        char name[30];
        sprintf(name, "cluster-%d.png", i);
        int width, height, channels;
        unsigned char *img = stbi_load(name, &width, &height, &channels, 3);
        //Saving it to a file
	    FILE *fp;
        char pixfile[30];
        sprintf(pixfile, "cluster-%d.txt", i);
	    fp = fopen(pixfile, "w");
	    for(int i = 0; i < 3 * width * height; i+= 3)
            fprintf(fp, "%d %d %d\n", *(img + i), *(img + i + 1), *(img + i + 2));
        fclose(fp);


        //lsb_fetch is a fuction tat will be fetch data hidden in LSB of each image
        lsb_fetch(pixfile, ( width * height ));
    }
    ```

2. Fetching Data hidden in LSB of each image till our flag.
    - Fetch LSB from image pixel file and storing them in a buffer, while buffer is not equal to
    - flag is `00000000`
    - Adding encrypted data to `cipherarr`, which will be a global array containing complete Encrypted_data.
    - Saving the Encrypted_data into file, for decryption.
    ```
    void lsb_fetch(char filename[], int total_pixels) {
        FILE *file;
        file = fopen(filename, "r+");
        int r,g,b,cluster, lsb_r, lsb_g, lsb_b;
        int buffer[8];
        for(int i=0;i<total_pixels;i++) {
            fscanf(file, "%d %d %d", &r, &g, &b);

            // Repeat for each pixel colour.
            lsb_pixel_colour = pixel_colour % 2;
            if (lsb_pixel_colour==0){
                strcat(finalarr, "0");  
            }
            else {
                strcat(finalarr, "1");
            }
            buffer[buffer_counter] = lsb_pixel_colour;
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
        buffer_counter = 0; 

        // Adding Encrypted_data except flag into 
        for(int i=0;i<(strlen(finalarr)-8);i++) {
            if(finalarr[i]=='0') {
                strcat(cipherarr, "0");
            }
            else {
                strcat(cipherarr, "1");
            }    
        }
        strcpy(finalarr, "");
    }
    ```
    
---
