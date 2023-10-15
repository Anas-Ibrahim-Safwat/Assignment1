// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: PhotoEditorRGB.cpp
// Author1 and ID and Email:  Philopateer Karam -- 20220246 -- philokrm@gmail.com
// Author2 and ID and Email:  Mahmoud Khaled -- 20220317 -- mahmoudkhaled3177@gmail.com
// Author3 and ID and Email:  Anas Ibrahim -- 20220068 -- anashima799@gmail.com

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];


void loadImage(){
    char imageFileName[100];
    cout << "Enter the source image file name to load: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}


void saveImage()
{
    char imageFileName[100];
    cout << "Enter the target image file name to save: " << endl;
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//---------------------------------------------------------------------------- 


void blackAndWhite()
{
      for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int t = 0; t < 3; t++)
            {
                if ((image[i][j][0]+image[i][j][1]+image[i][j][2])/3 > 128)
                    image[i][j][t] = 255;    //If the average of the pixels is greater than 128, we will replace its value to 255 (white)
                else 
                    image[i][j][t] = 0;      //If the average of the pixels is less than 128, we will replace its value to 0 (black)
            }
        }
    }
}

void flipImage(int n) 
{
    if (n == 1){    //horizontal
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                for(int t=0;t<3;t++){
                int num = image[i][j][t];               //In each row we change the value of the first pixel with the last pixel
                image[i][j][t] = image[i][SIZE - j][t]; //and then the value of the second pixel with the penultimate pixel and so on
                image[i][SIZE - j][t] = num;            //until we reach the middle of the row
                }
            }
        }
    }
    else{      //vertical
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE/2 ; j++) {
                for(int t=0;t<3;t++){
                int num = image[j][i][t];              //In each column we change the value of the first pixel with the last pixel
                image[j][i][t] = image[SIZE-j][i][t];  //and then the value of the second pixel with the penultimate pixel and so on
                image[SIZE-j][i] [t]= num;             //until we reach the middle of the column
                }                  
            }
        }
    }
}


void detect(){
    
    unsigned char image_bw[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++)   // Convert image to black and white to make it easier to find the edges
    {
        for (int j = 0; j < SIZE; j++) 
        {
            for(int t = 0; t < 3; t++)
            {
                if ((image[i][j][0]+image[i][j][1]+image[i][j][2])/3 > 128)
                    image_bw[i][j][t] = 255;
                else 
                    image_bw[i][j][t] = 0;
            }
        }
    }

       for (int i = 1; i < SIZE-1 ; ++i) {
        for (int j = 1; j < SIZE-1 ; ++j) {
            for(int t=0;t<3;t++){
           if(image_bw[i-1][j][t] != image_bw[i+1][j][t] || image_bw[i][j-1][t] != image_bw[i+1][j+1][t]  ){
           image[i][j][t]=image_bw[i][j][t];            // To find the edge, we stop at each pixel and compare the pixel after it and the pixel before it,
           }                                            // then compare the pixel above it and the pixel below it.
           else{                                        //  If the values are different, then the pixel is this edge, and if not, we make it white
            image[i][j][t] = 255;                       
           }
            }
        }}
}



void mirror(int n){
    if(n==1){  //left
     for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE/2 ; ++j) {
            for(int t=0;t<3;t++){
            image[i][SIZE-j][t]=image[i][j][t];
            }
        }}

    }
    else if(n==2){//right
        for (int i = 0; i < SIZE ; ++i) {
        for (int j = 128; j < SIZE ; ++j) {
             for(int t=0;t<3;t++){
            image[i][SIZE-j][t]=image[i][j][t];
             }
        }}

    }
    else if(n==3){//upper
        for (int i = 0; i < SIZE/2 ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
             for(int t=0;t<3;t++){
            image[SIZE-i][j][t]=image[i][j][t];
             }
        }}

    }
    else if(n==4){//down
        for (int i = 128; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
             for(int t=0;t<3;t++){
            image[SIZE-i][j][t]=image[i][j][t];
             }
        }}

    }


}









void crop(int x,int y , int lenth,int width){
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            for(int t=0;t<3;t++){
            if (i < x || i > x+lenth || j < y || j > y+width ){
                image[i][j][t]=255;

            }
            }
        }}

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
    cout << "7- Detect Image Edges" << endl;
    cout << "8- Enlarge Image" << endl;
    cout << "9- Shrink Image" << endl;
    cout << "a- Mirror 1/2 Image" << endl;
    cout << "b- Shuffle Image" << endl;
    cout << "c- Blur Image" << endl;
    cout << "d- Crop Image" << endl;
    cout << "e- Skew Image Right" << endl;
    cout << "f- Skew Image Up" << endl;
    cout << "l- Load new image" << endl;
    cout << "s- Save image" << endl;
    cout << "0- Exit" << endl;
}

//----------------------------------------------------------------------

int main()
{
    cout<<"           ________________________ \n          |                        | \n          | RGB photo Editor |\n          |________________________| \n\n";

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
            
        } 

        else if (filterNum == '3')
        {
           
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
            
        } 

        else if (filterNum == '6')
        {

        } 

        else if (filterNum =='7'){
            detect();
        }
        else if (filterNum == '8'){

        }
        else if (filterNum == '9'){
            
        }
        else if (filterNum == 'a'){
            cout << "Please select a mirror side: \n";
            cout << "\n1- left\n2- right\n3- upper\n4- down\n";
            int n;
            cin>>n;
            mirror(n);
        }
        else if (filterNum == 'b'){
            
        }
        else if (filterNum == 'c'){
            
        }
        else if (filterNum == 'd'){
            cout << "please enter  x ,y ,length ,width :  ";
            int x,y,length,width;
            cin >> x >> y >> length >> width;
            crop( x , y , length , width ) ;
        }
        else if (filterNum == 'e'){
            
        }
        else if (filterNum == 'f'){
            
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
