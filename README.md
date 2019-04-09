# TABLE EXTRACT
## About
A C++ package to extact tabular data from a scanned image using simple image processing techniques.

[Project Report](https://github.com/ayushjn20/tabla/blob/master/project-report.pdf)

## Installation and Setup
### Using CMake
Minimum CMake verison required: `3.10`
### Install OpenCV
Recommended OpenCV version:`3.4`
##### For Linux:
https://docs.opencv.org/3.4.1/d7/d9f/tutorial_linux_install.html
##### For macOS:  
1. Install XCode  
2. Install HomeBrew  
3. ```brew install opencv```  

### Install tesseract-ocr
Recommended version: `4.0`

##### For Linux:
https://github.com/tesseract-ocr/tesseract/wiki#linux
##### For macOS: 
`brew install tesseract`

### Problem Analysis
The goal is to extract text data from an image containing a table and generate the same tabular form for further analysis and usage.
### Feature Analysis
**Mask**
* Identify table border.
* Identify all distinct horizontal and vertical lines.
* Identify cells through horizontal and vertical lines.

**Text**
* Identify blocks of words.
* Identify bounding boxes.
* Indentify order of words to form the phrase.
### Concepts and Technologies Involved
**Language:** C++ STD 11
**Build Tool:** CMake (Minimum version 3.10)
**Dependencies:**

**1. OpneCV:**
* Binary inversion with adaptive gaussian noise removal filter.
* Contour mapping for identifying the table borders.
* Morphological operations -- _Erosion_ and _Dilation_ to anything except corresponding to a particular direction, either horizontal or vertical.
* Custom operations over CV matrix of the secluded horizontal lines image and the secluded vertical lines image to extract line coordinates.

**2. Tesseract-OCR**:
* Detection of blocks of word in the image.
* Detection of bounding boxes of each block of word.
* Language specific(by default, English) LSTM prediction in OCR.

### Code Structure
##### Directory Structure
```
.
├── CMakeLists.txt
├── main.cpp
└── src
    ├── generate_table.in
    ├── generate_table.cpp
    ├── line_detection
    │    ├── H.png
    │    ├── image.cpp
    │    ├── mask.cpp.in
    │    ├── mask.hpp
    │    └── V.png
    ├── ocr
    │    ├── ocr.cpp
    │    └── ocr.hpp
```
##### Description
Table Extract is made up of two components, built as two different packages. Line_detection is used to extract the borders of the table. The image is read, resized, and greyscaled using adaptive thresholding.

Mask is detected using customized algorithms, coded in `mask.hpp.in`. For easy usage, check the code for `extract_borders` function in that file. FHlines and FVlines represent the required data.

__Algorithm Theory__: For a vertical line we need to look for the starting point of a line and the ending point of the line. `lines` function detects the lines by traversing the image, looking for required values in pixel blocks. Pixel blocks are named as __Pools__ and Pool size represents the lenght of the side of that square block. Pool can be said as the lookup zoom-lens that is used to examine a small region in the image. Required values mean what is the extent of white content in that block (Note: Binary inverted image is used, therefore lines are white and background is black). Calibrate function is used to minutely(pixel-by-pixel) calibrate the pool window, so as that if white region is present, then the average of white region is as close as possible to the center of the pool. If there is no white region, we can say that the average of all white pixel postitions is center of the pool only. Thus calibrate function returns back with pool unchanged in all black or all white region.
If the pool is not on any line, all pixel values will be black. Then whenever the white region starts showing up in the pool, we mark the pool's centre as the starting point of any line. Now, if we look continue down in the vertical direction, we will see that there is significant amount of white content as long as the pool is traversing over a line. As soon as the line ends, again all the pixels of the pool will start becoming black. The point where it starts happening significantly is marked as the ending point. Since there may be glitches that a 1-3 pixel length is black between a line, the algorithm looks for subsequent pool values too, store them in buffer, and evaluates whether it is really starting point or ending point, or just a noise.

Text is detected using Google's `tesseract-ocr` library. Two points to note are
* The Page Segmentation mode is selected as __6__, which represents detection of bounding boxes on blocks of words.
* The confidence threshold represents the level of confidence the library has on the detection of that block of word.

### Testing
Make sure CMake is already installed.
Change filename if required in *main.cpp*.
Go to project directory, run the following commands in sequence. 
`cmake .`
`make`
`./table-reader`

### To-Dos
* Auto image formatting (like output provided by CamScanner, FastScanner, etc)
* Deskewing of slightly rotated image.
* Cell boundary confirmation using joints.
* Bolding edges through contrast manipulation.

### Dropped Ideas
Following ideas were dropped after experimenting out.
1. **pdftabextract**\
Links:\
&emsp; Repo: https://github.com/WZBSocialScienceCenter/pdftabextract \
&emsp; Blog: https://datascience.blog.wzb.eu/2017/02/16/data-mining-ocr-pdfs-using-pdftabextract-to-liberate-tabular-data-from-scanned-documents/
Reason: Firstly, the results were very bad of an image with fine lines. Tweaking the parameters didn't help much.

2. **Tabula**\
Links: https://tabula.technology/ \
Reason: This is a full-fledged package for extracting information (i.e. we cannot get intermediate results) if the text is already embedded in the pdf. There is no effective open-source tool available to detect text and embedd directly into the pdf. This has also been an open github issue on it's repo.
Issue: https://github.com/tabulapdf/tabula/issues/409
