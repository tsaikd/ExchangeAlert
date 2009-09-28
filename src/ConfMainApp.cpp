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

static const QVariant& operator << (double& val, const QVariant& var) {
	val = var.toDouble();
	return var;
}

void QConfMainApp::_init()
{
	DEWRP(QSettings, conf, m_conf, new QSettings(QString("%1.ini").arg(qAppName()), QSettings::IniFormat, this));
	m_mainWidget = NULL;
	m_closing = false;

	LOAD_CONFIG(initHideWindow, "0");
	LOAD_CONFIG(layoutStyle, "0");
	LOAD_CONFIG(hideStatusBar, "0");
	LOAD_CONFIG(dollarFontSize, "15");

	LOAD_CONFIG(enableTimeLimit, "1");
	LOAD_CONFIG(refreshTimer, "60");
	LOAD_CONFIG(USDollarLast, "0");
	LOAD_CONFIG(USEnable, "0");
	LOAD_CONFIG(USDollar, "0");
	LOAD_CONFIG(USEnable2, "0");
	LOAD_CONFIG(USDollar2, "0");
}

QConfMainApp& QConfMainApp::save()
{
	DECCP(QSettings, conf);

	SAVE_CONFIG(initHideWindow);
	SAVE_CONFIG(layoutStyle);
	SAVE_CONFIG(hideStatusBar);
	SAVE_CONFIG(dollarFontSize);

	SAVE_CONFIG(enableTimeLimit);
	SAVE_CONFIG(refreshTimer);
	SAVE_CONFIG(USDollarLast);
	SAVE_CONFIG(USEnable);
	SAVE_CONFIG(USDollar);
	SAVE_CONFIG(USEnable2);
	SAVE_CONFIG(USDollar2);

	return *this;
}
