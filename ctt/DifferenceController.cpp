#include "DifferenceController.h"
#include "DifferenceFactory.h"

namespace controller {

	using ::model::video::Video;
	using ::model::saveable::SaveableList;
	using ::model::difference::FrameDiff;

	DifferenceController::DifferenceController(SaveableList<FrameDiff>::sptr diffList) : diffList(diffList) {

	}

	void DifferenceController::diffInserted(QString id, Video::sptr video1, Video::sptr video2) {
	//model::difference::DifferenceFactory factory(model::difference::DifferenceFactory());
	QList<QByteArray> frameDiffs = model::difference::DifferenceFactory::getAllFrameDiffIDs();
	for (int i = 0; i < frameDiffs.length(); i++) {
		if (id == frameDiffs.at(i)) {			
			model::difference::FrameDiff::sptr frameDiff = model::difference::DifferenceFactory::createFrameDiff(id, video1, video2);
			diffList->insert((diffList->getSize()), frameDiff);
			return;
		}
	}
	QList<QByteArray> pixelDiffs = model::difference::DifferenceFactory::getAllPixelDiffIDs();
	for (int i = 0; i < pixelDiffs.length(); i++) {
		if (id == pixelDiffs.at(i)) {
			model::difference::PixelDiff::sptr pixelDiff = model::difference::DifferenceFactory::createPixelDiff(id, video1, video2);
			diffList->insert((diffList->getSize()), pixelDiff);
			return;
		}
	}
	throw exception::IllegalArgumentException("The given ID does not match any Difference Function.");
}

void DifferenceController::diffRemoved(int pos) {
	if (pos >= 0 && pos < diffList->getSize()) 	{
		diffList->remove(pos);
		return;
	}
	else throw exception::IllegalArgumentException("There is no Difference Function at the position one is to be removed.");
}

}  // namespace controller