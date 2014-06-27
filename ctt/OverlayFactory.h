


#if !defined(_OVERLAYFACTORY_H)
#define _OVERLAYFACTORY_H


class OverlayFactory {
public:
	List<QString> getAllOverlayIDs();
	Diff createOverlay(QString id);
private:
	void OverlayFactory();
};

#endif  //_OVERLAYFACTORY_H
