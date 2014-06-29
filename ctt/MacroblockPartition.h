#if !defined(_MACROBLOCKPARTITION_H)
#define _MACROBLOCKPARTITION_H

/**
* Partitioning of a macroblock
*/
enum MacroblockPartition {
	MB_PARTITION_16x16,
	MB_PARTITION_16x8,
	MB_PARTITION_8x16,
	MB_PARTITION_8x8
};

#endif //_MACROBLOCKPARTITION_H