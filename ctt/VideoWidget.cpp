#include "VideoWidget.h"

#include <QOffscreenSurface>
#include "NotImplementedException.h"
#include "ViewState.h"
#include "OpenGLException.h"
#include "Frame.h"

namespace view {

using ::model::player::VideoScrubber;
using ::model::Observer;
using ::exception::NotImplementedException;
using ::exception::OpenGLException;
using ::model::frame::Frame;

VideoWidget::VideoWidget(VideoScrubber::sptr scrubber, QWindow *parent)
        :QWindow(parent)
        ,context(0)
        ,isInitialized(false) {

	if (!scrubber.isNull()) {
		this->scrubber = scrubber;
		this->scrubber->subscribe(QSharedPointer<Observer>(this));

		setSurfaceType(QWindow::OpenGLSurface);

		glViewport(0, 0, width(), height());
		isInSingelFrameTest = false;
	} else {
		qDebug() << "Error in VideoWidget! Scrubber was empty.";
	}
}

VideoWidget::VideoWidget(Frame::sptr testFrame, QWindow *parent) : QWindow(parent), context(0), isInitialized(false) {
	this->testFrame = testFrame;

	setSurfaceType(QWindow::OpenGLSurface);

	isInSingelFrameTest = true;
}

const VideoScrubber &VideoWidget::getScrubber() const {
	return *this->scrubber.data();
}

void VideoWidget::resizeEvent(QResizeEvent *ev) {
	Q_UNUSED(ev);

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

void VideoWidget::adjustViewportCoordinates() {
	QSize windowSize = QSize(width(), height());
	viewportCoordinates = ViewState::getInstance()->getCurrentVideoDisplayPolicy()->getViewportSize(windowSize, scrubber->getVideoMetadata().getSize());

	glViewport(viewportCoordinates.x(), viewportCoordinates.y(), viewportCoordinates.width(), viewportCoordinates.height());
}

void VideoWidget::update() {
	render();
}

void VideoWidget::initialize() {
    program.reset(new QOpenGLShaderProgram());

    if(!program->addShaderFromSourceCode(QOpenGLShader::Vertex, 
                                        "//precision highp float;\n"
                                        "attribute vec2 aPos;\n"
                                        "attribute vec2 aTexcrd;\n"
                                        "varying vec2 pos;\n"
                                        "varying vec2 texcrd;\n"
                                        "void main() {\n"
                                        "   pos = aPos;\n"
                                        "   texcrd = aTexcrd;\n"
                                        "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
                                        "}\n")) {
        throw new OpenGLException("Adding of vertex shader failed. Log message: " + program->log());
    }

    if(!program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        "//precision highp float;\n"
                                        "uniform sampler2D tex;\n"
                                        "varying vec2 texcrd;\n"
                                        "varying vec2 pos;\n"
                                        "void main() {\n"
                                        "   vec4 outColor = texture2D(tex, texcrd);\n"
                                        "   gl_FragColor = outColor;\n"
                                        "}\n")) {
        throw new OpenGLException("Adding of fragment shader failed. Log message: " + program->log());
    }

    if (!program->link()) {
        throw new OpenGLException("Linking of shader program failed. Log message: " + program->log());
    }

    isInitialized = true;
}

void VideoWidget::getVertexPosition(GLfloat *vertices) const {
    //TODO: Use DisplayPolicy

    QSize frameSize = testFrame.data()->getSize();

    // Fill screen while keeping aspect ratio
    float viewportAspect = (float)width() / height();
    float frameAspect = (float)frameSize.width() / frameSize.height();

    float yRatio = 1.f;
    float xRatio = 1.f;

    // Decide if size of frame is bound by x axis and set the ratio
    if (frameAspect > viewportAspect) {
        yRatio = viewportAspect / frameAspect;
    } else {
        xRatio = frameAspect / viewportAspect;
    }

    vertices[0] = vertices[4] = -xRatio;
    vertices[1] = vertices[3] = yRatio;
    vertices[2] = vertices[6] = xRatio;
    vertices[5] = vertices[7] = -yRatio;
}

void VideoWidget::render() {
	bool needsInitialize = false;

	if (!context) {
		context = QSharedPointer<QOpenGLContext>(new QOpenGLContext(this));
		context->setFormat(requestedFormat());

		//TODO Testverzweigung rausnehmen
		if (isInSingelFrameTest) {
            context->setShareContext(testFrame->getContext().data());
            //testFrame->getContext()->setShareContext(m_context.data());
		} else {
            //TODO: handle different contexts
            context->setShareContext(scrubber->getCurrentFrame()->getContext().data());
		}

        if (!context->create()) {
            throw new OpenGLException("OpenGL context creation failed.");
        }

		needsInitialize = true;
	}

	context->makeCurrent(this);

	if (needsInitialize) {
		initializeOpenGLFunctions();
		initialize();
	}

    glViewport(0, 0, width(), height());


    GLfloat vertices[8];
    getVertexPosition(vertices);

    GLfloat texcrd[8] = {
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        1.f, 0.f};

    program->enableAttributeArray("aPos");
    program->enableAttributeArray("aTexcrd");
    program->setAttributeArray("aPos", vertices, 2);
    program->setAttributeArray("aTexcrd", texcrd, 2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, testFrame->getTextureHandle());
    program->setUniformValue("tex", static_cast<GLuint>(0));

    program->bind();
	
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	context->swapBuffers(this);

    program->release();

    program->disableAttributeArray("aPos");
    program->disableAttributeArray("aTexcrd");
}

}  // namespace view