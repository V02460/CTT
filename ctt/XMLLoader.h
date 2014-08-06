#ifndef _XMLLOADER_H
#define _XMLLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDomDocument>
#include <QXmlStreamReader>

#include "ProjectLoader.h"
#include "IOException.h"
#include "ParseException.h"
#include "NotImplementedException.h"
#include "Saveable.h"
#include "XMLSaver.h"

#include "EarthMoversHistogramDiff.h"
#include "HSLPixelDiff.h"
#include "YUVPixelDiff.h"
#include "BlurFilter.h"
#include "CoffeeFilter.h"
#include "GreyscaleFilter.h"
#include "MixFilter.h"
#include "NoiseFilter.h"
#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"
#include "MacropartitionOverlay.h"
#include "MotionVectorOverlay.h"
#include "RescaleFilter.h"
#include "RGBChannelFilter.h"
#include "TimeshiftFilter.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"
#include "ViewState.h"

namespace controller {
namespace project {

/**
 * Loads a project saved as XML file by the XMLSaver.
 */
class XMLLoader : public ProjectLoader {

public:
    typedef QScopedPointer<XMLLoader> uptr;
    typedef QSharedPointer<XMLLoader> sptr;
    typedef QWeakPointer<XMLLoader> wptr;

	/**
	 * Creates a new XMLLoader.
	 */
	XMLLoader();

	virtual void restore(QDir path, ::controller::project::Project project);

private:
	QXmlStreamReader *xml;

	QMap<int, ::model::saveable::Saveable::sptr> pointerMap;

	void openFile(QDir path);
	void createMaps(Project project);
	void restore();
};

}  // namespace project
}  // namespace controller

#endif  //_XMLLOADER_H
