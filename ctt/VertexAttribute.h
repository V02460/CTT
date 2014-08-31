#ifndef _VERTEXATTRIBUTE_H
#define _VERTEXATTRIBUTE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QVector2D>
#include <QVector3D>

#include "QOpenGLBuffer"

namespace helper {

class VertexAttribute : private QOpenGLBuffer {
public:
    typedef QScopedPointer<VertexAttribute> uptr;
    typedef QSharedPointer<VertexAttribute> sptr;
    typedef QWeakPointer<VertexAttribute> wptr;

    VertexAttribute(unsigned int vertexCount, unsigned int tupelSize);
    ~VertexAttribute();

    void bind();

    unsigned int getTupelSize() const;
    unsigned int getVertexCount() const;

    /**
     * Returns the type of value stored in this buffer.
     *
     * @return currently always GL_FLOAT
     */
    GLenum getType() const;

    /**
     * Writes the given values at the next free available position in the buffer.
     * The buffer may not be used as long as it is not completely filled.
     * When writing to a filled buffer the buffer is reset, the value written. It must be filled again then.
     */
    friend VertexAttribute &operator<<(VertexAttribute &attribute, float value);
    friend VertexAttribute &operator<<(VertexAttribute &attribute, QVector2D &value);
    friend VertexAttribute &operator<<(VertexAttribute &attribute, QVector3D &value);

private:
    Q_DISABLE_COPY(VertexAttribute);

    void startWrite();
    void finishWrite();

    void appendElement(float value);
    void appendElement(QVector2D value);
    void appendElement(QVector3D value);

    GLfloat *bufferStart;
    GLfloat *bufferPointer;
    GLfloat *bufferEnd;

    unsigned int tupelSize;
    unsigned int vertexCount;
    unsigned int entryCount;

    bool writeActive;
};

}  // namespace helper

#endif