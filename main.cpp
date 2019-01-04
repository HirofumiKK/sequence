//
//  main.cpp
//  Project2
//
//  Created by Hirofumi Koichihara on 4/24/18.
//  Copyright © 2018 Hirofumi Koichihara. All rights reserved.
//
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Sequence>::value,
              "Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
              "Sequence must be copy-constructible.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Sequence::operator=,  Sequence& (Sequence::*)(const Sequence&));
    CHECKTYPE(&Sequence::empty,      bool (Sequence::*)() const);
    CHECKTYPE(&Sequence::size,       int  (Sequence::*)() const);
    CHECKTYPE(&Sequence::insert,     bool (Sequence::*)(int, const ItemType&));
    CHECKTYPE(&Sequence::insert,     int (Sequence::*)(const ItemType&));
    CHECKTYPE(&Sequence::erase,      bool (Sequence::*)(int));
    CHECKTYPE(&Sequence::remove,     int  (Sequence::*)(const ItemType&));
    CHECKTYPE(&Sequence::get,     bool (Sequence::*)(int, ItemType&) const);
    CHECKTYPE(&Sequence::set,     bool (Sequence::*)(int, const ItemType&));
    CHECKTYPE(&Sequence::find,       int  (Sequence::*)(const ItemType&) const);
    CHECKTYPE(&Sequence::swap,       void (Sequence::*)(Sequence&));
    CHECKTYPE(subsequence, int  (*)(const Sequence&, const Sequence&));
    CHECKTYPE(interleave,  void (*)(const Sequence&, const Sequence&, Sequence&));
}

/*
void test0()
{
    Sequence s;
    assert(s.insert(0, "lavash"));
    assert(s.insert(0, "tortilla"));
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "lavash");
}
//*/
//*
void test1()
{
    Sequence s;
    assert(s.insert(0, 10));
    assert(s.insert(0, 20));
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x)  &&  x == 20);
    assert(s.get(1, x)  &&  x == 10);
    
    Sequence seq1;
    assert(seq1.insert(0, 30));
    assert(seq1.insert(1, 21));
    assert(seq1.insert(2, 63));
    assert(seq1.insert(3, 42));
    assert(seq1.insert(4, 17));
    assert(seq1.insert(5, 63));
    assert(seq1.insert(6, 17));
    assert(seq1.insert(7, 29));
    assert(seq1.insert(8, 8));
    assert(seq1.insert(9, 32));
    
    Sequence seq2;
    assert(seq2.insert(0, 63));
    assert(seq2.insert(1, 17));
    assert(seq2.insert(2, 29));
    

    assert(subsequence(seq1, seq2) == 5);
    interleave(seq1, seq2, s);
    //s.dump();
    
    Sequence s1;
    assert(s1.empty());
    assert(s1.size() == 0);
    assert(!s1.insert(1, 100));
    assert(s1.insert(0, 100));
    assert(s1.insert(1000) == 1);
    assert(s1.insert(10) == 0);
    assert(!s1.erase(3));
    assert(s1.erase(2));
    assert(s1.insert(2, 150));
    assert(s1.insert(10) == 0);
    s1.dump();
    assert(s1.remove(1000) == 0);
    s1.dump();
    assert(s1.insert(4, 10));
    assert(s1.remove(10) == 3);
    s1.dump();
    
    assert(!seq2.get(3, x));
    assert(seq2.get(0, x) && x == 63);
    assert(seq2.get(1, x) && x == 17);
    assert(seq2.get(2, x) && x == 29);
    
    Sequence s2 = seq2;
    assert(!s2.set(3, 100));
    assert(s2.set(0, 1));
    assert(s2.set(2, 9));
    assert(s2.find(19) == -1);
    assert(s2.find(17) == 1);
    assert(s2.find(1) == 0);
    
    Sequence s3 = seq1;
    s3.dump();
    s2.dump();
    s3.swap(s2);
    s3.dump();
    s2.dump();
    
    Sequence s4, s5;
    s4.dump();
    s5.dump();
    interleave(s4, s5, s3);
    s4.dump();
    s5.dump();
    s3.dump();
    
    assert(subsequence(s4, s5) == -1);
    assert(!s4.erase(0));
    assert(s4.remove(0) == 0);
    
}
//*/

int main()
{
    //test0();
    test1();
    cout << "Passed all tests" << endl;
}
