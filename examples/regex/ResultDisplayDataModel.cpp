#include "ResultDisplayDataModel.hpp"

ResultDisplayDataModel::
ResultDisplayDataModel()
  : _label(new QLabel("Resulting Text")), _regex("([A-z])")
{
	_label->setMargin(3);
}


unsigned int
ResultDisplayDataModel::
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
ResultDisplayDataModel::
dataType(PortType, PortIndex portIndex) const
{
	if (portIndex == 0)
		return TextData().type();
	return RegexData().type();
}


std::shared_ptr<NodeData>
ResultDisplayDataModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}
