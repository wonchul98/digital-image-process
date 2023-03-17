#include <iostream>
#include "opencv2/core/core.hpp" // Mat class와 각종 data structure 및 산술 루틴을 포함하는 헤더
#include "opencv2/highgui/highgui.hpp" // GUI와 관련된 요소를 포함하는 헤더(imshow 등)
#include "opencv2/imgproc/imgproc.hpp" // 각종 이미지 처리 함수를 포함하는 헤더
using namespace cv;
using namespace std;
void dark_and_darker(Mat img);
Mat GetHistogram(Mat& src);

int main() {
	Mat src_img = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/2주차 실습 자료/img2.jpg", 0); // 이미지 읽기
	dark_and_darker(src_img);
	Mat hist = GetHistogram(src_img);
	// int flags = IMREAD_COLOR 또는 int flags = 1 -> 컬러 영상으로 읽음
	// int flags = IMREAD_GRAYSCALE 또는 int flags = 0 -> 흑백 영상으로 읽음
	// int flags = IMREAD_UNCHANGED 또는 int flags = -1 -> 원본 영상의 형식대로 읽음
	imshow("Test window1", src_img); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("Test window"); // 이미지 출력창 종료
	imwrite("darker_gray.png", src_img); // 이미지 쓰기


	return 0;
}

void dark_and_darker(Mat img) {
	for (int j = 0; j < img.rows; j++) {
		for (int k = 0; k < img.cols; k++) {
			if(img.at<uchar>(j, k) - (j * 255 /img.rows) < 0) 
				img.at<uchar>(j, k) = 0;
			else 
				img.at<uchar>(j, k) -= (j * 255 / img.rows);
			
		}
	}
}

Mat GetHistogram(Mat& src) {
	cout << "get hist" << endl;
	Mat histogram;
	const int* channel_numbers = { 0 };
	float channel_range[] = { 0.0, 255.0 };
	const float* channel_ranges = channel_range;
	int number_bins = 255;

	calcHist(&src, 1, channel_numbers, Mat(), histogram, 1, &number_bins, &channel_ranges);
	//plot
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / number_bins);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());//정규화
	for (int i = 1; i < number_bins; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);

	}
	imshow("Test window2", histImage); // 이미지 출력
	return histImage;
}