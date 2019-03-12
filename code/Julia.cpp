#include "Julia.h"

Julia::Julia(QWidget *parent) : QWidget(parent), ui(new Ui::Julia)
{
	ui->setupUi(this);

	QFont ft;
	ft.setPointSize(12);
	ui->cOne->setFont(ft);
	ui->cTwo->setFont(ft);
	ui->cThree->setFont(ft);
	ui->cFour->setFont(ft);
}

Julia::~Julia()
{
	delete ui;
}

void Julia::setPen(QPen p)
{
	pen = p;
	update();
}

void Julia::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::darkGreen);
	painter.setPen(pen);
	painter.fillRect(130, 260, 800, 600, QColor(255, 255, 255));
	switch (cFlag)
	{
	case 1: JuliaGraphic(painter, 130, 260, 800, 600, c1); break;
	case 2: JuliaGraphic(painter, 130, 260, 800, 600, c2); break;
	case 3: JuliaGraphic(painter, 130, 260, 800, 600, c3); break;
	case 4: JuliaGraphic(painter, 130, 260, 800, 600, c4); break;
	}
	cFlag = 0;
	painter.end();
}

void Julia::JuliaGraphic(QPainter& painter, int x1, int y1, int width, int height, Complex c)
{
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			/*Complex z((x - width / 2) / (width / 0.5), (y - height / 2) / (height / 0.5));*/
			Complex z((x - width / 2) / (width * 0.4), (y - height / 2) / (height * 0.4));
			int n = 0;
			while (n < 128)
			{
				++n;
				if (z.Modular() > 2) break;
				z = z * z + c;
			}
			if (n > 36)
			{
				double h = double(n>>1) / 256.0;
				setHSBColor(h, 0.7, 1.0 - h*h / 1.2);
			}
			else
			{
				pen.setColor(QColor(228, 228, 228));
			}
			painter.setPen(pen);
			painter.drawPoint(QPoint(x + x1, y + y1));
		}
	}
}

void Julia::setHSBColor(float hue, float saturate, float bright)
{
	float red, green, blue;
	float h = (hue * 256) / 60;
	float p = bright * (1 - saturate);
	float q = bright * (1 - saturate * (h - (int)h));
	float t = bright * (1 - saturate * (1 - (h - (int)h)));
	switch ((int)h) 
	{
	case 0:
		red = bright, green = t, blue = p;
		break;
	case 1:
		red = q, green = bright, blue = p;
		break;
	case 2:
		red = p, green = bright, blue = t;
		break;
	case 3:
		red = p, green = q, blue = bright;
		break;
	case 4:
		red = t, green = p, blue = bright;
		break;
	case 5:
	case 6:
		red = bright, green = p, blue = q;
		break;
	}
	pen.setColor(QColor(red * 256, green * 256, blue * 256));
}

void Julia::Cone_click()
{
	cFlag = 1;
	update();
}
void Julia::Ctwo_click()
{
	cFlag = 2;
	update();
}
void Julia::Cthree_click()
{
	cFlag = 3;
	update();
}
void Julia::Cfour_click()
{
	cFlag = 4;
	update();
}

