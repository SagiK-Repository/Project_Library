#include <opencv2/opencv.hpp>
#include <time.h>
#include "ValueI.h"
using namespace cv;  // cv 안써도 됨
using namespace std; //std 안써도 됨

#pragma warning (disable:4819) //경고 메시지 숨기기
#pragma warning (disable:4996) //경고 메시지 숨기기



int main() {
	if (i == 0) {
		Mat image;
		image = imread("C:/opencv453/sources/samples/data/HappyFish.jpg");
		imshow("Test", image);
		waitKey();
	}

	return 0;

}


