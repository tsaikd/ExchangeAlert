/**
 * @file WinBase.h
 * @brief Extend QWidget class for QT4 library
 * @author tsaikd@gmail.com
 * @version 1.0.0.1
 * @date 2009/09/07
 **/

#ifndef _GENERAL_WINBASE_H
#define _GENERAL_WINBASE_H

#include <QtCore/QList>
#include <QtGui/QWidget>

class QWinExt : public QWidget
{
	Q_OBJECT
public:
	QWinExt(QWidget* parent = NULL);
	~QWinExt();

// clear pointer
public:
	void addClearPtr(void** ptr);
public slots:
	void clearPtrInList();
protected:
	QList<void**> m_listClearPtr;

// delete object after close
public:
	void setDeleteAfterClose(bool del);
protected:
	virtual void closeEvent(QCloseEvent* e);
protected:
	bool m_bDeleteAfterClose;
};

#endif//_GENERAL_WINBASE_H
