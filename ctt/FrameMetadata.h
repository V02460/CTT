#ifndef _FRAMEMETADATA_H
#define _FRAMEMETADATA_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QSize>
#include <QVector>
#include <QVector2D>

#include "MacroblockType.h"

#include "IllegalStateException.h"

namespace model {
namespace frame {

/**
 * Holds metadata information to be used in a Frame.
 * These include the size of the frame, motion vectors,  macroblock types and macroblock partitions.
*/
class FrameMetadata {
public:
    typedef QScopedPointer<FrameMetadata> uptr;
    typedef QSharedPointer<FrameMetadata> sptr;
    typedef QWeakPointer<FrameMetadata> wptr;

    /**
     * Creates a container holding metadata information for a Frame.
     *
     * @param size Size of the frame in pixel
     */
    explicit FrameMetadata(QSize size);

    /**
     * Creates a container holding metadata information for a Frame.
     *
     * @param size Size of the frame in pixel
     * @param macroblockTypes Type identifier for every macroblock in the frame
     * @param macroblockMotionvectors Motion vectors for every macroblock in the frame
     */
    FrameMetadata(QSize size,
                  QVector<QVector<MacroblockType>> macroblockTypes,
                  QVector<QVector<QVector2D>> macroblockMotionvectors);

	/**
	* Creates a container holding metadata information for a Frame.
	*
	* @param size Size of the frame in pixel
	* @param macroblockTypes Type identifier for every macroblock in the frame
	*/
	FrameMetadata(QSize size,
		QVector<QVector<MacroblockType>> macroblockTypes);

    /**
     * Get the stored frame size.
     *
     * @return QSize Frame size in pixel
     */
    QSize getSize() const;

    /**
     * Get an array of the stored type identifiers for every macroblock.
     *
     * @return QVector<QVector<MacroblockType>> [y][x]-Array of macroblock type ids
     * @throws IllegalStateException if no macroblock type information was stored
     */
    QVector<QVector<MacroblockType>> getMbType() const;


    /**
     * Get an array of the stored motion vectors.
     *
     * @return QVector<QVector<QVector2D>> [y][x]-Array of macroblock motionvectors.
     * @throws IllegalStateException if no motion vector information was stored
     */
    QVector<QVector<QVector2D>> getMbMotionvectors() const;

    /**
     * Checks if macroblock type information is stored.
     *
     * @return bool True if macroblock type information is stored.
     */
    bool hasMbType() const;


    /**
     * Checks if motion vector information is stored.
     *
     * @return bool True if motion vector information is stored.
     */
    bool hasMbMotionvectors() const;
private:
    const QSize size;
    const QVector<QVector<MacroblockType>> mbTypes;
    const QVector<QVector<QVector2D>> mbMotionvectors;

    const bool hasMbTypeFlag;
    const bool hasMbMotionvectorsFlag;
};

}  // namespace frame
}  // namespace model

#endif  //_FRAMEMETADATA_H
