# [How to scan images, lookup tables and time measurement with OpenCV](https://docs.opencv.org/4.x/db/da5/tutorial_how_to_scan_images.html)

<br>

# Main goal

-   How to go through each and every pixel of an image?
-   How are OpenCV matrix values stored?
-   How to measure the performance of our algorithm?
-   What are lookup tables and why use them?

<br>

# Our Test Case : Simple color reduction method

## What is it?

Uses a **<u>unsigned char</u>** to store stuff in a matrix

-   A single pixel in a channel can have <u>**up to 256 different values**</u>
-   Single three channel image --> ~16 million colors
    -   Working with that many channels will slow down algorithm performance
-   For this case : We're using <u>**color space reduction**</u>
    -   Pretty common
    -   How to accomplish that
        -   Divide the **<u>color space current value</u>** with the **<u>new input value</u>** --> Fewer colors
    -   Example : Every value between 0 and 9 takes new value 0
        -   Every value between 10 --> 19 = The value 10, ect.

<br>

## When dividing an unsigned char (uchar) with another int value

You'll get a char value back

-   Any remainders after division from this operation **<u>will be rounded down </u>**
    -   Dividing an unsigned char can be expressed mathmatically as :
        -   ### I<sub>new</sub> = (I<sub>old</sub> / 10) x 10

<br>

## Simple color space reduction algorithm

Would consist of just pass through **<u>every pixel</u>** of an image matrix

-   And apply this formula : I<sub>new</sub> = (I<sub>old</sub> / 10) x 10
-   The division and multiplication operation are **<u>computationally expensive</u>**
    -   Try to keep mathmatical operations to just addition and subtraction
-   Also keep in mind
    -   Have limited number of input values for upper operation
    -   In the case of a Unsigned Char system --> 256

<br>

## For larger images

Try to calculate all possible values before/during the assignment just to make the assignment

-   I have no idea what that means...
-   But it's recommended to use a **<u>look up table</u>**
    -   What are they?
        -   Simple arrays
        -   For a given input value variation holds the final output value
    -   Best part about look up tables
        -   You don't need to calculate anyhting
        -   Just need the results

<br>

## The test case program does the following

1. Read a image passed as a CLI argument
    - Image could be colored or grayscaled
2. Apply reduction with the provided integer value
    - In OpenCV, there's 3 major ways of going through an image pixel by pixel

-   To make things interesting
    -   We'll scan each image using the mentioned 3 methods to go through the entire image to see how long it'll take

### Source code here : https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/core/how_to_scan_images/how_to_scan_images.cpp

<br>

## Pratical Use Cases for Color Space Reduction

### 1) Image compression

-   Reducing number of colors --> significantly reduce file size w/o compromising visual quality
-   Reducing color space lets you quantize the image colors to a lmited set of representative colors
    -   Results in:
        -   Reduced memory requirements
        -   Faster data transmission over networks

<br>

### 2) Image Analysis and Processing

-   With certain imaging analysis tasks, reducing color space can:
    -   Simplify the image representation
    -   Make it easier to extract meaningful information, such as:
        -   Object recognition
            -   Reducing the color space lets --> Allows you to focus on most distinguished color feature(s) of an object
            -   Maing it easier to differentiate/classify them
        -   Sementation and region extraction
            -   Color space reduction helps with segmenting images by
                -   Grouping similar colors together
                -   Enabling easier extraction of regions/objects of interest
        -   Augmented Reality and Computer Vision
            -   Color space reduction useful in CV applications involved in
                -   Object detection
                -   Tracking
                -   Marker based tracking
                -   Reducing the color space --> helps isolate specific markers/bojects of interest

<br>

# How's the image matrix stored in memory?

## Size of the matrix depends on the color system used

-   Specifically the number of channels used
-   Depicted below are the channels for both a **<u>grayscale and multichannel</u>** using a BGR color system
    -   The order of the channels is inverse from RGB --> BGR
    -   Since in alot of cases memory is large eough to store the rows in a successive manner
        -   Creating a single long row
        -   Since everything is in a single place one right after another, this may help speed up the scanning process
        -   We can use **<u>cv::Mat::isContinuous()</u>** function to determine if everything is in a single place

![image](https://github.com/Digital1O1/4_DOF_Robotic_Arm/assets/39348633/f49ec54f-2476-4cd3-9afb-614b1296ab68)

<br>

## The efficient way

### In terms of performance, you can't beat the classic C style operator[] (pointer) access

-   Most efficient/recommended method for making the assignment

### Summary of code snippet below

-   Get a pointer to start at each row and go through everything
-   If a matrix is stored in a continuous manner
    -   We only need to request the pointer a **<u>single time</u>** and have it go through everything
-   Need to keep an eye out for color images
    -   Since we have three channels, we need to pass through three times more items in each row
-   Looking at a different perspective
    -   The <u>data</u> data member of a <u>Mat</u> object returs the pointer to the first row, first column
    -   If the pointer is NULL
        -   No valid input in that object
        -   Checking this --> simplest way to check if the image was loaded successfully
    -   If the storage is **<u>continuous</u>** we can use this code snippet to go through the whole data pointer
    -   In case if the image is grayscaled, check out the **<u>second</u>** code snippet
        -   You'll get the same result
        -   But code is harder to read

```cpp
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;
    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}

```

```cpp
uchar* p = I.data;
for( unsigned int i = 0; i < ncol*nrows; ++i)
    *p++ = table[*p];
```
