#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

#include "ChartNode.hpp"

namespace ariel
{
    class OrgChart;
    std::ostream &operator<<(std::ostream &out, OrgChart &organization);
} // namespace ariel

// this class would act like a tree data structure
class ariel::OrgChart
{
private:
    // the root of the tree
    ChartNode *root;

    // a simple private function to find a node in the tree
    ChartNode *get_node(ChartNode *root, const std::string &title) const;

public:
    // constructor and destructor
    OrgChart() : root(nullptr) {}
    ~OrgChart() {}

    // iterators (might change implementations)
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    class level_order_iterator
    {
    private:
        // the container on which to iterate
        const OrgChart &container;

        // current node
        ChartNode *node;

        // queue of nodes
        std::queue<ChartNode *> node_queue;

    public:
        // constructor destructor
        level_order_iterator(const OrgChart &organization) : container(organization),
                                                             node_queue(std::queue<ChartNode *>()),
                                                             node(organization.root)
        {
            if (node != nullptr)
            {
                for (ChartNode *child : this->node->get_children())
                {
                    this->node_queue.push(child);
                }
            }
        }
        ~level_order_iterator() {}

        // operator overloads
        bool operator!=(const level_order_iterator &other) const;
        level_order_iterator &operator++();
        ChartNode *operator->() const;
        std::string operator*() const;
    };

    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    class reverse_level_order_iterator
    {
    private:
        // the container on which to iterate
        const OrgChart &container;

        // current node
        ChartNode *node;

        // stack of nodes
        std::stack<ChartNode *> node_stack;

    public:
        // constructor destructor
        reverse_level_order_iterator(const OrgChart &organization) : container(organization),
                                                                     node(organization.root),
                                                                     node_stack(std::stack<ChartNode *>())
        {
            if (node != nullptr)
            {
                this->node_stack.push(nullptr);
                for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
                {
                    ChartNode *node = container.get_node(container.root, *it);
                    this->node_stack.push(node);
                }
                this->node = this->node_stack.top();
                this->node_stack.pop();
            }
        }
        ~reverse_level_order_iterator() {}

        // operator overloads
        bool operator!=(const reverse_level_order_iterator &) const;
        reverse_level_order_iterator &operator++();
        ChartNode *operator->() const;
        std::string operator*() const;
    };

    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    class preorder_iterator
    {
    private:
        // the container on which to iterate
        const OrgChart &container;

        // current node
        ChartNode *node;

        // stack of nodes
        std::stack<ChartNode *> node_stack;

    public:
        // constructor destructor
        preorder_iterator(const OrgChart &organization) : container(organization),
                                                          node(organization.root),
                                                          node_stack(std::stack<ChartNode *>())
        {
            this->node_stack.push(nullptr);
            if (node != nullptr)
            {
                std::vector<ChartNode *> reverse_list = node->get_children();
                std::reverse(reverse_list.begin(), reverse_list.end());
                for (ChartNode *child : reverse_list)
                {
                    node_stack.push(child);
                }
            }
        }
        ~preorder_iterator() {}

        // operator overloads
        bool operator!=(const preorder_iterator &other) const;
        preorder_iterator &operator++();
        ChartNode *operator->() const;
        std::string operator*() const;
    };

    friend class level_order_iterator;
    friend class reverse_level_order_iterator;
    friend class preorder_iterator;
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------

    // methods
    ariel::OrgChart &add_root(const std::string &);                     // add a new root to the chart or change current one
    ariel::OrgChart &add_sub(const std::string &, const std::string &); // add a subordinate to someomne in the chart
    level_order_iterator begin_level_order() const;                     // get the beginning an iterator for level order traversal
    level_order_iterator end_level_order() const;                       // get the ending of an iterator for level order traversal
    level_order_iterator begin() const;                                 // a default iterator over the continaer
    level_order_iterator end() const;                                   // a defualt end for the iterator over the container
    reverse_level_order_iterator begin_reverse_order() const;           // get the beginning an iterator for reverse level order traversal
    reverse_level_order_iterator reverse_order() const;                 // get the ending an iterator for reverse level order traversal
    preorder_iterator begin_preorder() const;                           // get the beginning an iterator for preorder traversal
    preorder_iterator end_preorder() const;                             // get the ending an iterator for preorder traversal

    // operator overloads
    friend std::ostream &ariel::operator<<(std::ostream &out, OrgChart &organization); // override << operator
};
