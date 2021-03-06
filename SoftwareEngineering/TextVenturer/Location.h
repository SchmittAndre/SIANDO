#pragma once

#include "AdventureObject.h"
#include "Inventory.h"
#include "CommandSystem.h"

class Item;
class Player;

class Location : public AdventureObject
{
public:
                                                                               
    class MultiInventory : public Inventory
    {
    public:
        enum Filter
        {
            ifBlacklist,
            ifWhitelist
        };
    private:
        stringlist prepAliasesList;    // stringlist for list/put          
        stringlist prepAliasesTake;    // stringlist also useable for take
        
        Filter mode;

        Inventory filter;
        
    public:
        MultiInventory(FileStream & stream, AdventureLoadHelp & help);
        MultiInventory();

        bool addPrepositionAlias(std::string alias, bool runOnTake = false);
        bool delPrepositionAlias(std::string alias);
        std::string getPrepositionName(bool runOnTake = false, bool startOfSentence = false) const;
        bool hasPrepositionAlias(std::string alias, bool runOnTake = false) const;

        void addItem(Item & item);
        bool canAddItem(Item & item) const;
        void addItemForce(Item & item);

        Filter getFilterMode() const;
        void setFilterMode(Filter mode);
        void filterAllowAll();
        void filterForbidAll();
        void addToFilter(Item & item);
        void delFromFilter(Item & item);

        void save(FileStream & stream, AdventureSaveHelp & help) const;
    };

    typedef std::unordered_map<std::string, MultiInventory> MultiInventoryList;

private:                                
    CommandArray locatedCommands;

    CustomAdventureAction * onGoto;
    CustomAdventureAction * onLeave;

    MultiInventoryList inventories;

public:
    Location();
    Location(FileStream & stream, AdventureLoadHelp & help);
    ~Location();

    MultiInventory & addInventory(std::string preposition);
    void delInventory(std::string preposition);
    bool hasInventory(std::string preposition) const;
    size_t filledInventoryCount() const;
    MultiInventory & firstFilledInventory();

    Item & findItem(std::string name) const;
    
    CommandArray & getLocatedCommands();

    CustomAdventureAction * getOnGoto() const;
    CustomAdventureAction * getOnLeave() const;

    void setOnGoto(CustomAdventureAction * onGoto);
    void setOnLeave(CustomAdventureAction * onLeave);

    MultiInventory & getInventory(std::string preposition);
    ref_vector<Location::MultiInventory> getInventories();
    ref_vector<Location::MultiInventory> findInventories(std::string preposition, bool runOnTake = false);

    std::string formatPrepositions(bool filledOnly = false) const;
    std::string formatPrepositions(Item & filterCheckItem) const;
    std::string formatInventories(Player & player) const;

    Type getType() const;
    void save(FileStream & stream, AdventureSaveHelp & help) const;
};

class EPrepositionExistsAlready : public Exception
{
public:
    EPrepositionExistsAlready(const Location & location, const std::string & preposition);
};

class EPrepositionDoesNotExist : public Exception
{
public:
    EPrepositionDoesNotExist(const Location & location, const std::string & preposition);
};       

class EAddItemFilterForbidden : public Exception
{
public:
    EAddItemFilterForbidden(const Item & item);
};

class EMultiInventoryEmpty : public Exception
{
public:
    EMultiInventoryEmpty(const Location & location);
};