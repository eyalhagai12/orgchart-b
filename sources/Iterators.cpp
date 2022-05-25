#include "OrgChart.hpp"
#include "ChartNode.hpp"

using ariel::ChartNode;
using ariel::OrgChart;

// ---------------------------------------------------------------------------------------------------------
// level order iterator
bool OrgChart::level_order_iterator::operator!=(const level_order_iterator &other) const
{
    return this->node != other.node;
}
OrgChart::level_order_iterator &OrgChart::level_order_iterator::operator++()
{
    if (!this->node_queue.empty())
    {
        this->node = this->node_queue.front();
        this->node_queue.pop();
    }
    else
    {
        this->node = nullptr;
    }

    if (this->node != nullptr)
    {
        for (ChartNode *child : this->node->get_children())
        {
            this->node_queue.push(child);
        }
    }

    return *this;
}
ChartNode *OrgChart::level_order_iterator::operator->() const { return this->node; }
std::string OrgChart::level_order_iterator::operator*() const
{
    std::string str = this->node->get_data();
    return str;
}
// ---------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------
// reverse level order iterator
bool OrgChart::reverse_level_order_iterator::operator!=(const reverse_level_order_iterator &other) const { return this->node != other.node; }
OrgChart::reverse_level_order_iterator &OrgChart::reverse_level_order_iterator::operator++()
{
    if (!this->node_stack.empty())
    {
        this->node = this->node_stack.top();
        this->node_stack.pop();
    }
    else
    {
        this->node = nullptr;
    }

    return *this;
}
ChartNode *OrgChart::reverse_level_order_iterator::operator->() const { return this->node; }
std::string OrgChart::reverse_level_order_iterator::operator*() const
{
    std::string str = this->node->get_data();
    return str;
}
// ---------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------
// preorder iterator
bool OrgChart::preorder_iterator::operator!=(const preorder_iterator &other) const { return this->node != other.node; }
OrgChart::preorder_iterator &OrgChart::preorder_iterator::operator++()
{
    if (!this->node_stack.empty())
    {
        this->node = this->node_stack.top();
        this->node_stack.pop();
    }
    else
    {
        this->node = nullptr;
    }

    if (this->node != nullptr)
    {
        std::vector<ChartNode *> reverse_list = this->node->get_children();
        std::reverse(reverse_list.begin(), reverse_list.end());
        for (ChartNode *child : reverse_list)
        {
            this->node_stack.push(child);
        }
    }

    return *this;
}
ChartNode *OrgChart::preorder_iterator::operator->() const { return this->node; }
std::string OrgChart::preorder_iterator::operator*() const
{
    std::string str = this->node->get_data();
    return str;
}
// ---------------------------------------------------------------------------------------------------------