// ========================================================================
//
// Copyright (C) 2017 Illogic 
//
// Module       : main
// Author       : aperetti
// Creation date: 2017-02-15
// Modified by  : $Author: aperetti $
// Last update  : $Date: 2017-02-15 16:09:40 +0200 (mer, 15 feb 2016) $
// Revision     : $Revision: 0 $
//
// @author aperetti
//
// ========================================================================


// Qt
#include <Somma.h>
#include <Somma.moc>
#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QDir>
#include <QtGui/qmessagebox.h>

#include <iostream>

#include <cassert>

using namespace std;

Somma::Somma(QWidget *parent) : QWidget(parent), ui(NULL)
{
	ui = new Ui::somma;
	ui->setupUi(this);
}

Somma::~Somma()
{
	delete ui;
}


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