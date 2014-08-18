#include "VideoWidget.h"

#include "NotImplementedException.h"
#include "ViewState.h"

namespace view {

using ::model::player::VideoScrubber;
using ::model::Observer;
using ::exception::NotImplementedException;

VideoWidget::VideoWidget(VideoScrubber::sptr scrubber, QWindow *parent) :QWindow(parent) {
	this->scrubber = scrubber;
	this->scrubber->subscribe(QSharedPointer<Observer>(this));
	isM_contextObsolete = true;

	setSurfaceType(QWindow::OpenGLSurface);

	adjustViewportCoordinates();

	isInSingelFrameTest = false;

	initialize();
}

VideoWidget::VideoWidget(model::frame::Frame *testFrame) {
	isM_contextObsolete = true;
	this->testFrame = testFrame;

	setSurfaceType(QWindow::OpenGLSurface);

	isInSingelFrameTest = true;

	//glViewport(0, 0, 400, 600);

	initialize();
}

const VideoScrubber &VideoWidget::getScrubber() const {
	return *this->scrubber.data();
}

void VideoWidget::resizeEvent(QResizeEvent *ev) {
	Q_UNUSED(ev);

	//adjustViewportCoordinates();

	if (isExposed()) {
		render();
	}
}

void VideoWidget::exposeEvent(QExposeEvent *ev) {
	Q_UNUSED(ev)

	if (isExposed()) {
		render();
	}
}

void VideoWidget::adjustViewportCoordinates() {
	QSize windowSize = QSize(width(), height());
	viewportCoordinates = ViewState::getInstance()->getCurrentVideoDisplayPolicy()->getViewportSize
		(windowSize, scrubber->getVideoMetadata().getSize());

	glViewport(viewportCoordinates.x(), viewportCoordinates.y(), viewportCoordinates.width(), viewportCoordinates.height());
}

void VideoWidget::update() {
	isM_contextObsolete = true;

	render();
}

void VideoWidget::initialize() {
	//m_program = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram(this));
	//m_program->link();
}

void VideoWidget::render() {
	bool needsInitialize = false;

	//TODO Frage: Muss bei jedem Frame ein neuer kontext erstellt werden?
	if (!m_context) {
		m_context = QSharedPointer<QOpenGLContext>(new QOpenGLContext(this));
		m_context->setFormat(requestedFormat());
		//TODO Für den Fall der Anpssung des Bildes auf die Komponentengröße muss hier die skalierte Textur benutzt werden
		//TODO Testverzweigung rausnehmen
		if (!isInSingelFrameTest) {
			m_context->setShareContext(scrubber->getCurrentFrame()->getContext().data());
		} else {
			m_context->setShareContext(testFrame->getContext().data());
			//testFrame->getContext()->setShareContext(m_context.data());
		}
		m_context->create();

		needsInitialize = true;
	}

	m_context->makeCurrent(this);

	if (needsInitialize) {
		initializeOpenGLFunctions();
		initialize();
	}

	//TODO Testverzweigung rausnehmen
	if (!isInSingelFrameTest) {
		adjustViewportCoordinates();
	}
	else {
		glViewport(0, 0, width(), height());
	}

	//glClearColor((float)0.0, 0.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//m_program->bind();
	

	//TODO Nicht sicher ob das notwendig ist
	//glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	m_context->swapBuffers(this);
}
}  // namespace view