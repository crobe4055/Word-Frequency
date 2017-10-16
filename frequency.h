/*
 * frequency.h

The Frequency class makes it easier to create a tree of word counts.

For example, by using this class you will be able to do create a binary tree of binary_tree_node<frequency<string> >*.
Note that the space after the second closing > is required.

frequency()
	Sets Item to blank and frequency to 0.  Be careful with this one, recommend the using the other constructor only.
	If you use this one you will have to increment frequency when you update the data field.

frequency(Item i)
	Constructor with an Item, will initialize frequency to 1

// MODIFICATION MEMBER FUNCTIONS
Item& data( )
	Return the data_field that you can change

size_t& operator++()
size_t operator++(int)
	Increments the frequency count only

bool isDataInc(Item i)
	If i matching the objects data, then it increments the frequency and returns true

// CONST MEMBER FUNCTIONS
const Item& data( ) const
	Return the data_field that you cannot change

bool isData(Item i) const
	If i matching the objects data, then it returns true

size_t count( ) const
	Return the frequency

bool operator< (Item b)
bool operator< (Item b)
bool operator> (Item b)
bool operator> (Item b)
	Use this to help decide where a new node should be placed based on data.  This will compare the data_field.
	Both const and non const versions provided.

bool operator< (size_t b)
bool operator< (size_t b)
bool operator> (size_t b)
bool operator> (size_t b)
	Use this to help decide where a node should be placed based on frequency count. This will compare the freq.field.
	Both const and non const versions provided.

std::ostream& operator<<(std::ostream& out, const frequency<Item>& f)
	Outputs the frequency and data_field is a friendly format, no spaces
	data_field[freq_field]

 */

#ifndef FREQUENCY_H_
#define FREQUENCY_H_

namespace FREQPROJ
{

	template <class Item>
    class frequency
    {
    public:
		frequency() { data_field=Item(); freq_field=0; }
		frequency(Item i) { data_field=i; freq_field=1; }
		// MODIFICATION MEMBER FUNCTIONS
		Item& data( ) { return data_field; }
		frequency<Item>& operator++() { ++freq_field; return *this; } //pre
		frequency<Item> operator++(int) { frequency<Item> tmp(*this); operator++(); return tmp; } //post
		bool isDataInc(Item i) { return (i == data_field && (freq_field += 1)); }
		// CONST MEMBER FUNCTIONS
		const Item& data( ) const { return data_field; }
		bool isData(Item i) const { return i == data_field; }
		size_t count( ) const { return freq_field; }
		bool operator< (Item b) { return data_field < b; }
		bool operator< (Item b) const { return data_field < b; }
		bool operator< (size_t b) { return freq_field < b; }
		bool operator< (size_t b) const { return freq_field < b; }
		bool operator> (Item b) { return data_field > b; }
		bool operator> (Item b) const { return data_field > b; }
		bool operator> (size_t b) { return freq_field > b; }
		bool operator> (size_t b) const { return freq_field > b; }
    private:
		Item data_field;
		size_t freq_field;
    };

	template <class Item>
	std::ostream& operator<<(std::ostream& out, const frequency<Item>& f)
	{
		out << f.data() << "[" << f.count() << "]";  return out;
	}

	//More comparisons to get around the fact that FREQ must be on the LEFT without these
	template <typename Item>
	bool operator > (Item left, frequency<Item>& right ) { return left > right.data() ; }

	template <typename Item>
	bool operator < (Item left, frequency<Item>& right ) { return left < right.data() ; }

	template <typename Item>
	bool operator < (std::size_t left, frequency<Item>& right ) { return left < right.count() ; }

	template <typename Item>
	bool operator > (std::size_t left, frequency<Item>& right ) { return left > right.count() ; }
	//End of comparisons

} //end namespace




#endif /* FREQUENCY_H_ */
