#if !defined(_MACROBLOCKPARTITION_H)
#define _MACROBLOCKPARTITION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace frame {

/**
* Partitioning of a macroblock
*/
enum MacroblockPartition {
	MB_PARTITION_16x16,
	MB_PARTITION_16x8,
	MB_PARTITION_8x16,
	MB_PARTITION_8x8
};

}  // namespace frame
}  // namespace model

#endif //_MACROBLOCKPARTITION_H