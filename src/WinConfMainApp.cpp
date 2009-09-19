#include "WinConfMainApp.h"

#include "ConfMainApp.h"

QWinConfMainApp::QWinConfMainApp(QConfMainApp* pConf, QWidget* parent/* = NULL*/)
	:	m_conf(pConf)
	,	QWinExt(parent)
{
	DECCP(QConfMainApp, conf);

	setWindowFlags(windowFlags() | Qt::Window);
	setDeleteAfterClose(true);

	QVBoxLayout* lot = new QVBoxLayout();
	{
		DEWRV(QCheckBox*, chk, m_chkInitHideWindow, new QCheckBox(this));
		chk->setText(tr("Hide window when start"));
		chk->setChecked(conf.m_initHideWindow);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
		lot->addWidget(chk);
	}
	{
		DEWRV(QCheckBox*, chk, m_chkHideStatusBar, new QCheckBox(this));
		chk->setText(tr("Hide status bar"));
		chk->setChecked(conf.m_hideStatusBar);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
		lot->addWidget(chk);
	}
	{
		DEWRV(QCheckBox*, chk, m_chkEnableTimeLimit, new QCheckBox(this));
		chk->setText(tr("Only update from internet in trading time"));
		chk->setChecked(conf.m_enableTimeLimit);
		connect(chk, SIGNAL(stateChanged(int)), this, SLOT(setConfChanged()));
		lot->addWidget(chk);
	}
	{
		QHBoxLayout* lot2 = new QHBoxLayout();
		{
			QLabel* lbl = new QLabel(this);
			lbl->setText(tr("Refresh time(sec):"));
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
			DEWRV(QPushButton*, btn, m_btnApply, new QPushButton(this));
			btn->setText(tr("&Apply"));
			btn->setEnabled(false);
			connect(btn, SIGNAL(clicked()), this, SLOT(applyConf()));
			lot2->addWidget(btn);
		}
		{
			QPushButton* btn = new QPushButton(this);
			btn->setText(tr("&Close"));
			connect(btn, SIGNAL(clicked()), this, SLOT(close()));
			lot2->addWidget(btn);
		}
		lot->addLayout(lot2);
	}
	setLayout(lot);
}

void QWinConfMainApp::setConfChanged()
{
	m_btnApply->setEnabled(true);
}

void QWinConfMainApp::applyConf()
{
	DECCP(QConfMainApp, conf);

	m_btnApply->setEnabled(false);

	conf.m_initHideWindow = (m_chkInitHideWindow->checkState() == Qt::Checked) ? true : false;
	conf.m_hideStatusBar = (m_chkHideStatusBar->checkState() == Qt::Checked) ? true : false;

	conf.m_enableTimeLimit = (m_chkEnableTimeLimit->checkState() == Qt::Checked) ? true : false;
	conf.m_refreshTimer = m_spinRefreshTimer->value();

	conf.save();
	emit(sigApplyConf());
}
