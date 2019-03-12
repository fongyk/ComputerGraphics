#ifndef BEZIER_H
#define BEZIER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <cmath>
#include <algorithm>
#include "ui_Bezier.h"
#include "Line.h"

const double du = 0.001;

inline int Factorial(int);

class Bezier : public QWidget
{
	Q_OBJECT

public:
	explicit Bezier(QWidget *parent = Q_NULLPTR);
	~Bezier();
	void setPen(QPen);
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	
private:
	Ui::Bezier *ui;
	QPen pen;
	//Line *line = new Line;// initialization is a must.
	Line *line;
	bool curveStatus = false;
	bool closePolygon = false;
	void BezierCurve(QVector<QPoint>, QPainter&);

private slots:
	void Clear_click();
};


#endif