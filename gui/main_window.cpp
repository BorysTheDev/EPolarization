#include "main_window.h"

MainWindow::MainWindow() {
	calcBtn = new QPushButton(this);
	connect(calcBtn, SIGNAL(clicked(bool)), SLOT(calculate()));
}

void MainWindow::calculate(){

}
