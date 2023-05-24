#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/cvconfig.h>

using namespace cv;
using namespace std;

enum class TransformType: int {
	Stretch,
	Compression,
	Rotation,
	StretchAndRotation,
	CompressionAndRotation
};

TransformType printStartMessage() {
	int methodOfDeformation;
	std::cout << "���������� ������� ������ ��������� �����������" << endl;
	std::cout << "0 - ���������� �� ����" << endl;
	std::cout << "1 - ������ �� ����" << endl;
	std::cout << "2 - ������� ������ ���, ���������� ����� ����� ������ � ��������������� ������" << endl;
	std::cout << "3 - ���������� ���������� � ��������" << endl;
	std::cout << "4 - ���������� ������ � ��������" << endl;
	std::cout << "������� ������ ����������: ";
	cin >> methodOfDeformation;
	return static_cast<TransformType>(methodOfDeformation);
}

struct MomentWrapper
{
	MomentWrapper(const vector<Point>& contour)
	{
		_moments = moments(contour, true);
	}
	void PrintCentralMoment() {
		cout << "������ m00: " << _moments.m00 << endl;
		cout << "������ m10: " << _moments.m10 << endl;
		cout << "������ m02: " << _moments.m02 << endl;
		cout << "������ m03: " << _moments.m03 << endl;
		cout << "������ m11: " << _moments.m11 << endl;
		cout << "������ m12: " << _moments.m12 << endl;
		cout << "������ m20: " << _moments.m20 << endl;
		cout << "������ m21: " << _moments.m21 << endl;
		cout << "������ m30: " << _moments.m30 << endl;

		cout << "������ mu20: " << _moments.mu20 << endl;
		cout << "������ mu11: " << _moments.mu11 << endl;
		cout << "������ mu02: " << _moments.mu02 << endl;

		cout << "������ mu30: " << _moments.mu30 << endl;
		cout << "������ mu21: " << _moments.mu21 << endl;
		cout << "������ mu12: " << _moments.mu12 << endl;
		cout << "������ mu03: " << _moments.mu03 << endl;
	}

private:

	Moments _moments;

};


//������� � ����� ��������
void momentsResult(Mat inputImg, Mat outputImg) 
{
	cout << endl;

	vector<vector<Point>> contours;
	findContours(inputImg, contours,  RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Moments> P(contours.size());

	vector<vector<Point>>  contours2;
	findContours(outputImg, contours2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Moments> T(contours2.size());

	//����������� �������
	cout << "����������� ������� ��� ������� �����������: " << endl;
	/*for (const auto& contour : contours)
	{
		MomentWrapper P; 

		Wrapper
		P.push_back();

	}*/
	for (int i = 0; i < (int)contours.size(); i++) {
		P[i] = moments(contours[i], true);
		cout << "������ m00: " << P[i].m00 << endl;
		cout << "������ m10: " << P[i].m10 << endl;
		cout << "������ m02: " << P[i].m02 << endl;
		cout << "������ m03: " << P[i].m03 << endl;
		cout << "������ m11: " << P[i].m11 << endl;
		cout << "������ m12: " << P[i].m12 << endl;
		cout << "������ m20: " << P[i].m20 << endl;
		cout << "������ m21: " << P[i].m21 << endl;
		cout << "������ m30: " << P[i].m30 << endl;

		cout << "������ mu20: " << P[i].mu20 << endl;
		cout << "������ mu11: " << P[i].mu11 << endl;
		cout << "������ mu02: " << P[i].mu02 << endl;

		cout << "������ mu30: " << P[i].mu30 << endl;
		cout << "������ mu21: " << P[i].mu21 << endl;
		cout << "������ mu12: " << P[i].mu12 << endl;
		cout << "������ mu03: " << P[i].mu03 << endl;
	}

	cout << '\n' << "����������� ������� ��� ������� �����������: " << endl;
	for (int i = 0; i < (int)contours2.size(); i++) {
		T[i] = moments(contours2[i], true);

		cout << "������ m00: " << T[i].m00 << endl;
		cout << "������ m10: " << T[i].m10 << endl;
		cout << "������ m02: " << T[i].m02 << endl;
		cout << "������ m03: " << T[i].m03 << endl;
		cout << "������ m11: " << T[i].m11 << endl;
		cout << "������ m12: " << T[i].m12 << endl;
		cout << "������ m20: " << T[i].m20 << endl;
		cout << "������ m21: " << T[i].m21 << endl;
		cout << "������ m30: " << T[i].m30 << endl;

		cout << "������ mu20: " << T[i].mu20 << endl;
		cout << "������ mu11: " << T[i].mu11 << endl;
		cout << "������ mu02: " << T[i].mu02 << endl;

		cout << "������ mu30: " << T[i].mu30 << endl;
		cout << "������ mu21: " << T[i].mu21 << endl;
		cout << "������ mu12: " << T[i].mu12 << endl;
		cout << "������ mu03: " << T[i].mu03 << endl;
	}
	cout << endl;

	cout << "������������� ����������� ������� ��� ������� �����������: " << endl;
	for (int i = 0; i < (int)contours.size(); i++) {
		P[i] = moments(contours[i], true);

		cout << "������ nu20: " << P[i].nu20 << endl;
		cout << "������ nu11: " << P[i].nu11 << endl;
		cout << "������ nu02: " << P[i].nu02 << endl;

		cout << "������ nu30: " << P[i].nu30 << endl;
		cout << "������ nu21: " << P[i].nu21 << endl;
		cout << "������ nu12: " << P[i].nu12 << endl;
		cout << "������ nu03: " << P[i].nu03 << endl;

	}

	cout << '\n' << "������������� ����������� ������� ��� ������� �����������: " << endl;
	for (int i = 0; i < (int)contours2.size(); i++) {
		T[i] = moments(contours2[i], true);

		cout << "������ nu20: " << T[i].nu20 << endl;
		cout << "������ nu11: " << T[i].nu11 << endl;
		cout << "������ nu02: " << T[i].nu02 << endl;

		cout << "������ nu30: " << T[i].nu30 << endl;
		cout << "������ nu21: " << T[i].nu21 << endl;
		cout << "������ nu12: " << T[i].nu12 << endl;
		cout << "������ nu03: " << T[i].nu03 << endl;
	}
	cout << endl;

	double huMoments[7];
	cout << "HuMoments ��� ������� �����������: " << endl;
	for (int i = 0; i < (int)contours.size(); i++) 
	{
		HuMoments(P[i], huMoments);
		for (int i = 0; i < 7; i++) {
			huMoments[i] = -1 * copysign(1.0, huMoments[i]) * log10(abs(huMoments[i]));
		}
		for (double hh : huMoments) {
			cout << hh << '\n';
		}
	}


	double huMoments2[7];
	cout << '\n' << "HuMoments ��� ������� �����������: " << endl;
	for (int i = 0; i < (int)contours2.size(); i++) 
	{
		HuMoments(T[i], huMoments2);
		for (int i = 0; i < 7; i++) {
			huMoments2[i] = -1 * copysign(1.0, huMoments2[i]) * log10(abs(huMoments2[i]));
		}
		for (double hh2 : huMoments2) {
			cout << hh2 << '\n';
		}
	}

	//����� ����������� � ����� (�������� � ����������) - �������� ��������������
	imshow("Input Image", inputImg);
	imshow("Output Image", outputImg);
	waitKey(0);
}

//����������
Point2f* stretchingTheFigure(Mat inputImg, Point2f outMat[]) {
	int direction;
	cout << "���������� ������� ����������� ����������" << endl;
	cout << "0 - ���������� ������" << endl;
	cout << "1 - ���������� ����" << endl;
	cout << "2 - ���������� ������ � ����" << endl;
	cout << "������� ������ �����������: ";
	cin >> direction;
	switch (direction)
	{
	case 0: //���������� ������ 
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols + 100, 0);
		outMat[2] = Point2f(0, inputImg.rows);
	}
	break;
	case 1: //���������� ����
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols, 0);
		outMat[2] = Point2f(0, inputImg.rows + 100);
	}
	break;
	case 2: //���������� ������ � ����
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols + 100, 0);
		outMat[2] = Point2f(0, inputImg.rows + 100);
	}
	default:
		break;
	}
	return outMat;
}

//������
Point2f* compressionTheFigure(Mat inputImg, Point2f outMat[]) {
	int direction;
	cout << "���������� ������� ����������� ������" << endl;
	cout << "0 - ������ �����" << endl;
	cout << "1 - ������ �����" << endl;
	cout << "2 - ������ ����� � �����" << endl;
	cout << "������� ������ �����������: ";
	cin >> direction;
	switch (direction)
	{
	case 0: //������ ����� 
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols - 100, 0);
		outMat[2] = Point2f(0, inputImg.rows);
	}
	break;
	case 1: //������ �����
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols, 0);
		outMat[2] = Point2f(0, inputImg.rows - 100);
	}
	break;
	case 2: //������ ����� � �����
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols - 100, 0);
		outMat[2] = Point2f(0, inputImg.rows - 100);
	}
	default:
		break;
	}
	return outMat;
}

//������� ������ ���
tuple<Point2f, double, double> rotationOfTheFigureAroundTheAxis(Mat inputImg, Point2f outMat[]) {
	double angle;
	cout << "���������� ������� ���� ��������" << endl;
	cout << "������� ���� ��������: ";
	cin >> angle;

	//������� ������ �������������� ����� �����
	Point2f center(inputImg.cols / 2, inputImg.rows / 2);
	double scale = 1;
	return make_tuple(center, angle, scale);
}

void main() {
	setlocale(LC_ALL, "ru");
	//import image
	string path = "Resourses/image.jpg"; //���������� ���� �� �����������

	//����� ������� ����������
	TransformType methodOfDeformation = printStartMessage();

	//////////// ROWS - ������ //////////// COLS - ������� ////////////

	//������� ���� ��������� �����������
	Mat inputImg = imread(path, IMREAD_GRAYSCALE); //����������� �������� � ���
	threshold(inputImg, inputImg, 128, 255, THRESH_BINARY);
	namedWindow("Input Image", WINDOW_AUTOSIZE); //������� ���� ������ ����������� � ������ ������

	//������� ���� ����������� �����������
	Mat outputImg = Mat(inputImg.size(), inputImg.type(), IMREAD_GRAYSCALE);
	threshold(outputImg, outputImg, 128, 255, THRESH_BINARY);
	namedWindow("Output Image", WINDOW_AUTOSIZE);

	///////////���� ��� ������ ���� ��������� �� ������

	//�������� ��������������
	Point2f inpMat[3];
	Point2f outMat[3];

	//������� ��������� �����������
	inpMat[0] = Point2f(0.0, 0.0);
	inpMat[1] = Point2f(inputImg.cols, 0);
	inpMat[2] = Point2f(0, inputImg.rows);

	switch (methodOfDeformation)
	{
	case TransformType::Stretch: //���������� �� ����
	{
		stretchingTheFigure(inputImg, outMat);

		Mat M = getAffineTransform(inpMat, outMat);

		warpAffine(inputImg, outputImg, M, outputImg.size());
		momentsResult(inputImg, outputImg);
	}
	break;
	case TransformType::Compression: //������ �� ����
	{
		compressionTheFigure(inputImg, outMat);

		Mat M = getAffineTransform(inpMat, outMat);

		warpAffine(inputImg, outputImg, M, outputImg.size());
		momentsResult(inputImg, outputImg);
	}
	break;
	case TransformType::Rotation: //������� ������ ���, ���������� ����� ����� ������ � ��������������� ������
	{
		//rotationOfTheFigureAroundTheAxis(inputImg, outMat);
		
		Point2f center;
		double angle;
		double scale;
		tie(center, angle, scale) = rotationOfTheFigureAroundTheAxis(inputImg, outMat);
		Mat MM = getRotationMatrix2D(center, angle, scale);

		Mat dstMat;
		//warpAffine(inputImg, dstMat, MM, inputImg.size()); //��������� ������� � ��������� �����������
		warpAffine(inputImg, outputImg, MM, outputImg.size()); //��������� ������� � ��������� �����������

		momentsResult(inputImg, outputImg);
	}
	break;
	case TransformType::StretchAndRotation: //���������� ���������� � ��������
	{
		stretchingTheFigure(inputImg, outMat);
		Mat M = getAffineTransform(inpMat, outMat);
		warpAffine(inputImg, outputImg, M, outputImg.size());

		Point2f center;
		double angle;
		double scale;
		tie(center, angle, scale) = rotationOfTheFigureAroundTheAxis(inputImg, outMat);
		Mat MM = getRotationMatrix2D(center, angle, scale);

		Mat dstMat;
		warpAffine(outputImg, dstMat, MM, inputImg.size()); //��������� ������� � �������� ����������

		momentsResult(inputImg, outputImg);

	}
	break;
	case TransformType::CompressionAndRotation: //���������� ������ � ��������
	{
		compressionTheFigure(inputImg, outMat);
		Mat M = getAffineTransform(inpMat, outMat);
		warpAffine(inputImg, outputImg, M, outputImg.size());

		Point2f center;
		double angle;
		double scale;
		tie(center, angle, scale) = rotationOfTheFigureAroundTheAxis(inputImg, outMat);
		Mat MM = getRotationMatrix2D(center, angle, scale);

		Mat dstMat;
		warpAffine(outputImg, dstMat, MM, inputImg.size()); //��������� ������� � �������� ����������

		momentsResult(inputImg, outputImg);
	}
	break;
	default:
		break;
	}
}