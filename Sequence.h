//
//  Sequence.h
//  Project2
//
//  Created by Hirofumi Koichihara on 4/23/18.
//  Copyright © 2018 Hirofumi Koichihara. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
//using ItemType = string;
using ItemType = unsigned long;

class Sequence
{
public:
    Sequence();    // Create an empty sequence (i.e., one with no items)
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    bool insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one higher than they were at before.
    // Return true if 0 <= pos <= size() and the value could be
    // inserted. Otherwise,
    // leave the sequence unchanged and return false.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    
    int insert(const ItemType& value);
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item at position
    // p.  The original item at position p and those that follow it end
    // up at positions one higher than before.  Return p if the value
    // was actually inserted.
    
    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed that item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.
    
    int remove(const ItemType& value);
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item at position pos
    // in the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    
    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.
    
    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    
    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.
    
    void dump() const;
    
    // Housekeeping functions
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);

private:
    struct Node
    {
        ItemType m_value;
        Node* m_next;
        Node* m_prev;
    };
    Node* head;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
/*
 Consider all the items in seq2; let's call them seq20, seq21, ..., seq2n. If there exists at least one k such that seq1k == seq20 and seq1k+1 == seq21 and ... and seq1k+n == seq2n, and k+n < seq1.size(), then this function returns the smallest such k. (In other words, if seq2 is a consecutive subsequence of seq1, the function returns the earliest place in seq1 where that subsequence starts.) If no such k exists or if seq2 is empty, the function returns -1. For example, if seq1 were a sequence of ints consisting of
 
 30 21 63 42 17 63 17 29 8 32
 and seq2 consists of
 
 63 17 29
 then the function returns 5, since the consecutive items 63 17 29 appear in seq1 starting with the 63 at position 5. (The result is not 2, because while there's a 63 at position 2, followed eventually by a 17 and a 29, those items are not consecutive in seq1.) With the same seq1, if seq2 consists of
 
 17 63 29
 then the function returns -1.
 */
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
/*
 This function produces as a result a sequence that consists of the first item in seq1, then the first in seq2, then the second in seq1, then the second in seq2, etc.
 
 More formally: Consider the items in seq1; let's call them seq10, seq11, …, seq1m, and let's call the items seq2 contains seq20, seq21, …, seq2n. If m equals n, then when this function returns, result must consist of the sequence seq10, seq20, seq11, seq21, …, seq1m, seq2n, and no other items.
 
 If m is less than n, then when this function returns, result must consist of the sequence seq10, seq20, seq11, seq21, …, seq1m, seq2m, seq2m+1, seq2m+2, …, seq2n, and no other items.
 
 If n is less than m, then when this function returns, result must consist of the sequence seq10, seq20, seq11, seq21, …, seq1n, seq2n, seq1n+1, seq1n+2, …, seq1m, and no other items.
 
 If either sequence is empty, then when this function returns, result must consist of a copy of the other sequence.
 
 When this function returns, result must not contain any items that this spec does not require it to contain. (You must not assume result is empty when it is passed in to this function; it might not be.)
 
 As an example, if seq1 were a sequence of ints consisting of
 
 30 21 63 42 17 63
 and seq2 consists of
 
 42 63 84 19
 then no matter what value it had before, result ends up consisting of:
 
 30 42 21 63 63 84 42 19 17 63
 Be sure this function behaves correctly in the face of aliasing: What if seq1 and result refer to the same Sequence, for example?
 */

#endif /* Sequence_h */
