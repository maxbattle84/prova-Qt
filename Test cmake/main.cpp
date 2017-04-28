// Qt
#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QDir>

#include <iostream>
#include <Somma2.h>
#include "XMLReader.h"

#include <cassert>

using namespace std;

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);

	XMLReader::loadFromFile();
	
	//QTranslator translator;
	//translator.load("english", "../x64/bin");
	//a.installTranslator(&translator);
	
	Somma2 *view = new Somma2();
	view->show();

	int result = a.exec();

	return result;

}
