#ifndef _VIDEOWIDGET_H
#define _VIDEOWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWindow>

#include "Observer.h"
#include "VideoScrubber.h"
#include "Surface.h"

namespace view {

/**
 * The VideoWidget is responsible for showing a concrete video frame.
 * Therefore it registers itself at a VideoScrubber and diplays the frame provided by it.
 */
	class VideoWidget : public QWindow, public QOpenGLFunctions, ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<VideoWidget> uptr;
    typedef QSharedPointer<VideoWidget> sptr;
    typedef QWeakPointer<VideoWidget> wptr;

    /**
     * Creates a VideoWidget and registers itself at the corresponding VideoScrubber.
     *
	 * @param parent The parent component if this VideoWidget
     * @param scrubber The VideoScrubber to register at and which provided the video frames.
     */
    VideoWidget(QWindow *parent, ::model::player::VideoScrubber::sptr scrubber);

    /**
     * Returns the VideoScrubber at which the VideoWidget is registered and where the VideoWidget receives its frames
     * from.
     *
     * @return The VideoScrubber which holds the current frame.
     */
    const ::model::player::VideoScrubber &getScrubber() const;

	virtual void resizeEvent(QResizeEvent *ev) Q_DECL_OVERRIDE;

	virtual void update() Q_DECL_OVERRIDE;

private:
	void initialize();

	void render();

	void adjustViewportCoordinates();

    ::model::player::VideoScrubber::sptr scrubber; /**< The scrubber at which the VideoWidget is registered */

	QSharedPointer<QOpenGLContext> m_context;
	QSharedPointer<QOpenGLShaderProgram> m_program;

	bool isM_contextObsolete;
	QRect viewportCoordinates;
};

}  // namespace view

#endif  //_VIDEOWIDGET_H
