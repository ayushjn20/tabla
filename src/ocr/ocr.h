#ifndef TABLE_READER_OCR_H
#define TABLE_READER_OCR_H
#include <vector>
#include <string>

struct Word{
    int x1, x2, y1, y2;
    std::pair<int, int> center;
    std::string text;
    Word(std::string str, int h1, int v1, int h2, int v2){
        text  = str;
        x1 = h1;
        x2 = h2;
        y1 = v1;
        y2 = v2;
        center = std::pair<int, int>( (h1+h2)/2, (v1+v2)/2 );
        return;
    };
};

std::vector<Word> read_image(std::string);

#endif //TABLE_READER_OCR_H
