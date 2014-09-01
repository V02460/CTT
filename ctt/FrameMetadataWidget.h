#ifndef _FRAMEMETADATAWIDGET_H
#define _FRAMEMETADATAWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

#include "Observer.h"
#include "VideoScrubber.h"
#include "VideoMetadata.h"

namespace view {

/**
 * The FrameMetadataWidget displays the metadata information provided by a frame.
 * Therefore it registers itself at a VideoScrubber to receive the metadata for the current frame.
 */
class FrameMetadataWidget : public QWidget, public::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<FrameMetadataWidget> uptr;
    typedef QSharedPointer<FrameMetadataWidget> sptr;
    typedef QWeakPointer<FrameMetadataWidget> wptr;

    /**
     * Creates a new FrameMetadataWidget which holds a VideoScrubber from where it gets the metadata for the current
     * frame.
     *
     * @param scrubber The VideoScrubber to register at and which provides the metadata.
     */
	FrameMetadataWidget(::model::player::VideoScrubber::sptr scrubber, QWidget *parent = 0);

	/**
	 * Destroys the FrameMetadataWidget.
	 */
	~FrameMetadataWidget();

	virtual void update();

private:
	/** The scrubber at which the FrameMetadataWidget is registered. */
    ::model::player::VideoScrubber::sptr scrubber;
};

}  // namespace view

#endif  //_FRAMEMETADATAWIDGET_H
