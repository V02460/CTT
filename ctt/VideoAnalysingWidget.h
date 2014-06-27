


#if !defined(_VIDEOANALYSINGWIDGET_H)
#define _VIDEOANALYSINGWIDGET_H


class VideoAnalysingWidget {
public:
	signal overlayChanged();
	QString getOverlay();
private:
	QComboBox comboboxOverlay;
};

#endif  //_VIDEOANALYSINGWIDGET_H
