#ifndef SOMMA2_H
#define SOMMA2_H

#include <ui_somma2.h>

namespace Ui {
	class somma2;
}

class Somma2 : public QWidget
{
	Q_OBJECT

public:
	explicit Somma2(QWidget *parent = 0);
	~Somma2();
	
	public slots:
	void sum();
	void on_languageBox_currentIndexChanged(int index);
	

private:
	Ui::somma2 *ui;
	void ApplyTranslation(QString lang);
	QTranslator* mTranslator;
};

#endif //SOMMA2_H