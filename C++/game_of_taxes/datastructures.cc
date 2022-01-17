// Datastructures.cc
Kristian Lempinen

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

Datastructures::Datastructures()
{
    // Container for Town-structs.
    std::unordered_map<TownID, Town> towns;
}

Datastructures::~Datastructures()
{
    // Cleanup
}

unsigned int Datastructures::town_count()
{
    return towns.size();
}

void Datastructures::clear_all()
{
    towns.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord location, int tax)
{  
    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        Town new_town = {
            id, // TownID
            name, // Name
            location, // Coord
            tax, // int
            std::vector<Town*>(), // Empty vector for Node children
            nullptr // Empty pointer for Node parent
        };
        towns.insert(std::pair<TownID, Town>(id, new_town));
        return true;
    }
    else
    {
        return false;
    }
}

Name Datastructures::get_town_name(TownID id)
{
    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        return NO_NAME;
    }
    else
    {
        return towns.at(id).name;
    }
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        return NO_COORD;
    }
    else
    {
        return towns.at(id).location;
    }
}

int Datastructures::get_town_tax(TownID id)
{
    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        return NO_VALUE;
    }
    else
    {
        return towns.at(id).tax;
    }
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> all_town_IDs;
    if ( towns.size() > 0 )
    {
        for ( auto const& map_pair : towns )
        {
            all_town_IDs.push_back(map_pair.first);
        }
    }
    return all_town_IDs;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    std::vector<TownID> match;
    if ( towns.size() > 0 )
    {
        for ( auto const& map_pair : towns )
        {
            if ( map_pair.second.name == name )
            {
                match.push_back(map_pair.first);
            }
        }
    }
    return match;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        return false;
    }
    else
    {
        towns.at(id).name = newname;
        return true;
    }
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    std::vector<TownID> all_town_IDs;
    if ( towns.size() > 0 )
    {
        for ( auto const& map_pair : towns )
        {
            all_town_IDs.push_back(map_pair.first);
        }
        sort( all_town_IDs.begin(), all_town_IDs.end() );
        // []( const std::string & a, const std::string & b ) -> bool { return a < b; }
    }
    return all_town_IDs;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    std::vector<TownID> distance_increasing;

    struct Town_Distance
    {
      TownID idf;
      int distance;
    };

    std::vector<Town_Distance> initializer;

    if ( towns.size() > 0 )
    {
        for ( auto const& map_pair : towns )
        {
            int x = map_pair.second.location.x;
            int y = map_pair.second.location.y;

            double dist_from_origo = sqrt( ( pow(x, 2) )+ ( pow(y, 2) ) );
            int dist = floor(dist_from_origo);

            Town_Distance new_distance = {map_pair.second.id, dist};
            initializer.push_back(new_distance);
        }
        sort(initializer.begin(), initializer.end(), [](const Town_Distance& a, const Town_Distance& b) { return a.distance < b.distance; });

        for ( auto data : initializer )
        {
            distance_increasing.push_back(data.idf);
        }
    }
    return distance_increasing;
}

TownID Datastructures::min_distance()
{
    if ( towns.size() == 0)
    {
        return NO_TOWNID;
    }
    else
    {
        int minimum_dist = 0;
        Town* closest = nullptr;

        for ( auto const& map_pair : towns )
        {
            int x = map_pair.second.location.x;
            int y = map_pair.second.location.y;

            double dist_from_origo = sqrt( ( pow(x, 2) ) + ( pow(y, 2) ) );
            int dist = floor(dist_from_origo);

            if ( dist == 0 )
            {
                return map_pair.first;
            }
            else
            {
                if ( minimum_dist == 0)
                {
                    minimum_dist = dist;
                    *closest = map_pair.second;
                }
                else if ( dist < minimum_dist )
                {
                    minimum_dist = dist;
                    *closest = map_pair.second;
                }
            }
        }
        return closest->id;
    }
}

TownID Datastructures::max_distance()
{
    if ( towns.size() == 0)
    {
        return NO_TOWNID;
    }
    else
    {
        int maximum_dist = 0;
        Town* farthest = nullptr;

        for ( auto const& map_pair : towns )
        {
            int x = map_pair.second.location.x;
            int y = map_pair.second.location.y;

            double dist_from_origo = sqrt( ( pow(x, 2) ) + ( pow(y, 2) ) );
            int dist = floor(dist_from_origo);

            if ( maximum_dist == 0 )
            {
                maximum_dist = dist;
                *farthest = map_pair.second;
            }
            else if ( dist> maximum_dist )
            {
                maximum_dist = dist;
                *farthest = map_pair.second;
            }
        }
        if ( farthest != nullptr )
        {
            return farthest->id;
        }
        else
        {
            return NO_TOWNID;
        }
    }
}

bool Datastructures::add_vassalship(TownID vassal_id, TownID master_id)
{

    std::unordered_map<TownID, Town>::const_iterator found = towns.find (vassal_id);
    if ( found == towns.end() )
    {
        return false;
    }
    else
    {
        std::unordered_map<TownID, Town>::const_iterator found = towns.find (master_id);
        if ( found == towns.end() )
        {
            return false;
        }
        else
        {
            if ( towns.at(vassal_id).master != nullptr )
            {
                return false;
            }
            else
            {
                if ( vassal_id != master_id )
                {
                    towns.at(master_id).vassals.emplace_back(&towns[vassal_id]);
                    towns.at(vassal_id).master = &towns.at(master_id);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    std::vector<TownID> list_of_vassals;

    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        list_of_vassals.push_back(NO_TOWNID);
    }
    else
    {
        for ( auto vassal : towns.at(id).vassals )
        {
            list_of_vassals.emplace_back(vassal->id);
        }
    }
    return list_of_vassals;
}

std::vector<TownID> Datastructures::taxer_path(TownID idf)
{
    // "idf" used here as parameter name to distinguish it from struct-member 'id'

    std::vector<TownID> taxpath;

    std::unordered_map<TownID, Town>::const_iterator found = towns.find (idf);
    if ( found == towns.end() )
    {
        taxpath.push_back(NO_TOWNID);
    }
    else
    {
        Town temp = towns.at(idf);

        while ( temp.master != nullptr ){
            taxpath.push_back(temp.id);
            temp = *towns.at(idf).master;
        }
    }
    return taxpath;
}

bool Datastructures::remove_town(TownID id)
{
    std::unordered_map<TownID, Town>::const_iterator found = towns.find (id);
    if ( found == towns.end() )
    {
        return false;
    }
    else
    {
        if ( towns.at(id).vassals.size() > 0 )
        {
            for ( auto vassal : towns.at(id).vassals)
            {
                if ( towns.at(id).master != nullptr )
                {
                    vassal->master = towns.at(id).master;
                    towns.at(id).master->vassals.push_back(vassal);
                }
                else
                {
                    vassal->master = nullptr;
                }
            }
        }
        if ( towns.at(id).master != nullptr )
        {
            auto iter = find(towns.at(id).master->vassals.begin(), towns.at(id).master->vassals.end(), &towns.at(id));
            towns.at(id).master->vassals.erase(iter);
        }
        towns.erase(id);
        return true;
    }
}
