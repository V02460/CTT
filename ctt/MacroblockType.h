#if !defined(_MACROBLOCKTYPE_H)
#define _MACROBLOCKTYPE_H

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
	MB_TYPE_INTRA4x4,
	MB_TYPE_INTRA16x16,
	MB_TYPE_INTRA_PCM,
	MB_TYPE_16x16,
	MB_TYPE_16x8,
	MB_TYPE_8x16,
	MB_TYPE_8x8,
	MB_TYPE_INTERLACED,
	MB_TYPE_DIRECT2,
	MB_TYPE_ACPRED,
	MB_TYPE_GMC,
	MB_TYPE_SKIP,
	MB_TYPE_P0L0,
	MB_TYPE_P1L0,
	MB_TYPE_P0L1,
	MB_TYPE_P1L1,
	MB_TYPE_L0,
	MB_TYPE_L1,
	MB_TYPE_L0L1,
	MB_TYPE_QUANT,
	MB_TYPE_CBP
};

}  // namespace frame
}  // namespace model

#endif //_MACROBLOCKTYPE_H