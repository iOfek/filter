#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{       
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            int avg = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            avg /=3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
        
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = width/2;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < mid; j++){
            BYTE tmpRed =image[i][j].rgbtRed;
            BYTE tmpGreen =image[i][j].rgbtGreen;
            BYTE tmpBlue =image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;

            image[i][width-1-j].rgbtRed = tmpRed;
            image[i][width-1-j].rgbtGreen = tmpGreen;
            image[i][width-1-j].rgbtBlue = tmpBlue;

        }
        
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    RGBTRIPLE blurred[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int count=0;
            int blue=0,red=0,green=0;
            for (int i = x-1 ; i <= x+1 && i < height; i++)
            {
                for (int j = y-1 ; j <= y+1 && j < width; j++)
                {   
                    if(i >=0 && j >=0){
                        count++;
                        red+= image[i][j].rgbtRed;
                        green+= image[i][j].rgbtGreen;
                        blue+= image[i][j].rgbtBlue;
                    }
                }
            }
            red/=count;
            green/=count;
            blue/=count;
            blurred[x][y].rgbtRed = red;
            blurred[x][y].rgbtGreen = green;
            blurred[x][y].rgbtBlue = blue;
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed= blurred[x][y].rgbtRed;
            image[x][y].rgbtGreen= blurred[x][y].rgbtGreen;
            image[x][y].rgbtBlue= blurred[x][y].rgbtBlue;
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            int xCount =0;
            for (int i = x-1 ; i <= x+1 && i < height; i++)
            {
                int yCount =0;
                for (int j = y-1 ; j <= y+1 && j < width; j++)
                {   
                    if(i >=0 && j >=0){
                    gxBlue += image[i][j].rgbtBlue * gx[xCount][yCount];
                    gyBlue += image[i][j].rgbtBlue * gy[xCount][yCount];
                    gxGreen += image[i][j].rgbtGreen * gx[xCount][yCount];
                    gyGreen += image[i][j].rgbtGreen * gy[xCount][yCount];
                    gxRed += image[i][j].rgbtRed * gx[xCount][yCount];
                    gyRed += image[i][j].rgbtRed * gy[xCount][yCount];
                        
                    }
                    yCount++;
                }
                xCount++;
            }
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            edges[x][y].rgbtBlue = (blue > 255) ? 255 : blue;
            edges[x][y].rgbtGreen = (green > 255) ? 255 : green;
            edges[x][y].rgbtRed = (red > 255) ? 255 : red;
        }
    }
    


    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {   
            image[x][y].rgbtRed = edges[x][y].rgbtRed;
            image[x][y].rgbtGreen = edges[x][y].rgbtGreen;
            image[x][y].rgbtBlue = edges[x][y].rgbtBlue;
        }
    }
    return;
}
