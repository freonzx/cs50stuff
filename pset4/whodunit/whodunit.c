#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //checks for proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: whodunit clue veridict\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    //open output file
    FILE *outptr = fopen(outfile, "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "Could not create %s\n", outfile);
        return 3;
    }
    //read bf and bi headers
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    //calculates padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; ++i)
    {
        for (int j = 0; j < bi.biWidth; ++j)
        {
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            //printf("Red:%x Green: %x Blue: %x  \n", triple.rgbtRed,triple.rgbtGreen,triple.rgbtBlue);
            if (triple.rgbtRed == 255 && triple.rgbtGreen == 0 && triple.rgbtBlue == 0)
            {
                triple.rgbtRed = 0;
                triple.rgbtBlue = 255;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            else if (triple.rgbtRed == 255 && triple.rgbtGreen == 255 && triple.rgbtBlue == 255)
            {
                triple.rgbtRed = 0;
                triple.rgbtGreen = 0;
                triple.rgbtBlue = 0;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            else
    	    {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    return 0;
}