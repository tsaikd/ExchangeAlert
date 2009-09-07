#include "WinExt.h"

QWinExt::QWinExt(QWidget* parent/* = NULL*/)
	:	QWidget(parent)
{
	// delete object after close
	m_bDeleteAfterClose = false;
}

QWinExt::~QWinExt()
{
	// clear widget pointer
	clearPtrInList();
}

void QWinExt::addClearPtr(void** ptr)
{
	m_listClearPtr.append(ptr);
}

void QWinExt::clearPtrInList()
{
	while (!m_listClearPtr.isEmpty()) {
		*m_listClearPtr.takeFirst() = NULL;
	}
}

void QWinExt::setDeleteAfterClose(bool del)
{
	m_bDeleteAfterClose = del;
}

void QWinExt::closeEvent(QCloseEvent* e)
{
	if (m_bDeleteAfterClose) {
		deleteLater();
	}
	return QWidget::closeEvent(e);
}
