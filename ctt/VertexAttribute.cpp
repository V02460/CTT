#include "VertexAttribute.h"

#include "NotImplementedException.h"

namespace helper {

using ::exception::NotImplementedException;

VertexAttribute::VertexAttribute() {
}

VertexAttribute::~VertexAttribute() {
}

void VertexAttribute::appendElement(float value) {
    throw new NotImplementedException();
}

void VertexAttribute::appendElement(QVector2D value) {
    throw new NotImplementedException();
}

void VertexAttribute::appendElement(QVector3D value) {
    throw new NotImplementedException();
}

}  // namespace helper