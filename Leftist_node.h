/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type nodeNumber;
		Type weight;

		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length; //similar to height in AVL
		void swap( Leftist_node *, Leftist_node * );
		int countHelper( Leftist_node*  , int  , Type const & ) const;

	public:
		Leftist_node( Type const &, double const & );
//		~Leftist_node();
		Type retrieveN() const;
		Type retrieveW() const;

		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj,double const &obj2 ):
nodeNumber( obj ),
weight( obj2 ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

//// You may need this
//template <typename Type>
//Leftist_node<Type>::~Leftist_node() {
//	clear();  // might as well use it...
//}

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );

}

template <typename Type>
Type Leftist_node<Type>::retrieveN() const {
	return ( this->nodeNumber );

}
template <typename Type>
Type Leftist_node<Type>::retrieveW() const {
	return ( this->weight );

}

//TODO
template <typename Type>
int Leftist_node<Type>::count(Type const & obj) const {
	int counter = 0;
	if(this == nullptr) return 0;
	if(obj == this->nodeNumber){
		counter++;
	}
	counter = countHelper(this->left_tree,counter,obj);
	return countHelper(this->right_tree,counter,obj);


}

template <typename Type>
int Leftist_node<Type>::countHelper(Leftist_node * node, int curr,Type const & obj ) const {

	 if (node == nullptr) return curr;
	 if(node->nodeNumber ==obj){
		  curr++;
	 }
	        // first recur on left subtree
	 curr = countHelper(node->left_tree, curr, obj);
	 countHelper(node->right_tree, curr, obj);
//	 return curr;//countHelper(node->right_tree, curr, obj);
// as ‘this’ argument discards qualifiers [-fpermissive]
}





template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {

	return this->left_tree;

}
template <typename Type>
Leftist_node<Type> * Leftist_node<Type> ::right() const  {

	return this->right_tree;

}

//TODO npl
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
if(this == nullptr) return -1;
else {

return 	 std::min( 1 + left_tree->null_path_length(), 1 + right_tree->null_path_length());
}

}
//TODO clear
template <typename Type>
void Leftist_node<Type>::clear() {

	if (this == nullptr) return;
	else {
		this->left_tree->clear();
		this->right_tree->clear();

		delete this;

	}

}


//TODO push
template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this  ) { //what if i pass const reference?
if (new_heap == nullptr) return;

 if (this == nullptr){
	 ptr_to_this = new_heap;
	return;
}

 if(this->weight > new_heap->weight ){
	 ptr_to_this = new_heap;
	 ptr_to_this->push( this, ptr_to_this );
	 return;
}
 if ( right_tree == nullptr ) {
	 right_tree = new_heap;
 }
 else {
 			right_tree->push( new_heap, right_tree );
 		}

 this->heap_null_path_length = null_path_length();

 if ( left_tree->null_path_length() < right_tree->null_path_length() ) {
        std:: swap(left_tree,right_tree);
 }



}



#endif
