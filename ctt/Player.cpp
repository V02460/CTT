#include "Player.h"

namespace model {
namespace player {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using namespace exception;

Player::Player(double fps): fps(fps) {
	if (!(fps > 0)) {
		throw new IllegalArgumentException("Tried to create a player with a playback speed not greater than zero.)");
	}

	currentFrameNumber = 0;
	looping = false;
	playing = false;

	timer.setTimerType(Qt::PreciseTimer);
	connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
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

QList<VideoScrubber::wptr> Player::getScrubbers() const {
	//TODO implement
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
	
	//TODO wie läuft das mit den Pointern?
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
	if (position > videoScrubbers.size())
	{
		throw new IllegalArgumentException("Tried to insert a Scrubber into a Player at position " 
			+ QString::number(position) + ", but " + QString::number(videoScrubbers.size()) 
			+ " was the highest valid position.");
	}
	//TODO wie läuft das mit den Pointern?
	videoScrubbers.insert(position, scrubber);
	connect(this, SIGNAL(currentFrameNrChanged()), scrubber.data(), SLOT(jumpToFrameNr()));

	scrubber->jumpToFrameNr(currentFrameNumber);
}

void Player::removeScrubber(unsigned int position) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to add a VideoScrubber to a dummy player.");
	}
	if (position >= videoScrubbers.size())
	{
		throw new IllegalArgumentException("Tried to remove a Scrubber from a Player at position "
			+ QString::number(position) + ", but it contained only " + QString::number(videoScrubbers.size())
			+ " elements.");
	}

	disconnect(this, SIGNAL(currentFrameNrChanged()), &videoScrubbers.at(position), SLOT(jumpToFrameNr()));
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
	videoScrubbers.removeOne(scrubber);
}

bool Player::controlsScrubber(const VideoScrubber &scrubber) const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy Player whether it controls a specific Scrubber.");
	}
	return videoScrubbers.contains(scrubber);
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

}

unsigned int Player::getVideoLength() const {

}

unsigned int Player::getCurrentFrameNumber() const {

}

void Player::setLoop(UIntegerInterval interval) {

}

UIntegerInterval Player::getLoop() const {

}

bool Player::isLooping() const {

}

void Player::stopLooping() {

}

Memento Player::getMemento() const {

}

void Player::restore(Memento memento) {

}

Saveable::sptr Player::getDummy() {

}

void Player::nextFrame() {

}

void Player::previousFrame() {

}

}  // namespace player
}  // namespace model