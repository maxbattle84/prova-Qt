// Qt
#include <Somma2.h>
#include <Somma2.moc>
#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QDir>
#include <QtGui/qmessagebox.h>

#include <iostream>

#include <cassert>

using namespace std;

Somma2::Somma2(QWidget *parent) : QWidget(parent), ui(NULL), mTranslator(NULL)
{
	ui = new Ui::somma2;
	ui->setupUi(this);
	ui->languageBox->setCurrentIndex(0);

	connect(ui->te_Intero1, SIGNAL(textChanged()), this, SLOT(sum()));
	connect(ui->te_Intero2, SIGNAL(textChanged()), this, SLOT(sum()));

}

Somma2::~Somma2()
{
	delete ui;
}

void Somma2::sum() 
{
	int i1, i2;
	QString str1 = ui->te_Intero1->toPlainText();
	QString str2 = ui->te_Intero2->toPlainText();
	bool ok1;
	bool ok2;
	i1 = str1.toInt(&ok1);
	i2 = str2.toInt(&ok2);

	if (!ok1 || !ok2) { // not integers
		ui->te_Result->setText("Insert two integers");
	}
	
	else {
		int somma;
		somma = i1 + i2;
		QString str = QString::number(somma);
		ui->te_Result->setText(str);
	}
}

void Somma2::ApplyTranslation(QString lang)
{
	// Install the translator
	if (!mTranslator)
		mTranslator = new QTranslator();
	mTranslator->load(lang, "../x64/bin");
	mTranslator->load("../x64/bin/" + lang);
	qApp->installTranslator(mTranslator);

	qApp->setProperty("lang", lang);
	qApp->processEvents();

	// Update the UI
	ui->retranslateUi(this);
	
}


void Somma2::on_languageBox_currentIndexChanged(int index)
{
	cout << "\n" << index;
	ui->languageBox->setItemData(0, "italiano");
	ui->languageBox->setItemData(1, "english");

	QString nome = ui->languageBox->itemData(index).toString();
	cout << "\n" << nome.toStdString();

	bool isBlocked = ui->languageBox->blockSignals(true);
	ApplyTranslation(ui->languageBox->itemData(index).toString());
	
	ui->languageBox->blockSignals(isBlocked);
	cout << "\n" << index;
	//Need to set also the previous index. the retranslate ui reset the index (the problem is the auto-generated retranslateUi, on my code it uses setItemText and not languageBox->insertItems. Maybe there is some flag to set in QtDesigner?

}