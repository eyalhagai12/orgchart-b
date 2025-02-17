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
    ChartNode *get_node(const std::string &title) const;

public:
    // constructor and destructor
    OrgChart() : root(nullptr) {}
    OrgChart(const OrgChart &other) : root(nullptr)
    {
        if (other.root != nullptr)
        {
        }
    }
    OrgChart(const OrgChart &&other) noexcept : root(other.root) {}
    ~OrgChart() { delete root; }

    // iterators (might change implementations)
    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    class level_order_iterator
    {
    private:
        // current node
        ChartNode *node;

        // queue of nodes
        std::queue<ChartNode *> node_queue;

    public:
        // constructor destructor
        level_order_iterator(const OrgChart &organization) : node_queue(std::queue<ChartNode *>()),
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
        level_order_iterator(const level_order_iterator &other) : node(other.node), node_queue(other.node_queue) {}
        level_order_iterator(level_order_iterator &&other) noexcept
        {
            this->node = other.node;
            this->node_queue = other.node_queue;
        }
        ~level_order_iterator() = default;

        // operator overloads
        bool operator!=(const level_order_iterator &other) const;
        level_order_iterator &operator++();
        ChartNode *operator->() const;
        std::string operator*() const;
        level_order_iterator &operator=(const level_order_iterator &other);
        level_order_iterator &operator=(level_order_iterator &&other) noexcept;
    };

    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    class reverse_level_order_iterator
    {
    private:
        // current node
        ChartNode *node;

        // stack of nodes
        std::stack<ChartNode *> node_stack;

    public:
        // constructor destructor
        reverse_level_order_iterator(const OrgChart &organization) : node(organization.root),
                                                                     node_stack(std::stack<ChartNode *>())
        {
            if (node != nullptr)
            {
                std::queue<ChartNode *> queue;
                queue.push(node);

                while (!queue.empty())
                {
                    ChartNode **pnode = &queue.front();
                    queue.pop();
                    this->node_stack.push(*pnode);

                    std::vector<ChartNode *> child_vec = (*pnode)->get_children();
                    std::reverse(child_vec.begin(), child_vec.end());
                    for (ChartNode *cnode : child_vec)
                    {
                        queue.push(cnode);
                    }
                }

                node = this->node_stack.top();
                this->node_stack.pop();
            }
        }
        reverse_level_order_iterator(const reverse_level_order_iterator &other) : node(other.node), node_stack(other.node_stack) {}
        reverse_level_order_iterator(reverse_level_order_iterator &&other) noexcept
        {
            this->node = other.node;
            this->node_stack = other.node_stack;
        }
        ~reverse_level_order_iterator() = default;

        // operator overloads
        bool operator!=(const reverse_level_order_iterator &) const;
        reverse_level_order_iterator &operator++();
        ChartNode *operator->() const;
        std::string operator*() const;
        reverse_level_order_iterator &operator=(const reverse_level_order_iterator &other);
        reverse_level_order_iterator &operator=(reverse_level_order_iterator &&other) noexcept;
    };

    // --------------------------------------------------------------------
    // --------------------------------------------------------------------
    class preorder_iterator
    {
    private:
        // current node
        ChartNode *node;

        // stack of nodes
        std::stack<ChartNode *> node_stack;

    public:
        // constructor destructor
        preorder_iterator(const OrgChart &organization) : node(organization.root),
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
        preorder_iterator(const preorder_iterator &other) : node(other.node), node_stack(other.node_stack) {}
        preorder_iterator(preorder_iterator &&other) noexcept
        {
            this->node = other.node;
            this->node_stack = other.node_stack;
        }
        ~preorder_iterator() = default;

        // operator overloads
        bool operator!=(const preorder_iterator &other) const;
        preorder_iterator &operator++();
        ChartNode *operator->() const;
        std::string operator*() const;
        preorder_iterator &operator=(const preorder_iterator &other);
        preorder_iterator &operator=(preorder_iterator &&other) noexcept;
    };

    // friend classes
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
    friend bool operator==(ChartNode *node, std::string &str);
    friend bool operator==(std::string &str, ChartNode *node);
    friend std::ostream &ariel::operator<<(std::ostream &out, OrgChart &organization); // override << operator
    OrgChart &operator=(OrgChart &&other) noexcept;
    OrgChart &operator=(const OrgChart &other);
};
