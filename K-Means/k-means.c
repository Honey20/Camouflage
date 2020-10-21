#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<time.h>
#include<math.h>

#define MAX 100000

struct Pixel
{
	double red, green, blue; //R, G, B will lie between 0 and 255

	int cluster;
	double min_dist;
};

void SameInitialCentroids(struct Pixel *centroids, int k)
{
	//Print random generated for first time
	for(int i = 0; i < k; i++)
		printf("Centroid-%d -> %f, %f, %f\n", i, centroids[i].red, centroids[i].green, centroids[i].blue);

	// //Get last saved from user
	// for(int i = 0; i < k; i++)
	// {
	// 	printf("Enter R, G, B for centroid-%d -> ", i);
	// 	scanf("%d %d %d", &centroids[i].red, &centroids[i].green, &centroids[i].blue);
	// }
}

void kmeansclustering(struct Pixel *pixels, int k, int epochs, int total_pixels)
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

	//Initialising clusters with random centroids amongst pixels
	struct Pixel centroids[k];
	srand(time(0));
	for(int i = 0; i < k; i++)
		centroids[i] = pixels[rand()%total_pixels];

	//Instead of generating random centroids at receiver side, generate with same initial centroids
	SameInitialCentroids(centroids, k);

	//Giving unique cluster ID to newly generated random centroids i.e. 0, 1, 2
	for(int i = 0; i < k; i++)
		centroids[i].cluster = i;

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

	//Results
	int n0 = 0, n1 = 0, n2 = 0;
	for(int i = 0; i < total_pixels; i++)
	{
		if(pixels[i].cluster == 0)
			n0++;
		else if(pixels[i].cluster == 1)
			n1++;
		else if(pixels[i].cluster == 2)
			n2++;
		else
			printf("Cluster is %d\n", pixels[i].cluster);
	}
	printf("Number: %d, %d, %d\n", n0, n1, n2);

	//Saving it to a file
	FILE *fp;
	fp = fopen("clusters.txt", "w");
	for(int i = 0; i < total_pixels; i++)
  		fprintf(fp, "%.0lf %.0lf %.0lf %d\n", pixels[i].red, pixels[i].green, pixels[i].blue, pixels[i].cluster);
  	fclose(fp);
}

int main()
{
	int k = 3; //number of clusters
	int epochs = 40; //Number of iterations
	int total_pixels = 335*187; //Number of pixels

	//An array of struct pixels to store values of each pixel
	struct Pixel pixels[MAX];

	FILE *file; //file pointer
	//reading values of red, green and blue part into struct pixel

	file = fopen("red.txt", "r");
	for(int i = 0; i < total_pixels; i++)
		fscanf(file, "%lf ", &pixels[i].red);

	file = fopen("green.txt", "r");
	for(int i = 0; i < total_pixels; i++)
		fscanf(file, "%lf ", &pixels[i].green);

	file = fopen("blue.txt", "r");
	for(int i = 0; i < total_pixels; i++)
		fscanf(file, "%lf ", &pixels[i].blue);

	fclose(file);

	//Initialising cluster with -1 as it does it not belong to any cluster
	//Initialising min_dist with infinty as it will decrease with number of iterations
	for(int i = 0; i < total_pixels; i++)
	{
		pixels[i].cluster = -1;
		pixels[i].min_dist = DBL_MAX;
	}

	//Training the model
	//And saving the results to a text file
	kmeansclustering(pixels, k, epochs, total_pixels);

	return 0;
}
