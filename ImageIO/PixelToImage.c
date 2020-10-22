#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
#define MAX 100000

struct Pixel
{
	int red, green, blue, cluster;
};

int main()
{
  //Pixels to image
	//Image width, height and count of clusters will be recieved from k-means
	int width = 335, height = 187;
  int n0 = 25212, n1 = 13969, n2 = 23464;
  unsigned char *img1 = malloc(3 * (int)sqrt(n0) * (int)sqrt(n0) * sizeof(uint8_t)); //for cluster-0
  unsigned char *img2 = malloc(3 * (int)sqrt(n1) * (int)sqrt(n1) * sizeof(uint8_t)); //for cluster-1
  unsigned char *img3 = malloc(3 * (int)sqrt(n2) * (int)sqrt(n2) * sizeof(uint8_t)); //for cluster-2

  FILE *file;
  file = fopen("clusters.txt", "r");
  struct Pixel pixels[MAX];
	for(int i = 0; i < width * height; i++)
		fscanf(file, "%d %d %d %d", &pixels[i].red, &pixels[i].green, &pixels[i].blue, &pixels[i].cluster);

  int i1 = 0, i2 = 0, i3 = 0;
  for(int i = 0; i < width * height; i++)
  {
    if(pixels[i].cluster == 0 && i1 < 3 * (int)sqrt(n0) * (int)sqrt(n0))
    {
      *(img1 + i1++) = (uint8_t)pixels[i].red;
      *(img1 + i1++) = (uint8_t)pixels[i].green;
      *(img1 + i1++) = (uint8_t)pixels[i].blue;
    }
    else if(pixels[i].cluster == 1 && i2 < 3 * (int)sqrt(n1) * (int)sqrt(n1))
    {
      *(img2 + i2++) = (uint8_t)pixels[i].red;
      *(img2 + i2++) = (uint8_t)pixels[i].green;
      *(img2 + i2++) = (uint8_t)pixels[i].blue;
    }
    else if(pixels[i].cluster == 2 && i3 < 3 * (int)sqrt(n2) * (int)sqrt(n2))
    {
      *(img3 + i3++) = (uint8_t)pixels[i].red;
      *(img3 + i3++) = (uint8_t)pixels[i].green;
      *(img3 + i3++) = (uint8_t)pixels[i].blue;
    }
  }

  int desired_no_channels = 3;
  stbi_write_png("cluster1.png", (int)sqrt(n0), (int)sqrt(n0), desired_no_channels, img1, (int)sqrt(n0) * desired_no_channels);
  stbi_write_png("cluster2.png", (int)sqrt(n1), (int)sqrt(n1), desired_no_channels, img2, (int)sqrt(n1) * desired_no_channels);
  stbi_write_png("cluster3.png", (int)sqrt(n2), (int)sqrt(n2), desired_no_channels, img3, (int)sqrt(n2) * desired_no_channels);

  return 0;
}
