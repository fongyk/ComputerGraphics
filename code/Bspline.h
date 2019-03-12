#ifndef BSPLINE_H
#define BSPLINE_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <cmath>
#include <algorithm>
#include "ui_Bspline.h"
#include "Line.h"

const double du2 = 0.01;

class Bspline : public QWidget
{
	Q_OBJECT

public:
	explicit Bspline(QWidget *parent = Q_NULLPTR);
	~Bspline();
	void setPen(QPen);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);

private:
	Ui::Bspline *ui;
	QPen pen;
	//Line *line = new Line;// initialization is a must.
	Line *line;
	char order = 3;
	bool curveStatus = false;
	void BsplineCurve(QVector<QPoint>, QPainter&);
	void DeBoor(int k, int i, double u, double *knots, QVector<QPoint> P, int pn, QPoint *outP);

	private slots:
	void Clear_click();
};


#endif