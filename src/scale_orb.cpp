#include "scale_orb.h"


using namespace std;
using namespace cv;

namespace so
{
	Sca::Sca()
    {
        rgb_py.resize(5);
	}

    Sca::Sca(char* path)
    {
        rgb_py.resize(5);
        rgb_input = cv::imread(path);
    }

	Sca::~Sca()
	{
		cout << "destory" << endl;
	}
    void Sca::showFeature(char* windows_name, Feature &f)
    {
        Mat out = f.img;
        for(int i = 0; i < f.kp.size(); ++i)
        {

            circle(out,f.kp[i].pt,2,Scalar(0,0,255),-1);
        }

        imshow(windows_name ,out);
        waitKey(0);
    }


    Feature Sca::getFeature( Mat &img, char* keyp_name, char* des_name)
    {
        if(img.empty())
        {
            cout << "getFeature: input img is empty." << endl;
            exit(-1);
        }

        Feature ff;
        ff.img = img;

        Ptr<FeatureDetector> fd = FeatureDetector::create(keyp_name);
        Ptr<DescriptorExtractor> dpE = DescriptorExtractor::create(des_name);

        if(fd.empty() || dpE.empty())
        {
            cout << "fd or dpE is empty" <<endl;
            exit(-1);
        }

        fd->detect(ff.img,ff.kp);
        dpE->compute(ff.img,ff.kp,ff.dp);

        return ff;

    }

    vector<DMatch> Sca::getMatch(Feature &f1, Feature& f2, char* match_name, int dist_scale = 3)
    {
        Mat dp1 = f1.dp;
        Mat dp2 = f2.dp;

        if( strcmp(match_name,"FlannBased") == 0 )
        {
            if(dp1.type()!=CV_32F)
            {
                dp1.convertTo(dp1,CV_32F);
            }

            if(dp2.type()!=CV_32F)
            {
                dp2.convertTo(dp2,CV_32F);
            }
        }

        Ptr<DescriptorMatcher> dpM = DescriptorMatcher::create(match_name);
        vector<DMatch> matches;

        dpM->match(dp1,dp2,matches);

        double max_dist = 0;
        double min_dist = 100;
        for(int i = 0 ; i < f1.dp.rows; ++i)
        {
            double dist = matches[i].distance;
            if( min_dist > dist) min_dist = dist;
            if( max_dist < dist) max_dist = dist;
        }

        std::vector<DMatch> good_matches;
        for(int i = 0; i < f1.dp.rows; ++i)
        {
            if(matches[i].distance < dist_scale*min_dist)
            {
                good_matches.push_back(matches[i]);
            }
        }

        return good_matches;

    }

    void Sca::dotest()
    {
        //"./descriptor_extractor_matcher ORB ORB FlannBased NoneFilter cola.jpg 0\n"
        // NoneFilter 0
        // CrossFilter 1
        Ptr<FeatureDetector> dr = FeatureDetector::create("ORB");
        Ptr<DescriptorExtractor> dpE = DescriptorExtractor::create("ORB");
        Ptr<DescriptorMatcher> dpM = DescriptorMatcher::create("FlannBased");

        int matcherFilterType = 0;
        if(dr.empty() || dpE.empty() || dpM.empty())
        {
            cout << "dr, dpE, dpM are empty" << endl;
            exit(-1);
        }

        Mat img = this->rgb_input;
        if(img.empty())
        {
            cout << "rgb_input is empty" << endl;
            exit(-1);
        }

        vector<KeyPoint> kp1;
        dr->detect(img,kp1);
//        cout <<"get < " << kp1.size() << " points > features" << endl;

        Mat dp;
        dpE->compute(img,kp1,dp);
//        cout << "get < " << dp.size() << " points > features descriptions" << endl;

//        namedWindow("test",1);

//        for(int i = 0 ; i < kp1.size(); ++i)
//        {
//            circle(img,kp1[i].pt,4,Scalar(0,0,255),-1);
//        }
//        resize(img,img,Size(img.cols/2,img.rows/2));
//        imshow("test",img);

        waitKey(0);

    }

}

