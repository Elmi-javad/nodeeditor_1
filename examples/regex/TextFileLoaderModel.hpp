#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include "TextData.hpp"

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextFileLoaderModel : public NodeDataModel
{
  Q_OBJECT

public:
	TextFileLoaderModel();

  virtual
  ~TextFileLoaderModel() {}

public:

  QString
  caption() const override
  { return QString(""); }

  QString
  name() const override { return QString("TextFileLoaderModel"); }

public:

  virtual QString
  modelName() const
  { return QString(""); }

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override
  { }

  QWidget *
  embeddedWidget() override { return _label; }

  bool
  resizable() const override { return true; }

protected:

  bool
  eventFilter(QObject *object, QEvent *event) override;

private:

  QLabel * _label;
  QLineEdit * _lineEdit;
  QString _textContent;
};
