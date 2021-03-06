#ifndef _VIDEOWIDGET_H
#define _VIDEOWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWindow>

#include "Observer.h"
#include "VideoScrubber.h"
#include "Surface.h"
#include "VertexAttribute.h"

namespace view {

/**
 * The VideoWidget is responsible for showing a concrete video frame.
 * Therefore it registers itself at a VideoScrubber and displays the frame provided by it.
 */
	class VideoWidget : public QWindow, public ::model::Observer {
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
	VideoWidget(::model::player::VideoScrubber::sptr scrubber, QWindow *parent = 0);

	~VideoWidget();

    /**
     * Returns the VideoScrubber at which the VideoWidget is registered and where the VideoWidget receives its frames
     * from.
     *
     * @return The VideoScrubber which holds the current frame.
     */
    const ::model::player::VideoScrubber::sptr getScrubber() const;

	virtual void resizeEvent(QResizeEvent *ev) Q_DECL_OVERRIDE;

	virtual void exposeEvent(QExposeEvent *ev) Q_DECL_OVERRIDE;

	virtual void update() Q_DECL_OVERRIDE;

private:
	void render();

	//void adjustViewportCoordinates();

    void getVertexPosition(::helper::VertexAttribute *attribute) const;

    ::model::player::VideoScrubber::sptr scrubber; /**< The scrubber at which the VideoWidget is registered */

	QSharedPointer<QOpenGLContext> context;
    QSharedPointer<QOpenGLShaderProgram> program;

	QRect viewportCoordinates;

    bool isInitialized;

    ::helper::VertexAttribute::sptr positionAttribute;
    ::helper::VertexAttribute::sptr texcrdAttribute;
};

}  // namespace view

#endif  //_VIDEOWIDGET_H
