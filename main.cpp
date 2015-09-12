#include "MainWindow.h"
#include <QApplication>

#include <qdebug.h>

int main(int argc, char* argv[])
{
	try
	{
		QApplication a(argc, argv);

		MainWindow w;
		w.resize(350, 400);
		w.show();

		return a.exec();
	}
	catch (const std::exception& e)
	{
		qDebug() << e.what();
	}
	catch (...)
	{
		qDebug() << "Unhandled exception";
	}
}
