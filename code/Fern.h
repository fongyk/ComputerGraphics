#ifndef FERN_H
#define FERN_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include "ui_Fern.h"

const int MIN = 1;
const int MAX = 100;

const double prob1[4] = { 0.01, 0.85, 0.07, 0.07 };
const double prob2[4] = { 0.33, 0.33, 0.33, 0.01 };
const double prob3[4] = { 0.01, 0.91, 0.04, 0.04 };

class Fern : public QWidget
{
	Q_OBJECT

public:
	explicit Fern(QWidget *parent = Q_NULLPTR);
	~Fern();
	void setPen(QPen);
	void paintEvent(QPaintEvent* event);

private:
	Ui::Fern *ui;
	QPen pen;
	char pflag = 0;
	void FernGraphic(QPainter&, const double prob[4]);
	std::vector<double> LinearProjection(std::vector<double> point, double a, double b, double c, double d, double e, double f);

	private slots:
	void P1_click();
	void P2_click();
	void P3_click();
};


#endif