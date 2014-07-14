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
using ::exception::IllegalStateException;
using ::exception::NotImplementedException;

Player::Player(double fps): fps(fps), loop(0,1), currentFrameNumber(0), looping(false), playing(false) {
	if (!(fps > 0)) {
		throw new IllegalArgumentException("Tried to create a player with a playback speed not greater than zero.)");
	}

	timer.setTimerType(Qt::PreciseTimer);
	connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
}


Player::Player() : loop(0, 1)
{
	isDummyFlag = true;
}

Player::~Player() {

}

void Player::play() {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to play a dummy player.");
	}

	if (!isPlaying())
	{
		playing = true;
		changed();
	}	

	if (currentFrameNumber == getVideoLength()) {
		currentFrameNumber = 0;
		emit currentFrameNrChanged(0);
	}
	timer.start(1000 / fps);
}

void Player::pause() {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to pause a dummy player.");
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
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request a frame jump from a dummy player.");
	}
	if (getVideoLength() <= frameNr) {
		throw new IllegalArgumentException("Tried to request a jump to a frame number which is too high for the "
			"scrubbers controlled by this player.");
	}

	currentFrameNumber = frameNr;

	changed();
	emit currentFrameNrChanged(currentFrameNumber);
}

void Player::setFPS(double fps){
	if (isDummy())
	{
		throw new IllegalStateException("Tried to set a playback speed on a dummy player.");
	}
	if (!(fps > 0)) {
		throw new IllegalArgumentException("Tried to set a playback speed not greater than zero.)");
	}

	this->fps = fps;
}

double Player::getFPS() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request the playback speed of a dummy player.");
	}
	return fps;
}

QList<VideoScrubber::sptr> Player::getScrubbers() const {
	return videoScrubbers;
}

bool Player::isPlaying() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy player whether its playing.");
	}
	return playing;
}

void Player::addScrubber(VideoScrubber::sptr scrubber) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to add a VideoScrubber to a dummy player.");
	}
	if (scrubber->isDummy())
	{
		throw new IllegalArgumentException("Tried to add a dummy VideoScrubber to a player.");
	}
	
	videoScrubbers.append(scrubber);
	connect(this, SIGNAL(currentFrameNrChanged()), scrubber.data(), SLOT(jumpToFrameNr()));

	scrubber->jumpToFrameNr(currentFrameNumber);
}

void Player::addScrubber(VideoScrubber::sptr scrubber, unsigned int position) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to add a VideoScrubber to a dummy player.");
	}
	if (scrubber->isDummy())
	{
		throw new IllegalArgumentException("Tried to add a dummy VideoScrubber to a player.");
	}
	if (position > static_cast<unsigned int>(videoScrubbers.size()))
	{
		throw new IllegalArgumentException("Tried to insert a Scrubber into a Player at position " 
			+ QString::number(position) + ", but " + QString::number(videoScrubbers.size()) 
			+ " was the highest valid position.");
	}

	videoScrubbers.insert(position, scrubber);
	connect(this, SIGNAL(currentFrameNrChanged()), scrubber.data(), SLOT(jumpToFrameNr()));

	scrubber->jumpToFrameNr(currentFrameNumber);
}

void Player::removeScrubber(unsigned int position) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to add a VideoScrubber to a dummy player.");
	}
    if (position >= static_cast<unsigned int>(videoScrubbers.size()))
	{
		throw new IllegalArgumentException("Tried to remove a Scrubber from a Player at position "
			+ QString::number(position) + ", but it contained only " + QString::number(videoScrubbers.size())
			+ " elements.");
	}

	disconnect(this, SIGNAL(currentFrameNrChanged()), videoScrubbers.at(position).data(), SLOT(jumpToFrameNr()));
	videoScrubbers.removeAt(position);
}

void Player::removeScrubber(const VideoScrubber &scrubber) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to remove a VideoScrubber from a dummy player.");
	}
	if (!controlsScrubber(scrubber))
	{
		throw new IllegalArgumentException("Tried to remove a scrubber from a player which doesn't control the "
			"scrubber.");
	}

	disconnect(this, SIGNAL(currentFrameNrChanged()), &scrubber, SLOT(jumpToFrameNr()));
	
	for each (VideoScrubber::sptr controledScrubber in videoScrubbers)
	{
		if (controledScrubber.data() == &scrubber)
		{
			videoScrubbers.removeOne(controledScrubber);
			return;
		}
	}
}

bool Player::controlsScrubber(const VideoScrubber &scrubber) const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player whether it controls a specific Scrubber.");
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
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player for the number of scrubbers it controls.");
	}
	return videoScrubbers.size();
}

bool Player::hasNextFrame() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player whether it has a next frame.");
	}

	return (getVideoLength() > (currentFrameNumber + 1));
}

bool Player::hasPreviousFrame() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player whether it has a previous frame.");
	}
	return (currentFrameNumber > 0);
}

unsigned int Player::getVideoLength() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player for the length of the shortest video of his "
			"scrubber.");
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
	if (isDummy())
	{
		throw new IllegalStateException("Tried to get the current Frame number from a dummy Player.");
}
	return currentFrameNumber;
}

void Player::setLoop(UIntegerInterval interval) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to set a loop on a dummy Player.");
}
	loop = interval;
	looping = true;
}

UIntegerInterval Player::getLoop() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to get a loop from a dummy Player.");
}
	return loop;
}

bool Player::isLooping() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player whether it's looping.");
}
	return looping;
}

void Player::stopLooping() {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to stop looping on a dummy Player.");
	}
	looping = false;
}

Memento Player::getMemento() const {
	//TODO wenn saveable zeug fertig ist
    throw new NotImplementedException();
}

void Player::restore(Memento memento) {
	//TODO wenn saveable zeug fertig ist
    throw new NotImplementedException();
}

Saveable::sptr Player::getDummy() {
	return Saveable::sptr(new Player());
}

void Player::nextFrame() {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to set a dummy Player to its next frame.");
	}

	if (hasNextFrame())
	{
		currentFrameNumber++;
		emit currentFrameNrChanged(currentFrameNumber);
	}
	else
	{
		pause();
	}
}

void Player::previousFrame() {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to set a dummy Player to its previous frame.");
	}
	if (hasPreviousFrame())
	{
		currentFrameNumber--;
		emit currentFrameNrChanged(currentFrameNumber);
	}
}

}  // namespace player
}  // namespace model