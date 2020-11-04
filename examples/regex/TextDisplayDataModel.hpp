#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "TextData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextDisplayDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  TextDisplayDataModel();

  virtual
  ~TextDisplayDataModel() {}

public:

  QString
  caption() const override
  { return QString("Text Display"); }

  bool
  captionVisible() const override { return false; }

  static QString
  Name()
  { return QString("TextDisplayDataModel"); }

  QString
  name() const override
  { return TextDisplayDataModel::Name(); }

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override
  {
    auto textData = std::dynamic_pointer_cast<TextData>(data);

    if (textData)
    {
		if (portIndex == 0)
		{
			_inputText = textData->text();
		}
		else
		{
			_regex = textData->text();
			if (_regex.isEmpty())
			{
				_regex = "No regex";
			}
		}

		QRegExp rxPattern(_regex);
		QStringList outputList;
		int pos = 0;
		while ((pos = rxPattern.indexIn(_inputText, pos)) != -1) {
			outputList << rxPattern.cap(1);
			pos += rxPattern.matchedLength();
		}
		if (outputList.isEmpty())
		{
			_label->setText("No match thing or invalid regex!");
		}
		else
		{
			_label->setText(outputList.join(", "));
		}
    }
    else
    {
      _label->clear();
    }

    _label->adjustSize();
  }

  QWidget *
  embeddedWidget() override { return _label; }

private:

  QLabel * _label;
  QString _inputText = "In the name of Allah";
  QString _regex = "(.)";
};
