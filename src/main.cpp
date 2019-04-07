#include <iostream>
#include <string>

#include "ocr.h"
#include "mask.h"

int main() {
    std::string filepath = "./test.png";
    Image img = Image(filepath);
    std::vector<Word> words = read_image(filepath);
    Mask mask = Mask(&img.binInv);
    std::cout << "-----words---" << std::endl;
    for (auto w : words) {
        std::cout << w.text << "   (" << w.center.first << ", " << w.center.second << ")" << std::endl;
    }
    std::cout << '\n';
    // extract_borders is just an utility test function
    // See code `extract_borders` function in
    // src/line_detection/mask.cpp.in
    // to check how to use the package functions
    // there are two arrays of points -- FHlines and VHlines
    // those are the required data
    mask.extract_borders();
    return 0;
}
