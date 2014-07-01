#if !defined(_DIFFERENCEFACTORY_H)
#define _DIFFERENCEFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "FrameDiff.h"
#include "Video.h"
#include "PixelDiff.h"

namespace model {
namespace difference {

/**
 * Creates FrameDiffs and PixelDiffs and provides lists of identifiers of the types of FrameDiffs and PixelDiffs it can
 * create.
 *
 */
class DifferenceFactory {
public:
    typedef QScopedPointer<DifferenceFactory> uptr;
    typedef QSharedPointer<DifferenceFactory> sptr;
    typedef QWeakPointer<DifferenceFactory> wptr;

    /**
     * Gets a List of all identifiers of types of FrameDiffs the Factory can create.
     *
     * @return QList<QString> a List of all identifiers of types of FrameDiffs the Factory can create
     */
    static QList<QString> getAllFrameDiffIDs();

    /**
    * Gets a List of all identifiers of types of PixelDiffs the Factory can create.
    *
    * @return QList<QString> a List of all identifiers of types of PixelDiffs the Factory can create
    */
    static QList<QString> getAllPixelDiffIDs();

    /**
     * Creates and returns a FrameDiff of the type specified by the submitted id for the two submitted videos.
     *
     * @param id the id of the type of FrameDiff which is created
     * @param video1 the first of the two videos which the FrameDiff compares
     * @param video2 the second of the two videos which the FrameDiff compares
     * @return FrameDiff a FrameDiff of the type specified by the submitted id for the two submitted videos.
     * @throws InvalidArgumentException if the factory can't create a FrameDiff of the type specified by the submitted
     *     id
     * @throws InvalidArgumentException if the two submitted videos create their frames in different contexts
     */
    static FrameDiff::sptr createFrameDiff(QString id,
                                           ::model::video::Video::sptr video1,
                                           ::model::video::Video::sptr video2);

    /**
    * Creates and returns a PixelDiff of the type specified by the submitted id for the two submitted videos.
    *
    * @param id the id of the type of PixelDiff which is created
    * @param video1 the first of the two videos which the PixelDiff compares
    * @param video2 the second of the two videos which the PixelDiff compares
    * @return PixelDiff a PixelDiff of the type specified by the submitted id for the two submitted videos.
    * @throws InvalidArgumentException if the factory can't create a PixelDiff of the type specified by the submitted id
    * @throws InvalidArgumentException if the two submitted videos create their frames in different contexts
    */
    static PixelDiff::sptr createPixelDiff(QString id,
                                           ::model::video::Video::sptr video1,
                                           ::model::video::Video::sptr video2);

private:
    DifferenceFactory();
};

}  // namespace difference
}  // namespace model

#endif  //_DIFFERENCEFACTORY_H
