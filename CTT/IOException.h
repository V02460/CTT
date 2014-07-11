#ifndef _IOEXCEPTION_H
#define _IOEXCEPTION_H

#include <QException>
#include <QString>

#include "RuntimeException.h"

namespace exception {

	/**
	* Signals that a method has been invoked at an illegal or inappropriate time.
	*/
	class IOException : public RuntimeException {
	public:
		/**
		* Creates a new IllegalStateException.
		*/
		IOException();

		/**
		* Creates a new IllegalStateException with an error message.
		*
		* @param msg descriptive error message
		*/
		IOException(QString msg);

		/**
		* Destroys the IllegalStateException.
		*/
		~IOException();

		virtual QString getName() const Q_DECL_OVERRIDE{ return "IOException"; }
		virtual QString getMsg() const Q_DECL_OVERRIDE;
		const char *what() const Q_DECL_OVERRIDE;

		virtual void IOException::raise() const Q_DECL_OVERRIDE;
		virtual IOException *clone() const Q_DECL_OVERRIDE;

	private:
		const QString msg;
		const QByteArray asciiMsg;
	};

}  // namespace exception

#endif