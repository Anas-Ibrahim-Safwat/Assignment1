// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: PhotoEditor.cpp
// Author1 and ID and email:  Philopateer Karam -- 20220246  -- philokrm@gmail.com
// Author2 and ID and email:  Mahmoud Khaled -- 20220317  -- 
// Author3 and ID and email:  Anas Ibrahim -- 20220068  -- 

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage();
void saveImage();
void blackAndWhite();
void invertImage();
void mergeImages();
void flipImage(int n);
void darkenAndLighten();
void rotateImage(int angle);


int main()
{
     //the name of program
    cout<<"           ______________________ \n          |                      | \n          | photo Editor program |\n          |______________________| \n\n\n";

    loadImage();

    while (true){
    // the menu
    cout << "Please choose your option from the following: "<< endl;
    cout << "1- Black & White Filter" << endl;
    cout << "2- Invert Filter" << endl;
    cout << "3- Merge Filter" << endl;
    cout << "4- Flip Image" << endl;
    cout << "5- Rotate Image" << endl;
    cout << "6- Darken And Lighten Image" << endl;
    cout << "a- save image" << endl;
    cout << "b- Add another filter" << endl;
    cout << "c- Enter another image" << endl;
    cout << "0- Exit" << endl;
    cout << "your choice is : ";

    char filterNum;
    cin >> filterNum;
    if (filterNum == '1')
        {
            blackAndWhite();
            cout<<"It's done\n";
        } 

        else if (filterNum == '2')
        {
            invertImage();
            cout<<"It's done\n";
        } 

        else if (filterNum == '3')
        {
            mergeImages();
            cout<<"It's done\n";
        } 

        else if (filterNum == '4')
        {
            cout << "If you want to flip the photo horizontally enter 1" << endl;
            cout << "If you want to flip the photo vertically  enter 2" << endl;
            int n;
            cin>>n;
            flipImage(n);
            cout<<"It's done\n";
        } 

        else if (filterNum == '5')
        {
            int angle = 0;

            cout << "Please select an angle to rotate: ";
            cout << "\n\n1- 90\n2- 180\n3- 270\n";
            
            cin >> angle;
            rotateImage(angle);
            cout<<"It's done\n";
        } 

        else if (filterNum == '6')
        {
            darkenAndLighten();
            cout<<"It's done\n";
        } 
         else if (filterNum == 'a')
        {  
            saveImage();
            cout<<"It's done\n";
        } 
         else if (filterNum == 'b')
        {  
            continue;
        }
         else if (filterNum == 'c')
        {  
            loadImage();
        }  
         else if (filterNum == '0'){
            return 0;
         }
          
          else {
            cout<<"wrong number ,choose a number in the mnue.\n";
           
        }

        
    }
}



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

void blackAndWhite()
{
    int sum = 0;
    for (int i = 0; i < SIZE; i++)   // Nested loop to calculate the sum of the value of each pixel 

    {
        for (int j = 0; j < SIZE; j++) 
        {
            sum += image[i][j];
        }
    }

    int average = sum / (SIZE*SIZE);  //calculate the average

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (image[i][j] > average)    //If the value of the pixels is greater than the average, we will replace its value to 255 (white)
                image[i][j] = 255;
            else 
                image[i][j] = 0;          //If the value of the pixels is less than the average, we will replace its value to 0 (black)
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

    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            image[i][j] = (image[i][j] + mergeImage[i][j]) / 2;
        }
    }
}


void flipImage(int n) 
{
    if (n == 1){  //horizontally 
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) { 
                /*In each row we change the value of the first pixel with the last pixel
                and then the value of the second pixel with the penultimate pixel and so on
                until we reach the middle of the row*/ 
                int num = image[i][j];
                image[i][j] = image[i][SIZE - j];
                image[i][SIZE - j] = num;
            }
        }
    }
    else{ //vertically 
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2 ; j++) {
                /*In each column we change the value of the first pixel with the last pixel
                and then the value of the second pixel with the penultimate pixel and so on
                until we reach the middle of the column*/ 
                int num = image[j][i];
                image[j][i] = image[SIZE-j][i];
                image[SIZE-j][i] = num;
            }
        }
    }
}


void darkenAndLighten()
{
   cout << "If you want to make the photo lighter enter 1" << endl;
    cout << "If you want to make the photo darker enter 2" << endl;
    int type;
    cin >> type;

    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            if(type == 1){
                if((image[i][j] + (image[i][j]) / 2) > 255){
                    image[i][j] = 255;
                }
                else{
                    image[i][j] += (image[i][j]) / 2;
                }
            }
            else{
                if(image[i][j] - ((image[i][j]) / 2) < 0){
                    image[i][j] = 0;
                }
                else{
                    image[i][j] -= (image[i][j]) / 2;
                }
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
