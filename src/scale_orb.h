#ifndef  _SCALE_ORB_H_
#define  _SCALE_ORB_H_


#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "string"


using namespace std;

using namespace cv;

namespace so{

    struct Feature{
        cv::Mat img;
        vector<KeyPoint> kp;
        cv::Mat dp;

    };

	class Sca{
		public:
			Sca();
            Sca(char* path);
			~Sca();

            Feature getFeature(Mat& img, char* keyp_name, char* des_name);

            void showFeature(char* windows_name, Feature& f);

            void dotest();

            vector<DMatch> getMatch(Feature& f1,Feature& f2, char* match_name, int dist_scale);

//            detectFeature();
//            matchFeature();


        private:
            Mat rgb_input;

            std::vector< cv::Mat > rgb_py;
	
	};

}

#endif
