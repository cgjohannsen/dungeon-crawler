#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

/* Do not modify write_pgm() or read_pgm() */
int write_pgm(char *file, void *image, uint32_t x, uint32_t y)
{
  FILE *o;

  if (!(o = fopen(file, "w"))) {
    perror(file);

    return -1;
  }

  fprintf(o, "P5\n%u %u\n255\n", x, y);

  /* Assume input data is correctly formatted. *
   * There's no way to handle it, otherwise.   */

  if (fwrite(image, 1, x * y, o) != (x * y)) {
    perror("fwrite");
    fclose(o);

    return -1;
  }

  fclose(o);

  return 0;
}

/* A better implementation of this function would read the image dimensions *
 * from the input and allocate the storage, setting x and y so that the     *
 * user can determine the size of the file at runtime.  In order to         *
 * minimize complication, I've written this version to require the user to  *
 * know the size of the image in advance.                                   */
int read_pgm(char *file, void *image, uint32_t x, uint32_t y)
{
  FILE *f;
  char s[80];
  unsigned i, j;

  if (!(f = fopen(file, "r"))) {
    perror(file);

    return -1;
  }

  if (!fgets(s, 80, f) || strncmp(s, "P5", 2)) {
    fprintf(stderr, "Expected P6\n");

    return -1;
  }

  /* Eat comments */
  do {
    fgets(s, 80, f);
  } while (s[0] == '#');

  if (sscanf(s, "%u %u", &i, &j) != 2 || i != x || j != y) {
    fprintf(stderr, "Expected x and y dimensions %u %u\n", x, y);
    fclose(f);

    return -1;
  }

  /* Eat comments */
  do {
    fgets(s, 80, f);
  } while (s[0] == '#');

  if (strncmp(s, "255", 3)) {
    fprintf(stderr, "Expected 255\n");
    fclose(f);

    return -1;
  }

  if (fread(image, 1, x * y, f) != x * y) {
    perror("fread");
    fclose(f);
    return -1;
  }

  fclose(f);

  return 0;
}

int apply_sobel(uint8_t input[1024][1024], uint8_t output[1024][1024]){
  
  int accumulator = 0;

  int16_t kx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
  int16_t ky[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

  int16_t Ox[1024][1024];
  int16_t Oy[1024][1024];

  int i, j, r, c;

  for(r = 1; r < 1023; r++){
    for(c = 1; c < 1023; c++){
      accumulator = 0;
      for(i = 0; i < 3; i++){
	for(j = 0; j < 3; j++){
	  accumulator = accumulator + kx[i][j]*(input[r+(i-2)][c+(j-2)]);
	}
      }
      Ox[r][c] = accumulator;
    }
  }

  for(r = 1; r < 1023; r++){
    for(c = 1; c < 1023; c++){
      accumulator = 0;
      for(i = 0; i < 3; i++){
	for(j = 0; j < 3; j++){
	  accumulator = accumulator + ky[i][j]*(input[r+(i-2)][c+(j-2)]);
	}
      }
      Oy[r][c] = accumulator;
    }
  }

  for(r = 1; r < 1023; r++){
    for(c = 1; c < 1023; c++){
      double xterm = (double) (Ox[r][c] * Ox[r][c]);
      double yterm = (double) (Oy[r][c] * Oy[r][c]);
      double value = sqrt(xterm + yterm);

      if(value > 255){
	value = 255;
      }
      output[r][c] = value;
    }
  }

  return 0;

}

int main(int argc, char *argv[])
{
  uint8_t image[1024][1024];
  uint8_t out[1024][1024];
  
  if(argc < 1){
    printf("Not enough arguments");
    return -1;
  } else {
    read_pgm(argv[1], image, 1024, 1024);
    
    apply_sobel(image, out);

    write_pgm("sobel.pgm", out, 1024, 1024);
  }
  
  return 0;
}
