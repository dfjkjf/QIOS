﻿#include "iniRead.h"

#include <QSettings>
#include <QString>

struct IniRead::IniReadPrivate
{
	QSettings * iniRead;
};

IniRead::IniReadPrivate * IniRead::data = new IniRead::IniReadPrivate;

IniRead::IniRead(QObject * _prent) :
	QObject(_prent)
{
	data->iniRead = nullptr;
}

IniRead::~IniRead()
{

}

void IniRead::loadIni(const QString & _path)
{
	if (data->iniRead == nullptr)
	{
		data->iniRead = new QSettings(_path, QSettings::IniFormat);
	}
	else
	{
		return;
	}
}

QSize IniRead::windowFormSize()
{
	return QSize(data->iniRead->value("/windowFormSize/width").toInt(),
		data->iniRead->value("/windowFormSize/height").toInt());
}

QStringList IniRead::dabaBaseMessage()
{
	return QStringList() << data->iniRead->value("/sqlDatabase/hostName").toString()
		<< data->iniRead->value("/sqlDatabase/port").toString()
		<< data->iniRead->value("/sqlDatabase/databaseName").toString()
		<< data->iniRead->value("/sqlDatabase/userName").toString()
		<< data->iniRead->value("/sqlDatabase/password").toString();
}
