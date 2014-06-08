#include <stdio.h>
#include <stdlib.h>

#define ORIGINAL_FILE_WIDTH	800

void usage()
{
	printf("\nrgb565 raw extraction tool by Oussema HARBI <oussema.elharbi@gmail.com>\n");
	printf("Usage : rgb565extract source_file dump_file yStart yEnd width\n");
	printf("Example : ./rgb565extract Settings.raw settings_half.raw 0 240 800\n\n");
}

int dump565Partial(char* srcName, char* dumpName, unsigned short yStart, unsigned short yEnd, unsigned short w)
{
  FILE *picFile, *dumpFile;
  unsigned short buff[ORIGINAL_FILE_WIDTH];
  unsigned int buffSize = ORIGINAL_FILE_WIDTH, writeBuffSize = w;
  unsigned char row, height = yEnd - yStart;
  
   
  picFile = fopen(srcName, "r+b");
  dumpFile = fopen(dumpName, "a+b");
  
  fseek( picFile, yStart * ORIGINAL_FILE_WIDTH * 2, SEEK_SET);
   
  for (row=0; row < height;row++)
  {
	  printf("Writing line %d : 0x%04x 0x%04x \n", row,  *(buff + rand()%w), *(buff + rand()%w));
      fread( buff, 2, buffSize, picFile);
      fwrite( buff, 2, writeBuffSize, dumpFile);  
  }
  fclose(dumpFile);
  fclose(picFile);
  
  return 0;
}

int main(int argc, char* argv[])
{
	if (argc > 0 && strcmp(argv[1], "-h") == 0 ) {
		usage();
	} else {	
		return dump565Partial(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	}
}


