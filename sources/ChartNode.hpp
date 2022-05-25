#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace ariel
{
    class ChartNode;
    std::ostream &operator<<(std::ostream &out, const ChartNode &node);
    std::ostream &operator<<(std::ostream &out, const ChartNode *node);
} // namespace ariel

class ariel::ChartNode
{
private:
    std::string data;
    std::vector<ChartNode *> children;

public:
    // constructor destructor
    ChartNode(const std::string &data) : data(data) {}
    ChartNode(const ChartNode &&other) noexcept
    {
        this->data = other.data;
        this->children = other.children;
    }
    ChartNode(const ChartNode &other) : data(other.data), children(other.children) {}
    ~ChartNode()
    {
        for (ChartNode *node : this->children)
        {
            delete node;
        }
    }

    // friends
    friend std::ostream &ariel::operator<<(std::ostream &out, const ChartNode &node);
    friend std::ostream &ariel::operator<<(std::ostream &out, const ChartNode *node);

    // methods
    size_t size();
    std::string get_data();
    void set_data(const std::string &);
    std::vector<ChartNode *> get_children();
    void add_child(ChartNode *node);
    size_t length();
    char at(size_t i);

    // operator overrides
    ChartNode &operator=(ChartNode &&other) noexcept; // move assignment operator
    ChartNode &operator=(const ChartNode &other);     // copy assignment operator
};
