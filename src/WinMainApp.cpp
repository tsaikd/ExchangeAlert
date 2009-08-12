#include "WinMainApp.h"

#include "ConfMainApp.h"
#include "QSyncHttp.h"

void QWinMainApp::_init()
{
	DEWRP(QConfMainApp, conf, m_conf, new QConfMainApp(this));
	m_http = new QSyncHttp(this);

	{
		DECRV(QRegExp, re, m_reUS);
		re.setMinimal(true);
		re.setPattern("USD.*(\\d+\\.\\d+)</td>");
	}

	// Tray Icon
	DEWRP(QSystemTrayIcon, tray, m_tray, new QSystemTrayIcon(this));
	tray.setIcon(QIcon(":/icon/ExchangeAlert.ico"));
	connect(&tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
	{	// Tray menu
		QMenu* menu = new QMenu(this);
		menu->addAction(tr("&Quit"), this, SLOT(close()));
		tray.setContextMenu(menu);
	}

	DEWRV(QTimer*, timer, m_timer, new QTimer(this));
	connect(timer, SIGNAL(timeout()), this, SLOT(refreshWebPage()));

	QVBoxLayout* lot = new QVBoxLayout();
	{
		DEWRV(QCheckBox*, chk, m_chkInitHideWindow, new QCheckBox(this));
		chk->setText(tr("Hide window when start"));
		chk->setChecked(conf.m_initHideWindow);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
		lot->addWidget(chk);
	}
	{
		QHBoxLayout* lot2 = new QHBoxLayout();
		{
			QLabel* lbl = new QLabel(this);
			lbl->setText(tr("Refresh time:"));
			lot2->addWidget(lbl);
		}
		{
			DEWRV(QSpinBox*, spin, m_spinRefreshTimer, new QSpinBox(this));
			spin->setRange(15, 3600);
			spin->setSingleStep(15);
			spin->setValue(conf.m_refreshTimer);
			connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setConfChanged()));
			lot2->addWidget(spin);
		}
		lot->addLayout(lot2);
	}
	{
		QHBoxLayout* lot2 = new QHBoxLayout();
		{
			DEWRV(QCheckBox*, chk, m_chkUSDollar, new QCheckBox(this));
			chk->setText(tr("US dollar:"));
			chk->setChecked(conf.m_USEnable);
			connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
			lot2->addWidget(chk);
		}
		{
			DEWRV(QLabel*, lbl, m_lblCurUSDollar, new QLabel(this));
			lbl->setText(QString::number(conf.m_USDollarLast));
			lot2->addWidget(lbl);
		}
		{
			DEWRV(QDoubleSpinBox*, spin, m_spinUSDollar, new QDoubleSpinBox(this));
			spin->setDecimals(3);
			spin->setRange(0, 9999);
			spin->setSingleStep(0.005);
			spin->setValue(conf.m_USDollar);
			connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setConfChanged()));
			lot2->addWidget(spin);
		}
		lot->addLayout(lot2);
	}
	{
		QHBoxLayout* lot2 = new QHBoxLayout();
		{
			DEWRV(QPushButton*, btn, m_btnApply, new QPushButton(this));
			btn->setText(tr("&Apply"));
			btn->setEnabled(false);
			connect(btn, SIGNAL(clicked()), this, SLOT(applyConf()));
			lot2->addWidget(btn);
		}
		{
			QPushButton* btn = new QPushButton(this);
			btn->setText(tr("&Quit"));
			connect(btn, SIGNAL(clicked()), this, SLOT(close()));
			lot2->addWidget(btn);
		}
		lot->addLayout(lot2);
	}
	setLayout(lot);

	resetTimer();
	if (conf.m_initHideWindow) {
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

void QWinMainApp::resetTimer()
{
	DECCP(QConfMainApp, conf);
	DECCV(QTimer*, timer);
	timer->stop();

	if (conf.m_USEnable) {
		timer->start(conf.m_refreshTimer*1000);
		QTimer::singleShot(2000, this, SLOT(refreshWebPage()));
	}
}

void QWinMainApp::alarmUSDollar(double val)
{
	QMessageBox::information(this, PROJNAME"App", tr("US Dollar reached %1").arg(val, 0, 'g', 6));
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

void QWinMainApp::setConfChanged()
{
	m_btnApply->setEnabled(true);
}

void QWinMainApp::applyConf()
{
	DECCP(QConfMainApp, conf);

	m_btnApply->setEnabled(false);

	conf.m_initHideWindow = (m_chkInitHideWindow->checkState() == Qt::Checked) ? true : false;

	conf.m_refreshTimer = m_spinRefreshTimer->value();
	conf.m_USEnable = (m_chkUSDollar->checkState() == Qt::Checked) ? true : false;
	conf.m_USDollar = m_spinUSDollar->value();

	conf.save();
	resetTimer();
}

void QWinMainApp::refreshWebPage()
{
	if (QDate::currentDate().dayOfWeek() >= Qt::Saturday)
		return;
	if (QTime::currentTime().hour() < 8)
		return;
	if (QTime::currentTime().hour() > 16)
		return;

	DECCP(QConfMainApp, conf);
	DECCP(QSyncHttp, http);
	DECOV(bool, conf, USEnable);

	if (USEnable) {
		QBuffer buf;
		http.syncSetHost("rate.bot.com.tw");
		http.syncGet("/Pages/Static/UIP003.zh-TW.htm", &buf);
		QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		QString page = codec->toUnicode(buf.data());

		double val = 0;
		int pos = 0;
		DECRV(QRegExp, re, m_reUS);
		while ((pos = re.indexIn(page, pos)) != -1) {
			val = re.cap(1).toDouble();
			break;
		}

		if (val != 0) {
			DECOV(double, conf, USDollar);
			DECOV(double, conf, USDollarLast);
			if (USDollarLast == 0) {
				if (val == USDollar) {
					USEnable = false;
					alarmUSDollar(val);
				}
			} else {
				if ( (USDollarLast >= USDollar) && (val <= USDollar) ) {
					USEnable = false;
					alarmUSDollar(val);
				} else if ( (USDollarLast <= USDollar) && (val >= USDollar) ) {
					USEnable = false;
					alarmUSDollar(val);
				}
			}
			USDollarLast = val;
			conf.save();

			m_lblCurUSDollar->setText(QString::number(val, 'g', 6));
		}
	}
}
