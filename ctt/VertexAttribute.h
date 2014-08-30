#ifndef _VERTEXATTRIBUTE_H
#define _VERTEXATTRIBUTE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QVector2D>
#include <QVector3D>

namespace helper {

class VertexAttribute {
public:
    typedef QScopedPointer<VertexAttribute> uptr;
    typedef QSharedPointer<VertexAttribute> sptr;
    typedef QWeakPointer<VertexAttribute> wptr;

    VertexAttribute();
    ~VertexAttribute();

    void appendElement(float value);
    void appendElement(QVector2D value);
    void appendElement(QVector3D value);
};

}  // namespace helper

#endif