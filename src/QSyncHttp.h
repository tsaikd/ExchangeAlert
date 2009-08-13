#ifndef _QSYNCHTTP_H
#define _QSYNCHTTP_H

#include <QHttp>
#include <QEventLoop>
#include <QHttpResponseHeader>

/**
 * Provide a synchronous api over QHttp
 * Uses a QEventLoop to block until the request is completed
 * @author Iulian M
 * @ref http://www.erata.net/qt-boost/synchronous-http-request/
 **/
class QSyncHttp: public QHttp
{
	Q_OBJECT

public:
	/// constructors
	QSyncHttp(QObject* parent=0)
		: QHttp(parent), requestID(-1), status(false)
	{
		///connect the requestFinished signal to our finished slot
		connect(this, SIGNAL(requestFinished(int,bool)), SLOT(finished(int,bool)));
	}

	QSyncHttp(const QString& hostName, quint16 port=80, QObject* parent=0)
		: QHttp(hostName, port, parent), requestID(-1), status(false)
	{
		///connect the requestFinished signal to our finished slot
		connect(this, SIGNAL(requestFinished(int,bool)), SLOT(finished(int,bool)));
	}

	bool syncGet(const QString& path, QIODevice* to = 0);
	bool syncPost(const QString& path, QIODevice* data, QIODevice* to = 0);
	bool syncPost(const QString& path, const QByteArray& data, QIODevice* to = 0);
	bool syncRequest(const QHttpRequestHeader& header, QIODevice* data = 0, QIODevice* to = 0);
	bool syncRequest(const QHttpRequestHeader& header, const QByteArray& data, QIODevice* to = 0);
	bool syncSetHost(const QString& hostName, quint16 port = 80);
	bool syncSetUser(const QString& userName, const QString& password = QString());
	QHttpResponseHeader syncTest(const QHttpRequestHeader& header);
	QHttpResponseHeader syncTest(const QString& path);
	static QHttpResponseHeader syncTestOnce(const QString& sUrl);

protected slots:
	virtual void finished(int idx, bool err);

private:
	/// id of current request
	int requestID;
	/// error status of current request
	bool status;
	/// event loop used to block until request finished
	QEventLoop loop;
};

#endif //_QSYNCHTTP_H
