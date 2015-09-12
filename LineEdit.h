#ifndef _CUSTOMLINEEDIT_LINEEDIT_H_
#define _CUSTOMLINEEDIT_LINEEDIT_H_

#include <QLineEdit>
#include <QRegularExpression>

#include <memory>

QT_FORWARD_DECLARE_CLASS(QToolButton)

namespace sm
{

class LineEdit : public QLineEdit
{
	Q_OBJECT

	//
	// Public types.
	//
public:
	//! Controllers enumeration.
	enum class Ctrl : int
	{
		None,
		Exam,
		Pwd,
		ExamAndPwd
	};

	//
	// Public function.
	//
public:
	//! Default constructor.
	explicit LineEdit(QWidget* parent = Q_NULLPTR);
	//! Constructor.
	explicit LineEdit(const Ctrl aux, QWidget* parent = Q_NULLPTR);
	//! Constructor.
	explicit LineEdit(const Ctrl aux, const QString& pht, QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~LineEdit();
	//! Returns true if an input text mathes a regular expression.
	bool IsCorrect() const { return m_isCorrect; }
	//! Sets new regular expression for the examiner button.
	void SetRegExpr(const QString& re);

	//
	// Class's signals.
	//
Q_SIGNALS:
	//! Emits then an input data matches a regular expression.
	void CorrectInput(const bool);

	//
	// Reimplemented protected function.
	//
protected:
	void resizeEvent(QResizeEvent*) Q_DECL_OVERRIDE;

	//
	// Private function.
	//
private:
	//! Init line edit.
	void Init(const Ctrl aux, const QString& pht);
	//! Initializes examiner controller, which checks an input text.
	void InitExamCtrl(const int len);
	//! Initializes controller, which shows a password.
	void InitShowPwdCtrl(const int len);

	//
	// Private slots.
	//
private Q_SLOTS:
	//! Sets password echo mode.
	void OnHidePwd();
	//! Converts the password into readable format.
	void OnShowPwd();
	//! Checks the input text.
	void OnTextChanged(const QString& text);

	//
	// Private data members.
	//
private:
	//! Checks an input text for correct.
	QToolButton* m_exam;
	//! Shows password in plain format.
	QToolButton* m_showPwd;
	//! Regular expression for examiner button.
	std::unique_ptr<QRegularExpression> m_regExpr;
	//! Indicator for correctness input data.
	bool m_isCorrect;
};

} // namespace sm

#endif // _CUSTOMLINEEDIT_LINEEDIT_H_
