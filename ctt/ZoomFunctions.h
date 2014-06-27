


#if !defined(_ZOOMFUNCTIONS_H)
#define _ZOOMFUNCTIONS_H


class ZoomFunctions {
public:
	void setZoomFactor(double zoomFactor);
	double getZoomFactor();
	signal zoomFactorChanged(double zoomFactor);
private:
	QPushButton btnZoomOut;
	QPushButton btnZoomIn;
	QSlider sliderZoom;
	double zoomFactor;
};

#endif  //_ZOOMFUNCTIONS_H
