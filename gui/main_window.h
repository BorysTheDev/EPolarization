#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QWidget>
#include <QPushButton>

class MainWindow: public QWidget {
Q_OBJECT
public:
	MainWindow();
private:
	QPushButton *calcBtn;

public slots:
	void calculate();
};

#endif /* MAIN_WINDOW_H_ */
