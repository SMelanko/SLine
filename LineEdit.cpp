#include "LineEdit.h"
#include <qtoolbutton.h>
#include <qstyle.h>

#include <qdebug.h>

namespace sm
{

LineEdit::LineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	Init(Ctrl::None, QString());
}

LineEdit::LineEdit(const Ctrl aux, QWidget* parent)
	: QLineEdit(parent)
{
	Init(aux, QString());
}

LineEdit::LineEdit(const Ctrl aux, const QString& pht, QWidget* parent)
	: QLineEdit(parent)
{
	Init(aux, pht);
}

LineEdit::~LineEdit()
{
}

void LineEdit::Init(const Ctrl aux, const QString& pht)
{
	m_exam = nullptr;
	m_showPwd = nullptr;
	m_regExpr = nullptr;
	m_isCorrect = false;

	const int minHeight = 38;
	setMinimumHeight(minHeight);

	if (!pht.isEmpty())
		setPlaceholderText(pht);

	if (aux == Ctrl::Exam || aux == Ctrl::ExamAndPwd)
	{
		InitExamCtrl(minHeight - 8);
	}

	if (aux == Ctrl::Pwd || aux == Ctrl::ExamAndPwd)
	{
		InitShowPwdCtrl(minHeight - 8);

		setEchoMode(EchoMode::Password);

		connect(m_showPwd, SIGNAL(released()), this, SLOT(OnHidePwd()));
		connect(m_showPwd, SIGNAL(pressed()), this, SLOT(OnShowPwd()));
	}

	connect(this, SIGNAL(textChanged(const QString&)),
			this, SLOT(OnTextChanged(const QString&)));
}

void LineEdit::InitExamCtrl(const int len)
{
	m_exam = new QToolButton(this);
	m_exam->setCursor(Qt::ArrowCursor);
	m_exam->setMinimumSize(len, len);
	m_exam->setIcon(QPixmap("://img/le_exam_fail.png"));
	m_exam->setStyleSheet(
		"QToolButton {"
			"border: 1px solid #FFFFFF;"
			"background-color: #FFFFFF;"
			"padding: 0px; }");
	m_exam->hide();
}

void LineEdit::InitShowPwdCtrl(const int len)
{
	m_showPwd = new QToolButton(this);
	m_showPwd->setCursor(Qt::ArrowCursor);
	m_showPwd->setFixedSize(len, len);
	m_showPwd->setStyleSheet(
		"QToolButton {"
			"border: 1px solid #FFFFFF;"
			"background-color: #FFFFFF;"
			"background-image: url(://img/le_pwd_original.png);"
			"background-position: center;"
			"background-repeat: no-repeat;"
			"padding: 0px; }"
		"QToolButton::hover {"
			"background-color: #D8D8D8; }"
		"QToolButton::pressed {"
			"background-color: #000000;"
			"background-image: url(://img/le_pwd_checked.png); }");
	m_showPwd->hide();
}

void LineEdit::OnHidePwd()
{
	if (m_showPwd)
		setEchoMode(EchoMode::Password);
}

void LineEdit::OnShowPwd()
{
	if (m_showPwd)
		setEchoMode(EchoMode::Normal);
}

void LineEdit::OnTextChanged(const QString& text)
{
	if (m_exam)
	{
		QIcon ico;

		if(!m_regExpr)
			throw std::runtime_error("Regular exception is missing");

		if (text.contains(*m_regExpr))
		{
			ico = QPixmap("://img/le_exam_ok.png");
			m_isCorrect = true;
		}
		else
		{
			ico = QPixmap("://img/le_exam_fail.png");
			m_isCorrect = false;
		}

		m_exam->setIcon(ico);
		m_exam->setVisible(!text.isEmpty());

		Q_EMIT CorrectInput(m_isCorrect);
	}

	if (m_showPwd)
		m_showPwd->setVisible(!text.isEmpty());
}

void LineEdit::resizeEvent(QResizeEvent *)
{
	int delta = 0;
	int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	int len = minimumSize().height() - 8;

	if (m_showPwd)
	{
		m_showPwd->move(
			rect().right() - frameWidth - len,
			(rect().bottom() + 1 - len) / 2);
		delta = 30;
	}

	if (m_exam)
	{
		m_exam->move(
			rect().right() - frameWidth - len - delta,
			(rect().bottom() + 1 - len) / 2);
	}
}

void LineEdit::SetRegExpr(const QString& re)
{
	if (m_exam)
		m_regExpr.reset(new QRegularExpression(re));
}

} // namespace sm
