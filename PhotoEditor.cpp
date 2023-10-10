// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: PhotoEditor.cpp
// Author1 and ID and Email:  Philopateer Karam -- 20220246 -- philokrm@gmail.com
// Author2 and ID and Email:  Mahmoud Khaled -- 20220317 -- mahmoudkhaled3177@gmail.com
// Author3 and ID and Email:  Anas Ibrahim -- 20220068 -- ????????

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
                image[i][j] = 255 - image[i][j];        // Subtracts 255 from the pixel value to get the opposite
    }                                                   // shade of gray in intensty
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

    while(angle)                                     // "angle" can be 1 or 2 or 3 depending on number of rotations to reach the desired angle
    {
        for (int i = 0; i < SIZE; i++)               // files a new 2d array (image) with the ol one but
        {                                            // by switching rows and colummns ( or "i" and "j")
            for (int j = SIZE - 1; j >= 0; j--)      // to achieve rotation and starts the columns 
            {                                        // from right to left ([SIZE - j]) to get clockwise rotation
                image_r[i][j] = image[SIZE - j][i];  // One loop rotates 90 degrees clockwise
            }
        }
        angle--;

        for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)       // sets the old image to the new one
                    image[i][j] = image_r[i][j];     // for viewing and saving
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
                image[i][j] += (256 - image[i][j])/2;
            else
                image[i][j] -= (image[i][j]/2);
        }

    }
}

void showmenu()
{
    cout << "Please select a filter to apply or 0 to exit: "<< endl;
    cout << "1- Black & White Filter" << endl;
    cout << "2- Invert Filter" << endl;
    cout << "3- Merge Filter" << endl;
    cout << "4- Flip Image" << endl;
    cout << "5- Rotate Image" << endl;
    cout << "6- Darken And Lighten Image" << endl;
    cout << "l- Load new image" << endl;
    cout << "s- Save image" << endl;
    cout << "0- Exit" << endl;
}

//----------------------------------------------------------------------

int main()
{
    cout<<"           ________________________ \n          |                        | \n          | Grayscale photo Editor |\n          |________________________| \n\n";

    loadImage();

    showmenu();

    char filterNum;

    while(cin >> filterNum)
    {

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

        else if (filterNum == 'l')
        {
            loadImage();
            showmenu();
            continue;
        } 

        else if (filterNum == 's')
        {
            saveImage();
        }
        else
        {
            cout << "Invaled choice" << endl;
            continue;
        }

        showmenu();
    }
}
