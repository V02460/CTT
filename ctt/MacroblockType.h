#ifndef _MACROBLOCKTYPE_H
#define _MACROBLOCKTYPE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace frame {

// FFmpeg definitions
//
//#define 	MB_TYPE_INTRA4x4   0x0001
//#define 	MB_TYPE_INTRA16x16   0x0002
//#define 	MB_TYPE_INTRA_PCM   0x0004
//#define 	MB_TYPE_16x16   0x0008
//#define 	MB_TYPE_16x8   0x0010
//#define 	MB_TYPE_8x16   0x0020
//#define 	MB_TYPE_8x8   0x0040
//#define 	MB_TYPE_INTERLACED   0x0080
//#define 	MB_TYPE_DIRECT2   0x0100
//#define 	MB_TYPE_ACPRED   0x0200
//#define 	MB_TYPE_GMC   0x0400
//#define 	MB_TYPE_SKIP   0x0800
//#define 	MB_TYPE_P0L0   0x1000
//#define 	MB_TYPE_P1L0   0x2000
//#define 	MB_TYPE_P0L1   0x4000
//#define 	MB_TYPE_P1L1   0x8000
//#define 	MB_TYPE_L0   (MB_TYPE_P0L0 | MB_TYPE_P1L0)
//#define 	MB_TYPE_L1   (MB_TYPE_P0L1 | MB_TYPE_P1L1)
//#define 	MB_TYPE_L0L1   (MB_TYPE_L0 | MB_TYPE_L1)
//#define 	MB_TYPE_QUANT   0x00010000
//#define 	MB_TYPE_CBP   0x00020000

/**
 * Type of macroblocks which can occur in a Frame.
 */
enum MacroblockType{
	INTER_SKIP,
	INTER_16X16,
	INTER_16X8,
	INTER_8X16,
	INTER_8X8,
	INTER_8X4,
	INTER_4X8,
	INTER_4X4,
	INTER_8X8_OR_BELOW,
	INTRA_4X4,
	INTRA_16X16,
	INTRA_8X8,
	INTRA_PCM,
	UNKNOWN
};

}  // namespace frame
}  // namespace model

#endif //_MACROBLOCKTYPE_H