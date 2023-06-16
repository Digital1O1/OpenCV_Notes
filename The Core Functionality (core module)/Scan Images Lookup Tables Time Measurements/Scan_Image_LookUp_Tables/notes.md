# [How to scan images, lookup tables and time measurement with OpenCV](https://docs.opencv.org/4.x/db/da5/tutorial_how_to_scan_images.html)

<br>

# Main goal

-   How to go through each and every pixel of an image?
-   How are OpenCV matrix values stored?
-   How to measure the performance of our algorithm?
-   What are lookup tables and why use them?

<br>

# Test Case

## A simple color reduction method

Using a unsigned char to store stuff in a matrix

-   A single pixel in a channel can have <u>**up to 256 different values**</u>
-   Three channel image --> ~16 million colors
    -   Working with that many channels will slow down algorithm performance
-   For this case : We're making a <u>**color space reduction**</u>
    -   How to accomplish that
        - Divide the color space current value with new input value --> Fewer  colors
    -   Example : Every value between 0 and 9 takes new value 0
        -   Every value between 10 --> 19 = The value 10, ect.

<br>

## When dividing an unsigned char (uchar) with another int value
You'll get a char value back
-   And only an unsigned char
-   If you get a fraction as a remainder, it will be <u>**rounded down**</u>
    -   Dividing an unsigned char can be expressed mathmatically as :
        -   ### I<sub>new</sub> = (I<sub>old</sub> / 10) x 10

<br>

## Simple color space reduction algorithm

Would just pass through **<u>every pixel</u>** of an image matrix

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

Look up tables

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
