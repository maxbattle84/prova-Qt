#ifndef SOMMA_H
#define SOMMA_H

#include <ui_somma.h>

namespace Ui {
	class somma;
}

class Somma : public QWidget
{
	Q_OBJECT

public:
	explicit Somma(QWidget *parent = 0);
	~Somma();
	//bool isChanged();
	public slots:
	void on_bt_Somma_clicked();


private:
	Ui::somma *ui;
};

#endif //SOMMA_H