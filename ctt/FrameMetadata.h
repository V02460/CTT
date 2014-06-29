#if !defined(_FRAMEMETADATA_H)
#define _FRAMEMETADATA_H

#include <QSize>
#include <QVector>
#include <QVector2D>
#include "MacroblockType.h"
#include "MacroblockPartition.h"

/**
 * Holds metdadate information to be used in a Frame.
 * These include the size of the frame, motionvectors,  macroblock types and marcroblock partitions.
*/
class FrameMetadata {
public:
	/**
	 * Creates a container holding metadata information for a Frame.
	 *
	 * @param size Size of the frame in pixel
	 */
	explicit FrameMetadata(const QSize size);

	/**
	 * Creates a container holding metadata information for a Frame.
	 *
	 * @param size Size of the frame in pixel
	 * @param macroblockType Type identifier for every macroblock in the frame
	 * @param macroblockPartitions Macroblock partition information for every macroblock in the frame
	 * @param macroblockMotionvectors Motionvectors for every macroblock in the frame
	 */
	FrameMetadata(const QSize size,
				  const QVector<QVector<MacroblockType>> macroblockTypes,
				  const QVector<QVector<MacroblockPartition>> macroblockPartitions,
				  const QVector<QVector<QVector2D>> macroblockMotionvectors);

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
	 */
	QVector<QVector<MacroblockType>> getMbType() const;

	/**
	 * Get an array of the stored macroblock partition information.
	 *
	 * @return QVector<QVector<int>> [y][x]-Array of macroblock partition information.
	 */
	QVector<QVector<MacroblockPartition>> getMbPartitions() const;

	/**
	 * Get an array of the stored motionvectors.
	 *
	 * @return QVector<QVector<QVector2D>> [y][x]-Array of macroblock motionvectors.
	 */
	QVector<QVector<QVector2D>> getMbMotionvectors() const;

	/**
	 * Checks if macroblock type information is stored.
	 *
	 * @return bool True if macroblock type information is stored.
	 */
	bool hasMbType() const;

	/**
	 * Checks if partition type information is stored.
	 *
	 * @return bool True if partition type information is stored.
	*/
	bool hasMbPartions() const;

	/**
	 * Checks if motionvector information is stored.
	 *
	 * @return bool True if motionvector information is stored.
	 */
	bool hasMbMotionvectors() const;
private:
	const QSize size;
	const QVector<QVector<MacroblockType>> mbTypes;
	const QVector<QVector<MacroblockPartition>> mbPartions;
	const QVector<QVector<QVector2D>> mbMotionvectors;
};

#endif  //_FRAMEMETADATA_H
