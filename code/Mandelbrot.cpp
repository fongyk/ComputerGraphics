#include "Mandelbrot.h"

Mandelbrot::Mandelbrot(QWidget *parent) : QWidget(parent), ui(new Ui::Mandelbrot)
{
	ui->setupUi(this);

	QFont ft;
	ft.setPointSize(18);
	ui->orderTwo->setFont(ft);
	ui->orderThree->setFont(ft);
	ui->orderFour->setFont(ft);
}

Mandelbrot::~Mandelbrot()
{
	delete ui;
}

void Mandelbrot::setPen(QPen p)
{
	pen = p;
	update();
}

void Mandelbrot::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	pen.setColor(Qt::darkGreen);
	//pen.setWidth(2);
	painter.setPen(pen);
	painter.fillRect(130, 260, 800, 600, QColor(255, 255, 255));
	if (order > 0)
	{
		MandelbrotGraphic(painter, order, 130, 260, 800, 600);
		order = 0;
	}
	painter.end();
}

void Mandelbrot::MandelbrotGraphic(QPainter& painter, const char order, int x1, int y1, int width, int height)
{
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			Complex z(0, 0);
			Complex c(-2.1 + (1.1 - -2.1) * (x / static_cast<double>(width)), -1.2 + (1.2 - -1.2) * (y / static_cast<double>(height)));
			int n = 0;
			while (n < 256)
			{
				++n;
				if (z.Modular() > 2) break;
				Complex tz = z;
				for (int i = 0; i < order - 1; ++i)
				{
					tz = tz * z;
				}
				z = tz + c;
			}
			double h = double((n<<2) + 130) / 256.0;
			setHSBColor(h, 0.7, 1.0 - h*h / 1.2);
			painter.setPen(pen);
			painter.drawPoint(QPoint(x+x1, y+y1));
		}
	}
}

void Mandelbrot::setHSBColor(float hue, float saturate, float bright)
{
	float red, green, blue;
	float h = (hue * 256) / 60;
	float p = bright * (1 - saturate);
	float q = bright * (1 - saturate * (h - (int)h));
	float t = bright * (1 - saturate * (1 - (h - (int)h)));
	switch ((int)h) {
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

void Mandelbrot::OrderTwo_click()
{
	order = 2;
	update();
}
void Mandelbrot::OrderThree_click()
{
	order = 3;
	update();
}
void Mandelbrot::OrderFour_click()
{
	order = 4;
	update();
}

