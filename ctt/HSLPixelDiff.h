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

    virtual ::model::Surface::sptr getPixelDiff(unsigned int frameNr) const;
    virtual double getDiff(unsigned int frameNr) const;

    virtual ::model::saveable::Memento getMemento() const;
    virtual void restore(::model::saveable::Memento memento);
    static Saveable::sptr getDummy();

	virtual ::model::saveable::Saveable::SaveableType getType() const;

protected:
    /**
     * Creates a dummy PixelDiff.
     */
    HSLPixelDiff();
};

}  // namespace difference
}  // namespace model

#endif  //_HSLPIXELDIFF_H
