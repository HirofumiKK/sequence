//
//  Sequence.cpp
//  Project2
//
//  Created by Hirofumi Koichihara on 4/23/18.
//  Copyright © 2018 Hirofumi Koichihara. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
#include <cstdlib>


Sequence::Sequence()
{
    // circularly linked list
    // head is the dummy node
    head = new Node;
    head->m_next = head;
    head->m_prev = head;
    m_size = 0;
}


bool Sequence::empty() const
{
    bool result = false;
    if(m_size == 0)
        result = true;
    return result;
}


int Sequence::size() const
{
    return m_size;
}


bool Sequence::insert(int pos, const ItemType& value)
{
    bool result = false;
    // true if 0 <= pos <= size
    if(pos >= 0 && pos <= m_size)
        result = true;
    if(result == false)
        return false;
    // if false is not returned above, true is returned at the end, so
    // i can assume i can insert if false is not returned above
    // for any insertion, dynamic allocation and assigning value are needed
    // since only one insertion is done one at a time using this function,
    // i'll do those parts here before applying correct method depending on conditions
    Node* ptr = new Node;
    ptr->m_value = value;
    
    // inserting conditions to consider:
    // empty list
    // one element list --> not really since already taken care by front and back
    // normal (middle)
    // front
    // back
    
    // empty list
    if(m_size == 0){
        // connect node and head
        ptr->m_next = head;
        ptr->m_prev = head;
        // connect head and node
        head->m_next = ptr;
        head->m_prev = ptr;
    }else if(pos == 0){ // inserting at front
        // connect FROM the new node to the surrounding two nodes
        ptr->m_next = head->m_next;
        ptr->m_prev = head;
        // connect FROM surronding two nodes to the new node
        head->m_next->m_prev = ptr;
        head->m_next = ptr;
    }else if(pos == m_size){ // inserting at back
        // temp is the original last node
        Node* temp = head->m_prev;
        // connect FROM the new node to the surrounding two nodes
        ptr->m_next = head;
        ptr->m_prev = temp;
        // connect FROM surronding two nodes to the new node
        temp->m_next = ptr;
        head->m_prev = ptr;
    }else{ // inserting into middle
        // after this while loop, temp will be the node right after the new node being inserted
        Node* temp = head->m_next;
        int i = 0;
        while(i != pos){
            temp = temp->m_next;
            i++;
        }
        // connect FROM the new node to the surrounding two nodes
        ptr->m_next = temp;
        ptr->m_prev = temp->m_prev;
        // connect FROM surronding two nodes to the new node
        temp->m_prev->m_next = ptr;
        temp->m_prev = ptr;
    }
    // increase size by one
    m_size++;
    return true;
}

int Sequence::insert(const ItemType& value)
{
    int p = 0;
    Node* temp = head->m_next;
    while(temp != head && temp->m_value < value){
        temp = temp->m_next;
        p++;
    }
    insert(p, value);
    return p;
}

bool Sequence::erase(int pos)
{
    bool result = false;
    if(pos >= 0 && pos < m_size && m_size != 0){
        result = true;
        //////////////// erasing starts //////////////////
        // conditions to consider:
        // empty list --> taken care by the first if statement
        // one element list
        // normal (middle)
        // front
        // back
        
        // one element list
        if(m_size == 1){
            // two ways to do this:
            // delete head->m_next, or
            // set temp = head->m_next and delete temp
            // I guess the former method is simpler, but
            // latter should be useful for some cases
            delete head->m_next;
            head->m_next = head;
            head->m_prev = head;
        }else if(pos == 0){ // erasing front node
            // temp is the first node that is to be erased
            Node* temp = head->m_next;
            // connect and then delete method
            head->m_next = temp->m_next;
            temp->m_next->m_prev = head;
            delete temp;
        }else if(pos == m_size){ // erasing end node
            // temp is the node at the end that is to be erased
            Node* temp = head->m_prev;
            // connect and then delete method
            temp->m_prev->m_next = head;
            head->m_prev = temp->m_prev;
            delete temp;
        }else{ // deleting node in middle
            // I first need to reach that node
            Node* temp = head->m_next;
            int i = 0;
            while(i != pos){
                temp = temp->m_next;
                i++;
            }
            // connect and delete method
            temp->m_prev->m_next = temp->m_next;
            temp->m_next->m_prev = temp->m_prev;
            delete temp;
        }
        //////////////// erasing complete //////////////////
        // decrease size by one
        m_size--;
    }
    return result;
}


int Sequence::remove(const ItemType& value)
{
    int num = 0;
    Node* temp = head->m_prev;
    // looping from back
    for(int i = m_size - 1; temp != head; i--, temp = temp->m_prev){
        if(temp->m_value == value){
            erase(i);
            num++;
        }
    }
    cerr << "num = " << num << endl;
    return num;
}


bool Sequence::get(int pos, ItemType& value) const
{
    bool result = false;
    // false if empty list
    if(pos >= 0 && pos < m_size && m_size != 0){
        result = true;
        // temp is the first node after head
        Node* temp = head->m_next;
        int i = 0;
        // looping until we reach position pos
        while(i != pos){
            temp = temp->m_next;
            i++;
        }
        value = temp->m_value;
    }
    return result;
}


bool Sequence::set(int pos, const ItemType& value)
{
    bool result = false;
    if(pos >= 0 && pos < m_size && m_size != 0){
        result = true;
        // temp is the first node after head
        Node* temp = head->m_next;
        int i = 0;
        // looping until we reach position pos
        while(i != pos){
            temp = temp->m_next;
            i++;
        }
        temp->m_value = value;
    }
    return result;
}


int Sequence::find(const ItemType& value) const
{
    Node* temp = head->m_next;
    for(int p = 0; p < m_size; temp = temp->m_next, p++){
        if(temp->m_value == value)
            return p;
    }
    return -1;
}


void Sequence::swap(Sequence& other)
{
    // swap head pointers
    Node* tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    // swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

void Sequence::dump() const
{
    cerr << "Display of List: ";
    Node* temp = head->m_next;
    while(temp != head){
        cerr << temp->m_value << " ";
        temp = temp->m_next;
    }
    cerr << endl;
}

Sequence::~Sequence()
{
    // looping to delete every element from the back
    while (head->m_prev != head)
    {
        // connect the node before the last and head and then delete
        Node* temp = head->m_prev;
        temp->m_prev->m_next= head;
        head->m_prev = temp->m_prev;
        delete temp;
    }
    delete head;
}


Sequence::Sequence(const Sequence& other)
: m_size(other.m_size)
{
    head = new Node;
    // dummy node of circularly linked list
    head->m_next = head;
    head->m_prev = head;
    // if empty list, do none of following
    if(m_size >= 1){
        // for the first element of the list, do the following
        // dynamic allocation of memory for new copy of node
        Node* newCopy = new Node;
        // copy m_value
        newCopy->m_value = other.head->m_next->m_value;
        // connecting FROM the new node to the surrounding two dummy nodes
        newCopy->m_next = head;
        newCopy->m_prev = head;
        // connecting FROM the surrounding two dummy nodes to the new node
        head->m_next = newCopy;
        head->m_prev = newCopy;
        
        // furthermore, do following if there are more than one element in the list
        if(m_size >= 2){
            // for list with more than one element, specifically
            // dealing with second element of the list and thereafter
            
            // looping through every element of the other list, creating copy for each
            for (Node* otherTemp = other.head->m_next->m_next; otherTemp != other.head; otherTemp = otherTemp->m_next){
                // dynamic allocation of memory for new copy of node
                Node* newCopy = new Node;
                // copy m_value
                newCopy->m_value = otherTemp->m_value;
                // connectring FROM the new node to the surrounding two nodes
                newCopy->m_next = head;
                newCopy->m_prev = head->m_prev;
                // connecting FROM surrounding two nodes to the new node
                head->m_prev->m_next = newCopy;
                head->m_prev = newCopy;
            }
        }
    }
}


Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this != &rhs){
        // I will add delete head here if there is memory leak, I won't if not
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // return -1 if empty or subsequence is longer than the sequence, which is not allowed
    if(seq1.empty() || seq2.empty() || seq1.size() < seq2.size()){
        return -1;
    }else{
        bool isSeq = false;
        // compare the first value of seq2 to every value of seq1
        ItemType v1, v2;
        for(int i = 0; i < seq1.size(); i++){
            seq1.get(i, v1);
            seq2.get(0, v2);
            if(v1 == v2){
                isSeq = true;
                // if the two values are equal, start comparing the rest of the values of seq2
                int pos = i;
                for(int j = 0, k = i; j < seq2.size(); j++, k++){
                    seq1.get(k, v1);
                    seq2.get(j, v2);
                    if(v1 != v2){
                        isSeq = false;
                        break;
                    }
                }
                if(isSeq){
                    cerr << "subsequence returns " << pos << endl;
                    return pos;
                }
            }
        }
    }
    cerr << "subsequence returns " << -1 << endl;
    return -1;
}
 

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    // in order to avoid aliasing
    Sequence temp(result);
    // delete all items in result
    while(!result.empty())
        result.erase(0);

    // if both seq1 and seq2 are empty, result is also empty
    if(seq1.empty() && seq2.empty()){
        result = seq1;
    }else if(seq1.empty()){ // if either seq is empty, result = the other seq
        result = seq2;
    }else if(seq2.empty()){
        result = seq1;
    }else if(seq1.size() == seq2.size() || seq1.size() > seq2.size() ){
        // for the two condiitons described in this if statement,
        // I can just insert every item of seq2 into every inbetween items in result,
        // which is a copy of seq1
        
        // copy seq1 to result
        result = seq1;
        ItemType v2;
        // in between every original item in result, insert items from seq2
        for(int i = 1, j = 0; j < seq2.size(); i += 2, j++){
            seq2.get(j, v2);
            result.insert(i, v2);
        }
    }else if(seq1.size() < seq2.size()){
        // I'll do the opposite of the previous method with some modifications
        result = seq2;
        ItemType v1;
        // in between every original item in result, insert items from seq1
        for(int i = 0, j = 0; j < seq1.size(); i += 2, j++){
            seq1.get(j, v1);
            result.insert(i, v1);
        }
    }
}
