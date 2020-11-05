#include "RegexSourceDataModel.hpp"

RegexSourceDataModel::
RegexSourceDataModel()
  : _lineEdit(new QLineEdit(""))
{
  connect(_lineEdit, &QLineEdit::textEdited,
          this, &RegexSourceDataModel::onTextEdited);
}


unsigned int
RegexSourceDataModel::
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


void
RegexSourceDataModel::
onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  Q_EMIT dataUpdated(0);
}


NodeDataType
RegexSourceDataModel::
dataType(PortType, PortIndex) const
{
  return RegexData().type();
}


std::shared_ptr<NodeData>
RegexSourceDataModel::
outData(PortIndex)
{
  QString regexText = std::make_shared<TextData>(_lineEdit->text())->text();
  QRegExp rxPattern(regexText);
  return std::make_shared<RegexData>(rxPattern);
}
