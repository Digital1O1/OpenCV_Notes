// https://docs.opencv.org/4.x/d6/d6d/tutorial_mat_the_basic_image_container.html

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat original_image = imread(image_path, IMREAD_COLOR);
    //printf("Shape : %p \r\n", original_image.size());
    cout << "Size of image : " << original_image.size() << endl;
    //cout << "M = " << endl << " " << original_image << endl << endl;

    Mat cropped_image;           //Rect(int x,int y,int width, int height)
    cropped_image = original_image(Rect(300, 300, 240, 240));
    namedWindow("Original Image"); //Declaring an window to show actual image//
    namedWindow("Cropped Image"); //Declaring an window to show ROI//


    if (original_image.empty())
    {
        std::cout << "could not read the image: " << image_path << std::endl;
        return 1;
    }
    //imshow("display window", original_image);
    imshow("Original Image", original_image);
    imshow("Cropped Image", cropped_image);
    int k = waitKey(0); // wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("starry_night.png", original_image);
    }
    return 0;
}