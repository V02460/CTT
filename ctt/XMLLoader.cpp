#include "XMLLoader.h"

#include "IOException.h"
#include "ParseException.h"

namespace controller {
namespace project {

using ::exception::IOException;
using ::exception::ParseException;
using ::exception::NotImplementedException;
using ::controller::project::XMLSaver;
using ::controller::project::Project;
using ::model::saveable::Saveable;

using ::model::FilterIntervalList;
using ::model::difference::EarthMoversHistogramDiff;
using ::model::difference::HSLPixelDiff;
using ::model::difference::YUVPixelDiff;
using ::model::filter::BlurFilter;
using ::model::filter::CoffeeFilter;
using ::model::filter::GreyscaleFilter;
using ::model::filter::MixFilter;
using ::model::filter::NoiseFilter;
using ::model::filter::overlay::HeatmapOverlay;
using ::model::filter::overlay::MacroblockOverlay;
using ::model::filter::overlay::MacropartionOverlay;
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

using ::model::difference::FrameDiff;
using ::model::difference::PixelDiff;
using ::model::Module;
using ::model::filter::Filter;
using ::model::filter::overlay::Overlay;
using ::model::filter::overlay::ColoringOverlay;
using ::model::video::Video;
using ::model::video::FileVideo;

XMLLoader::XMLLoader() {
}

void XMLLoader::restore(QDir path, Project project) {
	openFile(path);
	createMaps(project);
	restore();
}

void XMLLoader::openFile(QDir path) {
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		throw new IOException("File " + path.absolutePath() + " could not be opened.");
	}
	xml = new QXmlStreamReader(&file);
	if (!xml->readNextStartElement()) { // more to skip?
		throw new ParseException("Document to restore from is empty.");
	}
	if (xml->qualifiedName() != XMLSaver::ELEMENTS) {
		throw new ParseException("Tag <" + XMLSaver::ELEMENTS + "> expected.");
	}
}

void XMLLoader::createMaps(Project project) {
	while (xml->readNextStartElement()) {
		if (xml->qualifiedName() != XMLSaver::ELEMENT) {
			throw new ParseException("Tag <" + XMLSaver::ELEMENT + "> expected.");
		}
		QXmlStreamAttributes attributes = xml->attributes();
		if (!attributes.hasAttribute(XMLSaver::ID)) {
			throw new ParseException("Attribute " + XMLSaver::ID + " expected.");
		}
		bool valid = false;
		int id = attributes.value(XMLSaver::ID).toInt(&valid);
		if (!valid) {
			throw new ParseException(attributes.value(XMLSaver::ID).toString()
				                     + "is not a valid ID. IDs must be integer.");
		}
		if (pointerMap.contains(id)) {
			throw new ParseException("Multiple elements with key " + QString::number(id) + " exist.");
		}
		if (attributes.hasAttribute(XMLSaver::TYPE)) {
			XMLSaver::BaseSaveableType baseType =
				XMLSaver::stringToBaseSaveableType(attributes.value(XMLSaver::TYPE).toString());
			// abfangen, wenn class string / template nicht stimmt?
			switch (baseType) {
			case XMLSaver::BaseSaveableType::BaseVideoList:
				pointerMap.insert(id, project.getBaseVideoList()); break;
			case XMLSaver::BaseSaveableType::VideoList1:
				pointerMap.insert(id, project.getVideoList1()); break;
			case XMLSaver::BaseSaveableType::VideoList2:
				pointerMap.insert(id, project.getVideoList2()); break;
			case XMLSaver::BaseSaveableType::PlayerList1:
				pointerMap.insert(id, project.getPlayerList1()); break;
			case XMLSaver::BaseSaveableType::Player2:
				pointerMap.insert(id, project.getPlayer2()); break;
			case XMLSaver::BaseSaveableType::DiffList:
				pointerMap.insert(id, project.getDiffList()); break;
			case XMLSaver::BaseSaveableType::View:
				pointerMap.insert(id, project.getView()); break;
			default: throw new NotImplementedException("Unknown base savable type."); break;
			}
		} else {
			if (!attributes.hasAttribute(XMLSaver::CLASS)) {
				throw new ParseException("Attribute " + XMLSaver::CLASS + " expected.");
			}
			Saveable::SaveableType saveableType =
				Saveable::stringToSaveableType(attributes.value(XMLSaver::CLASS).toString());
			Saveable::sptr dummy;
			switch (saveableType) {
			default:
				throw new ParseException(attributes.value(XMLSaver::CLASS).toString()
					+ " can not be instanciated.");
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
			case Saveable::SaveableType::heatmapOverlay: dummy = HeatmapOverlay::getDummy(); break;
			case Saveable::SaveableType::macroblockOverlay: dummy = MacroblockOverlay::getDummy(); break;
			case Saveable::SaveableType::makropartitionOverlay: dummy = MacropartionOverlay::getDummy(); break;
			case Saveable::SaveableType::motionVektorOverlay: dummy = MotionVectorOverlay::getDummy(); break;
			case Saveable::SaveableType::rescaleFilter: dummy = RescaleFilter::getDummy(); break;
			case Saveable::SaveableType::rGBChannelFilter: dummy = RGBChannelFilter::getDummy(); break;
			case Saveable::SaveableType::timeshiftFilter: dummy = TimeshiftFilter::getDummy(); break;
			case Saveable::SaveableType::fFmpegDataVideo: dummy = FFmpegDataVideo::getDummy(); break;
			case Saveable::SaveableType::yUVDataVideo: dummy = YUVDataVideo::getDummy(); break;
			case Saveable::SaveableType::filteredVideo: dummy = FilteredVideo::getDummy(); break;
			case Saveable::SaveableType::player: dummy = Player::getDummy(); break;
			case Saveable::SaveableType::uIntegerInterval: dummy = UIntegerInterval::getDummy(); break;
			case Saveable::SaveableType::videoScrubber: dummy = VideoScrubber::getDummy(); break;
			case Saveable::SaveableType::viewState: dummy = ViewState::getDummy(); break;
			case Saveable::SaveableType::saveableList:
				if (!attributes.hasAttribute(XMLSaver::TEMPLATE_TYPE)) {
					throw new ParseException("Attribute " + XMLSaver::TEMPLATE_TYPE + " expected.");
				}
				Saveable::SaveableType templateType =
					Saveable::stringToSaveableType(attributes.value(XMLSaver::CLASS).toString());
				switch (templateType) {
				case Saveable::SaveableType::saveable: dummy = SaveableList<Saveable>::getDummy(); break;
				case Saveable::SaveableType::filterIntervalList: dummy = SaveableList<FilterIntervalList>::getDummy(); break;
				case Saveable::SaveableType::frameDiff: dummy = SaveableList<FrameDiff>::getDummy(); break;
				case Saveable::SaveableType::earthMoversHistogramDiff: dummy = SaveableList<EarthMoversHistogramDiff>::getDummy(); break;
				case Saveable::SaveableType::pixelDiff: dummy = SaveableList<PixelDiff>::getDummy(); break;
				case Saveable::SaveableType::hSLPixelDiff: dummy = SaveableList<HSLPixelDiff>::getDummy(); break;
				case Saveable::SaveableType::yUVPixelDiff: dummy = SaveableList<YUVPixelDiff>::getDummy(); break;
				case Saveable::SaveableType::module: dummy = SaveableList<Module>::getDummy(); break;
				case Saveable::SaveableType::filter: dummy = SaveableList<Filter>::getDummy(); break;
				case Saveable::SaveableType::blurFilter: dummy = SaveableList<BlurFilter>::getDummy(); break;
				case Saveable::SaveableType::coffeeFilter: dummy = SaveableList<CoffeeFilter>::getDummy(); break;
				case Saveable::SaveableType::greyscaleFilter: dummy = SaveableList<GreyscaleFilter>::getDummy(); break;
				case Saveable::SaveableType::mixFilter: dummy = SaveableList<MixFilter>::getDummy(); break;
				case Saveable::SaveableType::noiseFilter: dummy = SaveableList<NoiseFilter>::getDummy(); break;
				case Saveable::SaveableType::overlay: dummy = SaveableList<Overlay>::getDummy(); break;
				case Saveable::SaveableType::coloringOverlay: dummy = SaveableList<ColoringOverlay>::getDummy(); break;
				case Saveable::SaveableType::heatmapOverlay: dummy = SaveableList<HeatmapOverlay>::getDummy(); break;
				case Saveable::SaveableType::macroblockOverlay: dummy = SaveableList<MacroblockOverlay>::getDummy(); break;
				case Saveable::SaveableType::makropartitionOverlay: dummy = SaveableList<MacropartionOverlay>::getDummy(); break;
				case Saveable::SaveableType::motionVektorOverlay: dummy = SaveableList<MotionVectorOverlay>::getDummy(); break;
				case Saveable::SaveableType::rescaleFilter: dummy = SaveableList<RescaleFilter>::getDummy(); break;
				case Saveable::SaveableType::rGBChannelFilter: dummy = SaveableList<RGBChannelFilter>::getDummy(); break;
				case Saveable::SaveableType::timeshiftFilter: dummy = SaveableList<TimeshiftFilter>::getDummy(); break;
				case Saveable::SaveableType::video: dummy = SaveableList<Video>::getDummy(); break;
				case Saveable::SaveableType::fileVideo: dummy = SaveableList<FileVideo>::getDummy(); break;
				case Saveable::SaveableType::fFmpegDataVideo: dummy = SaveableList<FFmpegDataVideo>::getDummy(); break;
				case Saveable::SaveableType::yUVDataVideo: dummy = SaveableList<YUVDataVideo>::getDummy(); break;
				case Saveable::SaveableType::filteredVideo: dummy = SaveableList<FilteredVideo>::getDummy(); break;
				case Saveable::SaveableType::player: dummy = SaveableList<Player>::getDummy(); break;
				case Saveable::SaveableType::uIntegerInterval: dummy = SaveableList<UIntegerInterval>::getDummy(); break;
				case Saveable::SaveableType::videoScrubber: dummy = SaveableList<VideoScrubber>::getDummy(); break;
				case Saveable::SaveableType::viewState: dummy = SaveableList<ViewState>::getDummy(); break;
				case Saveable::SaveableType::saveableList:
					throw new ParseException("A saveable list may not contain another saveable list.");
					break;
				default: throw new NotImplementedException("Unknown saveable type."); break;
				}
				break;
			}
			pointerMap.insert(id, dummy);
		}
		// TODO map Memento to ID
	}
}

void XMLLoader::restore() {
	// TODO actually restore everything
}

}  // namespace project
}  // namespace controller


/* TO USE

QXmlStreamReader
	bool					atEnd()
	QXmlStreamAttributes	attributes()
	QString					errorString()
	bool					hasError()
	bool					isComment()
	bool					isEndElement() / isEndDocument()
	bool					isStartElement() / isStartDocument()
	bool					isWhitespace()
	QStringRef				name() / qualifiedName()
	QString					readElementText()
	TokenType / bool		readNext() / readNextStartElement()
	void					skipCurrentElement()

QXmlStreamAttributes
	bool					hasAttribute(QString qualifiedName)
	QStringRef				value(QString qualifiedName)

 */