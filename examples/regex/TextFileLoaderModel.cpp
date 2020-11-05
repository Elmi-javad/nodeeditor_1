#include "TextFileLoaderModel.hpp"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>
#include <QTextStream>

TextFileLoaderModel::
TextFileLoaderModel()
  : _label(new QLabel("Double click to load text"))
{
  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

  QFont f = _label->font();
  f.setBold(true);
  f.setItalic(true);

  _label->setFont(f);

  _label->setMargin(3);

  _label->installEventFilter(this);
}


unsigned int
TextFileLoaderModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


bool
TextFileLoaderModel::
eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

    if (event->type() == QEvent::MouseButtonPress)
    {

      QString fileName =
        QFileDialog::getOpenFileName(nullptr,
                                     tr("Open Text File"),
                                     QDir::homePath(),
                                     tr("Text Files (*.txt *.doc *.docx)"));

	  QFile file(fileName);
	  if (!file.open(QFile::ReadOnly | QFile::Text))
	  {
		  _label->setText("Can not open file!");
	  }
	  else
	  {
		  QTextStream textStream(&file);
		  _label->setText(fileName);
		  _textContent = textStream.readAll();
		  file.close();
	  }
	  _label->adjustSize();

      Q_EMIT dataUpdated(0);

      return true;
    }
  }

  return false;
}


NodeDataType
TextFileLoaderModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextFileLoaderModel::
outData(PortIndex)
{
  return std::make_shared<TextData>(_textContent);
}
