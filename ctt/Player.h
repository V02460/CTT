


#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "Savable.h"
#include "VideoScrubber.h"
#include "IntegerInterval.h"
#include "Memento.h"

class Player : public Savable {
public:
	void Player(double fps);
	virtual void play() = 0;
	virtual void pause() = 0;
	void togglePlayPause();
	void nextFrame();
	void previousFrame();
	virtual signal jumpToFrameNr(int frameNumber) = 0;
	virtual void setFPS(double fps) = 0;
	double getFPS();
	List<VideoSrubber> getScrubber();
	bool isPlaying();
	void addScrubber(VideoScrubebr scrubber);
	void addScrubber(VideoScrubber scrubber, int position);
	void remoteScrubber(int position);
	void removeScrubber(VideoScrubber scrubber);
	bool controlsScrubber(VideoScrubber scrubber);
	int scrubberCount();
	bool hasNextFrame();
	bool hasPreviousFrame();
	int getVideoLength();
	int getCurrentFrameNumber();
	void setLoop(IntegerInterval interval);
	IntegerInterval getLoop();
	bool isLooping();
	void removeLoop();
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
private:
	int currentFrameNumber;
	QTimer timer;
	double fps;
	bool looping;
	bool playing;
	IntegerInterval *loop;
	IntegerInterval *loop;
};

#endif  //_PLAYER_H
