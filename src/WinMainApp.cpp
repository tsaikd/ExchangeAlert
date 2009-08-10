#include "WinMainApp.h"

#include "ConfMainApp.h"

void QWinMainApp::_init()
{
	DEWRP(QConfMainApp, conf, m_conf, new QConfMainApp(this));

	// Tray Icon
	DEWRP(QSystemTrayIcon, tray, m_tray, new QSystemTrayIcon(this));
	tray.setIcon(QIcon(":/icon/ExchangeAlert.ico"));
	connect(&tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
	{	// Tray menu
		QMenu* menu = new QMenu(this);
		menu->addAction(tr("&Quit"), this, SLOT(close()));
		tray.setContextMenu(menu);
	}

	QVBoxLayout* lot = new QVBoxLayout();
	{
		QHBoxLayout* lot2 = new QHBoxLayout();
		{
			QLabel* lbl = new QLabel(this);
			lbl->setText(tr("US dollar:"));
			lot2->addWidget(lbl);

			QDoubleSpinBox* spin = new QDoubleSpinBox(this);
			spin->setDecimals(3);
			spin->setSingleStep(0.005);
			lot2->addWidget(spin);
		}
		lot->addLayout(lot2);
	}
	setLayout(lot);

	if (conf.m_initWithoutWindow) {
		tray.show();
	} else {
		show();
	}
}

void QWinMainApp::closeEvent(QCloseEvent* e)
{
	QWidget::closeEvent(e);
}

void QWinMainApp::changeEvent(QEvent* e)
{
	if (e->type() == QEvent::WindowStateChange) {
		if (e->spontaneous()) {
			if (isMinimized()) {
				DECCP(QSystemTrayIcon, tray);
				m_rect = geometry();
#if defined(Q_WS_WIN)
				setWindowFlags((windowFlags() | Qt::FramelessWindowHint) & (~Qt::Window));
#endif//defined(Q_WS_WIN)
				hide();
				tray.show();
			}
		}
	}
}

void QWinMainApp::handleAppMessage(const QString& sMsg)
{
	APPMSG msg = (APPMSG)sMsg.toInt();
	switch (msg) {
	case APPMSG_SHOWGUI:
		show();
/*
		raise();
		activateWindow();
//*/
		break;
	default:
		QTRACE() << "Unknown APPMSG:" << sMsg;
	}
}

void QWinMainApp::show()
{
	DECCP(QSystemTrayIcon, tray);
#if defined(Q_WS_WIN)
	setWindowFlags((windowFlags() | Qt::Window) & (~Qt::FramelessWindowHint));
#endif//defined(Q_WS_WIN)
	showNormal();
	activateWindow();
	tray.hide();
	if (m_rect.isValid())
		setGeometry(m_rect);

//	QWidget::show();
}

void QWinMainApp::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
//	DECCP(QSystemTrayIcon, tray);
	switch (reason) {
	case QSystemTrayIcon::Trigger:
		show();
/*
#if defined(Q_WS_WIN)
		setWindowFlags((windowFlags() | Qt::Window) & (~Qt::FramelessWindowHint));
#endif//defined(Q_WS_WIN)
		showNormal();
		activateWindow();
		tray.hide();
		if (m_rect.isValid())
			setGeometry(m_rect);
//*/
		break;
	default:
		break;
	}
}
