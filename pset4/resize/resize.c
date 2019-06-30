// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames and gets resize factor n
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]);
    
    if(n < 1 || n > 100)
    {
        fprintf(stderr, "N must be positive and less or equal to 100\n");
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //creates a copy of bi to hold old values
    BITMAPINFOHEADER biold = bi;
    
    bi.biWidth *= n;
    bi.biHeight *= n;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // determine padding for scanlines and old padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldpadding = (4 - (biold.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //calculates new sizes for headers
    bi.biSizeImage = ((3 * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biold.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for(int g = 0; g < n; g++)
        {
            for (int j = 0; j < biold.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // write RGB triple to outfile x factor
                for(int h = 0; h < n; h++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            //wirtes the new padding
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            //checks and rewinds to start of the line
            if (g < n - 1)
            {
                    fseek(inptr, -(biold.biWidth * (int)sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
