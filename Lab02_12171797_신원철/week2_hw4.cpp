#include <iostream>
#include "opencv2/core/core.hpp" // Mat class�� ���� data structure �� ��� ��ƾ�� �����ϴ� ���
#include "opencv2/highgui/highgui.hpp" // GUI�� ���õ� ��Ҹ� �����ϴ� ���(imshow ��)
#include "opencv2/imgproc/imgproc.hpp" // ���� �̹��� ó�� �Լ��� �����ϴ� ���
using namespace cv;
using namespace std;

int main() {
	Mat src_img3 = imread("C:/Users/shinw/OneDrive/���� ȭ��/�б�/4-1�б�/������ ���� ó��/digital-image-process/2���� �ǽ� �ڷ�/img3.jpg", 1); // �̹��� �б�
	Mat src_img4 = imread("C:/Users/shinw/OneDrive/���� ȭ��/�б�/4-1�б�/������ ���� ó��/digital-image-process/2���� �ǽ� �ڷ�/img4.jpg", 1); // �̹��� �б�
	Mat src_img5 = imread("C:/Users/shinw/OneDrive/���� ȭ��/�б�/4-1�б�/������ ���� ó��/digital-image-process/2���� �ǽ� �ڷ�/img5.jpg", 1); // �̹��� �б�
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

	
	imshow("Test window3", dst1); // �̹��� ���

	// int flags = IMREAD_COLOR �Ǵ� int flags = 1 -> �÷� �������� ����
	// int flags = IMREAD_GRAYSCALE �Ǵ� int flags = 0 -> ��� �������� ����
	// int flags = IMREAD_UNCHANGED �Ǵ� int flags = -1 -> ���� ������ ���Ĵ�� ����


	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyWindow("Test window2"); // �̹��� ���â ����
	destroyWindow("Test window3"); // �̹��� ���â ����
	imwrite("dst2.png", dst1); // �̹��� ����


	return 0;
}

