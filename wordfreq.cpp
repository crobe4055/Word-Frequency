//============================================================================
// Name        : wordfreq.cpp
// Author      : Christopher Roberts
// Version     : Project 3, Word Frequency
// Copyright   :
// Description : Reads a .txt file, tokenizes the words and creates 2 binary
//				 trees. The first tree is sorted alphabetically. The second
//				 tree is sorted by the frequency count of each word.
//============================================================================
#include <cstdlib>
#include <iostream>
#include <string>
#include "bintree.h"
#include "frequency.h"
#include "wordscollection.h"

using namespace FREQPROJ;

void outnode(const binary_tree_node<frequency<std::string> >& node) {
	std::cout << node.data() << " ";
}

void insert(binary_tree_node<frequency<std::string> >* root,
		const std::string& new_node) {

	if (root->data() > new_node) {
		if (root->left() == NULL) {

			binary_tree_node<frequency<std::string> > * left =
					new binary_tree_node<frequency<std::string> >;
			left->data() = new_node; // sets lefts data to new node
			root->set_left(left);
		} else
			insert(root->left(), new_node); // recursion
	}

	else if (root->data() < new_node) {
		if (root->right() == NULL) {
			binary_tree_node<frequency<std::string> > * right =
					new binary_tree_node<frequency<std::string> >;
			right->data() = new_node; // sets rights data to new node
			root->set_right(right);

		} else
			insert(root->right(), new_node); // recursion
	}

	else
	{
		root->data().isDataInc(new_node); // if (root->data() == new_node), If a word is seen again, increment the count.
	}

}

void insertFreq(binary_tree_node<frequency<std::string> >* root,
		frequency<std::string> new_node) { // This is pretty much the same as insert, but it compares the frequency count instead of alphabetical order.

	if (root->data().count() < new_node.count()) { //  IF roots data count is less then the data count of the new node.
		if (root->left() == NULL) {

			binary_tree_node<frequency<std::string> > * left =
					new binary_tree_node<frequency<std::string> >;
			left->data() = new_node;
			root->set_left(left);
		} else
			insertFreq(root->left(), new_node); // recursion
	}

	else {
		if (root->right() == NULL) {
			binary_tree_node<frequency<std::string> > * right =
					new binary_tree_node<frequency<std::string> >;
			right->data() = new_node;
			root->set_right(right);

		} else
			insertFreq(root->right(), new_node); // recursion
	}
}

void alphaToFreq(binary_tree_node<frequency<std::string> > *head_ptr, binary_tree_node<frequency<std::string> > *alpha_root,
		binary_tree_node<frequency<std::string> > * freq_root) {
	if (alpha_root == NULL) // If the root of the alphabetical tree is NULL return.

		return;
	if(head_ptr!=alpha_root) // Prevents freq tree from having root node twice

		insertFreq(freq_root, alpha_root->data());

	if (alpha_root->left() != NULL) {
		alphaToFreq(head_ptr,alpha_root->left(), freq_root); // recursion
	}

	if (alpha_root->right() != NULL) {
		alphaToFreq(head_ptr,alpha_root->right(), freq_root); // recursion
	}
}

int main(int argc, char *argv[]) {

	if (argc != 2) // argc should be 2 for correct execution.
			{
		std::cout << "usage: " << argv[0] << " <filename>\n"; // Print argv[0] assuming it is the program name.
		return 0;
	} else {

		binary_tree_node<frequency<std::string> > * root = NULL; // Root of the alphabetical binary tree.
		binary_tree_node<frequency<std::string> > * freq = NULL; // Root of the frequency binary tree.

		std::string nextWord;
		wordscollection wc; // Instance of wordcollection to tokenize filename.
		std::string fileName = argv[1]; // First argument is the file name.

		wc.tokenizeFile(fileName); // Tokenize file.

		root = new binary_tree_node<frequency<std::string> >(wc.getNextToken()); // Root equals the first node.
		freq = new binary_tree_node<frequency<std::string> >(root->data()); // Freq equals root's data. If instead a next token was grabbed, freq would be word # 2

		while (wc.hasTokens()) // While there are more words to tokenize.
		{
			nextWord = wc.getNextToken(); // NextWord equals the rest of the words.
			insert(root, nextWord); // insert the word into the alpha tree
		}

		alphaToFreq(root,root, freq);

		std::cout << "WORD FREQUENCY - Alphabetical\n"; // Prints words Alphabetically.
		inorder(outnode, root);

		std::cout << std::endl << std::endl; // Improve readability.

		std::cout << "WORD FREQUENCY - Highest to Lowest" << std::endl; // Prints words from most frequent to least frequent in appearance.

		inorder(outnode, freq);

		return 0;
	}
}

