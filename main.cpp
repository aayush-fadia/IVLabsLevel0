#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
uchar * getPixel(Mat* z, int x, int y, int channel){
    return z->data+((y*z->cols+x)*z->channels())+channel;
}
int main() {
Mat img = imread("./golf_ball.jpg");
Mat nimg;
img.copyTo(nimg);
cout<<img.rows<<endl<<img.cols<<endl;
namedWindow("img", WINDOW_GUI_NORMAL);
namedWindow("nimg", WINDOW_GUI_NORMAL);
long sumx = 0, sumy = 0, cnt = 0;
int miny = img.rows;
int maxy = 0;
for(int i = 0; i<img.cols; i++){
    for(int j = 0; j<img.rows; j++){
        if(*(getPixel(&img, i, j, 0))>70&&*(getPixel(&img, i, j, 2))>70){
            *(getPixel(&img, i, j, 0)) = 0;
            *(getPixel(&img, i, j, 1)) = 0;
            *(getPixel(&img, i, j, 2)) = 0;
            if(j<miny){
                miny = j;
            }
            if(j>maxy){
                maxy = j;
            }
            sumx+=i;
            sumy+=j;
            cnt++;
        }
    }
}
int cx = sumx/cnt;
int cy = sumy/cnt;
int radius = (maxy-miny)/2;
cout<<cx<<endl<<cy<<endl;
for(int p = cx-20; p<=cx+20; p++){
    for(int q = cy-20; q<=cy+20; q++){
        *(getPixel(&img, p, q, 0)) = 255;
        *(getPixel(&img, p, q, 1)) = 255;
        *(getPixel(&img, p, q, 2)) = 255;

    }
}
circle(nimg, Point(cx, cy), radius, Scalar(0, 0, 0), 10);
resizeWindow("img", 700, 700*(img.rows/img.cols));
resizeWindow("nimg", 700, 700*(nimg.rows/nimg.cols));
imshow("img", img);
imshow("nimg", nimg);
waitKey(0);
return 0;
}