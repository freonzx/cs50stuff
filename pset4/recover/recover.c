#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Ensure proper usage
if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover raw_data_file\n");
        return 1;
    }
    // saves file name
    char *infile = argv[1];
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    //creates buffer
    unsigned char buffer[512];
    //variable that will hold image count
    int jpgindex=0;
    //bool to check if we current working on a file
    int working=0;
    //declaring pointer so we can use it latter
    FILE *outptr = NULL;
    
    while(fread(buffer, 512, 1, inptr)){
        
        //checks for start of JPG
        if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
        {
            //if we were working on a jpg already, close it
            if (working == 1){
                fclose(outptr);
            }else{
                working = 1;
            }
            //printf("%x %x %x %x\n",buffer[0],buffer[1],buffer[2],buffer[3]);
            char filename[3];
            sprintf(filename,"%03i.jpg",jpgindex);
            outptr = fopen(filename, "a");
            jpgindex++;
        }
        if(working == 1)
        {
            fwrite(&buffer, 512, 1, outptr);
        }
    }
    //closing Fpointers
    fclose(inptr);
    fclose(outptr);
    return 0;
}