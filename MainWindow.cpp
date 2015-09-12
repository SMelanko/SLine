#include "MainWindow.h"
#include "LineEdit.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	QWidget* w(new QWidget(this));
	setCentralWidget(w);

	QVBoxLayout* mainLayout(new QVBoxLayout(w));
	mainLayout->setAlignment(Qt::AlignRight);

	sm::LineEdit* le(new sm::LineEdit(w));
	le->show();
	mainLayout->addWidget(le);

	sm::LineEdit* le1(
		new sm::LineEdit(sm::LineEdit::Ctrl::Exam, tr("Enter first name"), w));
	le1->SetRegExpr(QString("[a-z]"));
	le1->show();
	mainLayout->addWidget(le1);

	sm::LineEdit* le2(
		new sm::LineEdit(sm::LineEdit::Ctrl::Pwd, tr("Password"), w));
	le2->show();
	mainLayout->addWidget(le2);

	sm::LineEdit* le3(
		new sm::LineEdit(sm::LineEdit::Ctrl::ExamAndPwd, tr("Password"), w));
	le3->SetRegExpr(QString(""));
	le3->show();
	mainLayout->addWidget(le3);

	centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}
