#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int createMaskByKmeans(cv::Mat src, cv::Mat & mask)
{
	if ((mask.type() != CV_8UC1)
		|| (src.size() != mask.size())
		) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;
	//数据
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;

	sampleData.convertTo(km_data, CV_32F);
	//kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);

	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);
	//mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {

		for (int col = 0; col < width; col++) {

			mask.at<uchar>(row, col) = fg[labels.at<int>(row*width + col)];

		}

	}

	return 0;
}
int main()
{
	Mat ram = imread("D:\\360downloads\\33.png");
	Mat chang = Mat::zeros(ram.size(), CV_8UC1);

	createMaskByKmeans(ram, chang);

	imshow("ram", ram);

	imshow("chang", chang);

	waitKey(0);
}

