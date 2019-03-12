#ifndef JULIA_H
#define JULIA_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "ui_Julia.h"
#include "Line.h"
#include "Complex.h"

const Complex c1 = Complex(-0.745, 0.113);
const Complex c2 = Complex(-0.314, -0.628);
const Complex c3 = Complex(-0.8, 0.156);
const Complex c4 = Complex(0.281, 0.01);

class Julia : public QWidget
{
	Q_OBJECT

public:
	explicit Julia(QWidget *parent = Q_NULLPTR);
	~Julia();
	void setPen(QPen);
	void paintEvent(QPaintEvent* event);

private:
	Ui::Julia *ui;
	QPen pen;
	char cFlag = 0;
	void JuliaGraphic(QPainter&, int, int, int, int, Complex);
	void setHSBColor(float, float, float);

	private slots:
	void Cone_click();
	void Ctwo_click();
	void Cthree_click();
	void Cfour_click();
};


#endif