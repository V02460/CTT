#if !defined(_FRAMEMETADATAWIDGET_H)
#define _FRAMEMETADATAWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "Observer.h"
#include "VideoScrubber.h"

namespace view {

/**
 * The FrameMetadataWidget displays the metadata information provided by a frame.
 * Therefore it registers itself at a VideoScrubber to recieve the metadata for the current frame.
 */
class FrameMetadataWidget : public ::model::Observer , public QWidget{
    Q_OBJECT
public:
    typedef QScopedPointer<FrameMetadataWidget> uptr;
    typedef QSharedPointer<FrameMetadataWidget> sptr;
    typedef QWeakPointer<FrameMetadataWidget> wptr;

    /**
     * Creates a new FrameMetadataWidget which holds a VideoScrubber from where it gets the metadata for the current
     * frame.
     *
     * @param scrubber The VideoScrubber to regiser at and which provides the metadata.
     */
    FrameMetadataWidget(::model::player::VideoScrubber::sptr scrubber);

private:
    ::model::player::VideoScrubber::sptr scrubber /**< The scrubber at which the FrameMetadataWidget is registered */;
};

}  // namespace view

#endif  //_FRAMEMETADATAWIDGET_H
