#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "TextData.hpp"
#include "RegexData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ResultDisplayDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  ResultDisplayDataModel();

  virtual
  ~ResultDisplayDataModel() {}

public:

  QString
  caption() const override
  { return QString("Regex Display"); }

  bool
  captionVisible() const override { return false; }

  static QString
  Name()
  { return QString("ResultDisplayDataModel"); }

  QString
  name() const override
  { return ResultDisplayDataModel::Name(); }

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

    if (data)
    {
		if (portIndex == 0)
		{
			auto textData = std::dynamic_pointer_cast<TextData>(data);
			_inputText = textData->text();
		}
		else
		{
			_regex = std::dynamic_pointer_cast<RegexData>(data)->regex();
			if (_regex.isEmpty())
			{
				_label->setText("Regex box is empty!");
				_label->adjustSize();
				return;
			}
		}

		QStringList outputList;
		int pos = 0;
		while ((pos = _regex.indexIn(_inputText, pos)) != -1) {
			outputList << _regex.cap(1);
			pos += _regex.matchedLength();
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
  QRegExp _regex;
};
