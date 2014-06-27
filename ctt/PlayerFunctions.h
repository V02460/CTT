


#if !defined(_PLAYERFUNCTIONS_H)
#define _PLAYERFUNCTIONS_H

#include "Observable.h"

class PlayerFunctions : public Observable {
private:
	QPushButton btnPlayPause;
	QPushButton btnNextFrame;
	QPushButton btnPreviousFrame;
	QPushButton btnDefaultFPS;
	QSpinBox spinboxFPS;
};

#endif  //_PLAYERFUNCTIONS_H
