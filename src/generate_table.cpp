#include "generate_table.h"

#include "ocr.h"
#include "mask.h"
#include <string>

void testImage(std::string filepath){
    Image img = Image(filepath);
    std::vector<Word> words = read_image(filepath);
    Mask mask = Mask(&img.binInv);
    std::cout<< "words" << std::endl;
    for (auto w : words){
        std::cout<<w.text<<"("<<w.center.first<<","<<w.center.second<<")"<<std::endl;
    }
    mask.extract_borders();
}

