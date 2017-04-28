#include <iostream>
#include <QtXml/QDomDocument>
#include <QtXml\qxmlstream.h>
#include <QtCore\qfile.h>
#include <QtCore\qstring.h>
//#include <QtCore\qdiriterator.h>
//#include <QtCore\qcoreapplication.h>
#include <XMLReader.h>

using namespace std;

XMLReader::XMLReader() {

}

XMLReader::~XMLReader() {

}

void XMLReader::loadFromFile()
{
	QFile file("../bintree.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		cout << (qPrintable("Error reading the file " + file.fileName()));
		return;
	}
	else
		cout << (qPrintable("YEP ")) << "\n";

	QDomDocument doc;
	{
		QString errorStr;
		int errorLine;
		int errorColumn;

		if (!doc.setContent(&file, false, &errorStr, &errorLine,
			&errorColumn)) {
			std::cerr << "Error: Parse error at line " << errorLine << ", "
				<< "column " << errorColumn << ": "
				<< qPrintable(errorStr) << std::endl;
			return;
		}
	}

	QDomElement root = doc.documentElement();
	cout << (qPrintable(root.tagName()));

	QDomAttr a = root.attributeNode("xmlns:xsi");
	cout << " " << (qPrintable(a.value()));

	cout << "\n" << root.attributes().count();

	cout << "\n" << (qPrintable(root.attributes().item(2).nodeName()));
	cout << "\n" << (qPrintable(root.attributes().item(2).nodeValue()));


	// Get the first child of the root (Markup COMPONENT is expected)
	QDomElement Component = root.firstChild().toElement();
	cout << "\n" << (qPrintable(Component.tagName()));



/*
	// Loop while there is a child
	while (!Component.isNull())
	{
		// Check if the child tag name is COMPONENT
		if (Component.tagName() == "COMPONENT")
		{

			// Read and display the component ID
			QString ID = Component.attribute("ID", "No ID");

			// Get the first child of the component
			QDomElement Child = Component.firstChild().toElement();

			QString Name;
			double Value;

			// Read each child of the component node
			while (!Child.isNull())
			{
				// Read Name and value
				if (Child.tagName() == "NAME") Name = Child.firstChild().toText().data();
				if (Child.tagName() == "VALUE") Value = Child.firstChild().toText().data().toDouble();

				// Next child
				Child = Child.nextSibling().toElement();
			}

			// Display component data
			std::cout << "Component " << ID.toStdString().c_str() << std::endl;
			std::cout << "   Name  = " << Name.toStdString().c_str() << std::endl;
			std::cout << "   Value = " << Value << std::endl;
			std::cout << std::endl;
		}

		// Next component
		Component = Component.nextSibling().toElement();
	}
	*/
	/*for (int i = 0; i < root.attributes().count(); i++)
	//for (QString key : root.attributes())
	{
		QString key = root.attributes().item(i).toElement().text();
		cout << qPrintable(key);
	}*/
	/*
	QDomNamedNodeMap map = root.attributes();
	cout << "Attributes found: " << qPrintable(map.length());

	QDomAttr attr = root.toAttr();
	cout << qPrintable("Name: ") << qPrintable(attr.name());
	cout << qPrintable("Value: ") << qPrintable(attr.value());
	*/
	
}
