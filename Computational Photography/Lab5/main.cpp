#include "hw3_gn.h"
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <cmath>
using namespace std;
using namespace cv;
class ResidualFunction4200 :public ResidualFunction {
	int _R;
	int _X;
	double **data;
public:
	int nR() const{
		return _R;
	}
	int nX() const{
		return _X;
	}
	void eval(double *R, double *J, double *X) {
		for (int i = 0; i < _R;i++) {
			double tsum=0;
			for (int j = 0; j < _X;j++) {
				tsum += pow(data[i][j], 2) / pow(X[j], 2);
				J[i*_X + j] = -2 * pow(data[i][j], 2) / pow(X[j], 3);
			}
			R[i] = 1 - tsum;
		}
	}
	ResidualFunction4200(int __R,int __X,char *filename):_R(__R),_X(__X) {
		data = new double*[_R];
		ifstream input(filename);
		for (int i = 0; i < _R;i++) {
			data[i] = new double[_X];
			for (int j = 0; j < _X;j++) {
				input >> data[i][j];
			}
		}
	}
};
class Solver4200 :public GaussNewtonSolver {
public:
	// override solve function
	double solve(ResidualFunction *f, double *X,
		GaussNewtonParams param = GaussNewtonParams(),
		GaussNewtonReport *report = nullptr) {
		double *arrR = new double[f->nR()];
		double *arrJ = new double[f->nR()*f->nX()];
		Mat matR, matJ;
		Mat DeltaX;
		
		int n = 0;
		while (n<param.max_iter){
			f->eval(arrR, arrJ, X);
			matR = Mat(f->nR(), 1, CV_64F, arrR);
			matJ = Mat(f->nR(), f->nX(), CV_64F, arrJ);

			Mat JTJ = matJ.t()* matJ;
			Mat JTR = matJ.t() * matR;
			DeltaX = -JTJ.inv()*JTR;
			
			double Rmax = findMax(arrR, f->nR());
			double Dmin, Dmax;
			minMaxIdx(DeltaX, &Dmin, &Dmax);
			Dmin = (fabs(Dmin) < fabs(Dmax)) ? fabs(Dmin) : fabs(Dmax);
			for (int i = 0; i < f->nX();i++) {
				X[i] -= DeltaX.at<double>(i, 0);
			}
			if (Rmax <= param.residual_tolerance ){
				report->stop_type = report->STOP_RESIDUAL_TOL;
				break;
			}
			if (Dmin <= param.gradient_tolerance){
				report->stop_type = report->STOP_GRAD_TOL;
			}

			if (param.verbose){
				printf("Iter times: %d\n",report->n_iter);
				cout << "R: " << matR << endl;
				cout << "J: " << matJ << endl;
				for (int i = 0; i < f->nX();i++) {
					printf("X[%d]: %lf", i,X[i]);
				}
			}
			report->n_iter++;
		}
		report->stop_type = report->STOP_NO_CONVERGE;
		delete[] arrR;
		delete[] arrJ;
		return 1;
	}

private:
	double findMax(double* arr, int len) {
		double max = arr[0];
		for (int i = 1; i < len;i++) {
			max = (arr[i] > max) ? arr[i] : max;
		}
		return max;
	}
};


int main() {
	ResidualFunction4200 fun(753, 3, "ellipse753.txt");
	Solver4200 solver;
	double X[] = {0.9,0.9,0.9 };
	GaussNewtonReport report;
	solver.solve(&fun, X, GaussNewtonParams(), &report);
	printf("Result: %.3lf %.3lf %.3lf\n", X[0], X[1], X[2]);

	return 0;
}