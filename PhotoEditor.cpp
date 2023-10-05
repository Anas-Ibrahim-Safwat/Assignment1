// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: PhotoEditor.cpp
// Author1 and ID:  Philopateer Karam -- 20220246
// Author2 and ID:  Mahmoud Khaled -- 20220317
// Author3 and ID:  Anas Ibrahim -- 20220068

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];


void loadImage(){
    char imageFileName[100];
    cout << "Enter the source image file name to load: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}


void saveImage()
{
    char imageFileName[100];
    cout << "Enter the target image file name to save: " << endl;
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//----------------------------------------------------------------------------

void blackAndWhite()
{
    int average = 0;
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            average += image[i][j];
        }
    }

    average /= (SIZE*SIZE);

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (image[i][j] > average)
                image[i][j] = 255;
            else 
                image[i][j] = 0;
        }
    }
}


void invertImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
                image[i][j] = 255 - image[i][j];
    }
}


void mergeImages()
{
    unsigned char mergeImage[SIZE][SIZE];
    char mergeImageFileName[100];

    cout << "Enter the image file name you want to merge this image with: " << endl;
    cin >> mergeImageFileName;

    strcat (mergeImageFileName, ".bmp");
    readGSBMP(mergeImageFileName, mergeImage);

    for (int i = 0; i < SIZE ; ++i)
    {
        for (int j = 0; j < SIZE ; ++j) 
        {
            image[i][j] = (image[i][j] + mergeImage[i][j]) / 2;
        }
    }
}


void flipImage(int n) 
{
    if (n == 1)
    {
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE / 2; j++) 
            {
                int num = image[i][j];
                image[i][j] = image[i][SIZE - j];
                image[i][SIZE - j] = num;
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE/2 ; j++) 
            {
                int num = image[j][i];
                image[j][i] = image[SIZE-j][i];
                image[SIZE-j][i] = num;
            }
        }
    }
}

void rotateImage(int angle)
{
    unsigned char image_r[SIZE][SIZE];

    while(angle)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = SIZE - 1; j >= 0; j--)
            {
                image_r[i][j] = image[SIZE - j][i];
            }
        }
        angle--;

        for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    image[i][j] = image_r[i][j];
            }
    }
}


void darkenAndLighten()
{
    cout << "1- Lighten\n2- Darken\n" << endl;

    int type;
    cin >> type;

    for (int i = 0; i < SIZE ; ++i) 
    {
        for (int j = 0; j < SIZE ; ++j) 
        {
            if(type == 1)
            {
                if((image[i][j] + (image[i][j]) / 2) > 255)
                    image[i][j] = 255;
                else
                    image[i][j] += (image[i][j]) / 2;
            }
            else
            {
                if(image[i][j] - ((image[i][j]) / 2) < 0)
                    image[i][j] = 0;
                else
                    image[i][j] -= (image[i][j]) / 2;
            }
        }

    }
}

//----------------------------------------------------------------------

int main()
{
    loadImage();

    cout << "Please select a filter to apply or 0 to exit: "<< endl;
    cout << "1- Black & White Filter" << endl;
    cout << "2- Invert Filter" << endl;
    cout << "3- Merge Filter" << endl;
    cout << "4- Flip Image" << endl;
    cout << "5- Rotate Image" << endl;
    cout << "6- Darken And Lighten Image" << endl;
    cout << "0- Exit" << endl;

    char filterNum;

    while(cin >> filterNum) {

        if (filterNum == '1')
        {
            blackAndWhite();
        } 

        else if (filterNum == '2')
        {
            invertImage();
        } 

        else if (filterNum == '3')
        {
            mergeImages();
        } 

        else if (filterNum == '4')
        {
            int n = 0;

            cout << "choose axis: \n";
            cout << "1- horizontal\n2- vertical\n";

            cin >> n;

            flipImage(n);
        } 

        else if (filterNum == '5')
        {
            int angle = 0;

            cout << "Please select an angle to rotate: ";
            cout << "\n\n1- 90\n2- 180\n3- 270\n";
            
            cin >> angle;
            rotateImage(angle);
        } 

        else if (filterNum == '6')
        {
            darkenAndLighten();
        } 

        else
            return 0;

        saveImage();
    }
}
