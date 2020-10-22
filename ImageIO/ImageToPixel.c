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
  //Image to pixels
  int width, height, channels;
  unsigned char *img = stbi_load("new.png", &width, &height, &channels, 3);
  printf("%d, %d\n", width, height);
  
  if(img == NULL)
  {
  	printf("Error in loading the image\n");
  	exit(1);
  }
  
  //Saving it to a file
	FILE *fp;
	fp = fopen("pixels.txt", "w");
	for(int i = 0; i < 3 * width * height; i+= 3)
  fprintf(fp, "%d %d %d\n", *(img + i), *(img + i + 1), *(img + i + 2));
  fclose(fp);
  return 0;
}





