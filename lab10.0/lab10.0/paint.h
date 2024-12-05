#pragma once
#include"Observer.h"
#include"ContarctGUI.h"
#include"contract.h"
#include<QtWidgets>

class paintGUI :public QWidget, public Observer {
private:
	Contract& rep;
public:
	paintGUI(Contract& rep) :rep{ rep } {
		rep.addObserver(this);
		//paintEvent();
	}

	void paintEvent(QPaintEvent*)override {
		QPainter p{ this };
		int x;
		int y;
		for (auto& it : rep.getAllCont())
		{
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 1000, 1000);
			QImage image("Image.jpg");

			p.drawImage(target, image, source);
			x += 40;
		}
	}
	void update()override {
		repaint();
	}
	~paintGUI() {
		rep.removeObserver(this);
	}
};