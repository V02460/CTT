#ifndef _PLAYERWIDGET_H
#define _PLAYERWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "VideoProcessingWidget.h"

namespace view {

/**
 * The PlayerWidget holds the VideoWidget displaying the original and the filtered video.
 * The main purpose of this class is to handle the activation of a specific player by the user.
 */
class PlayerWidget : public QWidget{
public:
    typedef QScopedPointer<PlayerWidget> uptr;
    typedef QSharedPointer<PlayerWidget> sptr;
    typedef QWeakPointer<PlayerWidget> wptr;

    /**
     * Creates a PlayerWidget.
     */
    PlayerWidget();

public slots:
    /**
     * Receives the activation signal form a button in the ThumbnailListWidget and notifies the ProcessingWidget
     * about the activation by emitting the playerActivated signal.
     */
    void getActivationSignal();

signals:
    /**
     * This signal is emitted as soon as this PlayerWidget gets activated.
     *
     * @param playerWidget The concrete playerWidget which was activated.
     */
    void playerActivated(const PlayerWidget &playerWidget);

private:
    Q_DISABLE_COPY(PlayerWidget);

    VideoProcessingWidget inputVideo; /**< The original video on which the filters are applied */
    VideoProcessingWidget filteredVideo;/**< The original video plus the applied filters */
};

}  // namespace view

#endif  //_PLAYERWIDGET_H
