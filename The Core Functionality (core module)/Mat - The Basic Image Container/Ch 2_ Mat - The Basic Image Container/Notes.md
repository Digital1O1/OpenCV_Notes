# Goal

When taking pictures with digital devices, this is how the image really looks like

-   Just a matrix with intensity values of each pixel point
-   Images --> Just numerical matricies

![image](https://github.com/microsoft/vscode/assets/39348633/810d0e70-71e4-49d5-a95a-16b091d2f096)

OpenCV main focus

-   Manipulate the mentioned matricies

<br>

# Mat

What's a MAT?

-   A class with two data parts
    -   The **Matrix header**
        -   Holds info like :
            -   The size of the matrix
            -   Method used for storing
            -   The address where the matrix is stored
    -   A **pointer** to the matrix containing the pixel value

<br>

# Since OpenCV Is Computationally Heavy

OpenCV uses a **reference counting system**

-   The big idea
    -   Each Mat object has it's own **header**
        -   Header holds info about matrix
        -   But a matrix **can be shared between** two Mat objects
            -   Done by having both their matrix pointers pointing to same address
        -   Keep in mind : **copy operators** will **only** copy **headers and the pointers** to the large matrix
            -   **NOT THE DATA ITSELF**
        -   Everything below points to the **same single data matrix**
            -   In this context, any changes made to this matrix will affect the others pointing to it

```cpp
Mat A, C;                                 // creates just the header parts
A = imread(argv[1], IMREAD_COLOR);        // here we'll know the method used (allocate matrix)
Mat B(A);                                 // Use the copy constructor
C = A;                                    // Assignment operator
```

<br>

# The real fun starts when

You can create headers that **ONLY** refer to a subsction of the full data

-   Example : Creating a region of interest (ROI) in a image
    -   You also created a new header with new boundries

```cpp
Mat D (A, Rect(10, 10, 100, 100) );   // using a rectangle
Mat E = A(Range::all(), Range(1,3));  // using row and column boundaries
```

If there's mutliple MAT objects, what's cleaning them up when they're not needed?

-   Short answer : The last object that used it
-   It's handled by using a reference counting mechanism
    -   Someone copies a header of a MAT object --> **increases** counter for the matrix
    -   When a header is cleaned
        -   The mentioned counter is **decreased**
    -   When the counter reaches 0, the matrix is freed
-   You can also copy the matrix itself
    -   cv::Mat::clone()
    -   cv::Mat::copyTo()

```cpp
// REMEMBER BOTH THE HEADER IS COPIED, NOT THE DATA FROM THE MATRICIES
Mat F = A.clone();
Mat G;
A.copyTo(G);
```

Modifying F or G

-   Won't affect the a matrix pointed to A's header
-   Remember this
    -   Output image allocation for OpenCV funsions --> **Automatic**
    -   Don't worry about memory management with OpenCV C++ interface
    -   Assignment/copy operator **ONLY COPIES THE HEADER**
    -   The matrix of an image can be copied using
        -   cv::Mat::clone()
        -   cv::Mat::copyTo()

<br>

# Storing Methods

How to store pixel values
- Pick the **[color space]** and **[data type]** used
    - What's the color space?
        - How we combine color components to code a given color
        - Simplest one : Grayscale
        - For color, we have alot more methods to pick from
            - Each one breaks them down into four basic components
            - Most popular : RGB


<br>

# Numerous Color Systems With Their Perspective Advantage
 
## RGB
- Most common
- Keep in mind OpenCV makes color using the BGR color space 
    - Red and blue channels are swapped

## HSV and HLS
- Decomposes colors into their 
    - Hue 
    - Saturation
    - Value/luminance components
- More **natrual** way to describe colors

## YCrCb
- Used with JPEG image format

## CIE L*a*b 
- Perceptually uniform color space
- Handy if you need to measure the distance of a given color to another

<br>

# See mat_the_basic_image_container.cpp to observe Mat Matricies Manipulations