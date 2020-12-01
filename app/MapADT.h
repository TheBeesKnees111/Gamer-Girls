/***********************
 * NOT LINKED LIST MAP *
 ***********************/
//USE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE
//FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR
//PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR
//PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR PROJECTUSE FOR
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;template <typename K, typename Type>
class MapADT
{
        public:

                /**********************************
                 ***** CONSTRUCTOR/DESTRUCTOR *****
                 **********************************/
                MapADT();	//Default constructor initialize list to an empty state
                                //Post: first = NULL

                ~MapADT();	//Destructor
                                //Post: list object is destroyed

                /********************
                 ***** ACCESSORS ****
                 ********************/
                //Return True if the list is empty
                //Else return false
                bool IsEmptyList() const;

                //Return True if the item is in the list
                //Else return false
                bool SearchKey(K searchKey) const;

                //Output the info contained in each node
                void Print() const;

                //Outputs "Item is found in the list" if searchItem
                //is in the list; otherwise, outputs "Item not in the list"
                bool SearchItem(const Type searchItem) const;

                int Size() const;	//Return the size of the linked list

                //Get index in vector of key
                int GetKeyIndex(K& key) const;

                //Overload [] to reference item in map
                const Type operator[](K searchKey);

//		//returns first element of the map
//		Iterator Begin();

//		//Returns last element in map
//		Iterator Last();

//		//returns memory location after last element in map
//		Iterator End();


                /********************
                 ***** MODIFIERS ****
                 ********************/

                //Delete all nodes from the list
                //Post: first = NULL
                void Destroy();

                //newItem is inserted in the list
                //Post: first points to the new list and the
                // newItem is inserted at the proper place in the list
                void Insert(const K insertKey, const Type insertItem);

                //If found, the node containing the deleteItem is deleted
                //from the list
                //Post: first points to the first node of the
                // new list
                bool Delete(const K& deleteKey);

        private:
                vector <K>    keys;
                vector <Type> items{};
};


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

