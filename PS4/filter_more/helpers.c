#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int color = (int)((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = color;
            image[i][j].rgbtGreen = color;
            image[i][j].rgbtRed = color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0 ; i < height ; i++ ){
        for(int j = 0 ; j < width/2 ; j++){
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

int aver(int height,int width, RGBTRIPLE image[height][width], int i, int j, int color){
    int sum = 0;
    int count = 0;
    for(int k = i - 1 ; k <= i + 1 ; k++){
        for(int l = j - 1 ; l <= j + 1 ; l++){
            if(k >= 0 && k < height && l >= 0 && l < width){
                if(color == 0){
                    sum += image[k][l].rgbtBlue;
                }
                else if(color == 1){
                    sum += image[k][l].rgbtGreen;
                }
                else{
                    sum += image[k][l].rgbtRed;
                }
                count++;
            }
        }
    }
    return sum/count;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            int blue = aver(height, width, image, i, j, 0);
            int green = aver(height, width, image, i, j, 1);
            int red = aver(height, width, image, i, j, 2);
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtRed = red;
        }
    }
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            image[i][j] = temp[i][j];
        }
    }
    return;
}

int sober_x(int height, int width, RGBTRIPLE image[height][width], int i , int j , int color, int gx[3][3], int gy[3][3])
{
    int sum = 0;
    for(int k = 0 ; k <= 2 ; k++){
        for(int l = 0 ; l <= 2 ; l++){
            if(i - 1 + k >= 0 && i - 1 + k < height && j - 1 + l >= 0 && j - 1 + l < width){
                if(color == 0){
                    sum += image[k][l].rgbtBlue * gx[k][l];
                }
                else if(color == 1){
                    sum += image[k][l].rgbtGreen * gx[k][l];
                }
                else{
                    sum += image[k][l].rgbtRed * gx[k][l];
                }
            }
        }
    }
    return sum/9; 
}

int sober_y(int height, int width, RGBTRIPLE image[height][width], int i , int j , int color, int gx[3][3], int gy[3][3])
{
    int sum = 0;
    for(int k = 0 ; k <= 2 ; k++){
        for(int l = 0 ; l <= 2 ; l++){
            if(i - 1 + k >= 0 && i - 1 + k < height && j - 1 + l >= 0 && j - 1 + l < width){
                if(color == 0){
                    sum += image[k][l].rgbtBlue * gy[k][l];
                }
                else if(color == 1){
                    sum += image[k][l].rgbtGreen * gy[k][l];
                }
                else{
                    sum += image[k][l].rgbtRed * gy[k][l];
                }
            }
        }
    }
    return sum/9; 
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int blue_x = sober_x(height, width, image, i, j, 0, gx , gy);
            int green_x = sober_x(height, width, image, i, j, 1, gx, gy);
            int red_x = sober_x(height, width, image, i, j, 2, gx, gy);
            int blue_y = sober_y(height, width, image, i, j, 0, gx , gy);
            int green_y = sober_y(height, width, image, i, j, 1, gx, gy);
            int red_y = sober_y(height, width, image, i, j, 2, gx, gy);
            temp[i][j].rgbtBlue = round(sqrt(blue_x * blue_x + blue_y * blue_y));
            temp[i][j].rgbtGreen = round(sqrt(green_x * green_x + green_y * green_y));
            temp[i][j].rgbtRed = round(sqrt(red_x * red_x + red_y * red_y));

            if(temp[i][j].rgbtBlue > 255){
                temp[i][j].rgbtBlue = 255;
            }
            if(temp[i][j].rgbtGreen > 255){
                temp[i][j].rgbtGreen = 255;
            }
            if(temp[i][j].rgbtRed > 255){
                temp[i][j].rgbtRed = 255;
            }
        }
    }
    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            image[i][j] = temp[i][j];
        }
    }
    return;
}
