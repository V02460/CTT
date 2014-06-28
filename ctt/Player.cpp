


#include "Player.h"
#include "VideoScrubber.h"
#include "IntegerInterval.h"
#include "Memento.h"

Player::Player(double fps) {

}

void Player::togglePlayPause() {

}

void Player::nextFrame() {

}

void Player::previousFrame() {

}

double Player::getFPS() {

}

List<VideoScrubber> Player::getScrubbers() {

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

void Player::setLoop(IntegerInterval interval) {

}

IntegerInterval Player::getLoop() {

}

bool Player::isLooping() {

}

void Player::stopLooping() {

}

Memento Player::getMemento() {

}

void Player::restore(Memento memento) {

}

Savable* Player::getDummy() {

}

