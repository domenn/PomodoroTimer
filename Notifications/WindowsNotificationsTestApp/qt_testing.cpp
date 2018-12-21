//
// Created by Domen on 20. 12. 2018.
//

#include <QApplication.h>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include "PomodoroTimerApp/utils/get_logger_function.h"

class DummyCommunicator : public QObject
{
	Q_OBJECT

public slots:
	void some_button()
	{
		LOG_INFO << "That BTN clicked.";
	}
};

QPushButton*  add_button(QWidget* const window, const QString & text, QVBoxLayout * const layout, DummyCommunicator * obj_thingy)
{
	QPushButton* new_button = new QPushButton(text, window);
	layout->addWidget(new_button);

	QObject::connect(new_button, &QPushButton::released, obj_thingy, &DummyCommunicator::some_button);

	return new_button;
}

int main(int argc, char **argv)
{
	setup_logger("windowsTestQtApp.log", plog::verbose);
	LOG_VERBOSE << "Windows testing app up and running.";

	DummyCommunicator shitter;

    QApplication app(argc, argv);

    QWidget window;

    QPushButton* quitButton = new QPushButton("Quit", &window);

    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout layout;
    window.setLayout(&layout);

	add_button(&window, "Some btn", &layout, &shitter);

    layout.addWidget(quitButton);

    window.show();
    return app.exec();
}

#include "qt_testing.moc"