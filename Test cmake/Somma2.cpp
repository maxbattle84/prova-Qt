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
	qApp->installTranslator(mTranslator);

	//->setProperty("lang", lang);
	//qApp->processEvents();

	// Update the UI
	ui->retranslateUi(this);

	//qApp->removeTranslator(mTranslator);	//this->blockSignals(true);
	
}


void Somma2::on_languageBox_currentIndexChanged(int index)
{	
	int count = index;
	bool prova = false;
	if (count == 1)
	{
		ApplyTranslation("english");
		//qApp->blockSignals(true);
		//ui->retranslateUi(this);
	}


	/*if (count == 0)
	{
		ApplyTranslation("italiano");
		qApp->blockSignals(true);
		//ui->retranslateUi(this);
	}*/
	/*switch (count)
	{
	case 1:
		prova = true;
		cout << prova;
		ApplyTranslation("english");
		break;

	case 0:
		prova = false;
		cout << prova;
		ApplyTranslation("italiano");
		break;

	default:
		break;
	}*/
}

/*
case 0:
prova = false;
cout << prova;
if (translator->load("italiano", "../x64/bin"))
cout << "\n" << "italiano caricato";

//qApp->removeTranslator(&translator);
qApp->installTranslator(translator);
cout << "\n" << "italiano istallato";
break;
*/

/*
void Somma::on_bt_Somma_clicked() {

	int i1, i2;

	QString str1 = ui->te_Intero1->toPlainText();
	QString str2 = ui->te_Intero2->toPlainText();

	bool ok1;
	bool ok2;
	i1 = str1.toInt(&ok1);
	i2 = str2.toInt(&ok2);
	if (!ok1 || !ok2) { // not integers
		QMessageBox msgBox;
		msgBox.setText("Insert two integer");
		msgBox.exec();
	}
	else {
		int somma;
		somma = i1 + i2;
		QString str = QString::number(somma);
		ui->lb_Somma->setText(str);
	}
}
*/