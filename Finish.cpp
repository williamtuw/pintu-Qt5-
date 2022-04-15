#include "Finish.h"

Finish::Finish(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.btnback, &QPushButton::clicked, this, &Finish::Onback);
}

Finish::~Finish()
{
}
void Finish::Onback()
{
	accept();
}