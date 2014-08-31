#ifndef _ANALYSINGORDERINGWIDGET
#define _ANALYSINGORDERINGWIDGET

#include <QWidget>
#include <QDialog>
#include <QPushButton>

#include "SaveableList.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "VideoAnalysingWidget.h"
#include "Observer.h"
#include "ThumbnailListWidget.h"

namespace view {
	class AnalysingOrderingWidget : public QWidget, public ::model::Observer {
	public:
		typedef QScopedPointer<AnalysingOrderingWidget> uptr;
		typedef QSharedPointer<AnalysingOrderingWidget> sptr;
		typedef QWeakPointer<AnalysingOrderingWidget> wptr;

		AnalysingOrderingWidget(::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
			::model::player::Player::sptr player, ThumbnailListWidget::sptr thumbnails, QWidget *parent = 0);

		virtual void update() Q_DECL_OVERRIDE;

		QList<::model::filter::FilteredVideo::sptr> getVideos(int selectableCount);

	public slots:
		void videoActivated(int id);
		void videoReplaced(int oldId, int newId);
		void videoDeactivated(int id);

		void dialogButtonToggled(bool checked, int id);

	private:
		void setupDialog();
		void setupUi();

		::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
		QList<VideoAnalysingWidget::sptr> analysingWidget;
		QList<ListedPushButton::sptr> dialogButtons;
		::model::player::Player::sptr player;
		ThumbnailListWidget::sptr thumbnails;

		QScopedPointer<QGridLayout> widgetLayout;

		QDialog *videoSelectionDialog;
		QPushButton *dialogAcceptButton;
		QDialogButtonBox *dialogButtonBox;
		QScopedPointer<QGridLayout> dialogLayout;
		QList<int> activeDialogButtonIds;
		int selectableDialogButtons;
	};
}

#endif