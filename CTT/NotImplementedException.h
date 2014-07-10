#ifndef _NOTIMPLEMENTEDEXCEPTION_H
#define _NOTIMPLEMENTEDEXCEPTION_H

#include <QException>
#include <QString>

#include "RuntimeException.h"

namespace exception {

/**
 * Thrown to indicate that a method is not implemented. Mainly used by interfaces.
 */
	class NotImplementedException : public NotImplementedException {

public:
	/**
 	 * Creates a new NotImplementedException.
	 */
	NotImplementedException();

	/**
	 * Creates a new NotImplementedException with an error message.
	 *
	 * @param msg descriptive error message
	 */
	NotImplementedException(QString msg);

	/**
	 * Destroys the NotImplementedException.
	 */
	~NotImplementedException();

	virtual QString getName() const Q_DECL_OVERRIDE{ return "NotImplementedException"; }
	virtual QString getMsg() const Q_DECL_OVERRIDE;
	virtual const char *what() const Q_DECL_OVERRIDE;

	virtual void NotImplementedException::raise() const Q_DECL_OVERRIDE;
	virtual NotImplementedException *clone() const Q_DECL_OVERRIDE;

private:
	const QString msg;
	const QByteArray asciiMsg;
};

}  // namespace exception

#endif