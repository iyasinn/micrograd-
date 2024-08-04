#include "Value.h"
#include <memory>

Value::Value(double valueIn, const std::vector<std::shared_ptr<Value>> &prevIn,
             OPERATION operationIn)
    : value(valueIn), prev(prevIn), operation(operationIn) {}

Value::Value(double valueIn) : value(valueIn) {}

std::string Value::enumToString(OPERATION operationIn) const {
  switch (operationIn) {
  case ADD:
    return "ADD";
  case MULT:
    return "MULT";
  case SUB:
    return "SUB";
  case NEG:
    return "NEG";
  case NONE:
    return "NONE";
  }
}

std::string Value::getString() const {
  std::string final = "";
  final += "[VAL=" + std::to_string(value) + ":OP=" + enumToString(operation) +
           ":PREV= (";

  for (ValuePtr ptr : prev) {
    final += ptr->getString();
  }
  final += ")]";
  return final;
}
void Value::forwardPass() {

  for (auto &p : prev) {
    p->forwardPass();
  }

  switch (operation) {
  case ADD:
    value = prev[0]->value + prev[1]->value;
    break;
  case MULT:
    value = prev[0]->value * prev[1]->value;
    break;
  case SUB:
    value = prev[0]->value - prev[1]->value;
    break;
  case NEG:
    value = -prev[0]->value;
    break;
  case NONE:
    break;
  }
}
