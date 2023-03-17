#include <iostream>
#include "opencv2/core/core.hpp" // Mat class와 각종 data structure 및 산술 루틴을 포함하는 헤더
#include "opencv2/highgui/highgui.hpp" // GUI와 관련된 요소를 포함하는 헤더(imshow 등)
#include "opencv2/imgproc/imgproc.hpp" // 각종 이미지 처리 함수를 포함하는 헤더
using namespace cv;
using namespace std;
void SpreadSalts(Mat img, int num);
void CountSalt(Mat img);
int r=0, g=0, b=0;
int main() {
	Mat src_img = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/2주차 실습 자료/img1.jpg", 1); // 이미지 읽기
	cout << src_img.rows << " " << src_img.cols << endl;
 	SpreadSalts(src_img, 30);
	CountSalt(src_img);
	// int flags = IMREAD_COLOR 또는 int flags = 1 -> 컬러 영상으로 읽음
	// int flags = IMREAD_GRAYSCALE 또는 int flags = 0 -> 흑백 영상으로 읽음
	// int flags = IMREAD_UNCHANGED 또는 int flags = -1 -> 원본 영상의 형식대로 읽음
	imshow("Test window", src_img); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("Test window"); // 이미지 출력창 종료
	imwrite("langding_gray.png", src_img); // 이미지 쓰기
	
	
	return 0;
}

void SpreadSalts(Mat img, int num) {
	for (int n = 0; n < num; n++) {
		int x = rand() % img.cols;
		int y = rand() % img.rows;
		int x_1 = rand() % img.cols;
		int y_1 = rand() % img.rows;
		int x_2 = rand() % img.cols;
		int y_2 = rand() % img.rows;

		if (img.channels() == 1) {
			img.at<uchar>(y, x) = 255;
		}
		else {
			img.at<Vec3b>(y, x)[0] = 0; //b
			img.at<Vec3b>(y, x)[1] = 255; //g
			img.at<Vec3b>(y, x)[2] = 0; //r

			img.at<Vec3b>(y_1, x_1)[0] = 255; //b
			img.at<Vec3b>(y_1, x_1)[1] = 0; //g
			img.at<Vec3b>(y_1, x_1)[2] = 0; //r

			img.at<Vec3b>(y_2, x_2)[0] = 0; //b
			img.at<Vec3b>(y_2, x_2)[1] = 0; //g
			img.at<Vec3b>(y_2, x_2)[2] = 255; //r
		}
	}
}

void CountSalt(Mat img) {
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			if (img.at<Vec3b>(j, i)[0] == 255 && img.at<Vec3b>(j, i)[1] == 0 && img.at<Vec3b>(j, i)[2] == 0) b++;
			if (img.at<Vec3b>(j, i)[0] == 0 && img.at<Vec3b>(j, i)[1] == 255 && img.at<Vec3b>(j, i)[2] == 0) g++;
			if (img.at<Vec3b>(j, i)[0] == 0 && img.at<Vec3b>(j, i)[1] == 0 && img.at<Vec3b>(j, i)[2] == 255) r++;
		}
	}
	cout << "R: " << r << " G: " << g << " B: " << b << endl;
}