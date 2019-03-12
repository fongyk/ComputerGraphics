#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Fill.h"
#include "Bezier.h"
#include "Bspline.h"
#include "Koch.h"
#include "Mandelbrot.h"
#include "Julia.h"
#include "Fern.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;

	Line getLine;
	Circle getCircle;
	Ellipse getEllipse;
	Fill getFill;
	Bezier getBezier;
	Bspline getBspline;
	Koch getKoch;
	Mandelbrot getMandelbrot;
	Julia getJulia;
	Fern getFern;

private slots:
	void Line_click();
	void Circle_click();
	void Ellipse_click();
	void Fill_click();
	void Bezier_click();
	void Bspline_click();
	void Koch_click();
	void Mandelbrot_click();
	void Julia_click();
	void Fern_click();
};
