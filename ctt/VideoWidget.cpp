#include "VideoWidget.h"

#include "NotImplementedException.h"
#include "ViewState.h"

namespace view {

using ::model::player::VideoScrubber;
using ::model::Observer;
using ::exception::NotImplementedException;

VideoWidget::VideoWidget(QWindow *parent, VideoScrubber::sptr scrubber):QWindow(parent) {
	this->scrubber = scrubber;
	this->scrubber->subscribe(QSharedPointer<Observer>(this));
	isM_contextObsolete = true;

	setSurfaceType(QWindow::OpenGLSurface);

	adjustViewportCoordinates();

	initialize();
}

const VideoScrubber &VideoWidget::getScrubber() const {
	return *this->scrubber.data();
}

void VideoWidget::resizeEvent(QResizeEvent *ev) {
	Q_UNUSED(ev);

	adjustViewportCoordinates();

	render();
}

void VideoWidget::adjustViewportCoordinates() {
	QSize windowSize = QSize(width(), height());
	viewportCoordinates = ViewState::getInstance()->getCurrentVideoDisplayPolicy()->getViewportSize
		(windowSize, scrubber->getVideoMetadata->getSize());

	glViewport(viewportCoordinates.x(), viewportCoordinates.y(), viewportCoordinates.width(), viewportCoordinates.height());
}

void VideoWidget::update() {
	isM_contextObsolete = true;

	render();
}

void VideoWidget::initialize() {
	/*m_program = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram(this));
	m_program->link();*/
}

void VideoWidget::render() {
	bool needsInitialize = false;

	//TODO Frage: Muss bei jedem Frame ein neuer kontext erstellt werden?
	if (isM_contextObsolete || !m_context) {
		m_context = QSharedPointer<QOpenGLContext>(new QOpenGLContext(this));
		m_context->setFormat(requestedFormat());
		//TODO Für den Fall der Anpssung des Bildes auf die Komponentengröße muss hier die skalierte Textur benutzt werden
		m_context->setShareContext(scrubber->getCurrentFrame()->getContext().data());
		m_context->create();

		needsInitialize = true;
	}

	m_context->makeCurrent(this);

	if (needsInitialize) {
		initializeOpenGLFunctions();
		initialize();
	}

	//TODO Nicht sicher ob das notwendig ist
	//glClear(GL_COLOR_BUFFER_BIT);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	m_context->swapBuffers(this);
}

}  // namespace view