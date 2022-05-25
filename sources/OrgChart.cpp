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
    search for a node iteratively
*/
ChartNode *OrgChart::get_node(const std::string &title) const
{
    // a queue for nodes
    std::queue<ChartNode *> queue;
    ChartNode *node = nullptr;
    bool found = false;
    queue.push(this->root);

    // iterate over all nodes
    while (!queue.empty())
    {
        // pop first node from the queue
        node = queue.front();
        queue.pop();

        // check if the node was found
        if (node->get_data() == title)
        {
            found = true;
            break;
        }

        // add all the nodes children
        std::vector<ChartNode *> child_vec = node->get_children();
        for (auto it = child_vec.begin(); it != child_vec.end(); ++it)
        {
            queue.push(*it);
        }
    }

    if (found)
    {
        return node;
    }
    return nullptr;
}

OrgChart &OrgChart::add_sub(const std::string &parent, const std::string &subordinate)
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Cant Add Sub Without Root!\n");
    }

    ChartNode *node = this->get_node(parent);
    if (node != nullptr)
    {
        ChartNode *new_node = new ChartNode(subordinate);
        node->add_child(new_node);
    }
    else
    {
        throw std::runtime_error("Parent Doesnt Exist!\n");
    }
    return *this;
}

OrgChart::level_order_iterator OrgChart::begin_level_order() const
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Chart Is Empty!\n");
    }
    return OrgChart::level_order_iterator(*this);
}

OrgChart::level_order_iterator OrgChart::end_level_order() const
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Chart Is Empty!\n");
    }
    return OrgChart::level_order_iterator(OrgChart());
}

OrgChart::level_order_iterator OrgChart::begin() const { return this->begin_level_order(); }

OrgChart::level_order_iterator OrgChart::end() const { return this->end_level_order(); }

OrgChart::reverse_level_order_iterator OrgChart::begin_reverse_order() const
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Chart Is Empty!\n");
    }
    return OrgChart::reverse_level_order_iterator(*this);
}

OrgChart::reverse_level_order_iterator OrgChart::reverse_order() const
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Chart Is Empty!\n");
    }
    return OrgChart::reverse_level_order_iterator(OrgChart());
}

OrgChart::preorder_iterator OrgChart::begin_preorder() const
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Chart Is Empty!\n");
    }
    return OrgChart::preorder_iterator(*this);
}

OrgChart::preorder_iterator OrgChart::end_preorder() const
{
    if (this->root == nullptr)
    {
        throw std::runtime_error("Chart Is Empty!\n");
    }
    return OrgChart::preorder_iterator(OrgChart());
}

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
    while (!node_queue.empty())
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

OrgChart &OrgChart::operator=(OrgChart &&other) noexcept
{
    if (this != &other)
    {
        this->root = other.root;
    }
    return *this;
}

OrgChart &OrgChart::operator=(const OrgChart &other)
{
    if (this != &other)
    {
        if (this->root != nullptr)
        {
            delete this->root;
            this->root = nullptr;
        }

        this->root = new ChartNode(*(other.root));
    }

    return *this;
}