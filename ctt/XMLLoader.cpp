#include "XMLLoader.h"

#include "IOException.h"
#include "ParseException.h"

namespace controller {
namespace project {

using ::exception::IOException;
using ::exception::ParseException;
using ::exception::IllegalStateException;
using ::controller::project::XMLSaver;
using ::controller::project::Project;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

using ::model::FilterIntervalList;
using ::model::difference::EarthMoversHistogramDiff;
using ::model::difference::HSLPixelDiff;
using ::model::difference::YUVPixelDiff;
using ::model::filter::BlurFilter;
using ::model::filter::CoffeeFilter;
using ::model::filter::GreyscaleFilter;
using ::model::filter::MixFilter;
using ::model::filter::NoiseFilter;
using ::model::filter::InvertFilter;
using ::model::filter::overlay::HeatmapOverlay;
using ::model::filter::overlay::MacroblockOverlay;
using ::model::filter::overlay::MotionVectorOverlay;
using ::model::filter::RescaleFilter;
using ::model::filter::RGBChannelFilter;
using ::model::filter::TimeshiftFilter;
using ::model::video::FFmpegDataVideo;
using ::model::video::YUVDataVideo;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::UIntegerInterval;
using ::model::player::VideoScrubber;
using ::view::ViewState;
using ::model::saveable::SaveableList;
using ::view::ViewType;
using ::model::difference::FrameDiff;
using ::model::difference::PixelDiff;
using ::model::Module;
using ::model::filter::Filter;
using ::model::filter::overlay::Overlay;
using ::model::filter::overlay::ColoringOverlay;
using ::model::video::Video;
using ::model::video::FileVideo;

XMLLoader::XMLLoader() {}

void XMLLoader::restore(QString path) {
	pointerMap.clear();
	mementoIdMap.clear();
	mementoMap.clear();
	QFile *file = new QFile(path);
	if (!file->open(QIODevice::ReadOnly)) {
		throw IOException("File " + path + " could not be opened.");
	}
	xml = new QXmlStreamReader(file);
	while (!xml->atEnd() && !xml->hasError()) {
		if (xml->readNext() != QXmlStreamReader::StartElement) {
			continue;
		}
		if (xml->name() == XMLSaver::PROJECT) {
			readElements();
		} else {
			throw ParseException("Found unknown tag <" + xml->name().toString() + ">");
		}
	}
	if (xml->hasError()) {
		throw ParseException(xml->errorString());
	}
	file->close();
	restore();
}

void XMLLoader::readElements() {
	if (xml->tokenType() != QXmlStreamReader::StartElement || xml->name() != XMLSaver::PROJECT) {
		throw IllegalStateException("Wrong call of readElements().");
	}
	Project *project = Project::getInstance();
	while ((xml->readNext() != QXmlStreamReader::EndElement || xml->name() != XMLSaver::PROJECT) && !xml->hasError()) {
		if (xml->tokenType() != QXmlStreamReader::StartElement) {
			continue;
		}
		if (xml->name() == XMLSaver::VIEW) {
			loadView();
			continue;
		}
		if (xml->name() != XMLSaver::ELEMENT) {
			throw ParseException("Tag <" + XMLSaver::ELEMENT + "> expected.");
		}
		QXmlStreamAttributes attributes = xml->attributes();
		if (!attributes.hasAttribute(XMLSaver::ID)) {
			throw ParseException("Attribute " + XMLSaver::ID + " expected.");
		}
		bool valid = false;
		int id = attributes.value(XMLSaver::ID).toInt(&valid);
		if (!valid) {
			throw ParseException(attributes.value(XMLSaver::ID).toString()
				+ "is not a valid ID. IDs must be integer.");
		}
		if (pointerMap.contains(id)) {
			throw ParseException("Multiple elements with key " + QString::number(id) + " exist.");
		}
		if (attributes.hasAttribute(XMLSaver::TYPE)) {
			XMLSaver::BaseSaveableType baseType =
				XMLSaver::stringToBaseSaveableType(attributes.value(XMLSaver::TYPE).toString());
			switch (baseType) {
			case XMLSaver::BaseSaveableType::BaseVideoList:
				pointerMap.insert(id, project->getBaseVideoList()); break;
			case XMLSaver::BaseSaveableType::VideoList1:
				pointerMap.insert(id, project->getVideoList1()); break;
			case XMLSaver::BaseSaveableType::VideoList2:
				pointerMap.insert(id, project->getVideoList2()); break;
			case XMLSaver::BaseSaveableType::PlayerList1:
				pointerMap.insert(id, project->getPlayerList1()); break;
			case XMLSaver::BaseSaveableType::Player2:
				pointerMap.insert(id, project->getPlayer2()); break;
			case XMLSaver::BaseSaveableType::DiffList:
				pointerMap.insert(id, project->getDiffList()); break;
			default: throw IllegalArgumentException("Unknown base savable type."); break;
			}
		} else {
			if (!attributes.hasAttribute(XMLSaver::CLASS)) {
				throw ParseException("Attribute " + XMLSaver::CLASS + " expected.");
			}
			Saveable::SaveableType saveableType =
				Saveable::stringToSaveableType(attributes.value(XMLSaver::CLASS).toString());
			Saveable::sptr dummy;
			switch (saveableType) {
			default:
				throw ParseException(attributes.value(XMLSaver::CLASS).toString()
					+ " can not be instantiated.");
				break;
			case Saveable::SaveableType::filterIntervalList: dummy = FilterIntervalList::getDummy(); break;
			case Saveable::SaveableType::earthMoversHistogramDiff: dummy = EarthMoversHistogramDiff::getDummy(); break;
			case Saveable::SaveableType::hSLPixelDiff: dummy = HSLPixelDiff::getDummy(); break;
			case Saveable::SaveableType::yUVPixelDiff: dummy = YUVPixelDiff::getDummy(); break;
			case Saveable::SaveableType::blurFilter: dummy = BlurFilter::getDummy(); break;
			case Saveable::SaveableType::coffeeFilter: dummy = CoffeeFilter::getDummy(); break;
			case Saveable::SaveableType::greyscaleFilter: dummy = GreyscaleFilter::getDummy(); break;
			case Saveable::SaveableType::mixFilter: dummy = MixFilter::getDummy(); break;
			case Saveable::SaveableType::noiseFilter: dummy = NoiseFilter::getDummy(); break;
			case Saveable::SaveableType::invertFilter: dummy = InvertFilter::getDummy(); break;
			case Saveable::SaveableType::heatmapOverlay: dummy = HeatmapOverlay::getDummy(); break;
            case Saveable::SaveableType::heatmapOverlay_heatmap: dummy = HeatmapOverlay::Heatmap::getDummy(); break;
			case Saveable::SaveableType::macroblockOverlay: dummy = MacroblockOverlay::getDummy(); break;
			case Saveable::SaveableType::motionVektorOverlay: dummy = MotionVectorOverlay::getDummy(); break;
			case Saveable::SaveableType::macroblockOverlay_macroblocks: dummy = MacroblockOverlay::Macroblocks::getDummy(); break;
			case Saveable::SaveableType::rescaleFilter: dummy = RescaleFilter::getDummy(); break;
			case Saveable::SaveableType::rGBChannelFilter: dummy = RGBChannelFilter::getDummy(); break;
			case Saveable::SaveableType::timeshiftFilter: dummy = TimeshiftFilter::getDummy(); break;
			case Saveable::SaveableType::fFmpegDataVideo: dummy = FFmpegDataVideo::getDummy(); break;
			case Saveable::SaveableType::yUVDataVideo: dummy = YUVDataVideo::getDummy(); break;
			case Saveable::SaveableType::filteredVideo: dummy = FilteredVideo::getDummy(); break;
			case Saveable::SaveableType::player: dummy = Player::getDummy(); break;
			case Saveable::SaveableType::uIntegerInterval: dummy = UIntegerInterval::getDummy(); break;
			case Saveable::SaveableType::videoScrubber: dummy = VideoScrubber::getDummy(); break;
			case Saveable::SaveableType::saveableList:
				if (!attributes.hasAttribute(XMLSaver::TEMPLATE_TYPE)) {
					throw ParseException("Attribute " + XMLSaver::TEMPLATE_TYPE + " expected.");
				}
				Saveable::SaveableType templateType =
					Saveable::stringToSaveableType(attributes.value(XMLSaver::CLASS).toString());
				switch (templateType) {
				case Saveable::SaveableType::saveable: dummy = SaveableList<Saveable>::getDummy(); break;
//				case Saveable::SaveableType::filterIntervalList: dummy = SaveableList<FilterIntervalList>::getDummy(); break;
				case Saveable::SaveableType::frameDiff: dummy = SaveableList<FrameDiff>::getDummy(); break;
//				case Saveable::SaveableType::earthMoversHistogramDiff: dummy = SaveableList<EarthMoversHistogramDiff>::getDummy(); break;
//				case Saveable::SaveableType::pixelDiff: dummy = SaveableList<PixelDiff>::getDummy(); break;
//				case Saveable::SaveableType::hSLPixelDiff: dummy = SaveableList<HSLPixelDiff>::getDummy(); break;
//				case Saveable::SaveableType::yUVPixelDiff: dummy = SaveableList<YUVPixelDiff>::getDummy(); break;
//				case Saveable::SaveableType::module: dummy = SaveableList<Module>::getDummy(); break;
//				case Saveable::SaveableType::filter: dummy = SaveableList<Filter>::getDummy(); break;
//				case Saveable::SaveableType::blurFilter: dummy = SaveableList<BlurFilter>::getDummy(); break;
//				case Saveable::SaveableType::coffeeFilter: dummy = SaveableList<CoffeeFilter>::getDummy(); break;
//				case Saveable::SaveableType::greyscaleFilter: dummy = SaveableList<GreyscaleFilter>::getDummy(); break;
//				case Saveable::SaveableType::mixFilter: dummy = SaveableList<MixFilter>::getDummy(); break;
//				case Saveable::SaveableType::noiseFilter: dummy = SaveableList<NoiseFilter>::getDummy(); break;
				case Saveable::SaveableType::overlay: dummy = SaveableList<Overlay>::getDummy(); break;
//				case Saveable::SaveableType::coloringOverlay: dummy = SaveableList<ColoringOverlay>::getDummy(); break;
//				case Saveable::SaveableType::heatmapOverlay: dummy = SaveableList<HeatmapOverlay>::getDummy(); break;
//				case Saveable::SaveableType::macroblockOverlay: dummy = SaveableList<MacroblockOverlay>::getDummy(); break;
//				case Saveable::SaveableType::motionVektorOverlay: dummy = SaveableList<MotionVectorOverlay>::getDummy(); break;
//				case Saveable::SaveableType::rescaleFilter: dummy = SaveableList<RescaleFilter>::getDummy(); break;
//				case Saveable::SaveableType::rGBChannelFilter: dummy = SaveableList<RGBChannelFilter>::getDummy(); break;
//				case Saveable::SaveableType::timeshiftFilter: dummy = SaveableList<TimeshiftFilter>::getDummy(); break;
//				case Saveable::SaveableType::video: dummy = SaveableList<Video>::getDummy(); break;
//				case Saveable::SaveableType::fileVideo: dummy = SaveableList<FileVideo>::getDummy(); break;
//				case Saveable::SaveableType::fFmpegDataVideo: dummy = SaveableList<FFmpegDataVideo>::getDummy(); break;
//				case Saveable::SaveableType::yUVDataVideo: dummy = SaveableList<YUVDataVideo>::getDummy(); break;
				case Saveable::SaveableType::filteredVideo: dummy = SaveableList<FilteredVideo>::getDummy(); break;
				case Saveable::SaveableType::player: dummy = SaveableList<Player>::getDummy(); break;
				case Saveable::SaveableType::uIntegerInterval: dummy = SaveableList<UIntegerInterval>::getDummy(); break;
//				case Saveable::SaveableType::videoScrubber: dummy = SaveableList<VideoScrubber>::getDummy(); break;
				case Saveable::SaveableType::saveableList:
					throw ParseException("A saveable list may not contain another saveable list.");
					break;
				default: throw IllegalArgumentException("Unknown saveable type."); break;
				}
				break;
			}
			pointerMap.insert(id, dummy);
		}
		readMemento(id);
	}
}

void XMLLoader::loadView() {
	if (xml->tokenType() != QXmlStreamReader::StartElement || xml->name() != XMLSaver::VIEW) {
		throw IllegalStateException("Wrong call of loadView().");
	}
	QXmlStreamAttributes attributes = xml->attributes();
	if (!attributes.hasAttribute(XMLSaver::STATE)) {
		throw ParseException("Attribute " + XMLSaver::STATE + " expected.");
	}
	bool valid = false;
	int state = attributes.value(XMLSaver::STATE).toInt(&valid);
	if (!valid) {
		throw ParseException("Incorrect value for " + XMLSaver::STATE);
	}
	ViewState::getInstance()->changeView(static_cast<ViewType>(state));
}

void XMLLoader::readMemento(int id) {
	if (xml->tokenType() != QXmlStreamReader::StartElement || xml->name() != XMLSaver::ELEMENT) {
		throw IllegalStateException("Wrong call of readMemento().");
	}
	Memento memento = Memento();
	QMap<QString, int> idMap = QMap<QString, int>();
	while ((xml->readNext() != QXmlStreamReader::EndElement || xml->name() != XMLSaver::ELEMENT) && !xml->hasError()) {
		if (xml->tokenType() != QXmlStreamReader::StartElement) {
			continue;
		}
		if (xml->name() == XMLSaver::VARIABLE) {
			QXmlStreamAttributes variableAttributes = xml->attributes();
			if (!variableAttributes.hasAttribute(XMLSaver::NAME)) {
				throw ParseException("Attribute " + XMLSaver::NAME + " expected.");
			}
			if (!variableAttributes.hasAttribute(XMLSaver::VALUE)) {
				throw ParseException("Attribute " + XMLSaver::VALUE + " expected.");
			}
			memento.setString(variableAttributes.value(XMLSaver::NAME).toString(),
				              variableAttributes.value(XMLSaver::VALUE).toString());
		} else if (xml->name() == XMLSaver::POINTER) {
			QXmlStreamAttributes pointerAttributes = xml->attributes();
			if (!pointerAttributes.hasAttribute(XMLSaver::NAME)) {
				throw ParseException("Attribute " + XMLSaver::NAME + " expected.");
			}
			if (!pointerAttributes.hasAttribute(XMLSaver::ID)) {
				throw ParseException("Attribute " + XMLSaver::ID + " expected.");
			}
			bool valid;
			int pointerId = pointerAttributes.value(XMLSaver::ID).toInt(&valid);
			if (!valid) {
				throw ParseException(pointerAttributes.value(XMLSaver::ID).toString()
					+ "is not a valid ID. IDs must be integer.");
			}
			idMap.insert(pointerAttributes.value(XMLSaver::NAME).toString(),
				pointerId);
		} else {
			throw ParseException("Tag <" + XMLSaver::VARIABLE + "> or <" + XMLSaver::POINTER + "> expected.");
		}
		mementoMap.insert(id, memento);
		mementoIdMap.insert(id, idMap);
	}
}

void XMLLoader::restore() {
	for (int i = 0; i < pointerMap.size(); i++) {
		Saveable::sptr element = pointerMap[i];
		Memento memento = mementoMap[i];
		QMap<QString, int> mementoPointerMap = mementoIdMap[i];
		QList<QString> pointerMapKeys = mementoPointerMap.keys();
		for (int j = 0; j < pointerMapKeys.length(); j++) {
			QString key = pointerMapKeys[j];
			int id = mementoPointerMap.value(key);
			if (!pointerMap.contains(id)) {
				throw ParseException("No id " + QString::number(id) + " found.");
			}
			memento.setSharedPointer(key, pointerMap.value(id));
		}
		element->restore(memento);
	}
	Project::getInstance()->changed();
}

XMLLoader *XMLLoader::getInstance() {
	if (instance.isNull()) {
		instance.reset(new XMLLoader());
	}
	return instance.data();
}

XMLLoader::uptr XMLLoader::instance;

}  // namespace project
}  // namespace controller