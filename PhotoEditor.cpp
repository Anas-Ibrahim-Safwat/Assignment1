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

void detect(){
    unsigned char image_bw[SIZE][SIZE];    // Convert image to black and white to make it easier to find the edges
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
                image_bw[i][j] = 255;
            else 
                image_bw[i][j] = 0;
        }
    }

       for (int i = 1; i < SIZE-1 ; ++i) {
        for (int j = 1; j < SIZE-1 ; ++j) {
           if(image_bw[i-1][j] != image_bw[i+1][j] || image_bw[i][j-1] != image_bw[i+1][j+1]  ){
           image[i][j]=image_bw[i][j];        // To find the edge, we stop at each pixel and compare the pixel after it and the pixel before it,
           }                                  // then compare the pixel above it and the pixel below it.
           else{                              //  If the values are different, then the pixel is this edge, and if not, we make it white
            image[i][j] = 255; 
           }
        }}
}








void mirror(int n){
    if(n==1){  //left
     for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE/2 ; ++j) {
            image[i][SIZE-j]=image[i][j];
        }}

    }
    else if(n==2){//right
        for (int i = 0; i < SIZE ; ++i) {
        for (int j = 128; j < SIZE ; ++j) {
            image[i][SIZE-j]=image[i][j];
        }}

    }
    else if(n==3){//upper
        for (int i = 0; i < SIZE/2 ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            image[SIZE-i][j]=image[i][j];
        }}

    }
    else if(n==4){//down
        for (int i = 128; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            image[SIZE-i][j]=image[i][j];
        }}

    }


}



void shrinkImage(){
    //First I make temp white image to shrink the original one in it
    unsigned char image2[SIZE][SIZE];    
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            image2[i][j] = 255;
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
                image2[i/2][j/2] = image[i][j];
            }
        }
    }
        
    else if(shrinkType == 2){
        // if he chooses 2 I will shrink the image dimensions to one third 
        // by saving every 3 pixels in the original one in only 1 pixel in the temp image
        for (int i = 0; i < SIZE  ; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i/3][j/3] = image[i][j];
            }
        }
    }
    else{
        // if he chooses 3 I will shrink the image dimensions to a fourth 
        // by saving every 4 pixels in the original one in only 1 pixel in the temp image
        for (int i = 0; i < SIZE  ; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i/4][j/4] = image[i][j];
            }
        }
    }
    
    // finally I make the original image equal to the shrinked one to print it
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}








void crop(int x,int y , int length,int width){
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            if (i < x || i > x+length || j < y || j > y+width ){
                image[i][j]=255;

            }
        }}

}



void blur(){
    // first I made a temp image to assign the blured pixels in
    unsigned char image2[SIZE][SIZE];

    // The idea of blur is to make every pixel in the image equal to the average of all the pixels around it
    // But, we will face a problem, which is dealing with the pixels on the edges
    // So I made a directional array , one for the index of the row of the pixel I will check that is it in the range or not
    // and the other one for the index of the column of the same pixel
    int dx[] = {-1,-1,-1,0,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,0,1,-1,0,1};
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            // Now I made 2 variables, one for the total values of the pixels around the one i want to blur
            // and the other one will count how many pixels I will take ( in the range of the image )
            int tot = 0  , count = 0;
            for (int k = 0; k < 9 ; ++k) {
                // Now I looped on the 8 pixels around the pixel i want to blur
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(ny >= 0 && ny < SIZE && nx >= 0 && nx < SIZE){
                    //then checked if that pixel, which is around the pixel I want to blur, is in the range or not
                    // if the pixel in range of the image I will add its value in the (tot) variable
                    // and I will count it as a valid pixel (count++)
                    tot += image[nx][ny];
                    count++;
                }
            }
            //after that I will get the average of every valid pixel 
            // by dividing those value on the amount of them
            image2[i][j] = tot / count;
        }
    }
    
    // finally i will make the image I want to print = the blured image
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
    // I noticed that the degree of blur is not as same as the one on the sample PDF for filters
}


void blurImage(){
    // so I repeated the function 6 times to approach the same blur as the PDF filter
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
    unsigned char image2[SIZE][SIZE];
    unsigned char image3[SIZE][SIZE];
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255;
            image3[i][j] = 255;
        }
    }

    // now I will take the angle from the user
    double angle;
    cin >> angle;
    angle = 90 - angle;  // I did that because you want the angle that is complementary to the angle I am dealing with
    angle = (angle * 22) / (180 * 7);
    
    int x = (int)(SIZE / ( 1 + 1/tan(angle))); // this equation is the base I will shrink the original image in
    
    double step = SIZE - x; // this is the starting position to put the pixels in the skewed image
    double move = step/ SIZE; // this is the move I will take back to make the image skewed
    
    for (int i = 0; i < SIZE ; ++i) {
        for (int j = 0; j < SIZE ; ++j) {
            // now I shrank the original image in ( x / SIZE ) of the columns 
            image2[i][(j*x)/SIZE] = image[i][j];
        }
    }

    for (int i = 0; i <SIZE ; ++i) {
        for (int j = (int)step; j < step+x ; ++j) {
            // Now, I will start sorting the index from the starting position till complete the same size of shrank base
            //Every row I start copying the pixels from the shrank image, I want to make sure that I'm taking pixels
            // from the first column
            
            image3[i][j] = image2[i][(int)(j-step)];// ----> So i do (j - step)
        }
        
        // after that I start the new row of pixels from the new column, which will be 
        // starting position - the move i will take back
        
        step -= move;
    }
    //finally I make the original image equal to the skewed one to print it
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image3[i][j];
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
