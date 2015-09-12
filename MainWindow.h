#ifndef _CUSTOMLINEEDIT_MAINWINDOW_H_
#define _CUSTOMLINEEDIT_MAINWINDOW_H_

#include <QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	//
	// Public function.
	//
public:
	//! Constructor.
	MainWindow(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~MainWindow();
};

#endif // _CUSTOMLINEEDIT_MAINWINDOW_H_
