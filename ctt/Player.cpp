


#include "Player.h"
#include "VideoScrubber.h"
#include "IntegerInterval.h"
#include "Memento.h"

void Player::Player(double fps) {

}

void Player::togglePlayPause() {

}

void Player::nextFrame() {

}

void Player::previousFrame() {

}

double Player::getFPS() {

}

List<VideoSrubber> Player::getScrubber() {

}

bool Player::isPlaying() {

}

void Player::addScrubber(VideoScrubebr scrubber) {

}

void Player::addScrubber(VideoScrubber scrubber, int position) {

}

void Player::remoteScrubber(int position) {

}

void Player::removeScrubber(VideoScrubber scrubber) {

}

bool Player::controlsScrubber(VideoScrubber scrubber) {

}

int Player::scrubberCount() {

}

bool Player::hasNextFrame() {

}

bool Player::hasPreviousFrame() {

}

int Player::getVideoLength() {

}

int Player::getCurrentFrameNumber() {

}

void Player::setLoop(IntergerInterval interval) {

}

IntegerInterval Player::getLoop() {

}

bool Player::isLooping() {

}

void Player::removeLoop() {

}

Memento Player::getMemento() {

}

void Player::restore(Memento memento) {

}

Savable* Player::getDummy() {

}

