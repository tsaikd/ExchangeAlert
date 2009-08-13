#include "QSyncHttp.h"

#include <QBuffer>
#include <QUrl>

/// send GET request and wait until finished
bool QSyncHttp::syncGet(const QString& path, QIODevice* to/* = 0*/)
{
	/// start the request and store the requestID
	requestID = get(path, to);
	/// block until the request is finished
	loop.exec();
	/// return the request status
	return status;
}

/// send POST request and wait until finished
bool QSyncHttp::syncPost(const QString& path, QIODevice* data, QIODevice* to/* = 0*/)
{
	/// start the request and store the requestID
	requestID = post(path, data, to);
	/// block until the request is finished
	loop.exec();
	/// return the request status
	return status;
}

bool QSyncHttp::syncPost(const QString& path, const QByteArray& data, QIODevice* to/* = 0*/)
{
	/// create io device from QByteArray
	QBuffer buffer;
	buffer.setData(data);
	return syncPost(path, &buffer, to);
}

bool QSyncHttp::syncRequest(const QHttpRequestHeader& header, QIODevice* data/* = 0*/, QIODevice* to/* = 0*/)
{
	/// start the request and store the requestID
	requestID = request(header, data, to);
	/// block until the request is finished
	loop.exec();
	/// return the request status
	return status;
}

bool QSyncHttp::syncRequest(const QHttpRequestHeader& header, const QByteArray& data, QIODevice* to/* = 0*/)
{
	QBuffer buffer;
	buffer.setData(data);
	return syncRequest(header, &buffer, to);
}

bool QSyncHttp::syncSetHost(const QString& hostName, quint16 port/* = 80*/)
{
	/// start the request and store the requestID
	requestID = setHost(hostName, port);
	/// block until the request is finished
	loop.exec();
	/// return the request status
	return status;
}

bool QSyncHttp::syncSetUser(const QString& userName, const QString& password/* = QString()*/)
{
	/// start the request and store the requestID
	requestID = setUser(userName, password);
	/// block until the request is finished
	loop.exec();
	/// return the request status
	return status;
}

QHttpResponseHeader QSyncHttp::syncTest(const QHttpRequestHeader& header)
{
	connect(this, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(abort()));
	syncRequest(header);
	disconnect(this, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(abort()));
	return lastResponse();
}

QHttpResponseHeader QSyncHttp::syncTest(const QString& path)
{
	connect(this, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(abort()));
	syncGet(path);
	disconnect(this, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(abort()));
	return lastResponse();
}

QHttpResponseHeader QSyncHttp::syncTestOnce(const QString& sUrl)
{
	QUrl url(sUrl);

	QHttpRequestHeader req("GET", url.toEncoded(QUrl::RemoveScheme | QUrl::RemoveAuthority));
	req.setValue("Host", url.encodedHost());

	QSyncHttp http;
	http.setHost(url.encodedHost(), (url.scheme() == "https") ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, url.port(80));
	if (!url.userInfo().isEmpty()) {
		QString userinfo = QString("%1:%2").arg(url.encodedUserName().constData()).arg(url.encodedPassword().constData());
		req.setValue("Authorization", QString("Basic %1").arg(userinfo.toUtf8().toBase64().constData()));
	}

	return http.syncTest(req);
}

void QSyncHttp::finished(int idx, bool err)
{
	/// check to see if it¡¦s the request we made
	if (idx != requestID)
		return;
	/// set status of the request
	status = !err;
	/// end the loop
	loop.exit();
}
