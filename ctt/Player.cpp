#include "Player.h"

#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "NotImplementedException.h"

namespace model {
namespace player {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::IllegalArgumentException;
using ::exception::AccessToDummyException;
using ::exception::NotImplementedException;

const QString Player::fpsStringId("fps");
const QString Player::scrubbersStringId("scrubbers");
const QString Player::numberOfScrubbersStringId("numberOfScrubbers");
const QString Player::loopingStringId("looping");
const QString Player::loopEndAStringId("loopA");
const QString Player::loopEndBStringId("loopB");
const QString Player::frameNumberStringId("frameNr");


Player::Player(double fps): Observable(), fps(fps), defaultFPS(fps), loop(0, 0), currentFrameNumber(0), looping(false), playing(false) {
	if (!(fps > 0)) {
		throw IllegalArgumentException("Tried to create a player with a playback speed not greater than zero.)");
	}

	timer.setTimerType(Qt::PreciseTimer);
	connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
}


Player::Player() : Observable(), loop(0, 1)
{
	isDummyFlag = true;
	currentFrameNumber = 0;
}

Player::~Player() {

}

void Player::play() {
	if (isDummy()) {
		throw AccessToDummyException();
	}

	if (!isPlaying())
	{
		playing = true;
		changed();
	}	

	if (currentFrameNumber == getVideoLength() - 1) {
		jumpToFrameNr(0);
	}
	timer.start(1000 / fps);
}

void Player::pause() {
	if (isDummy()) {
		throw AccessToDummyException();
	}

	if (isPlaying())
	{
		playing = false;
		changed();
	}
	timer.stop();
}

void Player::togglePlayPause() {
	if (isPlaying())
	{
		pause();
	}
	else
	{
		play();
	}
}

void Player::jumpToFrameNr(unsigned int frameNr) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (getVideoLength() <= frameNr) {
		throw IllegalArgumentException("Tried to request a jump to a frame number which is too high for the "
			"scrubbers controlled by this player.");
	}

	currentFrameNumber = frameNr;

	changed();
	emit currentFrameNrChanged(getCurrentFrameNumber());
}

void Player::setFPS(double fps) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (!(fps > 0)) {
		throw IllegalArgumentException("Tried to set a playback speed not greater than zero.)");
	}

	this->fps = fps;
	changed();
}

double Player::getFPS() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return fps;
}

QList<VideoScrubber::sptr> Player::getScrubbers() const {
	return videoScrubbers;
}

bool Player::isPlaying() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return playing;
}

void Player::addScrubber(VideoScrubber::sptr scrubber) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	
	videoScrubbers.append(scrubber);
	connect(this, SIGNAL(currentFrameNrChanged(unsigned int)), scrubber.data(), SLOT(jumpToFrameNr(unsigned int)));

	if (scrubber->getFrameCount() < getCurrentFrameNumber())
	{
		currentFrameNumber = scrubber->getFrameCount();
		emit currentFrameNrChanged(getCurrentFrameNumber());
}
	else
	{
		scrubber->jumpToFrameNr(getCurrentFrameNumber());
	}

	if (isLooping() && (getLoop().getEnd() >= scrubber->getFrameCount()))
	{
		looping = false;
}

	changed();
}

void Player::addScrubber(VideoScrubber::sptr scrubber, unsigned int position) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (scrubber->isDummy())
	{
		throw IllegalArgumentException("Tried to add a dummy VideoScrubber to a player.");
	}
	if (position > static_cast<unsigned int>(videoScrubbers.size()))
	{
		throw IllegalArgumentException("Tried to insert a Scrubber into a Player at position " 
			+ QString::number(position) + ", but " + QString::number(videoScrubbers.size()) 
			+ " was the highest valid position.");
	}

	videoScrubbers.insert(position, scrubber);
	connect(this, SIGNAL(currentFrameNrChanged(unsigned int)), scrubber.data(), SLOT(jumpToFrameNr(unsigned int)));

	if (scrubber->getFrameCount() < getCurrentFrameNumber())
	{
		currentFrameNumber = scrubber->getFrameCount();
		emit currentFrameNrChanged(getCurrentFrameNumber());
}
	else
	{
		scrubber->jumpToFrameNr(getCurrentFrameNumber());
	}
	changed();
}

void Player::removeScrubber(unsigned int position) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    if (position >= static_cast<unsigned int>(videoScrubbers.size()))
	{
		throw IllegalArgumentException("Tried to remove a Scrubber from a Player at position "
			+ QString::number(position) + ", but it contained only " + QString::number(videoScrubbers.size())
			+ " elements.");
	}

	disconnect(this, SIGNAL(currentFrameNrChanged(unsigned int)), videoScrubbers.at(position).data(), SLOT(jumpToFrameNr(unsigned int)));
	videoScrubbers.removeAt(position);
	changed();
}

void Player::removeScrubber(const VideoScrubber &scrubber) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (!controlsScrubber(scrubber))
	{
		throw IllegalArgumentException("Tried to remove a scrubber from a player which doesn't control the "
			"scrubber.");
	}

	disconnect(this, SIGNAL(currentFrameNrChanged(unsigned int)), &scrubber, SLOT(jumpToFrameNr(unsigned int)));
	
	for each (VideoScrubber::sptr controledScrubber in videoScrubbers)
	{
		if (controledScrubber.data() == &scrubber)
		{
			videoScrubbers.removeOne(controledScrubber);
			return;
		}
	}
	changed();
}

bool Player::controlsScrubber(const VideoScrubber &scrubber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	for each (VideoScrubber::sptr controledScrubber in videoScrubbers)
	{
		if (controledScrubber.data() == &scrubber)
		{
			return true;
		}
	}
	return false;
}

unsigned int Player::scrubberCount() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return videoScrubbers.size();
}

bool Player::hasNextFrame() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return (getVideoLength() > (getCurrentFrameNumber() + 1));
}

bool Player::hasPreviousFrame() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return (getCurrentFrameNumber() > 0);
}

unsigned int Player::getVideoLength() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (scrubberCount() == 0)
	{
		return 0;
	}

	unsigned int shortest = UINT_MAX;
	for each (::model::player::VideoScrubber::sptr scrubber in videoScrubbers)
	{
		if (scrubber->getFrameCount() < shortest)
		{
			shortest = scrubber->getFrameCount();
}
	}
	return shortest;
}

unsigned int Player::getCurrentFrameNumber() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return currentFrameNumber;
}

void Player::setLoop(UIntegerInterval interval) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (interval.isDummy())
	{
		throw IllegalArgumentException("Tried to give a player a dummy interval to loop in.");
	}

	if ((interval.getStart() >= getVideoLength()) || (interval.getEnd() >= getVideoLength()))
	{
		throw IllegalArgumentException("Tried to set a loop from frame " + QString::number(interval.getStart()) 
			+ " to frame " + QString::number(interval.getEnd()) + " on a player with a video of length "
			+ QString::number(getVideoLength()) + ".");
	}

	loop = interval;
	looping = true;
	if (!loop.contains(getCurrentFrameNumber()))
	{
		jumpToFrameNr(loop.getStart());
	}	
	changed();
}

UIntegerInterval Player::getLoop() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return loop;
}

bool Player::isLooping() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return looping;
}

void Player::stopLooping() {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	looping = false;
}

Memento Player::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;

	memento.setDouble(fpsStringId, fps);
	memento.setUInt(frameNumberStringId, currentFrameNumber);

	memento.setBool(loopingStringId, looping);
	if (isLooping())
	{
		memento.setUInt(loopEndAStringId, loop.getStart());
		memento.setUInt(loopEndBStringId, loop.getEnd());
	}

	memento.setUInt(numberOfScrubbersStringId, videoScrubbers.size());
	for (unsigned int i = 0; i < static_cast<unsigned int>(videoScrubbers.size()); i++)
	{
		memento.setSharedPointer(scrubbersStringId + QString::number(i), videoScrubbers[i]);
	}

	return memento;
}

void Player::restore(Memento memento) {
	isDummyFlag = false;

	if (!(memento.getDouble(fpsStringId) > 0)) {
		throw IllegalArgumentException("Tried to create a player with a playback speed not greater than zero.)");
	}
	fps = memento.getDouble(fpsStringId);

 	looping = memento.getBool(loopingStringId);

	if (looping)
	{
		loop = UIntegerInterval(memento.getUInt(loopEndAStringId), memento.getUInt(loopEndBStringId));
		if (!loop.contains(currentFrameNumber))
		{
			currentFrameNumber = loop.getStart();
		}
	}

	playing = false;
	timer.setTimerType(Qt::PreciseTimer);
	timer.stop();
	connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

	videoScrubbers.clear();
	for (unsigned int i = 0; i < memento.getUInt(numberOfScrubbersStringId); i++)
	{
		videoScrubbers.append(memento.getSharedPointer(scrubbersStringId + QString::number(i)).dynamicCast<VideoScrubber>());
		connect(this, SIGNAL(currentFrameNrChanged(unsigned int)), videoScrubbers[i].data(), SLOT(jumpToFrameNr(unsigned int)));
	}

}

Saveable::sptr Player::getDummy() {
	return Saveable::sptr(new Player());
}

Saveable::SaveableType Player::getSaveableType() {
    return SaveableType::player;
}

void Player::nextFrame() {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if ((currentFrameNumber == loop.getEnd()) && isLooping()) {
		jumpToFrameNr(loop.getStart());
	} else if (hasNextFrame()) {
		jumpToFrameNr(getCurrentFrameNumber() + 1);
        pause();
	} else {
		pause();
	}
}

void Player::previousFrame() {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if ((currentFrameNumber == loop.getStart()) && isLooping()) {
		jumpToFrameNr(loop.getEnd());
	} else if (hasPreviousFrame()) {
		jumpToFrameNr(getCurrentFrameNumber() - 1);
        pause();
	}
}

double Player::getDefaultFPS() {
	return defaultFPS;
}

}  // namespace player
}  // namespace model