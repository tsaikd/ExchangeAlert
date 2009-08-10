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
	~QConfMainApp();
	QConfMainApp& save();

	QSettings* m_conf;
	QWidget* m_mainWidget;
	bool	m_closing;
	bool	m_initWithoutWindow;					// ini conf

protected:
	QMap<QString, QVariant> m_mapConfDefValue;
};

#endif//_EXCHANGEALERT_QCONFMAINAPP_H
