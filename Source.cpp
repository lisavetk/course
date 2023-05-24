#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/cvconfig.h>

using namespace cv;
using namespace std;

void main() {
	setlocale(LC_ALL, "ru");
	//Mat img = imread("C:/Users/Таиссия Савенова/Desktop/курсовая/image1.jpg"); //чтение файла

	//import image
	string path = "Resourses/image.jpg"; //запоминаем путь до изображения
	//Mat img = imread(path); //ввод изображения в программу
	//namedWindow("Pic", WINDOW_AUTOSIZE); //обозвать окно и задать размер
	//imshow("Pic", img); //открыть изображение
	//moveWindow("Pic", 500, 45); //координаты, где откроется окно
	//waitKey(0); //ждать закрытия по кнопке
	//destroyAllWindows(); //закрыть вместе с консолью

	//////////// ROWS - СТРОКИ //////////// COLS - СТОЛБЦЫ ////////////

	//создаем окно исходного изображения
	Mat inputImg = imread(path, IMREAD_GRAYSCALE);
	threshold(inputImg, inputImg, 128, 255, THRESH_BINARY);
	namedWindow("Input Image", WINDOW_AUTOSIZE);

	//создаем окно изменненого изображения
	Mat outputImg = Mat(inputImg.size(), inputImg.type(), IMREAD_GRAYSCALE);
	threshold(outputImg, outputImg, 128, 255, THRESH_BINARY);


	namedWindow("Output Image", WINDOW_AUTOSIZE);

	//аффинные преобразования
	Point2f inpMat[3];
	Point2f outMat[3];

	inpMat[0] = Point2f(0.0, 0.0);
	inpMat[1] = Point2f(inputImg.cols, 0);
	inpMat[2] = Point2f(0, inputImg.rows);

	/*outMat[0] = Point2f(0.0, 0.0);
	outMat[1] = Point2f(inputImg.cols, 0);
	outMat[2] = Point2f(0, inputImg.rows);*/

	////растяжение вправо
	//outMat[0] = Point2f(0.0, 0.0);
	//outMat[1] = Point2f(inputImg.cols+100, 0);
	//outMat[2] = Point2f(0, inputImg.rows);

	//растяжение вниз
	outMat[0] = Point2f(0.0, 0.0);
	outMat[1] = Point2f(inputImg.cols, 0);
	outMat[2] = Point2f(0, inputImg.rows+100);



	Mat M = getAffineTransform(inpMat, outMat);
	//cout << M << endl;

	warpAffine(inputImg, outputImg, M, outputImg.size());

	////вывод изображений в окнах (исходное и измененное) - аффинные преобразования
	//imshow("Input Image", inputImg);
	//imshow("Output Image", outputImg);
	//waitKey(0);

	//Поворот вокруг перпендикуляра церез центр
	Point2f center(inputImg.cols / 2, inputImg.rows / 2);
	double angle = 45;
	double scale = 1;

	Mat MM = getRotationMatrix2D(center, angle, scale); 

	Mat dstMat;
	//warpAffine(inputImg, dstMat, MM, inputImg.size()); //применить поворот к исходному изображению
	warpAffine(outputImg, dstMat, MM, inputImg.size()); //применить поворот к аффиному растяжению


	////////////// МОМЕНТЫ /////////////////

	vector<vector<Point>>  contours;
	vector<vector<Point>>  contours2;
	vector<Vec4i> hierarchy;
	vector<Vec4i> hierarchy2;
	findContours(inputImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	findContours(outputImg, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Moments> P(contours.size());
	vector<Moments> T(contours2.size());

	//центральные моменты
	cout << "Центральные моменты для первого изображения: ";
	for (int i = 0; i < (int)contours.size(); i++) {
		P[i] = moments(contours[i]);
		
		
		//cout << P[i].m00 << "  " << contourArea(contours[i]) << endl;
		//cout << P[i].m01 << "  " << contourArea(contours[i]) << endl;
		cout << P[i].m10 << endl;
		//cout << P[i].m02 << "  " << contourArea(contours[i]) << endl;
	}
	cout << '\n' << "Центральные моменты для второго изображения: ";
	for (int i = 0; i < (int)contours2.size(); i++) {
		T[i] = moments(contours2[i]);

		cout << T[i].m10 << "  "  << endl;
		//cout << P[i].m01 << "  " << contourArea(contours[i]) << endl;
		//cout << T[i].m02 << "  " << contourArea(contours2[i]) << endl;
	}
	cout << endl;

	cout << "Нормализованные центральные моменты для первого изображения: ";
	for (int i = 0; i < (int)contours.size(); i++) {
		P[i] = moments(contours[i]);


		//cout << P[i].m00 << "  " << contourArea(contours[i]) << endl;
		//cout << P[i].m01 << "  " << contourArea(contours[i]) << endl;
		cout << P[i].nu30 << endl;
		//cout << P[i].m02 << "  " << contourArea(contours[i]) << endl;
	}
	cout << '\n' << "Нормализованные центральные моменты для второго изображения: ";
	for (int i = 0; i < (int)contours2.size(); i++) {
		T[i] = moments(contours2[i]);

		cout << T[i].nu30 << "  " << endl;
		//cout << P[i].m01 << "  " << contourArea(contours[i]) << endl;
		//cout << T[i].m02 << "  " << contourArea(contours2[i]) << endl;
	}
	cout << endl;

	double huMoments[7];
	cout << "HuMoments для первого изображения: " <<endl;
	for (int i = 0; i < (int)contours.size(); i++) {
		
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
	for (int i = 0; i < (int)contours2.size(); i++) {
		
		HuMoments(T[i], huMoments2);
		for (int i = 0; i < 7; i++) {
			huMoments2[i] = -1 * copysign(1.0, huMoments2[i]) * log10(abs(huMoments2[i]));
		}
		for (double hh2 : huMoments2) {
			cout << hh2 << '\n';
		}
	}
	


	//Moments moments(inputImg, false);
	//imshow("IM", dstMat);
	//waitKey(0);
	//// Calculate Hu Moments 
	//double huMoments[7];
	//HuMoments(moments, huMoments);


		

	//вывод изображений в окнах (исходное и измененное) - поворот вокруг перпендикуляра
	imshow("Input Image", inputImg);
	imshow("Output Image", dstMat);
	waitKey(0);


//	/////// МОМЕНТЫ ИЗОБРАЖЕНИЙ ///////
//
//	Mat img = imread(path, IMREAD_GRAYSCALE);
//	namedWindow("In", 0);
//	//namedWindow("Out", 0);
//
//
//	////первая ось х, вторая у
//	//vector<Point> c1 = { {100, 100}, {150, 100},  {150, 200} };
//	//polylines(img, c1, 1, Scalar(0, 255, 255), 3);
//	//cout << contourArea(c1) << endl;
//
//	vector<vector<Point>>  contours;
//	vector<Vec4i> hierarchy;
//	threshold(img, img, 100, 255, THRESH_BINARY);
//
//	line(img, Point(15, 30), Point(40, 30), Scalar(255, 255, 255), 5);
//
//	circle(img, Point(100, 80), 25, Scalar(255), 5);
//
//	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//	//Mat out = Mat::zeros(img.size(), CV_8UC3);
//
//	//drawContours(out, contours, -1, Scalar(255, 255, 255), 3);
//
//	vector<Moments> M(contours.size());
//
//	for (int i = 0; i < (int)contours.size(); i++) {
//		M[i] = moments(contours[i]);
//
//		cout << M[i].m00 << "  " << contourArea(contours[i]) << endl;
//	}
//
//
//	/*Point2f p(350,350);
//	circle(img,p, 10, Scalar(255), FILLED);
//
//	cout << pointPolygonTest(contours[0], p, true) << endl;*/
//
//
//	imshow("In", img);
//	waitKey(0);
//
//	/*Mat img = imread(path, IMREAD_GRAYSCALE);
//	namedWindow("In", WINDOW_AUTOSIZE);
//	namedWindow("Out", WINDOW_AUTOSIZE);
//
//	vector<vector<Point>> contours;
//	vector <Vec4i> hierarchy;
//	threshold(img, img, 100, 255, THRESH_BINARY);
//
//	line(img, Point(150,300), Point(400,300), Scalar(255,255,255), 5)*/
//
//
//	//vector<Moments> M[contours.size()];
//
//	//Moments moments(im, false);
//	//imshow("IM", dstMat);
//	//waitKey(0);
//	//// Calculate Hu Moments 
//	//double huMoments[7];
//	//HuMoments(moments, huMoments);
//
//	//return 0;
}