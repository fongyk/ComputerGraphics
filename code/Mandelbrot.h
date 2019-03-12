#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "ui_Mandelbrot.h"
#include "Line.h"
#include "Complex.h"

class Mandelbrot : public QWidget
{
	Q_OBJECT

public:
	explicit Mandelbrot(QWidget *parent = Q_NULLPTR);
	~Mandelbrot();
	void setPen(QPen);
	void paintEvent(QPaintEvent* event);

private:
	Ui::Mandelbrot *ui;
	QPen pen;
	char order = 0;
	void MandelbrotGraphic(QPainter&, const char order, int, int, int, int);
	void setHSBColor(float, float, float);

	private slots:
	void OrderTwo_click();
	void OrderThree_click();
	void OrderFour_click();
};


#endif