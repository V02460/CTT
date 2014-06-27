


#if !defined(_VIDEOMETADATA_H)
#define _VIDEOMETADATA_H


class VideoMetadata {
public:
	void VideoMetadata(QSize size, double fps, QMap additionalData);
	bool hasData(QString key);
	bool getData(QString key);
	QSize getSize();
	double getFPS();
private:
	QSize size;
	double fps;
};

#endif  //_VIDEOMETADATA_H
