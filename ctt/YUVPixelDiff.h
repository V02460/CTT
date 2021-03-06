#ifndef _YUVPIXELDIFF_H
#define _YUVPIXELDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AveragePixelDiff.h"
#include "Module.h"
#include "Memento.h"

namespace model {
namespace difference {

/**
 * Calculates the distances in the YUV-colorspace between frames for every pair of corresponding pixels, and is able to
 * normalize the resulting matrix if required.
 */
class YUVPixelDiff : public AveragePixelDiff {
public:
    typedef QScopedPointer<YUVPixelDiff> uptr;
    typedef QSharedPointer<YUVPixelDiff> sptr;
    typedef QWeakPointer<YUVPixelDiff> wptr;

    static const QByteArray kDiffID;

    /**
     * Creates a new YUVPixelDiff comparing the two submitted videos.
     *
     * @param video1 the first of the two videos which will be compared
     * @param video2 the second of the two videos which will be compared
     * @throws InvalidArgumentException if the submitted videos don't create their frames in the same OpenGLContext
     */
    YUVPixelDiff(::model::Module::sptr module1, ::model::Module::sptr module2);

    /**
     * Destroys the HSLPixelDiff.
     */
    virtual ~YUVPixelDiff();

    virtual Surface::sptr getPixelDiff(unsigned int frameNr) const Q_DECL_OVERRIDE;
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("FrameDiff", kDiffID); }

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    static Saveable::sptr getDummy();

	static Saveable::SaveableType getSaveableType() { return Saveable::yUVPixelDiff; }
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

protected:
    /**
     * Creates a dummy YUVPixelDiff.
     */
    YUVPixelDiff();
};

}  // namespace difference
}  // namespace model

#endif  //_YUVPIXELDIFF_H
