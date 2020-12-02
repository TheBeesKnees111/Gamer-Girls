#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

/*!
 * @class MapADT
 * @brief The Database class manages core methods used to access the data stored in the database
 */
template <typename K, typename Type>
class MapADT
{
public:
    /*!
     * @brief Default constructor will intialize list to empty state
     */
    MapADT();

    /*!
     * @brief Destructor will destroy internal list object
     */
    ~MapADT();

    /*!
     * @brief Accessor will return true if empty. False if not
     * @return bool; Status of list's contents
     */
    bool IsEmptyList() const;

    /*!
     * @brief Accessor will search for key and return true if found. False if not
     * @param searchKey; Key to find
     * @return bool; Status of whether or not list contains specific key
     */
    bool SearchKey(K searchKey) const;

    /*!
     * @brief Accessor will print contents of each node in list
     */
    void Print() const;

    //Outputs "Item is found in the list" if searchItem
    //is in the list; otherwise, outputs "Item not in the list"

    /*!
     * @brief Accessor will search for value and output "Item is found on list" if found.
     * @param searchItem; Value to find
     * @return bool; Status of whether or not list contains specific value
     */
    bool SearchItem(const Type searchItem) const;

    /*!
     * @brief Accessor will return number of items in list
     * @return int; Number of items in list
     */
    int Size() const;

    /*!
     * @brief Accessor will return index of specific key desired
     * @param key; Key for which to return index
     * @return int; Index of specific key desired
     */
    int GetKeyIndex(K& key) const;

    /*!
     * @brief Index operator overload
     * @param searchKey; Key to find and access
     * @return Type; item at index
     */
    const Type operator[](K searchKey);

    //Delete all nodes from the list
    //Post: first = NULL

    /*!
     * @brief Destroy list
     */
    void Destroy();

    /*!
     * @brief Insert element into list
     * @param insertKey; Key to insert
     * @param insertItem; Value to insert
     */
    void Insert(const K insertKey, const Type insertItem);

    //If found, the node containing the deleteItem is deleted
    //from the list
    //Post: first points to the first node of the
    // new list

    /*!
     * @brief Delete element from list
     * @param deleteKey; Key of element to find and delete
     * @return bool; Status of deletion
     */
    bool Delete(const K& deleteKey);

private:
    /// Map keys
    vector <K>    keys;
    /// Map values
    vector <Type> items{};
};

// Class Definition

/**********************************
 ***** CONSTRUCTOR/DESTRUCTOR *****
 **********************************/
template <typename K, typename Type>
MapADT<K, Type>::MapADT()
{}

template <typename K, typename Type>
MapADT<K, Type>::~MapADT()
{}

/********************
 ***** ACCESSORS ****
 ********************/
//Checks if the map is empty
template <typename K, typename Type>
bool MapADT<K, Type>::IsEmptyList() const
{
        return(keys.empty());
}

//Search for a key in a map
template <typename K, typename Type>
bool MapADT<K, Type>::SearchKey(K searchKey) const
{
        bool found = false;

        if(GetKeyIndex(searchKey) != -1)
                found = true;
        /***************************************************************************
         * OUTPUT - Whether or not the key was found in the map
         **************************************************************************/
        if(found)
        {
                cout << searchKey << " exists in the map!\n";
        }
        else
        {
                cout << searchKey << " does not exist in the map!\n";
        }

        return found;
}

//Print the elements in the map
template <typename K, typename Type>
void MapADT<K, Type>::Print() const
{
        for(int index = 0; index < keys.size(); index++)
        {
                cout << "Key:  " << keys[index]  << endl;
                cout << "Item: " << items[index] << endl;
                cout << endl;
        }

}//end printList


template <typename K, typename Type>
bool MapADT<K, Type>::SearchItem(const Type searchItem) const
{
        bool found = false;
        int  index = 0;

        while(!found && index < items.size())
        {
			if(items[index] == searchItem)
			{
					found = true;
			}

			index++;
        }

        /***************************************************************************
         * OUTPUT - Whether or not the key was found in the map
         **************************************************************************/
        if(found)
        {
                cout << searchItem << " exists in the map!\n";
        }
        else
        {
                cout << searchItem << " does not exist in the map!\n";
        }

        return found;

}//end search

//Returns the umber of elements in the map
template <typename K, typename Type>
int MapADT<K, Type>::Size() const
{
        return keys.size();
}

//Overload [] to reference item in map
template <typename K, typename Type>
const Type MapADT<K,Type>::operator[](K searchKey)
{
        Type voidType {};

        if(SearchKey(searchKey))
                return items[GetKeyIndex(searchKey)];
        else
                return voidType;

}

template<typename K, typename Type>
int MapADT<K,Type>::GetKeyIndex(K& key) const
{
        int  index = 0;

        while(index < keys.size())
        {
                if(keys[index] == key)
                {
                        return index;
                }

                index++;
        }

        return -1;
}

/********************
 ***** MODIFIERS ****
 ********************/
//Delete the entire map
template <typename K, typename Type>
void MapADT<K, Type>::Destroy()
{
        keys.clear ();
        items.clear();
}

//Insert into the map
template <typename K, typename Type>
void MapADT<K, Type>::Insert(const K insertKey, const Type insertItem)
{
        keys.push_back(insertKey);
        items.push_back(insertItem);
}//end insertNode

//Delete Node
template <typename K, typename Type>
bool MapADT<K, Type>::Delete(const K& deleteKey)
{
        bool found = false;

        if(GetKeyIndex(deleteKey) != -1)
        {
                found = true;
                keys [GetKeyIndex(deleteKey)] == 0;
                items[GetKeyIndex(deleteKey)] == 0;
        }

        return found;

}//end deleteNode

