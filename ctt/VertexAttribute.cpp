#include "VertexAttribute.h"

#include "OpenGLException.h"
#include "IllegalStateException.h"

namespace helper {

using ::exception::OpenGLException;
using ::exception::IllegalStateException;

VertexAttribute::VertexAttribute(unsigned int vertexCount, unsigned int tupelSize)
        : QOpenGLBuffer(VertexBuffer)
        , tupelSize(tupelSize)
        , vertexCount(vertexCount)
        , entryCount(vertexCount * tupelSize)
        , writeActive(false){
    create();
    QOpenGLBuffer::bind();
    allocate(entryCount * sizeof(GLfloat));
}

VertexAttribute::~VertexAttribute() {
}

void VertexAttribute::reset(unsigned int vertexCount, unsigned int tupelSize) {
    if (vertexCount != getVertexCount() || tupelSize != getTupelSize()) {
        this->vertexCount = vertexCount;
        this->tupelSize = tupelSize;
        entryCount = vertexCount * tupelSize;

        QOpenGLBuffer::bind();
        allocate(entryCount * sizeof(GLfloat));
    }

    if (writeActive) {
        finishWrite();
    }
}

void VertexAttribute::bind() {
    if (writeActive) {
        throw IllegalStateException("Write must be finished before attribute can be bound. Wrong buffer size?");
    }

    QOpenGLBuffer::bind();
}

void VertexAttribute::appendElement(float value) {
    if (!writeActive) {
        startWrite();
    }
    if (bufferPointer + 1 > bufferEnd) {
        throw IllegalStateException("Write would cause buffer overflow.");
    }

    *bufferPointer++ = value;

    if (bufferPointer == bufferEnd) {
        finishWrite();
    }
}

void VertexAttribute::appendElement(QVector2D value) {
    if (!writeActive) {
        startWrite();
    }
    if (bufferPointer + 2 > bufferEnd) {
        throw IllegalStateException("Write would cause buffer overflow.");
    }

    *bufferPointer++ = value.x();
    *bufferPointer++ = value.y();

    if (bufferPointer == bufferEnd) {
        finishWrite();
    }
}

void VertexAttribute::appendElement(QVector3D value) {
    if (!writeActive) {
        startWrite();
    }
    if (bufferPointer + 3 > bufferEnd) {
        throw IllegalStateException("Write would cause buffer overflow.");
    }

    *bufferPointer++ = value.x();
    *bufferPointer++ = value.y();
    *bufferPointer++ = value.z();

    if (bufferPointer == bufferEnd) {
        finishWrite();
    }
}

void VertexAttribute::startWrite() {
    if (writeActive) {
        throw IllegalStateException("Already in write mode.");
    }

    QOpenGLBuffer::bind();
    bufferStart = reinterpret_cast<GLfloat*>(map(WriteOnly));
    if (bufferStart == nullptr) {
        throw OpenGLException("Could not map vertex attribute buffer.");
    }

    bufferPointer = bufferStart;
    bufferEnd = bufferStart + entryCount;

    writeActive = true;
}

void VertexAttribute::finishWrite() {
    if (!writeActive) {
        throw IllegalStateException("Already finished writing.");
    }

    QOpenGLBuffer::bind();
    unmap();

    writeActive = false;
}


unsigned int VertexAttribute::getTupelSize() const {
    return tupelSize;
}

unsigned int VertexAttribute::getVertexCount() const {
    return vertexCount;
}

GLenum VertexAttribute::getType() const {
    return GL_FLOAT;
}

VertexAttribute &operator<<(VertexAttribute &attribute, float value) {
    attribute.appendElement(value);
    return attribute;
}

VertexAttribute &operator<<(VertexAttribute &attribute, QVector2D &value) {
    attribute.appendElement(value);
    return attribute;
}

VertexAttribute &operator<<(VertexAttribute &attribute, QVector3D &value) {
    attribute.appendElement(value);
    return attribute;
}

}  // namespace helper