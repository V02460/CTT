


#if !defined(_PLAYERWIDGET_H)
#define _PLAYERWIDGET_H


class PlayerWidget {
public:
	signal playerActivated(PlayerWidget playerWidget);
	slot getActivationSignal();
};

#endif  //_PLAYERWIDGET_H
