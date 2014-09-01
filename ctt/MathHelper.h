#ifndef _MATHHELPER_H
#define _MATHHELPER_H

#include <QSize>

namespace helper {

template <class T>
static T ceilTo(T x, int n) {
    return (static_cast<int>(x + (n - 1)) / n) * n;
}

template <>
static QSize ceilTo(QSize x, int n) {
    return QSize(((x.width() + (n - 1)) / n) * n,
        ((x.height() + (n - 1)) / n) * n);
}

template <class T>
static T floorTo(T x, int n) {
    return (static_cast<int>(x) / n) * n;
}

template <>
static QSize floorTo(QSize x, int n) {
    return QSize(((x.width()) / n) * n,
        ((x.height()) / n) * n);
}

}  // namespace helper

#endif  // _GPU_HELPER