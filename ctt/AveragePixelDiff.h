#ifndef _AVERAGEPIXELDIFF_H
#define _AVERAGEPIXELDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "PixelDiff.h"
#include "Video.h"

namespace model {
namespace difference {

/**
* A PixelDiff where the frame diff can be calculated from the average pixel diff.
*/
class AveragePixelDiff : public PixelDiff {
public:
    typedef QScopedPointer<AveragePixelDiff> uptr;
    typedef QSharedPointer<AveragePixelDiff> sptr;
    typedef QWeakPointer<AveragePixelDiff> wptr;

    AveragePixelDiff(::model::Module::sptr module1, ::model::Module::sptr module2);
    ~AveragePixelDiff();
    
    virtual double getDiff(unsigned int frameNr) Q_DECL_OVERRIDE;
protected:
    /**
     * Creates a new dummy AveragePixelDiff.
     */
    AveragePixelDiff();

private:
	virtual void calculateFrameDiff(unsigned int frameNr) Q_DECL_OVERRIDE;
};

}  // namespace difference
}  // namespace model

#endif  //_AVERAGEPIXELDIFF_H