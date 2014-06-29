#if !defined(_VIDEOANALYSINGWIDGET_H)
#define _VIDEOANALYSINGWIDGET_H

namespace view {

class VideoAnalysingWidget {
public:
	signal overlayChanged();
	QString getOverlay();
private:
	QComboBox comboboxOverlay;
};

}  // namespace view

#endif  //_VIDEOANALYSINGWIDGET_H
