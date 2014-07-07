#ifndef _HUEHISTOGRAM_H
#define _HUEHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Histogram.h"
#include "Frame.h"

namespace model {
	namespace frame {
		namespace histogram {

			/**
			* A Histogram describing the distribution of the intensity of the hue channel in a frame.
			*/
			class HueHistogram : public Histogram {
			public:
				typedef QScopedPointer<HueHistogram> uptr;
				typedef QSharedPointer<HueHistogram> sptr;
				typedef QWeakPointer<HueHistogram> wptr;

				/**
				* Creates a new HueHistogram describing the distribution of the intensity of the hue channel of the submitted frame.
				* @param frame the HueHistogram will describe the distribution of the intensity of the hue channel of this frame
				*/
				HueHistogram(Frame frame);
			};

		}  // namespace histogram
	}  // namespace frame
}  // namespace model

#endif  //_HUEHISTOGRAM_H
