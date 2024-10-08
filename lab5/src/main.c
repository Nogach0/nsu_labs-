#include "compression.h"

int main(void) {
  FILE *input_file = fopen("in.txt", "rb");
  FILE *output_file = fopen("out.txt", "wb");

  char mode = fgetc(input_file);
  // Zip.
  if (mode == 'c') {
    Encode(input_file, output_file);
  }
  // Unzip.
  else if (mode == 'd') {
    Decode(input_file, output_file);
  }

  fclose(input_file);
  fclose(output_file);
}
