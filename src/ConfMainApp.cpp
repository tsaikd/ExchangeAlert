#include "ConfMainApp.h"

#define LOAD_CONFIG(var, defvalue) m_##var << conf.value(#var, defvalue); m_mapConfDefValue.insert(#var, defvalue);
#define SAVE_CONFIG(var) if (m_##var == m_mapConfDefValue.value(#var)) { conf.remove(#var); } else { conf.setValue(#var, m_##var); }

static const QVariant& operator << (bool& val, const QVariant& var) {
	val = var.toBool();
	return var;
}

static const QVariant& operator << (int& val, const QVariant& var) {
	val = var.toInt();
	return var;
}

void QConfMainApp::_init()
{
	DEWRP(QSettings, conf, m_conf, new QSettings(PROJNAME".ini", QSettings::IniFormat, this));
	m_mainWidget = NULL;
	m_closing = false;
	LOAD_CONFIG(initWithoutWindow, "1");
}

QConfMainApp::~QConfMainApp()
{
	save();
}

QConfMainApp& QConfMainApp::save()
{
	DECCP(QSettings, conf);

	SAVE_CONFIG(initWithoutWindow);

	return *this;
}
