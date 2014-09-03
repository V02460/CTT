#include "MainWindow.h"

#include <QMenu>
#include <QFileDialog>

#include "Project.h"
#include "ProcessingWidget.h"
#include "AnalysingWidget.h"
#include "VideoListController.h"
#include "ViewState.h"
#include "Video.h"
#include "SaveFileType.h"
#include "OperationList.h"
#include "ABXTestWidget.h"
#include "GlobalContext.h"
#include "YUVDataVideo.h"

using ::controller::project::Project;
using ::controller::VideoListController;
using ::model::saveable::SaveableList;
using ::model::video::Video;
using ::controller::MainController;
using ::controller::project::SaveFileType;
using ::controller::operation::OperationList;
using ::model::video::YUVDataVideo;
using  ::model::GlobalContext;

namespace view {
	MainWindow::MainWindow() {
		Project *project = Project::getInstance();

		VideoListController::sptr analysingListController = VideoListController::sptr(new VideoListController(project->getVideoList2()));

		ProcessingWidget *processingView = new ProcessingWidget(project->getPlayerList1(), project->getVideoList1(), project->getBaseVideoList(), analysingListController, this);

		AnalysingWidget *analysingView = new AnalysingWidget(project->getVideoList2(), project->getPlayer2(), analysingListController, project->getDiffList(), this);

		//TODO jztdiztd remove test stuff, add real support for abx
		YUVDataVideo::sptr testVideo(new YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, GlobalContext::get()));
		YUVDataVideo::sptr testVideo2(new YUVDataVideo("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, GlobalContext::get()));
		ABXController::sptr aBXController(new ABXController(testVideo, testVideo2));
		ABXTestWidget *aBXView = new ABXTestWidget(aBXController, this);

		centralWidgetLayout = new QStackedLayout();
		centralWidgetLayout->setContentsMargins(0, 0, 0, 0);
		centralWidgetLayout->addWidget(processingView);
		centralWidgetLayout->addWidget(analysingView);
		centralWidgetLayout->addWidget(aBXView);

		ViewState::getInstance()->subscribe(this);

		mainController = MainController::sptr(new MainController());

		setupUi();

		update();
	}

	MainWindow::~MainWindow() {
		ViewState::getInstance()->unsubscribe(this);
	}

	void MainWindow::setupUi() {
		QWidget *centralWidget = new QWidget(this);
		centralWidget->setLayout(centralWidgetLayout);

		menu = menuBar();

		QMenu *file = menu->addMenu(tr("MENU_FILE"));
		
		QAction *newProject = new QAction(tr("MENUENTRY_NEW_PROJECT"), file);
		QObject::connect(newProject, SIGNAL(triggered(bool)), mainController.data(), SLOT(newProject()));
		file->addAction(newProject);

		QAction *loadProject = new QAction(tr("MENUENTRY_LOAD_PROJECT"), file);
		loadProject->setEnabled(false);
		QObject::connect(loadProject, SIGNAL(triggered(bool)), this, SLOT(menuLoad()));
		QObject::connect(this, SIGNAL(loadProject(QString)), mainController.data(), SLOT(loadClicked(QString)));
		file->addAction(loadProject);

		file->addSeparator();

		QAction *saveProject = new QAction(tr("MENUENTRY_SAVE_PROJECT"), file);
		saveProject->setEnabled(false);
		QObject::connect(saveProject, SIGNAL(triggered(bool)), mainController.data(), SLOT(saveClicked()));

		file->addAction(saveProject);

		QAction *saveProjectAs = new QAction(tr("MENUENTRY_SAVE_PROJECT_AS"), file);
		saveProjectAs->setEnabled(false);
		QObject::connect(saveProjectAs, SIGNAL(triggered(bool)), this, SLOT(menuSave()));
		QObject::connect(mainController.data(), SIGNAL(requestSavePath()), this, SLOT(menuSave()));
		QObject::connect(this, SIGNAL(saveProjectAs(QString, ::controller::project::SaveFileType)), mainController.data(),
			SLOT(saveAsClicked(QString, ::controller::project::SaveFileType)));
		file->addAction(saveProjectAs);


		QMenu *edit = menu->addMenu(tr("MENU_EDIT"));

		undo = new QAction(tr("MENUENTRY_UNDO"), edit);
		undo->setEnabled(OperationList::getInstance()->canUndo());
		QObject::connect(undo, SIGNAL(triggered()), this, SLOT(menuUndo()));
		edit->addAction(undo);

		redo = new QAction(tr("MENUENTRY_REDO"), edit);
		redo->setEnabled(OperationList::getInstance()->canRedo());
		QObject::connect(redo, SIGNAL(triggered()), this, SLOT(menuRedo()));
		edit->addAction(redo);


		QMenu *view = menu->addMenu(tr("MENU_VIEW"));

		toProcessingView = new QAction(tr("MENUENTRY_TO_PROCESSING"), view);
		QObject::connect(toProcessingView, SIGNAL(triggered()), this, SLOT(menuToProcessing()));
		view->addAction(toProcessingView);

		toAnalysingView = new QAction(tr("MENUENTRY_TO_ANALYSING"), view);
		QObject::connect(toAnalysingView, SIGNAL(triggered()), this, SLOT(menuToAnalysing()));
		view->addAction(toAnalysingView);

		toABXView = new QAction(tr("MENUENTRY_TO_ABX"), view);
		QObject::connect(toABXView, SIGNAL(triggered()), this, SLOT(menuToABX()));
		view->addAction(toABXView);

		QMenu *help = menu->addMenu(tr("MENU_HELP"));

		QAction *about = new QAction(tr("MENUENTRY_ABOUT"), help);
		help->addAction(about);

		setCentralWidget(centralWidget);

		resize(1024, 768);
		move(40, 40);

		update();
	}

	void MainWindow::update() {
		ViewType currentType = ViewState::getInstance()->getCurrentViewType();

		undo->setEnabled(OperationList::getInstance()->canUndo());

		redo->setEnabled(OperationList::getInstance()->canRedo());

		if (currentType == ViewType::PROCESSING_VIEW) {
			centralWidgetLayout->setCurrentIndex(0);
			toProcessingView->setVisible(false);
			toAnalysingView->setVisible(true);
			toABXView->setVisible(true);
		} else if (currentType == ViewType::ANALYSING_VIEW) {
			centralWidgetLayout->setCurrentIndex(1);
			toProcessingView->setVisible(true);
			toAnalysingView->setVisible(false);
			toABXView->setVisible(true);
		}
		else if (currentType == ViewType::ABX_VIEW)
		{
			centralWidgetLayout->setCurrentIndex(2);
			toProcessingView->setVisible(true);
			toAnalysingView->setVisible(true);
			toABXView->setVisible(false);
		}
		
	}

	void MainWindow::menuToProcessing() {
		ViewState::getInstance()->changeView(ViewType::PROCESSING_VIEW);
	}

	void MainWindow::menuToAnalysing() {
		ViewState::getInstance()->changeView(ViewType::ANALYSING_VIEW);
	}

	void MainWindow::menuLoad() {
		QString path = QFileDialog::getOpenFileName(this, tr("LOAD_PROJECT"), "", tr("CTT_FILES *.ctt"));

		if (path != "") {
			emit loadProject(path);
		}
	}

	void MainWindow::menuSave() {
		QString path = QFileDialog::getSaveFileName(this, tr("SAVE_PROJECT"), "", tr("CTT_FILES *.ctt"));

		if (path != "") {
			if (!path.endsWith(".xml")) {
				path.append(".xml");
			}

			emit saveProjectAs(path, SaveFileType::XML);
		}
	}

	void MainWindow::menuUndo() {
		try {
			OperationList::getInstance()->undoOperation();
		} catch (IllegalArgumentException e) {
			//Ignoriere Excpetion und tue nichts
		}
	}

	void MainWindow::menuRedo() {
		try {
			OperationList::getInstance()->redoOperation();
		}
		catch (IllegalArgumentException e) {
			//Ignoriere Excpetion und tue nichts
		}
	}

	void MainWindow::menuToABX()
	{
		ViewState::getInstance()->changeView(ABX_VIEW);
	}

}  // namespace view