# K-Means Clustering 

K-means clustering is one of the simplest and popular unsupervised machine learning algorithms. This technique partitions n objects into k clusters in which each object belongs to the cluster with the nearest mean. This method outputs exactly k different clusters of the greatest possible variation. The objective of K-Means clustering is to minimize total intra-cluster variance. Here, it is used to insert various segments of encrypted data into an image. Now, to segment image, we have to classify image into different groups. There are different methods for image segmentation, here the pixels of the image are clustered into groups based on the pixel values (RGB) using K-Means clustering algorithm. 

Below flow chart describes the working of K-Means Clustering algorithm:

![K-Means](https://user-images.githubusercontent.com/47852407/101285592-13548000-380c-11eb-845a-713577e9e6a9.png)

## Pseudocode
   ```
    struct Pixel
    {
      double red, green, blue, min_dist
      int cluster
    }

    kmeansclustering(struct Pixel *pixels, k, epochs, total_pixels, *clustercount)
    {
      for(i = 0; i < total_pixels; i++)
        Initializing cluster with -1 as it does it not belong to any cluster
        Initializing min_dist with infinity as it will decrease with number of iterations

      for(i = 0; i < k; i++)
        Initializing clusters with random centroids amongst pixels

      for(i = 0; i < k; i++)
        Giving unique cluster ID to newly generated random centroids

      Calculate distance, update centroids and repeat for given epochs
      for(e = 0; e < epochs; e++)
      {
        for(int i = 0; i < k; i++)
        {
          for(int j = 0; j < total_pixels; j++)
          {
            Calculate distance of the point to the centroid
            Assigning points to clusters by minimizing euclidean distance
          }
        }

        Computing new centroids (Heart of k-means i.e. updating centroids)
        Calculating mean of points in a cluster

        for(i = 0; i < total_pixels; i++)
        {
          Reset distance to max
        }

        Computing the new centroids
        for(i = 0; i < k; i++)
        {
          if(num_pixels[i] == 0)
          {
            Assigning new random centroid
          }
          else
          {
            Calculate mean of the points in the cluster and assign them as new centroid
          }
        }
      }

      Storing Results
      for(c = 0; c < k; c++)
        Initializing clustercount[c] as 0

      for(c = 0; c < k; c++)
      {
        for(i = 0; i < total_pixels; i++)
        {
          if(pixels[i].cluster == c)
            Increment clustercount[c] by one
        }
      }

      Saving it to a file for LSB
    }

    main()
    {
      User input:-
      -> Cover image
      -> Parameter k for k-means algorithm, to define number of clusters
      -> Number of iterations for which k-means will train

      Declare an array of struct pixels to store values of each pixel

      Loading image

      for(i = 0; i < 3 * total_pixels; i+= 3)
      {
        Storing pixels in array of structure from image
      }

      Training the model
      kmeansclustering(pixels, k, epochs, total_pixels, clustercount);

      Printing Results of k-means algorithm

      Pixels to Image
      for(i = 0; i < k; i++)
        Dynamically allocating memory for images

      for(c = 0; c < k; c++)
      {
        counter = 0;
        for(i = 0; i < width * height; i++)
        {
          if(pixels[i].cluster == c and counter < current image size)
          {
            Store pixel value in images
          }
        }
      }

      for(c = 0; c < k; c++)
      {
        Saving images in the same directory
      }
    }
   ```

## How to use

Compile and Run:-
```
gcc k-means.c -o k-means -lm
./k-means
```
![Screenshot from 2020-12-07 02-16-02](https://user-images.githubusercontent.com/47852407/101291949-65a89780-3832-11eb-8d0f-d84d93eb1101.png)
![Screenshot from 2020-12-07 02-18-47](https://user-images.githubusercontent.com/47852407/101291978-95f03600-3832-11eb-8c6e-b5b0ee504e47.png)



