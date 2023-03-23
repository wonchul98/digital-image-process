

#include <iostream>
#include<vector>
#include "opencv2/core/core.hpp" // Mat class와 각종 data structure 및 산술 루틴을 포함하는 헤더
#include "opencv2/highgui/highgui.hpp" // GUI와 관련된 요소를 포함하는 헤더(imshow 등)
#include "opencv2/imgproc/imgproc.hpp" // 각종 이미지 처리 함수를 포함하는 헤더
using namespace cv;
using namespace std;
Mat myCopy(Mat srcImg);
int myKernelConv3x3(uchar* arr, int kernel[][3], int x, int y, int width, int height);
int myKernelConv9x9(uchar* arr, int kernel[][9], int x, int y, int width, int height);
Mat myGaussianFilter(Mat srcImg);
Mat myGaussiancolorFilter(Mat srcImg);
Mat mySobelFilter(Mat srcImg);
Mat mySampling(Mat srcImg);
Mat GetHistogram(Mat& src);
void SpreadSalts(Mat img, int num);
vector<Mat> myGaussianPyramid(Mat srcImg);
vector<Mat> myLaplacianPyramid(Mat srcImg);
int main() {
	Mat src_img = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/3주차 실습 자료/gear.jpg", 0); // 이미지 읽기
	Mat src_img2 = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/3주차 실습 자료/gear.jpg", 0); // 이미지 읽기
	Mat src_img_color = imread("C:/Users/shinw/OneDrive/바탕 화면/학교/4-1학기/디지털 영상 처리/digital-image-process/3주차 실습 자료/gear.jpg", 1); // 이미지 읽기
	Mat g_filter = myGaussianFilter(src_img);
	Mat s_filter = mySobelFilter(src_img);
	SpreadSalts(src_img2, 1000);
	Mat g_filter2 = myGaussianFilter(src_img2);
	Mat dst_img;
	vector<Mat> VecLap = myLaplacianPyramid(src_img_color);
	vector<Mat> VecGau = myGaussianPyramid(src_img_color);
	reverse(VecLap.begin(), VecLap.end());
	reverse(VecGau.begin(), VecGau.end());

	for (int i = 0; i < VecLap.size(); i++) {
		string fname = "ex5_lap_pyr_recover" + to_string(i) + ".png";
		dst_img = VecLap[i];
		//imshow(fname, dst_img);
		//waitKey(0);
		//destroyWindow(fname);
		if (i == 0) {
			dst_img = VecLap[i];
		}
		else {
			resize(dst_img, dst_img, VecLap[i].size());
			vector<Mat> channels_dst;
			split(dst_img, channels_dst);
			vector<Mat> channels_lap;
			split(VecLap[i], channels_lap);
			for (int c = 0; c < dst_img.channels(); c++) {
				channels_dst[c] = channels_dst[c] + channels_lap[c] - 128;
			}
			merge(channels_dst, dst_img);
		}
		
		//imwrite(fname, dst_img);
		imshow(fname, dst_img);
		waitKey(0);
		destroyWindow(fname);
	}

	for (int i = 0; i < VecGau.size(); i++) {
		string fname = "ex5_gau_pyr" + to_string(i) + ".png";
		//imwrite(fname, dst_img);
		dst_img = VecGau[i];
		imshow(fname, dst_img);
		waitKey(0);
		destroyWindow(fname);
	}

	imshow("salt and pepper", src_img2);
	imshow("g_filter1", g_filter); // 이미지 출력
	imshow("g_filter2", g_filter2); // 이미지 출력
	imshow("histogram0", GetHistogram(src_img));
	imshow("histogram1", GetHistogram(g_filter));
	imshow("histogram2", GetHistogram(g_filter2));
	imshow("s_filter", s_filter); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("salt and pepper"); // 이미지 출력창 종료
	destroyWindow("g_filter1"); // 이미지 출력창 종료
	destroyWindow("g_filter2"); // 이미지 출력창 종료
	destroyWindow("histogram"); // 이미지 출력창 종료
	destroyWindow("s_filter"); // 이미지 출력창 종료
	//imwrite("g_filter.png", g_filter); // 이미지 쓰기
	//imwrite("s_filter.png", s_filter); // 이미지 쓰기
	return 0;
}

Mat myCopy(Mat srcImg) {
	int width = srcImg.cols;
	int height = srcImg.rows;
	Mat dstImg(srcImg.size(), CV_8UC1);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = srcData[y * width + x];
		}
	}
	return dstImg;
}

int myKernelConv3x3(uchar* arr, int kernel[][3], int x, int y, int width, int height) {
	int sum = 0;
	int sumKernel = 0;
	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			if ((y + j) >= 0 && (y + j) < height && (x + i) >= 0 && (x + i) < width) {
				sum += arr[(y + j) * width + (x + i)] * kernel[i + 1][j + 1];
				sumKernel += kernel[i + 1][j + 1];
			}
		}
	}
	if (sumKernel != 0) { return sum / sumKernel; }//합 1로 정규화
	else { return sum; }
}

int myKernelConv9x9(uchar* arr, int kernel[][9], int x, int y, int width, int height) {
	int sum = 0;
	int sumKernel = 0;
	for (int j = -4; j <= 4; j++) {
		for (int i = -4; i <= 4; i++) {
			if ((y + j) >= 0 && (y + j) < height && (x + i) >= 0 && (x + i) < width) {
				sum += arr[(y + j) * width + (x + i)] * kernel[i + 4][j + 4];
				sumKernel += kernel[i + 4][j + 4];
			}
		}
	}
	if (sumKernel != 0) { return sum / sumKernel; }//합 1로 정규화
	else { return sum; }
}
#define USE_OPENCV false
Mat myGaussianFilter(Mat srcImg) {
#if USE_OPENCV 
	Mat dstImg(srcImg.size(), CV_8UC1);
	cv::GaussianBlurs(srcImg, dstImg, Size(3, 3), 0);

#else 
	int width = srcImg.cols;
	int height = srcImg.rows;
	int kernel[9][9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0,
						 0, 0, 2, 11, 18, 11, 2, 0, 0,
						 0, 2, 29, 131, 215, 131, 29, 2, 0,
						 0, 11, 131, 585, 965, 585, 131, 11, 0,
						 1, 18, 215, 965, 1592, 965, 215, 18, 1,
						 0, 11, 131, 585, 965, 585, 131, 11, 0,
						 0, 2, 29, 131, 215, 131, 29, 2, 0,
						 0, 0, 2, 11, 18, 11, 2, 0, 0,
						 0, 0, 0, 0, 1, 0, 0, 0, 0 };
	Mat dstImg(srcImg.size(), CV_8UC1);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = myKernelConv9x9(srcData, kernel, x, y, width, height);
		}
	}

	return dstImg;
#endif
}

Mat myGaussiancolorFilter(Mat srcImg) {
	int width = srcImg.cols;
	int height = srcImg.rows;
	int kernel[9][9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0,
						 0, 0, 2, 11, 18, 11, 2, 0, 0,
						 0, 2, 29, 131, 215, 131, 29, 2, 0,
						 0, 11, 131, 585, 965, 585, 131, 11, 0, 
						 1, 18, 215, 965, 1592, 965, 215, 18, 1,
						 0, 11, 131, 585, 965, 585, 131, 11, 0,
						 0, 2, 29, 131, 215, 131, 29, 2, 0,
						 0, 0, 2, 11, 18, 11, 2, 0, 0, 
						 0, 0, 0, 0, 1, 0, 0, 0, 0 };
	Mat dstImg(srcImg.size(), CV_8UC3);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if ((x >= 4) && (y >= 4) && (x < width - 4) && (y < height - 4)) {
				for (int c = 0; c < srcImg.channels(); c++) {
					int sum = 0;
					int sumKernel = 0;
					for (int j = -4; j <= 4; j++) {
						for (int i = -4; i <= 4; i++) {
							sum += srcData[((y + j) * width + (x + i)) * srcImg.channels() + c] * kernel[i + 4][j + 4];
							sumKernel += kernel[i + 4][j + 4];
						}
					}
					if (sumKernel != 0) { dstData[(y * width + x) * srcImg.channels() + c] = sum / sumKernel; }//합이1로 정규화
					else { dstData[(y * width + x) * srcImg.channels() + c] = sum; }
				}
			}
			else {
				for (int c = 0; c < srcImg.channels(); c++) {
					dstData[(y * width + x) * srcImg.channels() + c] = srcData[(y * width + x) * srcImg.channels() + c];
				}
			}
		}
	}

	return dstImg;
}

Mat mySobelFilter(Mat srcImg) {
#if USE_OPENCV
	Mat dstImg(srcImg.size(), CV_8UC1);
	Mat soberlX, sobelY;

	sobel(srcImg, sobelX, CV_8UC1, 1, 0);//가로방향 sobel
	sobel(srcImg, sobelX, CV_8UC1, 0, 1);//세로방향 sobel
	dstImg = (abs(sobelX) + abs(sobelY)) / 2;

	return dstImg;
#else
	int kernelX[3][3] = { 0, 1, 2,
						 -1, 0, 1,
						 -2, -1, 0 };
	int kernelY[3][3] = { -2, -1, 0,
						 -1, 0, 1,
						 0, 1, 2 };

	Mat dstImg(srcImg.size(), CV_8UC1);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;
	int width = srcImg.cols;
	int height = srcImg.rows;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[y * width + x] = (abs(myKernelConv3x3(srcData, kernelX, x, y, width, height)) +
				abs(myKernelConv3x3(srcData, kernelY, x, y, width, height)) / 2);
		}
	}

	return dstImg;
#endif
}

Mat mySampling(Mat srcImg) {
	int width = srcImg.cols / 2;
	int height = srcImg.rows / 2;
	Mat dstImg(height, width, CV_8UC3);
	uchar* srcData = srcImg.data;
	uchar* dstData = dstImg.data;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstData[(y * width + x) * 3] = srcData[((y * 2) * (width * 2) + (x * 2)) * 3];
			dstData[(y * width + x) * 3 + 1] = srcData[((y * 2) * (width * 2) + (x * 2)) * 3 + 1];
			dstData[(y * width + x) * 3 + 2] = srcData[((y * 2) * (width * 2) + (x * 2)) * 3 + 2];
		}
	}
	return dstImg;
}

vector<Mat> myGaussianPyramid(Mat srcImg) {
	vector<Mat> Vec;
	Vec.push_back(srcImg);
	for (int i = 0; i < 4; i++) {
#if USE_OPEN_CV
		pyrDown(srcImg, srcImg, Size(srcImg.cols / 2, srcImg.rows / 2));
#else 
		srcImg = mySampling(srcImg);
		srcImg = myGaussiancolorFilter(srcImg);
#endif 
		Vec.push_back(srcImg);
	}
	return Vec;
}

vector<Mat> myLaplacianPyramid(Mat srcImg) {
	vector<Mat> Vec;

	for (int i = 0; i < 4; i++) {
		if (i != 3) {
			Mat highImg = srcImg;
#if USE_OPENCV
			pyrDown(srcImg, srcImg, Size(srcImg.cols / 2, srcImg.rows / 2));
#else
			srcImg = mySampling(srcImg);
			srcImg = myGaussiancolorFilter(srcImg);
#endif 
			Mat lowImg = srcImg;
			resize(lowImg, lowImg, highImg.size());
			Vec.push_back(highImg - lowImg + 128);
		}
		else {
			Vec.push_back(srcImg);
		}
	}
	return Vec;
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
	//imshow("Test window2", histImage); // 이미지 출력
	return histImage;
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
			img.at<uchar>(y_1, x_1) = 0;
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