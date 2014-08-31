#ifndef _HSLPIXELDIFF_H
#define _HSLPIXELDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

/**
 * Calculates the distances in the HSL color space between frames for every pair of corresponding pixels, and is able to
 * normalize the resulting matrix if required.
 */
class HSLPixelDiff : public PixelDiff {
public:
    typedef QScopedPointer<HSLPixelDiff> uptr;
    typedef QSharedPointer<HSLPixelDiff> sptr;
    typedef QWeakPointer<HSLPixelDiff> wptr;

    /**
     * Creates a new HSLPixelDiff comparing the two submitted videos.
     *
     * @param video1 the first of the two videos which will be compared
     * @param video2 the second of the two videos which will be compared
     * @throws InvalidArgumentException if the submitted videos don't create their frames in the same OpenGLContext
     */
    HSLPixelDiff(::model::video::Video::sptr video1, ::model::video::Video::sptr video2);

    /**
     * Destroys the HSLPixelDiff.
     */
    ~HSLPixelDiff();

	virtual Surface getPixelDiff(unsigned int frameNr) const Q_DECL_OVERRIDE;
	virtual double getDiff(unsigned int frameNr) const Q_DECL_OVERRIDE;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    static Saveable::sptr getDummy();
    static Saveable::SaveableType getSaveableType();
};

}  // namespace difference
}  // namespace model

#endif  //_HSLPIXELDIFF_H
