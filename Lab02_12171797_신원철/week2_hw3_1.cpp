#include <iostream>
#include "opencv2/core/core.hpp" // Mat class�� ���� data structure �� ��� ��ƾ�� �����ϴ� ���
#include "opencv2/highgui/highgui.hpp" // GUI�� ���õ� ��Ҹ� �����ϴ� ���(imshow ��)
#include "opencv2/imgproc/imgproc.hpp" // ���� �̹��� ó�� �Լ��� �����ϴ� ���
using namespace cv;
using namespace std;
void dark_and_darker(Mat img);
Mat GetHistogram(Mat& src);

int main() {
	Mat src_img = imread("C:/Users/shinw/OneDrive/���� ȭ��/�б�/4-1�б�/������ ���� ó��/digital-image-process/2���� �ǽ� �ڷ�/img2.jpg", 0); // �̹��� �б�
	dark_and_darker(src_img);
	Mat hist = GetHistogram(src_img);
	// int flags = IMREAD_COLOR �Ǵ� int flags = 1 -> �÷� �������� ����
	// int flags = IMREAD_GRAYSCALE �Ǵ� int flags = 0 -> ��� �������� ����
	// int flags = IMREAD_UNCHANGED �Ǵ� int flags = -1 -> ���� ������ ���Ĵ�� ����
	imshow("Test window1", src_img); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyWindow("Test window"); // �̹��� ���â ����
	imwrite("darker_gray.png", src_img); // �̹��� ����


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
	normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());//����ȭ
	for (int i = 1; i < number_bins; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);

	}
	imshow("Test window2", histImage); // �̹��� ���
	return histImage;
}