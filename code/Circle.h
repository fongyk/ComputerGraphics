#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>
#include "ui_Circle.h"
#include <QPen>
#include <QMouseEvent>
#include <QPainter>
#include <cmath>

class Circle : public QWidget
{
	Q_OBJECT

public:
	explicit Circle(QWidget *parent = Q_NULLPTR);
	~Circle();
	void setPen(QPen);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void BresenhamCircle();

private:
	Ui::Circle *ui;
	QPen pen;
	QVector<QPoint> CenterRadius;

private slots:
	void Clear_click();
};

#endif
