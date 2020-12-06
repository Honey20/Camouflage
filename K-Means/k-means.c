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
#define MAX 100000

struct Pixel
{
	double red, green, blue; //R, G, B will lie between 0 and 255

	int cluster;
	double min_dist;
};

void kmeansclustering(struct Pixel *pixels, int k, int epochs, int total_pixels, int *clustercount)
{
	/*
	Input:
		-> An array of structures containing RGB values of pixels
		-> Paramter k for k-means algorithm, to define number of clusters
		-> Number of iterations for which k-means will train
		-> Total pixels of the image
	Output:
		-> Displaying number of pixels in every cluster
		-> Saving pixel and it's respective cluster to clusters.txt
	*/

	float distance;
	
	//Initialising cluster with -1 as it does it not belong to any cluster
	//Initialising min_dist with infinty as it will decrease with number of iterations
	for(int i = 0; i < total_pixels; i++)
	{
		pixels[i].cluster = -1;
		pixels[i].min_dist = DBL_MAX;
	}

	//Initialising clusters with random centroids amongst pixels
	struct Pixel centroids[k];
	srand(time(0));
	for(int i = 0; i < k; i++)
		centroids[i] = pixels[rand()%total_pixels];

	//Instead of generating random centroids at receiver side, generate with same initial centroids
	//SameInitialCentroids(centroids, k);

	//Giving unique cluster ID to newly generated random centroids i.e. 0, 1, 2
	for(int i = 0; i < k; i++)
		centroids[i].cluster = i;

	printf("\nK-Means Algorithm:-\n");
  //Calculate distance, update centroids and repeat for given epochs
	for(int e = 0; e < epochs; e++)
	{
		//Assigning points to clusters by minimizing euclidean distance
		for(int i = 0; i < k; i++)
		{
			for(int j = 0; j < total_pixels; j++)
			{
				//Calculate distance of the point to the centroid
				distance = sqrt(pow((pixels[j].red - centroids[i].red), 2) +
				 				pow((pixels[j].green - centroids[i].green), 2) +
								pow((pixels[j].blue - centroids[i].blue), 2));
				if(distance < pixels[j].min_dist)
				{
					pixels[j].min_dist = distance;
					pixels[j].cluster = centroids[i].cluster;
				}
			}
		}

		//Computing new centroids (Heart of k-means i.e. updating centroids)
		//Calculating mean of points in a cluster
		double num_pixels[k];
		double sum_red[k], sum_green[k], sum_blue[k];

		for(int i = 0; i < k; i++)
		{
			num_pixels[i] = 0.0;
			sum_red[i] = 0.0;
			sum_green[i] = 0.0;
			sum_blue[i] = 0.0;
		}

		for(int i = 0; i < total_pixels; i++)
		{
			num_pixels[pixels[i].cluster] += 1;
			sum_red[pixels[i].cluster] += pixels[i].red;
			sum_green[pixels[i].cluster] += pixels[i].green;
			sum_blue[pixels[i].cluster] += pixels[i].blue;

			//Again, reset distance to max
			pixels[i].min_dist = DBL_MAX;
		}

		//Computing the new centroids
		printf("Epoch - %d\n", e+1);
		for(int i = 0; i < k; i++)
		{
			if(num_pixels[i] == 0) //If no point is assigned to the cluster, assigning new random centroid
			{
				centroids[i] = pixels[rand()%total_pixels];
				centroids[i].cluster = i;
			}
			else //Else, calculate mean of the points in the cluster and assign them as new centroid
			{
				centroids[i].red = sum_red[i]/num_pixels[i];
				centroids[i].blue = sum_blue[i]/num_pixels[i];
				centroids[i].green = sum_green[i]/num_pixels[i];
			}
			printf("Centroid - %d : (%f, %f, %f)\n", i, centroids[i].red, centroids[i].green, centroids[i].blue);
		}
		printf("\n");
	}

	//Storing Results
	for(int c = 0; c < k; c++)
		clustercount[c] = 0;
		
	for(int c = 0; c < k; c++)
	{
		for(int i = 0; i < total_pixels; i++)
		{
			if(pixels[i].cluster == c)
				clustercount[c]++;
		}
	}
	
	/*
	//Saving it to a file for LSB input
	FILE *fp;
	fp = fopen("clusters.txt", "w");
	for(int i = 0; i < total_pixels; i++)
  		fprintf(fp, "%d %.0lf %.0lf %.0lf %d\n", i+1, pixels[i].red, pixels[i].green, pixels[i].blue, pixels[i].cluster);
  	fclose(fp);
  */
}

int main()
{
	//Image to pixels
  int width, height, channels;
  
  int k; //number of clusters
	int epochs; //Number of iterations
	char imagename[20]; //Input image for clustering
	
	printf("K-Means Clustering for Image Segmentation on the basis of RGB values\n");
	printf("`````````````````````````````````````````````````````````````````````\n");
	printf("Enter name of image: ");
	scanf("%s", imagename);
	printf("Enter number of clusters(k): ");
	scanf("%d", &k);
	printf("Enter number of iterations(epochs): ");
	scanf("%d", &epochs); 
	
	int total_pixels; //Number of pixels
	int clustercount[k]; //Number of pixels in each cluster
  
  //An array of struct pixels to store values of each pixel
	struct Pixel pixels[MAX];
	
	//Loading image
  unsigned char *img = stbi_load(imagename, &width, &height, &channels, 3);
  total_pixels = width * height;
  
  //Error in loading the image
  if(img == NULL)
  {
  	printf("Error in loading the image\n");
  	exit(1);
  }
  
  //Storing pixels
  int counter = 0; 	
	for(int i = 0; i < 3 * total_pixels; i+= 3)
	{
		pixels[counter].red = (double)*(img + i);
		pixels[counter].green = (double)*(img + i + 1);
		pixels[counter].blue = (double)*(img + i + 2);
		counter++;
	}

	//Training the model and saving the results to a text file
	kmeansclustering(pixels, k, epochs, total_pixels, clustercount);

	//Results
	printf("Total pixels - %d\n", total_pixels);
	printf("Pixels in each cluster:-\n");	
	for(int c = 0; c < k; c++)
		printf("Cluster-%d : %d\n", c, clustercount[c]);
	
	//Pixels to Image
  unsigned char *images[k];
  
  for(int i = 0; i < k; i++)
  	images[i] = malloc(3 * (int)sqrt(clustercount[i]) * (int)sqrt(clustercount[i]) * sizeof(uint8_t));

	for(int c = 0; c < k; c++)
	{
		counter = 0;
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
	return 0;
}



