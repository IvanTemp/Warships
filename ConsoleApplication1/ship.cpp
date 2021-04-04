#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ship.h"
#include "Aircraft_Carrier.h"
#include "Heavy_Cruiser.h"
#include "Tsundere.h"
#include "Small.h"


int ship::count_ = 0;

ship::ship(const std::string& nm, const int IDen) : name_(nm), id_(IDen), type_(nullptr), cid_(count_++)
{
}

ship::ship(const std::string& nm, type& tp, const int IDen) : name_(nm), id_(IDen), type_(&tp), cid_(count_++)
{
    durability_.resize(type_->get_size());
    std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void ship::print(std::ostream& out) const
{
    out << "[" << id_ << "]\t";
    out << name_ << "\t";
    if (name_.size() < 6) out << "\t";
    out << "Type: ";
        if (type_ != nullptr)
        {
            std::cout << type_->get_name();
            if (type_->get_name().size() < 9) out << "\t";
        }
        else
        {
            std::cout << "none type";
        }
    std::cout << "\t";
    out << "Durability: ";
    for (int i = 0; i < durability_.size(); i++)
    {
        out << " " << durability_[i];
    }
    out << std::endl;
}

void ship::read(std::istream& in)
{
    std::string temp;
    std::getline(in, temp);
    id_ = stoi(temp);
    std::getline(in, name_);
    //std::getline(in, type_);
    temp = "";
    std::getline(in, temp);
    if (temp == "Aircraft Carrier") 
    {
        type_ = new Aircraft_Carrier();
    }
    else if (temp == "Heavy Cruiser")
    {
        type_ = new Heavy_Cruiser();
    }
    else if (temp == "Tsundere")
    {
        type_ = new Tsundere();
    }
    else if (temp == "Small")
    {
        type_ = new Small();
    }
    else
    {
        type_ = nullptr;
    }
    durability_.resize(type_->get_size());
    std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void ship::set_name(const std::string &name)
{
    name_ = name;
}

std::string ship::get_name() const
{
    return name_;
}

void ship::set_type(const type* tp)
{
    type_ = (type*)tp;
}

 type* ship::get_type() const
{
    return type_;
}

void ship::set_durability(const std::vector<int> &durability)
{
    durability_ = durability;
}

unsigned int ship::get_durability_sum() const {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < durability_.size(); i++) {
        sum += durability_[i];
    }
    return sum;
}

std::vector<int> ship::get_durability() const
{
    return durability_;
}

void ship::damage_by_index(const int dmg, const int ind) {
    if (durability_[ind] - dmg > 0) { durability_[ind] -= dmg; }
    else { durability_[ind] = 0; }
}

int ship::get_id() const
{
    return id_;
}

bool ship::operator==(const ship& right) const
{
    bool durabilityIsEqual = false;
    std::string s = std::to_string(durability_.size()) + std::to_string(right.durability_.size());
    std::sort(s.begin(), s.end());
    for (int x = 0; x < s[0] - '0'; x++)
    {
        if (durability_[x] == right.durability_[x])
        {
            durabilityIsEqual = 1;
        }
        else
        {
            durabilityIsEqual = 0;
            break;
        }
    }
    return (name_ == right.name_ && type_ == right.type_ && id_ == right.id_ && durabilityIsEqual);
}

bool ship::operator!=(const ship& right) const
{
    return !(*this == right);
}

ship& ship::operator=(const ship& right)
{
    if (this != &right)
    {
        name_ = right.name_;
        type_ = right.type_;
        durability_ = right.durability_;
    }
    return *this;
}

ship ship::operator++(int)
{
    ship copyThis(*this);
    for (int i = 0; i < durability_.size(); i++)
    {
        if (durability_[i] == Tsundere_Durability)
        {
            durability_[i]++;
        }
    }
    return copyThis;
}

void ship::klee(const std::vector <std::pair<unsigned int, unsigned int>> coords, const bool side)const {
    extern void field_get_vision(const unsigned int x, const unsigned int y, const bool side);
    if (DEBUG_MODE) {
        for (int i = 0; i < coords.size(); i++) {
            std::cout << "[DEBUG INFO]" << i << ": X = " << coords[i].first << "; Y = " << coords[i].second << std::endl;
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < coords.size(); i++) {
        if (coords[i].first) {
            if (coords[i].second) {
                field_get_vision(coords[i].first - 1, coords[i].second - 1, side);
            }
            field_get_vision(coords[i].first - 1, coords[i].second, side);
            if (coords[i].second < width_height - 1) {
                field_get_vision(coords[i].first - 1, coords[i].second + 1, side);
            }
        }
        if (coords[i].second) {
            field_get_vision(coords[i].first, coords[i].second - 1, side);
        }
        if (coords[i].second < width_height - 1) {
            field_get_vision(coords[i].first, coords[i].second + 1, side);
        }
        if (coords[i].first < width_height - 1) {
            if (coords[i].second) {
                field_get_vision(coords[i].first + 1, coords[i].second - 1, side);
            }
            field_get_vision(coords[i].first + 1, coords[i].second, side);
            if (coords[i].second < width_height - 1) {
                field_get_vision(coords[i].first + 1, coords[i].second + 1, side);
            }
        }
    }
}

void ship::nuclear_bomb() {
    for (int i = 0; i < durability_.size(); i++) {
        durability_[i] = 0;
    }
}

std::istream& operator>>(std::istream& in, ship& shp)
{
    shp.read(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, const ship& shp)
{
    shp.print(out);
    return out;
}