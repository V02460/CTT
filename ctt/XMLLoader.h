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
#include "InvertFilter.h"
#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"
#include "MotionVectorOverlay.h"
#include "RescaleFilter.h"
#include "RGBChannelFilter.h"
#include "TimeshiftFilter.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"
#include "ViewState.h"
#include "Observable.h"

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

	virtual void restore(QString path);

	/**
	 * Returns the one instance this class can have.
	 */
	static XMLLoader *getInstance();

private:
	Q_DISABLE_COPY(XMLLoader)

	XMLLoader();

	static XMLLoader::uptr instance;

	QXmlStreamReader *xml;

	QMap<int, ::model::saveable::Saveable::sptr> pointerMap;
	QMap<int, ::model::saveable::Memento> mementoMap;
	QMap<int, QMap<QString, int>> mementoIdMap;

	void readElements();
	void loadView();
	void readMemento(int id);
	void restore();

	QXmlStreamReader::TokenType type;
	QString string;
};

}  // namespace project
}  // namespace controller

#endif  //_XMLLOADER_H
