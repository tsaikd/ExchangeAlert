#ifndef _EXCHANGEALERT_WINMAINAPP_H
#define _EXCHANGEALERT_WINMAINAPP_H

#include "stable.h"

enum APPMSG {
	APPMSG_SHOWGUI,
};

class QConfMainApp;

class QWinMainApp : public QWidget
{
	Q_OBJECT
private:
	void _init();
public:
	QWinMainApp() { _init(); }

protected:
	virtual void closeEvent(QCloseEvent* e);
	virtual void changeEvent(QEvent* e);

public slots:
	void handleAppMessage(const QString& sMsg);

protected slots:
	void show();
	// for trayicon
	void trayActivated(QSystemTrayIcon::ActivationReason reason);

protected:
	QConfMainApp* m_conf;
	QSystemTrayIcon* m_tray;
	QRect m_rect; // used for restore minimized window geometry
};

#endif//_EXCHANGEALERT_WINMAINAPP_H
