#ifndef _FFMPEGEXCEPTION_H
#define _FFMPEGEXCEPTION_H

#include <QException>
#include <QString>

#include "RuntimeException.h"

namespace exception {

	/**
	* Signals that a method has been invoked at an illegal or inappropriate time.
	*/
	class FFmpegException : public RuntimeException {
	public:
		/**
		* Creates a new IllegalStateException.
		*/
		FFmpegException();

		/**
		* Creates a new IllegalStateException with an error message.
		*
		* @param msg descriptive error message
		*/
		FFmpegException(QString msg);

		/**
		* Destroys the IllegalStateException.
		*/
		~FFmpegException();

		virtual QString getName() const Q_DECL_OVERRIDE{ return "FFmpegException"; }
		virtual QString getMsg() const Q_DECL_OVERRIDE;
		const char *what() const Q_DECL_OVERRIDE;

		virtual void FFmpegException::raise() const Q_DECL_OVERRIDE;
		virtual FFmpegException *clone() const Q_DECL_OVERRIDE;

	private:
		const QString msg;
		const QByteArray asciiMsg;
	};

}  // namespace exception

#endif