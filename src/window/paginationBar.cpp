#include "paginationBar.h"
#include "paginationButton.h"
#include "xmlRead.h"
#include "dataPool.h"

#include <cassert>
#include <QLayout>
#include <QButtonGroup>
#include <QStackedLayout>
#include <QVector>

struct PaginationBar::PaginationBarPrivate
{
	QStackedLayout * layout;
	QVector<QButtonGroup *> * vector;
};

PaginationBar::PaginationBar(QFrame * _parent) :
	QFrame(_parent),
	data(new PaginationBarPrivate)
{
	setObjectName("PaginationBar");
	setMinimumWidth(120);
	setMaximumWidth(120);

	data->layout = new QStackedLayout;
	data->vector = new QVector<QButtonGroup *>;

	setLayout(data->layout);
}

PaginationBar::~PaginationBar()
{
	delete data;
}

void PaginationBar::loadConfig(const QString & _path)
{
	assert(!_path.isEmpty());

	XmlRead xmlRead;

	xmlRead.loadFile(_path);

	QDomElement root = xmlRead.rootElement();

	connect(DataPool::internalDataMap()->value(root.attribute("navigationData")),
		SIGNAL(signalDataUpdata(const QString &)),
		this,
		SLOT(slotNavigationChange(const QString &)));

	QDomElement element = root.firstChildElement();

	PaginationButton * button = nullptr;
	QButtonGroup * group = nullptr;

	while (!element.isNull())
	{
		QWidget * widget = new QWidget;
		QVBoxLayout * layout = new QVBoxLayout;
		layout->setMargin(0);
		layout->setSpacing(0);
		layout->setAlignment(Qt::AlignTop | Qt::AlignRight);
		widget->setLayout(layout);

		QDomElement node = element.firstChildElement();

		group = new QButtonGroup;
		data->vector->push_back(group);

		for (size_t i = 0; !node.isNull(); i++)
		{
			button = new PaginationButton;
			button->setText(node.attribute("text"));
			layout->addWidget(button);
			group->addButton(button, i);
			node = node.nextSiblingElement();
		}
		group->button(0)->setChecked(true);
		data->layout->addWidget(widget);
		element = element.nextSiblingElement();
	}

}

void PaginationBar::slotNavigationChange(const QString & _value)
{
	data->layout->setCurrentIndex(_value.toInt());
}