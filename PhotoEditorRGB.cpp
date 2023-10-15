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



void mergeImage(){
    //first I took the image that the user want to merge with
    unsigned char merge[SIZE][SIZE][RGB];
    char mergeFileName[100];
    cout << "Enter the source image file name you want to merge with: " << endl;
    cin >> mergeFileName;
    strcat(mergeFileName , ".bmp");
    readRGBBMP(mergeFileName , merge);

    //then I looped on the 3D array and assign every pixel
    //to the average between the original image and the one I want to merge with
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB ; ++k) {
                image[i][j][k] = (image[i][j][k] + merge[i][j][k]) / 2;
            }
        }
    }
}



void darkenAndLighten(){
    cout << "1- Lighten\n2- Darken\n" << endl; // first i asked the user what he wants to do, lighten or darken

    int type;
    cin >> type;   // if he chooses to light the image he will enter 1 , else he will enter 2


    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k < RGB; ++k) {
                if(type == 1){
                    image[i][j][k] += (256 - image[i][j][k]) / 2;
                    // if he chooses to light it, I'll light the pixel by 50% by this equation: image[i][j][k] += (256 - image[i][j][k])/2
                }
                else{
                    image[i][j][k] -= (image[i][j][k] / 2);
                    // And if he chooses 2, I will just minus 50% of the pixel amount by this equation: image[i][j][k] -= image[i][j][k] / 2
                }

            }
            }
        }

    }




void shrinkImage(){
    //First I make temp white image to shrink the original one in it
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k < RGB ; ++k) {
                image2[i][j][k] = 255;
            }
        }
    }

    //I ask the user to choose the dimension he wants to shrink the original image in
    cout << "You want to shrink the image dimensions to: " << endl;
    cout << "1- Half" << endl;
    cout << "2- One third" << endl;
    cout << "3- a Fourth" << endl;
    int shrinkType;
    cin >> shrinkType;
    if(shrinkType == 1){
        // if he chooses 1 I will shrink the image dimensions to half
        // by saving every 2 pixels in the original one in only 1 pixel in the temp image
        for (int i = 0; i < SIZE  ; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k <RGB ; ++k) {
                    image2[i/2][j/2][k] = image[i][j][k];
                }
            }
        }
    }
    else if(shrinkType == 2){
        // if he chooses 2 I will shrink the image dimensions to one third
        // by saving every 3 pixels in the original one in only 1 pixel in the temp image
        for (int i = 0; i < SIZE  ; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k <RGB ; ++k) {
                    image2[i/3][j/3][k] = image[i][j][k];
                }
            }
        }
    }
    else{
        // if he chooses 3 I will shrink the image dimensions to a fourth
        // by saving every 4 pixels in the original one in only 1 pixel in the temp image
        for (int i = 0; i < SIZE  ; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k <RGB ; ++k) {
                    image2[i/4][j/4][k] = image[i][j][k];
                }
            }
        }
    }

    // finally I make the original image equal to the shrinked one to print it
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k <RGB ; ++k) {
                image[i][j][k] = image2[i][j][k];
            }

        }
    }
}



void blur(){
    // first I made a temp image to assign the blurred pixels in
    unsigned char image2[SIZE][SIZE][RGB];

    // The idea of blur is to make every pixel in the image equal to the average of all the pixels around it
    // But, we will face a problem, which is dealing with the pixels on the edges
    // So I made a directional array , one for the index of the row of the pixel I will check that is it in the range or not
    // and the other one for the index of the column of the same pixel

    int dx[] = {-1,-1,-1,0,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,0,1,-1,0,1};

    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            // Now, I made 3 variables for the total values of every part of the pixel [ Red , Green , Blue ]
            // And 3 counters to count how many parts I will take with me ( in the range of the image )
            int tot1 = 0 ,tot2 = 0,tot3 = 0, count1 = 0 ,count2 = 0,count3 = 0;
                for (int l = 0; l < 9 ; ++l) {
                    // Now I looped on the 8 pixels around the pixel i want to blur
                    int nx = i + dx[l];
                    int ny = j + dy[l];
                    if(ny >= 0 && ny < SIZE && nx >= 0 && nx < SIZE){

                        //then checked if that pixel, which is around the pixel I want to blur, is in the range or not
                        // if the pixel in range of the image I will add all of its value [ Red , Green , Blue ] in the (tot) variables
                        // and I will count it as a valid pixel in each counter
                        tot1 += image[nx][ny][0];
                        count1++;
                        tot2 += image[nx][ny][1];
                        count2++;
                        tot3 += image[nx][ny][2];
                        count3++;
                }
                }
            //after that I will get the average of every valid pixel part [RGB]
            // by dividing those value on the amount of them
            image2[i][j][0] = tot1 / count1;
            image2[i][j][1] = tot2 / count2;
            image2[i][j][2] = tot3 / count3;
        }
    }

    // finally i will make the image I want to print = the blured image
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k <RGB ; ++k) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
    // I noticed that the degree of blur is not as same as the one on the sample PDF for filters
}
void blurImage(){
    // so I repeated the function 10 times to approach the same blur as the PDF filter
    blur();
    blur();
    blur();
    blur();
    blur();
    blur();
    blur();
    blur();
    blur();
    blur();
}



void skewImageHorizontally(){
    // first I made 2 white temp images
    // one I will shrink the original image in
    // the other one I will skew the shrank image in
    unsigned char image2[SIZE][SIZE][RGB];
    unsigned char image3[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB ; ++k) {
                image2[i][j][k] = 255;
                image3[i][j][k] = 255;
            }

        }
    }

    // now I will take the angle from the user
    double angle;
    cin >> angle;
    angle = 90 - angle;  // I did that because you want the angle that is complementary to the angle I am dealing with
    angle = (angle * 22) / (180 * 7);

    int x = (int)(SIZE / ( 1 + 1/tan(angle))); // this equation is the base I will shrink the original image in


    double step = SIZE - x;   // this is the starting position to put the pixels in the skewed image
    double move = step/ SIZE;   // this is the move I will take back to make the image skewed


    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            for (int k = 0; k <RGB ; ++k) {
                // now I shrank the original image in ( x / SIZE ) of the columns
                image2[i][(j*x)/SIZE][k] = image[i][j][k];
            }

        }
    }

    for (int i = 0; i <SIZE ; ++i) {
        for (int j = (int)step; j < step+x ; ++j) {
            for (int k = 0; k <RGB ; ++k) {
                // Now, I will start sorting the index from the starting position till complete the same size of shrank base
                //Every row I start copying the pixels from the shrank image, I want to make sure that I'm taking pixels
                // from the first column
                image3[i][j][k] = image2[i][(int)(j-step)][k];
            }

        }
        // after that I start the new row of pixels from the new column, which will be
        // starting position - the move i will take back
        step -= move;
    }

    //finally I make the original image equal to the skewed one to print it
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k <RGB ; ++k) {
                image[i][j][k] = image3[i][j][k];
            }

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
           mergeImage();
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
            darkenAndLighten();
        } 

        else if (filterNum =='7'){
            detect();
        }
        else if (filterNum == '8'){

        }
        else if (filterNum == '9'){
             shrinkImage();
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
            blurImage();
        }
        else if (filterNum == 'd'){
            cout << "please enter  x ,y ,length ,width :  ";
            int x,y,length,width;
            cin >> x >> y >> length >> width;
            crop( x , y , length , width ) ;
        }
        else if (filterNum == 'e'){
            skewImageHorizontally();
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
