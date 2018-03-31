#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

char k = 1, scan = 0, selected = 0;
vector<Point> points;

void onMouse(int evt, int x, int y, int flags, void* param) {
        if(evt == CV_EVENT_MOUSEMOVE) {
                if((k>0)&&(k<9)){
                        points[k].x = x;
                        points[k].y = y;
                }
        }
        if(evt == CV_EVENT_LBUTTONDOWN) {
                if((k<=9)&&(!selected))
                        k = k + 1;
                else
                        k=0;

                if(k==9){
                        selected = 1;
                        for(int i=1;i<9;i++)
                                cout << "Point "<< i << "\tx:" << points[i].x << "\ty:" << (points[i].y-10) << endl;
                }
        }
}

int main( int argc, char** argv )
{
        namedWindow("Output Window");
        Mat img = imread("FRONT_0.png");
        setMouseCallback("Output Window", onMouse, (void*)&points);
                
        for(int i=0;i<9;i++)
                points.push_back(cv::Point(0,0));

        while(1)
        {
                Mat frame = img.clone();

                for(int i=0;i<9;i++){
                        char n[10];
                        sprintf(n, "%d", i);
                        line(frame, cvPoint(points[i].x, points[i].y-10),  cvPoint(points[i].x, points[i].y-50), cvScalar(0,255,0),0.5);
                        putText(frame, n, cvPoint(points[i].x-5, points[i].y-55), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,255,255), 1, CV_AA);
                }

                imshow("Output Window", frame);

                scan = (char)waitKey(33) - '0';
                
                if((scan>0)&&(scan<9))
                        k = scan;                       
                        
                if(scan==-21)
                        break;

                frame.release();
        }
        return(0);
}

