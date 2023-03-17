#include <iostream>
#include "opencv2/core/core.hpp" // Mat class�� ���� data structure �� ��� ��ƾ�� �����ϴ� ���
#include "opencv2/highgui/highgui.hpp" // GUI�� ���õ� ��Ҹ� �����ϴ� ���(imshow ��)
#include "opencv2/imgproc/imgproc.hpp" // ���� �̹��� ó�� �Լ��� �����ϴ� ���
using namespace cv;
using namespace std;
void SpreadSalts(Mat img, int num);
void CountSalt(Mat img);
int r=0, g=0, b=0;
int main() {
	Mat src_img = imread("C:/Users/shinw/OneDrive/���� ȭ��/�б�/4-1�б�/������ ���� ó��/digital-image-process/2���� �ǽ� �ڷ�/img1.jpg", 1); // �̹��� �б�
	cout << src_img.rows << " " << src_img.cols << endl;
 	SpreadSalts(src_img, 30);
	CountSalt(src_img);
	// int flags = IMREAD_COLOR �Ǵ� int flags = 1 -> �÷� �������� ����
	// int flags = IMREAD_GRAYSCALE �Ǵ� int flags = 0 -> ��� �������� ����
	// int flags = IMREAD_UNCHANGED �Ǵ� int flags = -1 -> ���� ������ ���Ĵ�� ����
	imshow("Test window", src_img); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyWindow("Test window"); // �̹��� ���â ����
	imwrite("langding_gray.png", src_img); // �̹��� ����
	
	
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