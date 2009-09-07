#ifndef _EXCHANGEALERT_WINMAINAPP_H
#define _EXCHANGEALERT_WINMAINAPP_H

#include "stable.h"

enum APPMSG {
	APPMSG_SHOWGUI,
};

class QSyncHttp;
class QConfMainApp;
class QWinConfMainApp;

class QWinMainApp : public QWidget
{
	Q_OBJECT
private:
	void _init();
public:
	QWinMainApp() { _init(); }

	static bool numBetweenNums(double num, double base1, double base2, bool bIncEq = true);

protected:
	virtual void changeEvent(QEvent* e);

	void resetTimer();
	void alarmUSDollar(double val);

public slots:
	void handleAppMessage(const QString& sMsg);

protected slots:
	void show();
	// for trayicon
	void trayActivated(QSystemTrayIcon::ActivationReason reason);

	void showWinConf();
	void setConfChanged();
	void applyConf();
	void refreshWebPage();

protected:
	QConfMainApp* m_conf;
	QWinConfMainApp* m_winConf;
	QSyncHttp* m_http;
	QRegExp m_reUS;
	QSystemTrayIcon* m_tray;
	QRect m_rect; // used for restore minimized window geometry

	QTimer* m_timer;
	QLabel* m_lblCurUSDollar;
	QCheckBox* m_chkUSDollar;
	QDoubleSpinBox* m_spinUSDollar;
	QCheckBox* m_chkUSDollar2;
	QDoubleSpinBox* m_spinUSDollar2;
	QPushButton* m_btnApply;

	QStatusBar* m_bar;
};

#endif//_EXCHANGEALERT_WINMAINAPP_H
