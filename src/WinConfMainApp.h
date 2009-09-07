#ifndef _EXCHANGEALERT_WINCONFMAINAPP_H
#define _EXCHANGEALERT_WINCONFMAINAPP_H

#include "stable.h"

#include "WinExt.h"

class QConfMainApp;

class QWinConfMainApp : public QWinExt
{
	Q_OBJECT
public:
	QWinConfMainApp(QConfMainApp* pConf, QWidget* parent = NULL);

public slots:
	void setConfChanged();
	void applyConf();

signals:
	void sigApplyConf();

protected:
	QConfMainApp* m_conf;

	QCheckBox* m_chkInitHideWindow;
	QCheckBox* m_chkEnableTimeLimit;
	QSpinBox* m_spinRefreshTimer;

	QPushButton* m_btnApply;
};

#endif//_EXCHANGEALERT_WINCONFMAINAPP_H
