#pragma once
#include "DisciplinaGUI.h"
#include "contractGUI.h"
#include "observer.h"
#include <qpainter.h>

class contRDOnlyGUI : public QWidget, public Observer
{
	// cos RDOnly
	friend class DisciplinaGUI;
	friend class contCRUDGUI;

	// pointer la cosul curent
	contCRUDGUI* cos;

public:

	// constructorul clasei
	contRDOnlyGUI(contCRUDGUI* c);

	// construim interfata
	void build_UI();

	// actualizam (redesenam figurile)
	void update() override;

	// desenam figurile
	void paintEvent(QPaintEvent* ev) override;

	// destructorul clasei
	~contRDOnlyGUI();
};