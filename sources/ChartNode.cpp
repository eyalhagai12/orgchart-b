#include "ChartNode.hpp"

using ariel::ChartNode;

size_t ChartNode::size() { return this->data.size(); }

std::string ChartNode::get_data() { return this->data; }

void ChartNode::set_data(const std::string &data) { this->data = data; }

std::vector<ChartNode *> ChartNode::get_children() { return this->children; }

void ChartNode::add_child(ChartNode *node) { this->children.push_back(node); }

size_t ChartNode::length() { return this->data.length(); }

char ChartNode::at(size_t i) { return this->data.at(i); }

std::ostream &ariel::operator<<(std::ostream &out, const ChartNode &node)
{
    out << node.data;
    return out;
}

std::ostream &ariel::operator<<(std::ostream &out, const ChartNode *node)
{
    out << node->data;
    return out;
}
