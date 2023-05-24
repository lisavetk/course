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
	std::cout << "Необходимо выбрать способ изменения изображения" << endl;
	std::cout << "0 - растяжение по осям" << endl;
	std::cout << "1 - сжатие по осям" << endl;
	std::cout << "2 - поворот вокруг оси, проходящей через центр креста и перпендикулярно экрану" << endl;
	std::cout << "3 - комбинация растяжения и поворота" << endl;
	std::cout << "4 - комбинация сжатия и поворота" << endl;
	std::cout << "Введите нужную деформацию: ";
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
		cout << "Момент m00: " << _moments.m00 << endl;
		cout << "Момент m10: " << _moments.m10 << endl;
		cout << "Момент m02: " << _moments.m02 << endl;
		cout << "Момент m03: " << _moments.m03 << endl;
		cout << "Момент m11: " << _moments.m11 << endl;
		cout << "Момент m12: " << _moments.m12 << endl;
		cout << "Момент m20: " << _moments.m20 << endl;
		cout << "Момент m21: " << _moments.m21 << endl;
		cout << "Момент m30: " << _moments.m30 << endl;

		cout << "Момент mu20: " << _moments.mu20 << endl;
		cout << "Момент mu11: " << _moments.mu11 << endl;
		cout << "Момент mu02: " << _moments.mu02 << endl;

		cout << "Момент mu30: " << _moments.mu30 << endl;
		cout << "Момент mu21: " << _moments.mu21 << endl;
		cout << "Момент mu12: " << _moments.mu12 << endl;
		cout << "Момент mu03: " << _moments.mu03 << endl;
	}

private:

	Moments _moments;

};


//подсчет и вывод моментов
void momentsResult(Mat inputImg, Mat outputImg) 
{
	cout << endl;

	vector<vector<Point>> contours;
	findContours(inputImg, contours,  RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Moments> P(contours.size());

	vector<vector<Point>>  contours2;
	findContours(outputImg, contours2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Moments> T(contours2.size());

	//центральные моменты
	cout << "Центральные моменты для первого изображения: " << endl;
	/*for (const auto& contour : contours)
	{
		MomentWrapper P; 

		Wrapper
		P.push_back();

	}*/
	for (int i = 0; i < (int)contours.size(); i++) {
		P[i] = moments(contours[i], true);
		cout << "Момент m00: " << P[i].m00 << endl;
		cout << "Момент m10: " << P[i].m10 << endl;
		cout << "Момент m02: " << P[i].m02 << endl;
		cout << "Момент m03: " << P[i].m03 << endl;
		cout << "Момент m11: " << P[i].m11 << endl;
		cout << "Момент m12: " << P[i].m12 << endl;
		cout << "Момент m20: " << P[i].m20 << endl;
		cout << "Момент m21: " << P[i].m21 << endl;
		cout << "Момент m30: " << P[i].m30 << endl;

		cout << "Момент mu20: " << P[i].mu20 << endl;
		cout << "Момент mu11: " << P[i].mu11 << endl;
		cout << "Момент mu02: " << P[i].mu02 << endl;

		cout << "Момент mu30: " << P[i].mu30 << endl;
		cout << "Момент mu21: " << P[i].mu21 << endl;
		cout << "Момент mu12: " << P[i].mu12 << endl;
		cout << "Момент mu03: " << P[i].mu03 << endl;
	}

	cout << '\n' << "Центральные моменты для второго изображения: " << endl;
	for (int i = 0; i < (int)contours2.size(); i++) {
		T[i] = moments(contours2[i], true);

		cout << "Момент m00: " << T[i].m00 << endl;
		cout << "Момент m10: " << T[i].m10 << endl;
		cout << "Момент m02: " << T[i].m02 << endl;
		cout << "Момент m03: " << T[i].m03 << endl;
		cout << "Момент m11: " << T[i].m11 << endl;
		cout << "Момент m12: " << T[i].m12 << endl;
		cout << "Момент m20: " << T[i].m20 << endl;
		cout << "Момент m21: " << T[i].m21 << endl;
		cout << "Момент m30: " << T[i].m30 << endl;

		cout << "Момент mu20: " << T[i].mu20 << endl;
		cout << "Момент mu11: " << T[i].mu11 << endl;
		cout << "Момент mu02: " << T[i].mu02 << endl;

		cout << "Момент mu30: " << T[i].mu30 << endl;
		cout << "Момент mu21: " << T[i].mu21 << endl;
		cout << "Момент mu12: " << T[i].mu12 << endl;
		cout << "Момент mu03: " << T[i].mu03 << endl;
	}
	cout << endl;

	cout << "Нормированные центральные моменты для первого изображения: " << endl;
	for (int i = 0; i < (int)contours.size(); i++) {
		P[i] = moments(contours[i], true);

		cout << "Момент nu20: " << P[i].nu20 << endl;
		cout << "Момент nu11: " << P[i].nu11 << endl;
		cout << "Момент nu02: " << P[i].nu02 << endl;

		cout << "Момент nu30: " << P[i].nu30 << endl;
		cout << "Момент nu21: " << P[i].nu21 << endl;
		cout << "Момент nu12: " << P[i].nu12 << endl;
		cout << "Момент nu03: " << P[i].nu03 << endl;

	}

	cout << '\n' << "Нормированные центральные моменты для второго изображения: " << endl;
	for (int i = 0; i < (int)contours2.size(); i++) {
		T[i] = moments(contours2[i], true);

		cout << "Момент nu20: " << T[i].nu20 << endl;
		cout << "Момент nu11: " << T[i].nu11 << endl;
		cout << "Момент nu02: " << T[i].nu02 << endl;

		cout << "Момент nu30: " << T[i].nu30 << endl;
		cout << "Момент nu21: " << T[i].nu21 << endl;
		cout << "Момент nu12: " << T[i].nu12 << endl;
		cout << "Момент nu03: " << T[i].nu03 << endl;
	}
	cout << endl;

	double huMoments[7];
	cout << "HuMoments для первого изображения: " << endl;
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
	cout << '\n' << "HuMoments для второго изображения: " << endl;
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

	//вывод изображений в окнах (исходное и измененное) - аффинные преобразования
	imshow("Input Image", inputImg);
	imshow("Output Image", outputImg);
	waitKey(0);
}

//растяжение
Point2f* stretchingTheFigure(Mat inputImg, Point2f outMat[]) {
	int direction;
	cout << "Необходимо выбрать направление растяжения" << endl;
	cout << "0 - растяжение вправо" << endl;
	cout << "1 - растяжение вниз" << endl;
	cout << "2 - растяжение вправо и вниз" << endl;
	cout << "Введите нужное направление: ";
	cin >> direction;
	switch (direction)
	{
	case 0: //растяжение вправо 
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols + 100, 0);
		outMat[2] = Point2f(0, inputImg.rows);
	}
	break;
	case 1: //растяжение вниз
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols, 0);
		outMat[2] = Point2f(0, inputImg.rows + 100);
	}
	break;
	case 2: //растяжение вправо и вниз
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

//сжатие
Point2f* compressionTheFigure(Mat inputImg, Point2f outMat[]) {
	int direction;
	cout << "Необходимо выбрать направление сжатия" << endl;
	cout << "0 - сжатие влево" << endl;
	cout << "1 - сжатие вверх" << endl;
	cout << "2 - сжатие влево и вверх" << endl;
	cout << "Введите нужное направление: ";
	cin >> direction;
	switch (direction)
	{
	case 0: //сжатие влево 
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols - 100, 0);
		outMat[2] = Point2f(0, inputImg.rows);
	}
	break;
	case 1: //сжатие вверх
	{
		outMat[0] = Point2f(0.0, 0.0);
		outMat[1] = Point2f(inputImg.cols, 0);
		outMat[2] = Point2f(0, inputImg.rows - 100);
	}
	break;
	case 2: //сжатие влево и вверх
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

//поворот вокруг оси
tuple<Point2f, double, double> rotationOfTheFigureAroundTheAxis(Mat inputImg, Point2f outMat[]) {
	double angle;
	cout << "Необходимо выбрать угол поворота" << endl;
	cout << "Введите угол поворота: ";
	cin >> angle;

	//Поворот вокруг перпендикуляра церез центр
	Point2f center(inputImg.cols / 2, inputImg.rows / 2);
	double scale = 1;
	return make_tuple(center, angle, scale);
}

void main() {
	setlocale(LC_ALL, "ru");
	//import image
	string path = "Resourses/image.jpg"; //запоминаем путь до изображения

	//выбор способа деформации
	TransformType methodOfDeformation = printStartMessage();

	//////////// ROWS - СТРОКИ //////////// COLS - СТОЛБЦЫ ////////////

	//создаем окно исходного изображения
	Mat inputImg = imread(path, IMREAD_GRAYSCALE); //изображение попадает в код
	threshold(inputImg, inputImg, 128, 255, THRESH_BINARY);
	namedWindow("Input Image", WINDOW_AUTOSIZE); //назвать окно вывода изображения и задать размер

	//создаем окно изменненого изображения
	Mat outputImg = Mat(inputImg.size(), inputImg.type(), IMREAD_GRAYSCALE);
	threshold(outputImg, outputImg, 128, 255, THRESH_BINARY);
	namedWindow("Output Image", WINDOW_AUTOSIZE);

	///////////цикл для работы всей программы по выбору

	//аффинные преобразования
	Point2f inpMat[3];
	Point2f outMat[3];

	//матрица исходного изображения
	inpMat[0] = Point2f(0.0, 0.0);
	inpMat[1] = Point2f(inputImg.cols, 0);
	inpMat[2] = Point2f(0, inputImg.rows);

	switch (methodOfDeformation)
	{
	case TransformType::Stretch: //растяжение по осям
	{
		stretchingTheFigure(inputImg, outMat);

		Mat M = getAffineTransform(inpMat, outMat);

		warpAffine(inputImg, outputImg, M, outputImg.size());
		momentsResult(inputImg, outputImg);
	}
	break;
	case TransformType::Compression: //сжатие по осям
	{
		compressionTheFigure(inputImg, outMat);

		Mat M = getAffineTransform(inpMat, outMat);

		warpAffine(inputImg, outputImg, M, outputImg.size());
		momentsResult(inputImg, outputImg);
	}
	break;
	case TransformType::Rotation: //поворот вокруг оси, проходящей через центр креста и перпендикулярно экрану
	{
		//rotationOfTheFigureAroundTheAxis(inputImg, outMat);
		
		Point2f center;
		double angle;
		double scale;
		tie(center, angle, scale) = rotationOfTheFigureAroundTheAxis(inputImg, outMat);
		Mat MM = getRotationMatrix2D(center, angle, scale);

		Mat dstMat;
		//warpAffine(inputImg, dstMat, MM, inputImg.size()); //применить поворот к исходному изображению
		warpAffine(inputImg, outputImg, MM, outputImg.size()); //применить поворот к исходному изображению

		momentsResult(inputImg, outputImg);
	}
	break;
	case TransformType::StretchAndRotation: //комбинация растяжения и поворота
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
		warpAffine(outputImg, dstMat, MM, inputImg.size()); //применить поворот к аффиному растяжению

		momentsResult(inputImg, outputImg);

	}
	break;
	case TransformType::CompressionAndRotation: //комбинация сжатия и поворота
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
		warpAffine(outputImg, dstMat, MM, inputImg.size()); //применить поворот к аффиному растяжению

		momentsResult(inputImg, outputImg);
	}
	break;
	default:
		break;
	}
}