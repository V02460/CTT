#include "Player.h"
#include "VideoScrubber.h"
#include "UIntegerInterval.h"
#include "Memento.h"

namespace model {
namespace player {

Player::Player(double fps) {

}

void Player::togglePlayPause() {

}

void Player::nextFrame() {

}

void Player::previousFrame() {

}

void Player::jumpToFrameNr(unsigned int frameNr) {

}

double Player::getFPS() {

}

QList<VideoScrubber> Player::getScrubbers() {

}

bool Player::isPlaying() {

}

void Player::addScrubber(VideoScrubber scrubber) {

}

void Player::addScrubber(VideoScrubber scrubber, int position) {

}

void Player::removeScrubber(int position) {

}

void Player::removeScrubber(VideoScrubber scrubber) {

}

bool Player::controlsScrubber(VideoScrubber scrubber) {

}

unsigned int Player::scrubberCount() {

}

bool Player::hasNextFrame() {

}

bool Player::hasPreviousFrame() {

}

unsigned int Player::getVideoLength() {

}

unsigned int Player::getCurrentFrameNumber() {

}

void Player::setLoop(UIntegerInterval interval) {

}

UIntegerInterval Player::getLoop() {

}

bool Player::isLooping() {

}

void Player::stopLooping() {

}

Memento Player::getMemento() {

}

void Player::restore(Memento memento) {

}

Saveable* Player::getDummy() {

}

}  // namespace player
}  // namespace model