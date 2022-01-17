// Datastructures.hh
//
// Student name: Kristian Lempinen
// Student email: kristian.lempinen@tuni.fi
// Student number: H296236

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>

// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: unordered_map public member function 'size()' complexity is constant. It is a single operation.
    unsigned int town_count();

    // Estimate of performance: Linear (N)
    // Short rationale for estimate: unordered_map public member function 'clear()' complexity is linear on size, as destructor has to be called for each element.
    void clear_all();

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: unordered_map public member function 'insert()' complexity for single elements is constant on average. Prerequisite 'find()' is also constant on average.
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: unordered_map public member functions 'at()' and 'find()' are both constant on average.
    Name get_town_name(TownID id);

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: unordered_map public member functions 'at()' and 'find()' are both constant on average.
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: unordered_map public member functions 'at()' and 'find()' are both constant on average.
    int get_town_tax(TownID id);

    // Estimate of performance: Linear (N)
    // Short rationale for estimate: for-loop iterates through each unordered_map element and does 'push_back()' to a vector, which is constant per element.
    std::vector<TownID> all_towns();

    // Estimate of performance:  Linear (N)
    // Short rationale for estimate: for-loop iterates through each unordered_map element. Push_back() to a vector is done for each element, which is constant.
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: unordered_map public member functions 'at()' and 'find()' are both constant on average.
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance: N log (N)
    // Short rationale for estimate: for-loop iterates through elements with linear complexity, sort is linearithmic in distance between first and last.
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: N log (N)
    // Short rationale for estimate: Two linear for-loops (which aren't embedded) and sort() function.
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: Linear (N)
    // Short rationale for estimate: unordered_map public member function size() is constant. for-loop iterates through elements with linear complexity, performing constant operations per element.
    TownID min_distance();

    // Estimate of performance: Linear (N)
    // Short rationale for estimate: unordered_map public member function size() is constant. for-loop iterates through elements with linear complexity, performing constant operations per element.
    TownID max_distance();

    // Estimate of performance: Constant (1)
    // Short rationale for estimate: Function contains series of constant at average operations: find() twice, emplace_back() once and several at() operations.
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: Linear (N)
    // Short rationale for estimate: for-loop iterates through each vector element, then uses constanty emplace_back() operation if needed.
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: log (N)
    // Short rationale for estimate: while-loop iterates through node levels, with best case being constant and worst linear, since vassalship-loops aren't allowed. Constant at() and push_back() operations are used if needed.
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: N log (N)
    // Short rationale for estimate: for-loop iterates through each element if condition is fulfilled. Constant at average operation find() is used and constant operations at(). Erase is linear for number of elements (in this case 1) + num. of elements after last.
    bool remove_town(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);

private:

    // Add stuff needed for your class implementation here
    struct Town
    {
        TownID id;
        Name name;
        Coord location;
        int tax;

        std::vector<Town*> vassals; // Node children
        Town* master; // Node parent
    };

    std::unordered_map<TownID, Town> towns;

};

#endif // DATASTRUCTURES_HH
