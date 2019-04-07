#include "image.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include "mask.h"

using namespace cv;

Image::Image(std::string filepath){

    //extract filename from path
    filename = filepath.substr(filepath.find_last_of("/\\")+1);

    //Read file
    try {
        original = imread(filepath);
    }
    catch(Exception e) {
        throw e;
    }

    //Convert to greyscale
    if(original.channels() == 3){
        cvtColor(original, grey, cv::COLOR_BGR2GRAY);
    }
    else{
        grey = original;
    }

    //Binary Inversion using adaptive threshold
    adaptiveThreshold(
            ~grey, //Inversion
            binInv, //Output matrix
            255, //white as max value
            cv::ADAPTIVE_THRESH_MEAN_C, //Adaptive threshold mode
            THRESH_BINARY, //Binary conversion
            ADAPTIVE_THRESHOLD_BLOCK_SIZE, //blockSize
            ADAPTIVE_THRESHOLD_CONSTANT //a constant
    );

    return;
}

