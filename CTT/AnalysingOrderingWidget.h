#ifndef _ANALYSINGORDERINGWIDGET
#define _ANALYSINGORDERINGWIDGET

#include <QWidget>

#include "SaveableList.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "VideoScrubber.h"
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

	public slots:
		void videoActivated(int id);
		void videoReplaced(int oldId, int newId);
		void videoDeactivated(int id);

	private:
		::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
		QList<::model::player::VideoScrubber::sptr> scrubbers;
		::model::player::Player::sptr player;
		ThumbnailListWidget::sptr thumbnails;
	};
}

#endif