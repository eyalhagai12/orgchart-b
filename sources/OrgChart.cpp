#include "OrgChart.hpp"

using ariel::ChartNode;
using ariel::OrgChart;

OrgChart &OrgChart::add_root(const std::string &root)
{
    if (this->root == nullptr)
    {
        this->root = new ChartNode(root);
    }
    else
    {
        this->root->set_data(root);
    }
    return *this;
}

/*
    search for a node recursively (might change to something else)
*/
ChartNode *OrgChart::get_node(ChartNode *root, const std::string &title) const
{
    if (root->get_data() == title) // if found the return it
    {
        return root;
    }
    else if (root->get_children().size() == 0) // if not and there is no where to go return null
    {
        return nullptr;
    }

    // else work recursively  on the children
    for (ChartNode *node : root->get_children())
    {
        ChartNode *result = get_node(node, title);
        if (result != nullptr)
        {
            return result;
        }
    }

    return nullptr;
}

OrgChart &OrgChart::add_sub(const std::string &parent, const std::string &subordinate)
{
    ChartNode *new_node = new ChartNode(subordinate);
    ChartNode *node = this->get_node(this->root, parent);
    if (node != nullptr)
    {
        node->add_child(new_node);
    }
    return *this;
}

OrgChart::level_order_iterator OrgChart::begin_level_order() const { return OrgChart::level_order_iterator(*this); }

OrgChart::level_order_iterator OrgChart::end_level_order() const { return OrgChart::level_order_iterator(OrgChart()); }

OrgChart::level_order_iterator OrgChart::begin() const { return this->begin_level_order(); }

OrgChart::level_order_iterator OrgChart::end() const { return this->end_level_order(); }

OrgChart::reverse_level_order_iterator OrgChart::begin_reverse_order() const { return OrgChart::reverse_level_order_iterator(*this); }

OrgChart::reverse_level_order_iterator OrgChart::reverse_order() const { return OrgChart::reverse_level_order_iterator(OrgChart()); }

OrgChart::preorder_iterator OrgChart::begin_preorder() const { return OrgChart::preorder_iterator(*this); }

OrgChart::preorder_iterator OrgChart::end_preorder() const { return OrgChart::preorder_iterator(OrgChart()); }

/*
    print the tree in some way, not yet done as well as i wanted
*/
std::ostream &ariel::operator<<(std::ostream &out, OrgChart &organization)
{
    std::queue<ChartNode *> node_queue;
    node_queue.push(organization.root);
    size_t level_size = organization.root->get_children().size();

    std::cout << *organization.root << std::endl;
    size_t depth = 1;
    while (node_queue.size() > 0)
    {
        ChartNode *node = node_queue.front();
        node_queue.pop();

        if (!node->get_children().empty())
        {
            for (ChartNode *child : node->get_children())
            {
                std::cout << *child << "      ";
                node_queue.push(child);
                level_size--;
            }

            if (level_size <= 0)
            {
                std::cout << std::endl;
                level_size = node_queue.size();
            }
        }
    }

    return out;
}