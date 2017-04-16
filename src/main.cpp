#include <iostream>

#include "scale_orb.h"

using namespace so;
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cout << "input: ./scale image_path1 image_path2" << endl;
        return -1;
    }
    Sca test;

    Mat img1 = imread(argv[1]);
    Mat img2 = imread(argv[2]);

    Feature f1,f2;

    f1 = test.getFeature(img1,"FAST","BRIEF");
    f2 = test.getFeature(img2,"FAST","BRIEF"); // BRISK & FREAK not perform well

    cout << f1.dp.size() <<endl; //  [32x500] in ORB
    cout << f2.dp.size() <<endl; //  [32x500] in ORB

//    test.showFeature("f1",f1);
//    test.showFeature("f2",f2);

    std::vector<cv::DMatch> matches;
    matches = test.getMatch(f1,f2,"FlannBased",3);

    Mat drawImg;
    drawMatches(f1.img,f1.kp,f2.img,f2.kp, matches,drawImg,Scalar(0,255,0),Scalar(255,0,0),vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    imshow("match",drawImg);
    waitKey(0);

    // the framework is OK, then add multi scale and show different result.

	return 0;
}
