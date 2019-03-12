#ifndef LINE_H
#define LINE_H

#include <QWidget>
#include "ui_Line.h"
#include <QPainter>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <QPen>
#include <QMouseEvent>

const int mapSize = 1000;

//namespace Ui
//{
//	class Line;//class Line was defined in ui_Line.h, which is derived from call Ui_Line.
//}

class Line : public QWidget //different from call Ui::Line.
{
    Q_OBJECT

public:
	explicit Line(QWidget *parent = Q_NULLPTR);
	~Line();
    void setPen(QPen);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
	void BresenhamLine(int, QPainter&);
	QVector<QPoint> StartEndPoints;
	bool **pixelMap;

private:
	Ui::Line *ui;
    QPen pen;
    //QVector<QPoint> StartEndPoints;

private slots:
	void Clear_click();
};

#endif
