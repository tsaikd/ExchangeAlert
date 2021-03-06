#include "WinMainApp.h"

#include "ConfMainApp.h"
#include "WinConfMainApp.h"
#include "QSyncHttp.h"

void QWinMainApp::_init()
{
	setWindowTitle(QString("%1 %2").arg(qAppName()).arg(qApp->applicationVersion()));
	DEWRP(QConfMainApp, conf, m_conf, new QConfMainApp(this));
	{
		QAction* act = new QAction(this);
		act->setShortcut(Qt::Key_Escape);
		addAction(act);
		connect(act, SIGNAL(triggered()), this, SLOT(close()));
	}
	m_winConf = NULL;

	m_http = new QSyncHttp(this);

	{
		DECRV(QRegExp, re, m_reUS);
		re.setMinimal(true);
		re.setPattern("USD.*(\\d+\\.\\d+)</td>.*>(\\d+\\.\\d+)</td>.*>(\\d+\\.\\d+)</td>.*>(\\d+\\.\\d+)</td>");
	}

	// Tray Icon
	DEWRP(QSystemTrayIcon, tray, m_tray, new QSystemTrayIcon(this));
	tray.setToolTip(windowTitle());
	tray.setIcon(QIcon(":/icon/ExchangeAlert2.png"));
	connect(&tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
	{	// Tray menu
		QMenu* menu = new QMenu(this);
		menu->addAction(tr("&Quit"), this, SLOT(close()));
		tray.setContextMenu(menu);
	}

	DEWRV(QTimer*, timer, m_timer, new QTimer(this));
	connect(timer, SIGNAL(timeout()), this, SLOT(refreshWebPage()));

	// Init UI widget
	QLabel* lblUSDollar = new QLabel(tr("US dollar:"), this);;
	DEWCV(QLabel*, lblCurUSDollar, new QLabel(QString::number(conf.m_USDollarLast), this));
	DEWCV(QCheckBox*, chkUSDollar, new QCheckBox(this));
	{
		QCheckBox*& chk = chkUSDollar;
		chk->setChecked(conf.m_USEnable);
		chk->setMaximumWidth(15);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
	}
	DEWCV(QDoubleSpinBox*, spinUSDollar, new QDoubleSpinBox(this));
	{
		QDoubleSpinBox*& spin = spinUSDollar;
		spin->setDecimals(3);
		spin->setRange(0, 9999);
		spin->setSingleStep(0.005);
		spin->setValue(conf.m_USDollar);
		connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setConfChanged()));
	}
	DEWCV(QCheckBox*, chkUSDollar2, new QCheckBox(this));
	{
		QCheckBox*& chk = chkUSDollar2;
		chk->setChecked(conf.m_USEnable2);
		chk->setMaximumWidth(15);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
	}
	DEWCV(QDoubleSpinBox*, spinUSDollar2, new QDoubleSpinBox(this));
	{
		QDoubleSpinBox*& spin = spinUSDollar2;
		spin->setDecimals(3);
		spin->setRange(0, 9999);
		spin->setSingleStep(0.005);
		spin->setValue(conf.m_USDollar2);
		connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setConfChanged()));
	}
	DEWCV(QStatusBar*, bar, new QStatusBar(this));
	{
		bar->setSizeGripEnabled(false);
	}
	DEWCV(QPushButton*, btnApply, new QPushButton(this));
	{
		QPushButton*& btn = btnApply;
		btn->setEnabled(false);
		connect(btn, SIGNAL(clicked()), this, SLOT(applyConf()));
	}
	QPushButton* btnConfig = new QPushButton(this);
	{
		QPushButton*& btn = btnConfig;
		connect(btn, SIGNAL(clicked()), this, SLOT(showWinConf()));
	}
	QPushButton* btnQuit = new QPushButton(this);
	{
		QPushButton*& btn = btnQuit;
		connect(btn, SIGNAL(clicked()), this, SLOT(close()));
	}

	switch (conf.m_layoutStyle) {
	case 1:
	case 2:
		{
			QPushButton*& btn = btnApply;
			btn->setIcon(QIcon(":/icon/apply.png"));
			btn->setToolTip(tr("&Apply"));
		}
		{
			QPushButton*& btn = btnConfig;
			btn->setIcon(QIcon(":/icon/config.png"));
			btn->setToolTip(tr("Extra &Config"));
		}
		{
			SAFE_DELETE(btnQuit);
		}
		break;
	default:
		{
			QPushButton*& btn = btnApply;
			btn->setText(tr("&Apply"));
		}
		{
			QPushButton*& btn = btnConfig;
			btn->setText(tr("Extra &Config"));
		}
		{
			QPushButton*& btn = btnQuit;
			btn->setText(tr("&Quit"));
		}
		break;
	}

	// Setup UI layout
	switch (conf.m_layoutStyle) {
	case 1:
		{
			QVBoxLayout* lot = new QVBoxLayout();
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(lblUSDollar);
				lot2->addWidget(lblCurUSDollar);
				lot2->addWidget(chkUSDollar);
				lot2->addWidget(spinUSDollar);
				lot2->addWidget(chkUSDollar2);
				lot2->addWidget(spinUSDollar2);
				lot->addLayout(lot2);
			}
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(bar);
				lot2->addWidget(btnApply);
				lot2->addWidget(btnConfig);
				lot2->addWidget(btnQuit);
				lot->addLayout(lot2);
			}
			setLayout(lot);
		}
		break;
	case 2:
		{
			QVBoxLayout* lot = new QVBoxLayout();
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(lblUSDollar);
				lot2->addWidget(lblCurUSDollar);
				lot->addLayout(lot2);
			}
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(chkUSDollar);
				lot2->addWidget(spinUSDollar);
				lot->addLayout(lot2);
			}
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(chkUSDollar2);
				lot2->addWidget(spinUSDollar2);
				lot->addLayout(lot2);
			}
			{
				lot->addWidget(bar);
			}
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(btnApply);
				lot2->addWidget(btnConfig);
				lot->addLayout(lot2);
			}
			setLayout(lot);
		}
		break;
	default:
		{
			QVBoxLayout* lot = new QVBoxLayout();
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(lblUSDollar);
				lot2->addWidget(lblCurUSDollar);
				lot2->addWidget(chkUSDollar);
				lot2->addWidget(spinUSDollar);
				lot2->addWidget(chkUSDollar2);
				lot2->addWidget(spinUSDollar2);
				lot->addLayout(lot2);
			}
			{
				lot->addWidget(bar);
			}
			{
				QHBoxLayout* lot2 = new QHBoxLayout();
				lot2->addWidget(btnApply);
				lot2->addWidget(btnConfig);
				lot2->addWidget(btnQuit);
				lot->addLayout(lot2);
			}
			setLayout(lot);
		}
		break;
	}

	updateExtConf();
	resetTimer();
	if (conf.m_initHideWindow) {
		tray.show();
	} else {
		show();
	}
}

bool QWinMainApp::numBetweenNums(double num, double base1, double base2, bool bIncEq/* = true*/)
{
	int iNum = (int)((num * 10000 + 5) / 10);
	int iBase1 = (int)((base1 * 10000 + 5) / 10);
	int iBase2 = (int)((base2 * 10000 + 5) / 10);
	if (bIncEq) {
		if (iBase1 <= iNum && iNum <= iBase2)
			return true;
		if (iBase1 >= iNum && iNum >= iBase2)
			return true;
	} else {
		if (iBase1 < iNum && iNum < iBase2)
			return true;
		if (iBase1 > iNum && iNum > iBase2)
			return true;
	}
	return false;
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

	if (conf.m_USEnable || conf.m_USEnable2) {
		timer->start(conf.m_refreshTimer*1000);
		QTimer::singleShot(2000, this, SLOT(refreshWebPage()));
	}
}

void QWinMainApp::alarmUSDollar(double val)
{
	DECCP(QConfMainApp, conf);

	{
		DECRV(QCheckBox*, chk, m_chkUSDollar);
		disconnect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
		chk->setChecked(conf.m_USEnable);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
	}
	{
		DECRV(QCheckBox*, chk, m_chkUSDollar2);
		disconnect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
		chk->setChecked(conf.m_USEnable2);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
	}

	QMessageBox::information(this, qAppName(), tr("US Dollar reached %1").arg(val, 0, 'g', 6));
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

void QWinMainApp::showWinConf()
{
	DECCV(QWinConfMainApp*, winConf);
	if (winConf) {
		winConf->activateWindow();
		return;
	}

	winConf = new QWinConfMainApp(m_conf, this);
	winConf->addClearPtr((void**)&winConf);
	connect(winConf, SIGNAL(sigApplyConf()), this, SLOT(updateExtConf()));

	winConf->show();
}

void QWinMainApp::setConfChanged()
{
	m_btnApply->setEnabled(true);
}

void QWinMainApp::applyConf()
{
	DECCP(QConfMainApp, conf);

	m_btnApply->setEnabled(false);

	conf.m_USEnable = (m_chkUSDollar->checkState() == Qt::Checked) ? true : false;
	conf.m_USDollar = m_spinUSDollar->value();
	conf.m_USEnable2 = (m_chkUSDollar2->checkState() == Qt::Checked) ? true : false;
	conf.m_USDollar2 = m_spinUSDollar2->value();

	conf.save();
	resetTimer();
}

void QWinMainApp::updateExtConf()
{
	CDCCP(QConfMainApp, conf);

	{
		DECCP(QStatusBar, bar);
		if (conf.m_hideStatusBar) {
			bar.hide();
		} else {
			bar.show();
		}
	}
	{
		DECRV(QLabel*, lbl, m_lblCurUSDollar);
		QFont f("", conf.m_dollarFontSize);
		lbl->setFont(f);
	}
}

void QWinMainApp::refreshWebPage()
{
	DECCP(QStatusBar, bar);
	DECCP(QConfMainApp, conf);
	DECCP(QSyncHttp, http);
	DECOV(bool, conf, USEnable);
	DECOV(bool, conf, USEnable2);
	double val = 0;

	if (conf.m_enableTimeLimit) {
		if (QDate::currentDate().dayOfWeek() >= Qt::Saturday)
			return;
		if (QTime::currentTime().hour() < 8)
			return;
		if (QTime::currentTime().hour() > 16)
			return;
	}

	bar.showMessage(tr("Updating US dollar ..."));
	if (USEnable || USEnable2) {
		QBuffer buf;
		http.syncSetHost("rate.bot.com.tw");
		http.syncGet("/Pages/Static/UIP003.zh-TW.htm", &buf);
		QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		QString page = codec->toUnicode(buf.data());

		int pos = 0;
		DECRV(QRegExp, re, m_reUS);
		while ((pos = re.indexIn(page, pos)) != -1) {
			val = (re.cap(3).toDouble() + re.cap(4).toDouble()) / 2;
			break;
		}
	}

	if (val != 0) {
		DECOV(double, conf, USDollarLast);
		if (USEnable) {
			DECOV(double, conf, USDollar);
			if (USDollarLast == 0) {
				if (val == USDollar) {
					USEnable = false;
					alarmUSDollar(val);
				}
			} else {
				if (numBetweenNums(USDollar, val, USDollarLast)) {
					USEnable = false;
					alarmUSDollar(val);
				}
			}
		}
		if (USEnable2) {
			DECOV(double, conf, USDollar2);
			if (USDollarLast == 0) {
				if (val == USDollar2) {
					USEnable2 = false;
					alarmUSDollar(val);
				}
			} else {
				if (numBetweenNums(USDollar2, val, USDollarLast)) {
					USEnable2 = false;
					alarmUSDollar(val);
				}
			}
		}

		USDollarLast = val;
		conf.save();

		m_lblCurUSDollar->setText(QString::number(val, 'g', 6));
	}
	bar.showMessage(tr("Updated US dollar"), 2000);
}
