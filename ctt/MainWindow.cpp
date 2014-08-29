#include "MainWindow.h"

#include <QMenu>

#include "Project.h"
#include "ProcessingWidget.h"
#include "AnalysingWidget.h"
#include "VideoListController.h"
#include "ViewState.h"
#include "Video.h"

using ::controller::project::Project;
using ::controller::VideoListController;
using ::model::saveable::SaveableList;
using ::model::video::Video;

namespace view {
	MainWindow::MainWindow() {
		Project *project = Project::getInstance();

		VideoListController::sptr analysingListController = VideoListController::sptr(new VideoListController(project->getVideoList2().dynamicCast<SaveableList<Video>>()));

		ProcessingWidget *processingView = new ProcessingWidget(project->getPlayerList1(), project->getVideoList1(), project->getBaseVideoList(), analysingListController, this);

		AnalysingWidget *analysingView = new AnalysingWidget(project->getVideoList2(), project->getPlayer2(), analysingListController, project->getDiffList(), this);

		centralWidgetLayout = new QStackedLayout();
		centralWidgetLayout->addWidget(processingView);
		centralWidgetLayout->addWidget(analysingView);

		ViewState::getInstance()->subscribe(this);

		setupUi();

		update();
	}

	void MainWindow::setupUi() {
		QWidget *centralWidget = new QWidget(this);
		centralWidget->setLayout(centralWidgetLayout);

		menu = menuBar();

		QMenu *file = menu->addMenu(tr("MENU_FILE"));
		
		QAction *newProject = new QAction(tr("MENUENTRY_NEW_PROJECT"), file);
		file->addAction(newProject);

		QAction *loadProject = new QAction(tr("MENUENTRY_LOAD_PROJECT"), file);
		file->addAction(loadProject);

		file->addSeparator();

		QAction *saveProject = new QAction(tr("MENUENTRY_SAVE_PROJECT"), file);
		file->addAction(saveProject);

		QAction *saveProjectAs = new QAction(tr("MENUENTRY_SAVE_PROJECT_AS"), file);
		file->addAction(saveProjectAs);


		QMenu *edit = menu->addMenu(tr("MENU_EDIT"));

		QAction *undo = new QAction(tr("MENUENTRY_UNDO"), edit);
		edit->addAction(undo);

		QAction *redo = new QAction(tr("MENUENTRY_REDO"), edit);
		edit->addAction(redo);


		QMenu *view = menu->addMenu(tr("MENU_VIEW"));

		toProcessingView = new QAction(tr("MENUENTRY_TO_PROCESSING"), view);
		QObject::connect(toProcessingView, SIGNAL(triggered()), this, SLOT(menuToProcessing()));
		view->addAction(toProcessingView);

		toAnalysingView = new QAction(tr("MENUENTRY_TO_ANALYSING"), view);
		QObject::connect(toAnalysingView, SIGNAL(triggered()), this, SLOT(menuToAnalysing()));
		view->addAction(toAnalysingView);


		QMenu *help = menu->addMenu(tr("MENU_HELP"));

		QAction *about = new QAction(tr("MENUENTRY_ABOUT"), help);
		help->addAction(about);

		setCentralWidget(centralWidget);

		resize(800, 600);

		update();
	}

	void MainWindow::update() {
		ViewType currentType = ViewState::getInstance()->getCurrentViewType();

		if (currentType == ViewType::PROCESSING_VIEW) {
			centralWidgetLayout->setCurrentIndex(0);
			toProcessingView->setVisible(false);
			toAnalysingView->setVisible(true);
		} else if (currentType == ViewType::ANALYSING_VIEW) {
			centralWidgetLayout->setCurrentIndex(1);
			toProcessingView->setVisible(true);
			toAnalysingView->setVisible(false);
		}
		
	}

	void MainWindow::menuToProcessing() {
		ViewState::getInstance()->changeView(ViewType::PROCESSING_VIEW);
	}

	void MainWindow::menuToAnalysing() {
		ViewState::getInstance()->changeView(ViewType::ANALYSING_VIEW);
	}
}  // namespace view