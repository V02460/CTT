#include "MainWindow.h"

namespace view {

MainWindow::MainWindow(::controller::project::Project *project, ViewState::sptr currentState) {
	processingWidget = new ProcessingWidget(project);
	analysingWidget = new AnalysingWidget();

	viewState = currentState;
}

MainWindow::MainWindow() {

}

void MainWindow::update() {
	if (viewState->getCurrentViewType == ViewType::PROCESSING_VIEW) {
		this->setCentralWidget(processingWidget);
	}
	else {
		this->setCentralWidget(analysingWidget);
	}
}

void MainWindow::setupUi() {
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("MainWindow"));
	this->resize(viewState->getMainWindowSize());

	update();

	menu = new QMenuBar(this);
	menu->setObjectName(QStringLiteral("menubar"));
	menu->setGeometry(QRect(0, 0, 800, 21));
	this->setMenuBar(menu);

	retranslateUi();
}

void MainWindow::retranslateUi() {

}

void MainWindow::resizeEvent(QResizeEvent *ev) {
	viewState->setMainWindowSize(this->size());
}

}  // namespace view