#include "Saveable.h"

#include "NotImplementedException.h"

namespace model {
namespace saveable {

using ::exception::NotImplementedException;

const QString Saveable::FILE_VIDEO = "FileVideo";
const QString Saveable::FILTERED_VIDEO = "FilteredVideo";
const QString Saveable::PLAYER = "Player";
const QString Saveable::DIFF = "FrameDiff";
const QString Saveable::VIEW = "View";
const QString Saveable::LIST = "SavableList";

const QList<QString> Saveable::SAVEABLE_TYPE_STRINGS = QList<QString>()
	<< FILE_VIDEO
	<< FILTERED_VIDEO
	<< PLAYER
	<< DIFF
	<< VIEW
	<< LIST;

bool Saveable::isDummy() const {
	return isDummyFlag;
}

Saveable::sptr getDummy() {
    throw new NotImplementedException();
}

}  // namespace savable
}  // namespace model