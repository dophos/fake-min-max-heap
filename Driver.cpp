#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdexcept>
#include "MinMaxHeap.h"
#include <set>
using namespace std ;

//sanityCheck: provided by Dr. Chang
template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
  int n = H.size() ;
  T minKey, maxKey, leftKey, rightKey ;
  int minPos, maxPos, pos ;
   
  bool passed=true ;

  cout << "Sanity Check minHeap...\n" ;

  for (int i=1 ; i<=n ; i++) {
    H.locateMin(i,minKey,maxPos) ; 
    H.locateMax(maxPos,maxKey,minPos) ; 
      
    if (minKey != maxKey) {
      passed = false ;
      cout << "Key mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (minPos != i) {
      passed = false ;
      cout << "Position mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (2*i <= n) {  // has left child
      H.locateMin(2*i,leftKey,pos) ;
      if (leftKey < minKey) {  // left child smaller than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << minKey << ", " 
	     << "left key = " << leftKey 
	     << endl ;
      }
    }  

    if (2*i+1 <= n) {  // has right child
      H.locateMin(2*i+1,rightKey,pos) ;
      if (rightKey < minKey) {  // right child smaller than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << minKey << ", " 
	     << "right key = " << rightKey 
	     << endl ;
      }
    }  

  }  // end of for (...)


  cout << "Sanity Check maxHeap...\n" ;

  for (int i=1 ; i<=n ; i++) {
    H.locateMax(i,maxKey,minPos) ; 
    H.locateMin(minPos,minKey,maxPos) ; 
      
    if (minKey != maxKey) {
      passed = false ;
      cout << "Key mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (maxPos != i) {
      passed = false ;
      cout << "Position mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (2*i <= n) {  // has left child
      H.locateMax(2*i,leftKey,pos) ;
      if (leftKey > maxKey) {  // left child bigger than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << maxKey << ", " 
	     << "left key = " << leftKey 
	     << endl ;
      }
    }  

    if (2*i+1 <= n) {  // has right child
      H.locateMax(2*i+1,rightKey,pos) ;
      if (rightKey > maxKey) {  // right child bigger than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << maxKey << ", " 
	     << "right key = " << rightKey 
	     << endl ;
      }
    }  
  }  // end of for (...)


  if (passed) {
    cout << "Passed sanityCheck().\n" ;
  } else {
    cout << "*** Failed sanityCheck().\n" ;
  }
}

//checkAgainstSet (for MinHeap): provided by Dr. Chang
template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T>& origS) {
  multiset<T> S ;  
  typename multiset<T>::iterator it ;

  int n = H.size() ;
  int pos ;
  int key ;

  bool passed = true ;

  S = origS ;  // make copy

  if ( n != S.size() ) {
    passed = false ;
    cout << "Heap and multiset sizes do not match!\n" ;
    cout << "   Heap size = " << n << endl ;
    cout << "   Set size  = " << S.size() << endl ;
  }


  for (int i=1 ; i <= n ; i++) {
    H.locateMin(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the min-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }


  S = origS ;  // start over

  for (int i=1 ; i <= n ; i++) {
    H.locateMax(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the max-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }

  if (passed) {
    cout << "Passed check against multiset\n" ;
  } else {
    cout << "***Failed check against multiset\n" ;
  }

}

//checkAgainstSet(for MaxHeap): provided by Dr. Chang
template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T,greater<T> >& origS) {
  multiset<T,greater<T> > S ;  
  typename multiset<T,greater<T> >::iterator it ;

  int n = H.size() ;
  int pos ;
  int key ;

  bool passed = true ;

  S = origS ;  // make copy

  if ( n != S.size() ) {
    passed = false ;
    cout << "Heap and multiset sizes do not match!\n" ;
    cout << "   Heap size = " << n << endl ;
    cout << "   Set size  = " << S.size() << endl ;
  }


  for (int i=1 ; i <= n ; i++) {
    H.locateMin(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the min-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }


  S = origS ;  // start over

  for (int i=1 ; i <= n ; i++) {
    H.locateMax(i,key,pos) ;
    it = S.find(key) ;
    if (it == S.end()) {
      passed = false ;
      cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
    } else {
      S.erase(it) ;
    }
  }

  if (S.size() > 0) {
    cout << "There are " << S.size() 
	 << " items in multiset that not in the max-heap.\n" ;
    for (it=S.begin() ; it != S.end() ; it++) {
      cout << *it << " " ;
    }
    cout << endl ;
  }

  if (passed) {
    cout << "Passed check against multiset\n" ;
  } else {
    cout << "***Failed check against multiset\n" ;
  }

}

//NoCopyString class provided by Dr. Chang
class NoCopyString {
 public:
  NoCopyString() ;
  NoCopyString(const char *) ;

  bool operator<  (const NoCopyString& other) const ;
  bool operator<= (const NoCopyString& other) const ;
  bool operator== (const NoCopyString& other) const ;
  bool operator!= (const NoCopyString& other) const ;
  bool operator>  (const NoCopyString& other) const ;
  bool operator>= (const NoCopyString& other) const ;

  const char *m_str ;

} ;


std::ostream& operator<< (std::ostream& sout, const NoCopyString& s) ;


NoCopyString::NoCopyString() {
  m_str = NULL ;
}

NoCopyString::NoCopyString(const char *str) {
  m_str = str ;
}

bool NoCopyString::operator<  (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) <  0) return true ;
  return false ;
}

bool NoCopyString::operator<= (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) <= 0) return true ;
  return false ;
}

bool NoCopyString::operator== (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) == 0) return true ;
  return false ;
}

bool NoCopyString::operator!= (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) != 0) return true ;
  return false ;
}

bool NoCopyString::operator>= (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) >= 0) return true ;
  return false ;
}

bool NoCopyString::operator>  (const NoCopyString& other) const {
  if (strcmp(m_str, other.m_str) >  0) return true ;
  return false ;
}


std::ostream& operator<< (std::ostream& sout, const NoCopyString& s) {
  sout << s.m_str ;
  return sout ;
}


int main() {
  cout << "**********************************" << endl;
  cout << "** Test 1 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<int> H1(25) ;
  H1.insert(5) ;
  H1.insert(10) ;
  H1.insert(7) ;
  H1.insert(9) ;
  H1.insert(6) ;
  H1.insert(2) ;
  H1.insert(16) ;
  H1.insert(12) ;
  H1.insert(11) ;

  cout << "Initial MinMax Heap\n" ;
  H1.dump() ;

  H1.insert(8); 
  cout << "After inserting 8\n" ;
  H1.dump() ;

  sanityCheck(H1) ;

  int answer1 ;
  answer1 = H1.deleteMin() ;
  cout << "\n\nMin item " << answer1 << " removed from MinMax Heap\n" ;

  H1.dump() ;
  sanityCheck(H1) ;

  answer1 = H1.deleteMax() ;
  cout << "\n\nMax item " << answer1 << " removed from MinMax Heap\n" ;

  H1.dump() ;
  sanityCheck(H1) ;
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 2 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<string> H2(25) ;
  H2.insert("jkl") ;
  H2.insert("yz_") ;
  H2.insert("abc") ;
  H2.insert("mno") ;
  H2.insert("vwx") ;
  H2.insert("pqr") ;
  H2.insert("ghi") ;
  H2.insert("def") ;
  H2.insert("stu") ;

  H2.dump() ;
  sanityCheck(H2) ;

  string answer2 ;
  answer2 = H2.deleteMin() ;
  cout << "Min item " << answer2 << " removed from MinMax Heap\n" ;

  answer2 = H2.deleteMax() ;
  cout << "Max item " << answer2 << " removed from MinMax Heap\n" ;

  H2.dump() ;
  sanityCheck(H2) ;
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 3 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;
  
  MinMaxHeap<NoCopyString> H3(9) ;

  const char* myData[9] = {
    "jkl", "yz_", "abc",
    "mno", "vwx", "pqr",
    "ghi", "def", "stu" 
  } ;

  H3.insert(myData[0]) ;
  H3.insert(myData[1]) ;
  H3.insert(myData[2]) ;
  H3.insert(myData[3]) ;
  H3.insert(myData[4]) ;
  H3.insert(myData[5]) ;
  H3.insert(myData[6]) ;
  H3.insert(myData[7]) ;
  H3.insert(myData[8]) ;

  H3.dump() ;
  sanityCheck(H3) ;

  NoCopyString answer3 ;
  answer3 = H3.deleteMin() ;
  cout << "Min item " << answer3 << " removed from MinMax Heap\n" ;

  answer3 = H3.deleteMax() ;
  cout << "Max item " << answer3 << " removed from MinMax Heap\n" ;

  H3.dump() ;
  sanityCheck(H3) ;
  cout << endl;

  cout << "********************************************************\n"
       << "** Test A: Checks for out-of-range exception handling **\n"  
       << "********************************************************\n";
    
  MinMaxHeap<int> K1(1);
  MinMaxHeap<string> K2(1);

  cout << "(a) MinMaxHeap<int> object with capcity 1:" << endl;
  cout << "\nDump empty heap..." << endl;
  K1.dump();

  cout << "Delete Min..." << endl;
  try {
    K1.deleteMin();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "Delete Max..." << endl;
  try {
    K1.deleteMax();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after deletes..." << endl;
  K1.dump();
  
  cout << "Insert 1...\n";
  K1.insert(1);
  cout << "Insert 2...\n";
  try {
    K1.insert(2);
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after inserts..." << endl;
  K1.dump();
  cout << endl;

  cout << "(b) MinMaxHeap<string> object with capcity 1:" << endl;
  cout << "\nDump empty heap..." << endl;
  K2.dump();

  cout << "Delete Min..." << endl;
  try {
    K2.deleteMin();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  
  cout << "Delete Max..." << endl;
  try {
    K2.deleteMax();
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after deletes..." << endl;
  K2.dump();
  
  cout << "Insert 'first'...\n";
  K2.insert("first");
  cout << "Insert 'second'...\n";
  try {
    K2.insert("second");
  }
  catch (out_of_range e){
    cout << e.what() << endl;
  }
  cout << "\nDump heap after inserts..." << endl;
  K2.dump();
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 4 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  srand(4178012351) ;

  MinMaxHeap<int> H4(1000) ;
  multiset<int> S4 ;
  //multiset<int>::iterator it4 ;
  int key4 ;
  bool passed4 ;

  for (int i=0 ; i < 500 ; i++) {
    key4 = rand() % 100 ;
    H4.insert(key4) ;
    S4.insert(key4) ;
  }
  sanityCheck(H4) ;
  checkAgainstSet(H4,S4) ;

  passed4 = true ;
  for (int i=0 ; i < 450 ; i++) {
    key4 = H4.deleteMin() ;
    if (key4 != *S4.begin()) {
      passed4 = false ;
      cout << "deleteMin() returns key that is not the smallest key!\n" ;
    } else {
      S4.erase(S4.begin()) ;
    }
  }

  sanityCheck(H4) ;

  if (passed4) {
    checkAgainstSet(H4,S4) ;
  } else {
    cout << "***Failed deleteMin() test!\n" ;
    cout << "Skipped check against multiset\n" ;
  }
  cout << endl;

  cout << "**********************************" << endl;
  cout << "** Test 5 provided by Dr. Chang **" << endl;
  cout << "**********************************" << endl;

  MinMaxHeap<int> H5(1000) ;
  multiset<int,greater<int> > S5 ;
  //multiset<int,greater<int> >::iterator it5 ;
  int key5 ;
  bool passed5 ;

  for (int i=0 ; i < 750 ; i++) {
    key5 = rand() % 100 ;
    H5.insert(key5) ;
    S5.insert(key5) ;
  }
  sanityCheck(H5) ;
  checkAgainstSet(H5,S5) ;

  passed5 = true ;
  for (int i=0 ; i < 400 ; i++) {
    key5 = H5.deleteMax() ;
    if (key5 != *S5.begin()) {
      passed5 = false ;
      cout << "deleteMax() returns key that is not the largest key!\n" ;
    } else {
      S5.erase(S5.begin()) ;
    }
  }

  sanityCheck(H5) ;

  if (passed5) {
    checkAgainstSet(H5,S5) ;
  } else {
    cout << "***Failed deleteMax() test!\n" ;
    cout << "Skipped check against multiset\n" ;
  }
  

  return 0;

}
