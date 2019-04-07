#ifndef TABLE_READER_MASK_H
#define TABLE_READER_MASK_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

/* defining a namespace so as to separate out
 * structs/classes/methods with same name of opencv
 */
namespace line{

    /*
     * Defining a struct for a point,
     * (x,y)
     */
    struct Point{
        int x, y;
        Point(){};
        Point(int m, int n){
            x = m;
            y = n;
        }
        Point (int* m, int* n){
            x = *m;
            y = *n;
        }

    };

    /* Defining a struct for a line,
     * two points => start and end
     */
    struct Line {
        Point start, end;
        Line(){};
        Line(const Point &p1) {
            start = p1;
        }

        Line(Point p1, Point p2) {
            start = p1;
            end = p2;
        }

    };
}

/*Class definition for image object*/
class Image{
private:
    std::string filename;
    cv::Mat grey; //cv image matrix var for greyscaled
    //const static int max_area = 500000; //0.5MP

public:
    cv::Mat original;
    cv::Mat binInv; //cv image matrix var for binary inverted image
    Image(std::string);
};

class Mask {
private:
    const static int SCALE = 15;
    // const static int POOL_SIZE = 5;
    // const static int BUFFER_CAPACITY = 3;
    void calibrate(cv::Mat *, int *, int *, int); //util function to calibrate pool window
    line::Point mean(cv::Mat *, int *, int *, int); //util function to calculate mean of the pool window
    void clean_list(std::vector<line::Line> *, std::vector<line::Line> *); //util function to clear irregularities

public:
    cv::Mat mask;
    cv::Mat mask_points;
    cv::Mat joints;
    std::vector<int> rows;
    std::vector<int> cols;
    cv::Mat horizontal; //image containing only horizontal lines
    cv::Mat vertical; //image containing only vertical lines
    Mask(const cv::Mat* );

    void extract_borders(); //main function that detects and extracts line coordinates
    void lines(cv::Mat *, std::vector<line::Line> *);

    cv::Mat cells;
};

static bool compare_lines(line::Line, line::Line); //a customized compare function to compare between two lines


#endif //TABLE_READER_MASK_H
