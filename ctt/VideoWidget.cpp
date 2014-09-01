#include "VideoWidget.h"

#include <QOffscreenSurface>

#include "NotImplementedException.h"
#include "ViewState.h"
#include "OpenGLException.h"
#include "Frame.h"
#include "GPUSurfacePainter.h"

namespace view {

using ::model::player::VideoScrubber;
using ::model::Observer;
using ::exception::NotImplementedException;
using ::exception::OpenGLException;
using ::model::frame::Frame;
using ::model::Surface;
using ::helper::GPUSurfacePainter;
using ::helper::VertexAttribute;

VideoWidget::VideoWidget(VideoScrubber::sptr scrubber, QWindow *parent)
        : QWindow(parent)
        , context(0)
        , isInitialized(false)
        , scrubber(scrubber)
        , positionAttribute(new VertexAttribute(4, 2))
        , texcrdAttribute(new VertexAttribute(4, 2)) {

	if (scrubber.isNull()) {
        throw new IllegalArgumentException("Error in VideoWidget! Scrubber was empty.");
    }

    setSurfaceType(QWindow::OpenGLSurface);
	this->scrubber->subscribe(this);
}

const VideoScrubber::sptr VideoWidget::getScrubber() const {
	return this->scrubber;
}

void VideoWidget::resizeEvent(QResizeEvent *ev) {
	Q_UNUSED(ev);

    if (isInitialized) {
        //glViewport(0, 0, width(), height());
    }

	if (isExposed()) {
		render();
	}
}

void VideoWidget::exposeEvent(QExposeEvent *ev) {
	Q_UNUSED(ev);

    if (isExposed()) {
        render();
    }
}

// void VideoWidget::adjustViewportCoordinates() {
// 	QSize windowSize = QSize(width(), height());
// 	viewportCoordinates = ViewState::getInstance()->getCurrentVideoDisplayPolicy()->getViewportSize(windowSize, scrubber->getVideoMetadata().getSize());
// 
// 	glViewport(viewportCoordinates.x(), viewportCoordinates.y(), viewportCoordinates.width(), viewportCoordinates.height());
// }

void VideoWidget::update() {
	render();
}

void VideoWidget::getVertexPosition(VertexAttribute *attribute) const {
    //TODO: Use DisplayPolicy

	QSize frameSize = scrubber->getCurrentFrame()->getSize();

    // Fill screen while keeping aspect ratio
    float viewportAspect = static_cast<float>(width()) / height();
    float frameAspect = static_cast<float>(frameSize.width()) / frameSize.height();

    float yRatio = 1.f;
    float xRatio = 1.f;

    // Decide if size of frame is bound by x axis and set the ratio
    if (frameAspect > viewportAspect) {
        yRatio = viewportAspect / frameAspect;
    } else {
        xRatio = frameAspect / viewportAspect;
    }

    *attribute << -xRatio <<  yRatio
               <<  xRatio <<  yRatio
               << -xRatio << -yRatio
               <<  xRatio << -yRatio;
}

void VideoWidget::render() {
	bool needsInitialize = false;

    // fetch from default context must be done before the VideoWidget context is made current
    Surface::sptr sourceFrame = scrubber->getCurrentFrame();

    // create the context if that did not happened
	if (!context) {
		context = QSharedPointer<QOpenGLContext>(new QOpenGLContext(this));
		context->setFormat(requestedFormat());

        //TODO: handle different contexts
        context->setShareContext(sourceFrame->getContext().data());

        if (!context->create()) {
            throw OpenGLException("OpenGL context creation failed.");
        }
	}

	context->makeCurrent(this);

    // set the new dimension of the viewport
    // TODO: move to rescale method
    glViewport(0, 0, width(), height());

    GPUSurfacePainter painter(":/Shader/VideoWidget/VideoWidget.vs",
                              ":/Shader/VideoWidget/VideoWidget.fs",
                              context);

    // set position of the quad
    getVertexPosition(positionAttribute.data());
    
    // set texture coordinates of the quad
    *texcrdAttribute << 0.f << 1.f
                     << 1.f << 1.f
                     << 0.f << 0.f
                     << 1.f << 0.f;

    // assign shader variables
    painter.setValue("aPos", positionAttribute);
    painter.setValue("aTexcrd", texcrdAttribute);
    painter.setValue("tex", sourceFrame);

    // fill the background
    painter.fill(QColor(0, 0, 0, 0));

    painter.run();

	context->swapBuffers(this);
}

}  // namespace view