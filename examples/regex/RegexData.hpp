#pragma once

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class RegexData : public NodeData
{
public:

  RegexData() {}

  RegexData(QRegExp const &text)
    : _regex(text)
  {}

  NodeDataType type() const override
  { return NodeDataType {"regex", "Regex"}; }

  QRegExp regex() const { return _regex; }

private:

  QRegExp _regex;
};
