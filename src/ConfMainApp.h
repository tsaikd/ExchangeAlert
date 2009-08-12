#ifndef _EXCHANGEALERT_QCONFMAINAPP_H
#define _EXCHANGEALERT_QCONFMAINAPP_H

#include "stable.h"

class QConfMainApp : public QObject
{
private:
	void _init();
public:
	QConfMainApp(QObject* parent = NULL)
		:	QObject(parent)
	{ _init(); }
	~QConfMainApp() { save(); }
	QConfMainApp& save();

	QSettings* m_conf;			// app conf
	QWidget* m_mainWidget;		// app conf
	bool	m_closing;			// app conf
	bool	m_initHideWindow;

	bool	m_enableTimeLimit;
	int		m_refreshTimer;
	bool	m_USEnable;
	double	m_USDollar;
	double	m_USDollarLast;

protected:
	QMap<QString, QVariant> m_mapConfDefValue;
};

#endif//_EXCHANGEALERT_QCONFMAINAPP_H
