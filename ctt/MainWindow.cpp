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
#include "FilteredVideo.h"

using ::controller::project::Project;
using ::controller::VideoListController;
using ::model::saveable::SaveableList;
using ::model::video::Video;
using ::controller::MainController;
using ::controller::project::SaveFileType;
using ::controller::operation::OperationList;
using ::model::video::YUVDataVideo;
using ::model::GlobalContext;
using ::model::filter::FilteredVideo;

namespace view {
	MainWindow::MainWindow() : abxTestingIsInitialized(false) {
		Project *project = Project::getInstance();

		analysingController = VideoListController::sptr(new VideoListController(project->getVideoList2()));

		ProcessingWidget *processingView = new ProcessingWidget(project->getPlayerList1(), project->getVideoList1(), project->getBaseVideoList(), project->getVideoList2(), analysingController, this);

		AnalysingWidget *analysingView = new AnalysingWidget(project->getVideoList2(), project->getPlayer2(), analysingController, project->getDiffList(), this);

		centralWidgetLayout = new QStackedLayout();
		centralWidgetLayout->setContentsMargins(0, 0, 0, 0);
		centralWidgetLayout->addWidget(processingView);
		centralWidgetLayout->addWidget(analysingView);

		ViewState::getInstance()->subscribe(this);
		OperationList::getInstance()->subscribe(this);

		mainController = MainController::sptr(new MainController());

		setupUi();
		setupDialog();

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
		loadProject->setEnabled(true);
		QObject::connect(loadProject, SIGNAL(triggered(bool)), this, SLOT(menuLoad()));
		QObject::connect(this, SIGNAL(loadProject(QString)), mainController.data(), SLOT(loadClicked(QString)));
		file->addAction(loadProject);

		file->addSeparator();

		QAction *saveProject = new QAction(tr("MENUENTRY_SAVE_PROJECT"), file);
		saveProject->setEnabled(true);
		QObject::connect(saveProject, SIGNAL(triggered(bool)), mainController.data(), SLOT(saveClicked()));

		file->addAction(saveProject);

		QAction *saveProjectAs = new QAction(tr("MENUENTRY_SAVE_PROJECT_AS"), file);
		saveProjectAs->setEnabled(true);
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

		resize(1600, 900);
		move(40, 40);

		update();
	}

	void MainWindow::update() {
		ViewType currentType = ViewState::getInstance()->getCurrentViewType();

		undo->setEnabled(OperationList::getInstance()->canUndo());

		redo->setEnabled(OperationList::getInstance()->canRedo());

		setWindowModified(false);

		if (currentType == ViewType::PROCESSING_VIEW) {
			centralWidgetLayout->setCurrentIndex(0);
			toProcessingView->setVisible(false);
			toAnalysingView->setVisible(true);
			toABXView->setVisible(true);
			setWindowTitle(tr("CODEC_TESTING_TOOLKIT") + "[*] - " + tr("PROCESSING_VIEW"));
		} else if (currentType == ViewType::ANALYSING_VIEW) {
			centralWidgetLayout->setCurrentIndex(1);
			toProcessingView->setVisible(true);
			toAnalysingView->setVisible(false);
			toABXView->setVisible(true);
			setWindowTitle(tr("CODEC_TESTING_TOOLKIT") + "[*] - " + tr("ANALYSING_VIEW"));
		} else if (currentType == ViewType::ABX_VIEW)
		{
			centralWidgetLayout->setCurrentIndex(2);
			toProcessingView->setVisible(true);
			toAnalysingView->setVisible(true);
			toABXView->setVisible(true);
			setWindowTitle(tr("CODEC_TESTING_TOOLKIT") + "[*] - " + tr("ABX_VIEW"));
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
			if (!path.endsWith(".ctt")) {
				path.append(".ctt");
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

	void MainWindow::menuToABX() {
		if (abxTestingIsInitialized) {
			int wantsReinitialize = QMessageBox::question(this, tr("REINITIALIZE_ABX_TESTING_TITLE"),
				tr("REINITIALIZE_ABX_TESTING_QUESTION"), QMessageBox::Yes | QMessageBox::No);
			if (wantsReinitialize == QMessageBox::Yes) {
				initializeABXTesting();
			}
		} else {
			initializeABXTesting();
		}

		if (abxTestingIsInitialized) {
			ViewState::getInstance()->changeView(ABX_VIEW);
		}
	}

	void MainWindow::initializeABXTesting() {
		if (startABXTesting->exec() == QDialog::Accepted) {
			FilteredVideo::sptr videoA = Project::getInstance()->getVideoList2()->get(videoSelection->getActiveIndices().at(0));
			FilteredVideo::sptr videoB = Project::getInstance()->getVideoList2()->get(videoSelection->getActiveIndices().at(1));

			if (abxTestingIsInitialized) {
				abxController->reset(videoA, videoB);
			} else {
				abxController = ABXController::sptr(new ABXController(videoA, videoB));
				ABXTestWidget *abxWidget = new ABXTestWidget(abxController, this);
				centralWidgetLayout->addWidget(abxWidget);
				abxTestingIsInitialized = true;
			}
		}
	} 

	void MainWindow::setupDialog() {
		startABXTesting = new QDialog(this, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

		QVBoxLayout *dialogLayout = new QVBoxLayout();

		videoSelection = ThumbnailListWidget::sptr(new ThumbnailListWidget(Project::getInstance()->getVideoList2(), 2, true, startABXTesting));
		videoSelection->subscribe(analysingController);
		QObject::connect(videoSelection.data(), SIGNAL(buttonActivated(int)), this, SLOT(videoActivated(int)));
		QObject::connect(videoSelection.data(), SIGNAL(buttonDeactivated(int)), this, SLOT(videoDeactivated(int)));
		dialogLayout->addWidget(videoSelection.data());

		QDialogButtonBox *dialogButtons = new QDialogButtonBox(QDialogButtonBox::Cancel, startABXTesting);
		dialogAcceptButton = dialogButtons->addButton(QDialogButtonBox::Ok);
		QObject::connect(dialogButtons, SIGNAL(accepted()), startABXTesting, SLOT(accept()));
		QObject::connect(dialogButtons, SIGNAL(rejected()), startABXTesting, SLOT(reject()));
		dialogAcceptButton->setEnabled(false);

		dialogLayout->addWidget(dialogButtons);

		startABXTesting->setLayout(dialogLayout);
	}

	void MainWindow::videoActivated(int id) {
		if (videoSelection->getActiveIndices().size() == 2) {
			dialogAcceptButton->setEnabled(true);
		}
	}

	void MainWindow::videoDeactivated(int id) {
		if (videoSelection->getActiveIndices().size() != 2) {
			dialogAcceptButton->setEnabled(false);
		}
	}

}  // namespace view