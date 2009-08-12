#ifndef _EXCHANGEALERT_WINMAINAPP_H
#define _EXCHANGEALERT_WINMAINAPP_H

#include "stable.h"

enum APPMSG {
	APPMSG_SHOWGUI,
};

class QSyncHttp;
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

	void resetTimer();
	void alarmUSDollar(double val);

public slots:
	void handleAppMessage(const QString& sMsg);

protected slots:
	void show();
	// for trayicon
	void trayActivated(QSystemTrayIcon::ActivationReason reason);

	void setConfChanged();
	void applyConf();
	void refreshWebPage();

protected:
	QConfMainApp* m_conf;
	QSyncHttp* m_http;
	QRegExp m_reUS;
	QSystemTrayIcon* m_tray;
	QRect m_rect; // used for restore minimized window geometry

	QCheckBox* m_chkInitHideWindow;

	QSpinBox* m_spinRefreshTimer;
	QTimer* m_timer;
	QLabel* m_lblCurUSDollar;
	QCheckBox* m_chkUSDollar;
	QDoubleSpinBox* m_spinUSDollar;
	QPushButton* m_btnApply;
};

#endif//_EXCHANGEALERT_WINMAINAPP_H
