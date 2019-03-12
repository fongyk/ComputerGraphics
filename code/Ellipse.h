#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QWidget>
#include "ui_Ellipse.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <QPen>
#include <QMouseEvent>


class Ellipse : public QWidget
{
	Q_OBJECT

public:
	explicit Ellipse(QWidget *parent = Q_NULLPTR);
	~Ellipse();
	void setPen(QPen);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void BresenhamEllipse();

private:
	Ui::Ellipse *ui;
	QPen pen;
	QVector<QPoint> TriPoints;

private slots:
	void Clear_click();

};

#endif
