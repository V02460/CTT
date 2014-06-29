


#if !defined(_VIDEOMETADATA_H)
#define _VIDEOMETADATA_H


class VideoMetadata {
public:
	VideoMetadata(QSize size, double fps, unsigned int length, QMap<QString, QString> additionalData);
	VideoMetadata(QSize size, double fps, unsigned int length);
	bool hasData(QString key);
	bool getData(QString key);
	QSize getSize();
	double getFPS();
	unsigned int getLength();
private:
	QSize size;
	double fps;
};

#endif  //_VIDEOMETADATA_H
