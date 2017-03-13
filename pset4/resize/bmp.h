/**
 * BMP-related data types based on Microsoft's own.
 */

#include <stdint.h>

/**
 * Common Data Types
 *
 * The data types in this section are essentially aliases for C/C++
 * primitive data types.
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 *
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx.
 */
typedef struct
{
    WORD bfType; //Type (fixed as 2 bytes)
    DWORD bfSize; //Size of the BMP file in bytes
    WORD bfReserved1; //Unchanged reserved
    WORD bfReserved2;  //Unchanged reserved
    DWORD bfOffBits; //Offset of the first Byte of the actual image data
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx.
 */
typedef struct
{
    DWORD biSize; //The size of this current header
    LONG biWidth; //Bitmap width in pixels
    LONG biHeight; //Bitmap height in pixels
    WORD biPlanes; //Number of color planes (1, fixed)
    WORD biBitCount; //Number of bits per pixel == color depth (1, 4, 8, 16, 24, 32)
    DWORD biCompression; //Compression method (don't need to change)
    DWORD biSizeImage; //Size of raw bitmap data, can be set to 0 for BI_RGB (?)
    LONG biXPelsPerMeter; //Horizontal pixels per meter (resolution)
    LONG biYPelsPerMeter; //Vertical pixels per meter (resolution)
    DWORD biClrUsed;  //Numbers of colors used in teh palette, unchanged
    DWORD biClrImportant; // Number of important colors used
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * RGBTRIPLE
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 *
 * Adapted from https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx.
 */
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
