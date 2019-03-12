#pragma once

#include <QWidget>
#include "ui_Fill.h"
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <cmath>
#include "Line.h"

//class Fill : public Line
class Fill: public QWidget
{
	Q_OBJECT

public:
	explicit Fill(QWidget *parent = Q_NULLPTR);
	~Fill();
	void setPen(QPen);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);

private:
	Ui::Fill *ui;
	//Line *line = new Line;// initialization is a must.
	Line *line;
	QPen pen;
	void seedFilling(QPoint, QPainter&);
	bool closePolygon = false;
	bool fillSig = false;
	QVector<QPoint> fillPos;

private slots:
	void Clear_click();
};
