#include "TextDisplayDataModel.hpp"

TextDisplayDataModel::
TextDisplayDataModel()
  : _label(new QLabel("Resulting Text"))
{
  _label->setMargin(3);
}


unsigned int
TextDisplayDataModel::
nPorts(PortType portType) const
{
  unsigned int result;

  if (portType == PortType::In)
    result = 2;
  else
    result = 0;

  return result;
}


NodeDataType
TextDisplayDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextDisplayDataModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}
