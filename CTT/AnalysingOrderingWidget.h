#ifndef _ANALYSINGORDERINGWIDGET_H
#define _ANALYSINGORDERINGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QDialogButtonBox>

#include "SaveableList.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "Observer.h"
#include "ThumbnailListWidget.h"

//#include "VideoAnalysingWidget.h"
namespace view {
	class VideoAnalysingWidget;
}  // namespace view 

namespace view {

class AnalysingOrderingWidget : public QWidget, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<AnalysingOrderingWidget> uptr;
    typedef QSharedPointer<AnalysingOrderingWidget> sptr;
    typedef QWeakPointer<AnalysingOrderingWidget> wptr;

    AnalysingOrderingWidget(::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
                            ::model::player::Player::sptr player,
                            ThumbnailListWidget::sptr thumbnails,
                            QWidget *parent = 0);

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
    QList<QSharedPointer<VideoAnalysingWidget>> analysingWidget;
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

}  // namespace view

#endif  //_ANALYSINGORDERINGWIDGET_H