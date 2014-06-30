#if !defined(_HISTOGRAMTYPE_H)
#define _HISTOGRAMTYPE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace frame {
namespace histogram {

/**
 * Labels for the channels histograms describe the intensity distribution of.
 *
 */
enum HistogramType {
	Red,
	Green,
	Blue,
	Luminance,
	Hue,
	Saturation
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_HISTOGRAMTYPE_H
