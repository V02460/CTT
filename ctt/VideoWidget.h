#if !defined(_VIDEOWIDGET_H)
#define _VIDEOWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "Observer.h"
#include "VideoScrubber.h"

namespace view {

/**
 * The VideoWidget is responsible for showing a concrete video frame.
 * Therefore it registers itself at a VideoScrubber and diplays the frame provided by it.
 */
class VideoWidget : public QWidget, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<VideoWidget> uptr;
    typedef QSharedPointer<VideoWidget> sptr;
    typedef QWeakPointer<VideoWidget> wptr;

    /**
     * Creates a VideoWidget and registeres itself at the corresponding VideoScrubber.
     *
     * @param scubber The VideoScrubber to register at and which provided the video frames.
     */
    VideoWidget(::model::player::VideoScrubber::sptr scrubber);

    /**
     * Returns the VideoScrubber at which the VideoWidget is registered and where the VideoWidget recieves its frames
     * from.
     *
     * @return The VideoScrubber which holds the current frame.
     */
    const ::model::player::VideoScrubber &getScrubber() const;

private:
    ::model::player::VideoScrubber::sptr scrubber; /**< The scrubber at which the VideoWidget is registered */
};

}  // namespace view

#endif  //_VIDEOWIDGET_H
