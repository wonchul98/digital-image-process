#include <iostream>
#include "opencv2/core/core.hpp" // Mat class와 각종 data structure 및 산술 루틴을 포함하는 헤더
#include "opencv2/highgui/highgui.hpp" // GUI와 관련된 요소를 포함하는 헤더(imshow 등)
#include "opencv2/imgproc/imgproc.hpp" // 각종 이미지 처리 함수를 포함하는 헤더
using namespace cv;
using namespace std;

int main() {
	Mat src_img3 = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/2주차 실습 자료/img3.jpg", 1); // 이미지 읽기
	Mat src_img4 = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/2주차 실습 자료/img4.jpg", 1); // 이미지 읽기
	Mat src_img5 = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/2주차 실습 자료/img5.jpg", 1); // 이미지 읽기
	Mat dst1, dst2;
	
	resize(src_img4, src_img4, Size(src_img3.cols, src_img3.rows));
	dst1 = src_img3 - src_img4;
	int x = dst1.cols/4, y = dst1.rows/2;
	for (int i = x; i < x+src_img5.cols; i++) {
		for (int j = y; j < y + src_img5.rows; j++) {
			if (src_img5.at<Vec3b>(j - y, i - x)[0] != 255 && src_img5.at<Vec3b>(j - y, i - x)[1] != 255 && src_img5.at<Vec3b>(j - y, i - x)[2] != 255) {
				for (int k = 0; k < 3; k++) {
					dst1.at<Vec3b>(j, i)[k] = src_img5.at<Vec3b>(j - y, i - x)[k];
				}
			}	
		}
	}
	//dst1 = dst1 + src_img5;

	
	imshow("Test window3", dst1); // 이미지 출력

	// int flags = IMREAD_COLOR 또는 int flags = 1 -> 컬러 영상으로 읽음
	// int flags = IMREAD_GRAYSCALE 또는 int flags = 0 -> 흑백 영상으로 읽음
	// int flags = IMREAD_UNCHANGED 또는 int flags = -1 -> 원본 영상의 형식대로 읽음


	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("Test window2"); // 이미지 출력창 종료
	destroyWindow("Test window3"); // 이미지 출력창 종료
	imwrite("dst2.png", dst1); // 이미지 쓰기


	return 0;
}

