// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: PhotoEditor.cpp
// Author1 and ID and Email:  Philopateer Karam -- 20220246 -- philokrm@gmail.com
// Author2 and ID and Email:  Mahmoud Khaled -- 20220317 -- mahmoudkhaled3177@gmail.com
// Author3 and ID and Email:  Anas Ibrahim -- 20220068 -- anashima799@gmail.com

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
    int sum = 0;
    for (int i = 0; i < SIZE; i++)        // Nested loop to calculate the sum of the value of each pixel 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            sum += image[i][j];
        }
    }

    int average = sum / (SIZE*SIZE);     //calculate the average

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (image[i][j] > average)  //If the value of the pixels is greater than the average, we will replace its value to 255 (white)
                image[i][j] = 255;
            else 
                image[i][j] = 0;       //If the value of the pixels is less than the average, we will replace its value to 0 (black)
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
    unsigned char mergeImage[SIZE][SIZE];    //first i took the image that the user want to merge with
    char mergeImageFileName[100];
    cout << "Enter the image file name you want to merge this image with: " << endl;
    cin >> mergeImageFileName;

    strcat (mergeImageFileName, ".bmp");
    readGSBMP(mergeImageFileName, mergeImage);

    for (int i = 0; i < SIZE ; ++i)      //then i looped on the 2D array and assign every pixel 
        for (int j = 0; j < SIZE ; ++j)  //to the average between the original image and the one i want to merge with
    {
        {
            image[i][j] = (image[i][j] + mergeImage[i][j]) / 2;
        }
    }
}


void flipImage(int n) 
{
    if (n == 1)  //horizontal
    {
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE / 2; j++) 
            {
                int num = image[i][j];             //In each row we change the value of the first pixel with the last pixel
                image[i][j] = image[i][SIZE - j]; //and then the value of the second pixel with the penultimate pixel and so on
                image[i][SIZE - j] = num;        //until we reach the middle of the row
            }
        }
    }

    else     //vertical
    {
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j < SIZE/2 ; j++) 
            {
                int num = image[j][i];            //In each column we change the value of the first pixel with the last pixel
                image[j][i] = image[SIZE-j][i];  //and then the value of the second pixel with the penultimate pixel and so on
                image[SIZE-j][i] = num;         //until we reach the middle of the column
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
    cout << "1- Lighten\n2- Darken\n" << endl; // first i asked the user what he wants to do, lighten or darken

    int type;
    cin >> type;                              // if he chooses to light the image he will enter 1 , else he will enter 2

    for (int i = 0; i < SIZE ; ++i) 
    {
        for (int j = 0; j < SIZE ; ++j) 
        {
            if(type == 1)                              
                image[i][j] += (256 - image[i][j])/2;    // if he chooses to light it, i'll light the pixel by 50% by this equation: image[i][j] += (256 - image[i][j])/2
            else
                image[i][j] -= (image[i][j]/2);          // And if he chooses 2, i will just minus 50% of the pixel amount by this equation: image[i][j] -= image[i][j] / 2
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
    cout << "Your choice is: ";

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
        else if (filterNum == '0')
        {
            cout << "App closed" << endl;
            cout << "Thank you" << endl;
            return 0;
        }
        else
        {
            cout << "Invaled choice" << endl;
            continue;
        }

        showmenu();

        cout << "Your choice is: ";
    }
}
