#include "Fern.h"

Fern::Fern(QWidget *parent) : QWidget(parent), ui(new Ui::Fern)
{
	ui->setupUi(this);

	QFont ft;
	ft.setPointSize(18);
	ui->prob1->setFont(ft);
	ui->prob2->setFont(ft);
	ui->prob3->setFont(ft);
}

Fern::~Fern()
{
	delete ui;
}

void Fern::setPen(QPen p)
{
	pen = p;
	update();
}

void Fern::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::darkGreen);
	//pen.setWidth(2);
	painter.setPen(pen);
	painter.fillRect(130, 250, 650, 650, QColor(228, 228, 228));
	switch (pflag)
	{
	case 1: FernGraphic(painter, prob1);
	case 2: FernGraphic(painter, prob2);
	case 3: FernGraphic(painter, prob3);
	}
	pflag = 0;

	painter.end();
}

inline std::vector<double> Fern::LinearProjection(std::vector<double> point, double a, double b, double c, double d, double e, double f)
{
	double x, y;
	x = point[0];
	y = point[1];
	point[0] = (a * x + b * y + e);
	point[1] = (c * x + d * y + f);
	return point;
}

void Fern::FernGraphic(QPainter& painter, const double prob[4])
{
	std::srand((unsigned)time(NULL));
	const int times = 1000000;
	double mileStone0 = MAX * prob[0];
	double mileStone1 = MAX * (prob[0] + prob[1]);
	double mileStone2 = MAX * (prob[0] + prob[1] + prob[2]);
	std::vector<double> point{ 1, 1 };
	for (int k = 0; k < times; ++k)
	{
		double randN = MIN + std::rand() % (MAX - MIN + 1);
		if (randN < mileStone0)
		{
			//point = LinearProjection(point, 0.85, 0.04, -0.04, 0.85, 0.0, 1.6);

			point = LinearProjection(point, 0.0, 0.0, 0.0, 0.16, 0.0, 0.0);
		}
		else if (randN < mileStone1)
		{
			//point = LinearProjection(point, 0.20, -0.26, 0.23, 0.22, 0.0, 1.6);

			point = LinearProjection(point, 0.85, 0.04, -0.04, 0.85, 0.0, 1.6);
		}
		else if (randN < mileStone2)
		{
			//point = LinearProjection(point, -0.15, 0.28, 0.26, 0.24, 0.0, 0.44);

			point = LinearProjection(point, 0.20, -0.26, 0.23, 0.22, 0.0, 1.6);
		}
		else
		{
			//point = LinearProjection(point, 0.0, 0.0, 0.0, 0.16, 0.0, 0.0);

			point = LinearProjection(point, -0.15, 0.28, 0.26, 0.24, 0.0, 0.44);
		}
		painter.drawPoint(- point[0] * 40 + 500, - point[1] * 40 + 800);
	}
}

void Fern::P1_click()
{
	pflag = 1;
	update();
}
void Fern::P2_click()
{
	pflag = 2;
	update();
}
void Fern::P3_click()
{
	pflag = 3;
	update();
}

