#if !defined(_PLAYERWIDGET_H)
#define _PLAYERWIDGET_H

namespace view {

class PlayerWidget {
public:
	signal playerActivated(PlayerWidget playerWidget);
	slot getActivationSignal();
};

}  // namespace view

#endif  //_PLAYERWIDGET_H
