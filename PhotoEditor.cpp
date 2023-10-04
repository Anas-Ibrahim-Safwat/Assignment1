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
    cout << "Enter the source image file name: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage(){
    char imageFileName[100];
    cout << "Enter the target image file name: " << endl;
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void blackAndWhite(){

}

void invertImage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
                image[i][j] = 255 - image[i][j];

    }
}

void mergeImages(){

}

void flipImage(){

}

void darkenAndLighten(){

}

void rotateImage(){

}

int main(){
    loadImage();

    cout << "Please select a filter to apply or 0 to exit: "<< endl;
    cout << "1- Black & White Filter" << endl;
    cout << "2- Invert Filter" << endl;
    cout << "3- Merge Filter" << endl;
    cout << "4- Flip Image" << endl;
    cout << "5- Darken And Lighten Image" << endl;
    cout << "6- Rotate Image" << endl;
    cout << "0- Exit" << endl;

    char filterNum;
    while(cin >> filterNum) {

        if (filterNum == '1') {

        } else if (filterNum == '2') {
            invertImage();
        } else if (filterNum == '3') {

        } else if (filterNum == '4') {

        } else if (filterNum == '5') {

        } else if (filterNum == '6') {

        } else {

            return 0;
        }

        saveImage();
    }
}



