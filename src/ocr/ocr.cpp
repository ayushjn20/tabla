#include "ocr.h"
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

std::vector<Word> read_image(std::string filename){
    char name[filename.length()];
    strcpy(name, filename.c_str());
    //read image
    Pix* image = pixRead(name);

    //initialize empty vector
    std::vector<Word> words;

    //Initialising Tesseract Base API
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, "eng")) {
        //LOG HERE
        //fprintf(stderr, "Could not initialize tesseract.\n");
        //exit(1);
    }

    //Tesseract config
    api->Init(NULL, "eng");
    api->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK	); //PSM - 6 : detect single blocks of words
    api->SetImage(image);
    api->Recognize(0);

    //Iterate and push
    tesseract::ResultIterator* ri = api->GetIterator(); // traversal using iterator
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    if (ri != 0) {
        do {
            const char* str = ri->GetUTF8Text(level);

            //conf stores the % confidence of package in this word detection
            float conf = ri->Confidence(level);
            int x1, y1, x2, y2;
            ri->BoundingBox(level, &x1, &y1, &x2, &y2);

            //emplace words only if confidence crosses the threshold
            if(conf > PERCENT_CONFIDENCE_THRESHOLD) words.emplace_back(str, x1, y1, x2, y2);
            delete[] str;
        } while (ri->Next(level));
    }

    //Return a vector of words
    return words;
}
