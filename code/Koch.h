#ifndef KOCH_H
#define KOCH_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "ui_Koch.h"
#include "Line.h"

class Koch : public QWidget
{
	Q_OBJECT

public:
	explicit Koch(QWidget *parent = Q_NULLPTR);
	~Koch();
	void setPen(QPen);
	void paintEvent(QPaintEvent* event);

private:
	Ui::Koch *ui;
	QPen pen;
	//Line *line = new Line;// initialization is a must.
	Line *line;
	char level = -1;
	//bool curveStatus = false;
	void KochGraphic(QVector<QPoint>&, QPainter&, char level);

private slots:
	void Clear_click();
	void LevelZero_click();
	void LevelOne_click();
	void LevelTwo_click();
	void LevelThree_click();
	void LevelFour_click();
};


#endif