#include "Player.h"

namespace model {
namespace player {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;

Player::Player(double fps) {

}

Player::~Player() {

}

void Player::play() {

}

void Player::pause() {

}

void Player::togglePlayPause() {

}

void Player::jumpToFrameNr(unsigned int frameNr) {

}

void Player::setFPS(double fps){

}

double Player::getFPS() const {

}

QList<VideoScrubber::sptr> Player::getScrubbers() const {

}

bool Player::isPlaying() const {

}

void Player::addScrubber(VideoScrubber::sptr scrubber) {

}

void Player::addScrubber(VideoScrubber::sptr scrubber, int position) {

}

void Player::removeScrubber(int position) {

}

void Player::removeScrubber(const VideoScrubber &scrubber) {

}

bool Player::controlsScrubber(const VideoScrubber &scrubber) const {

}

unsigned int Player::scrubberCount() const {

}
bool Player::hasNextFrame() const {

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