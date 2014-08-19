#ifndef _FILENOTFOUNDEXCEPTION_H
#define _FILENOTFOUNDEXCEPTION_H

#include <QException>
#include <QString>

#include "IOException.h"

namespace exception {

/**
* Thrown to indicate that a method has been passed an illegal or inappropriate argument.
*/
class FileNotFoundException : public IOException {
public:
    /**
    * Creates a new FileNotFoundException.
    */
    FileNotFoundException();

    /**
    * Creates a new FileNotFoundException with an error message.
    *
    * @param msg descriptive error message
    */
    FileNotFoundException(QString msg);

    /**
    * Destroys the FileNotFoundException.
    */
    ~FileNotFoundException();

    virtual QString getName() const Q_DECL_OVERRIDE{return "FileNotFoundException";}
    virtual QString getMsg() const Q_DECL_OVERRIDE;
    virtual const char *what() const Q_DECL_OVERRIDE;

    virtual void FileNotFoundException::raise() const Q_DECL_OVERRIDE;
    virtual FileNotFoundException *clone() const Q_DECL_OVERRIDE;
private:
    const QString msg;
    const QByteArray asciiMsg;
};

}  // namespace exception

#endif  //_FILENOTFOUNDEXCEPTION_H