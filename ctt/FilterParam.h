


#if !defined(_FILTERPARAM_H)
#define _FILTERPARAM_H


class FilterParam {
public:
	any getValue();
	void FilterParam(QString name);
private:
	QString name;
};

#endif  //_FILTERPARAM_H
