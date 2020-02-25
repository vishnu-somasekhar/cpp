/***************************************************************
 * SMART POINTERS
 * This is a tutorial for smart pointers.
 * Include file 'memory'
 * List of smart pointers
 *      auto_ptr       : deprecated as of C++11
 *      unique_pter
 *      shared_ptr
 *      weak_ptr
 ***************************************************************/


#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
    void show() { cout<< "A::show()" << endl; }
};


int main()
{

/*********************************************************************
 * AUTO POINTER         auto_ptr
 * 
 * An object when described using auto_ptr class it stores a pointer to a single allocated object 
 * which ensures that when it goes out of scope, the object it points to must get automatically destroyed.
 *  It is based on exclusive ownership model i.e. 
 * two pointers of the same type can’t point to the same resource at the same time.
**********************************************************************/

    cout<< " AUTO POINTER " << endl;
    // p1 is an auto_ptr of type A
    auto_ptr<A> p1(new A);
    p1->show();

    //return memory address of p1
    cout<< p1.get() << endl;

    // copy constructor called, this make p1 empty
    // The copy constructor and the assignment operator of auto_ptr do not actually 
    // copy the stored pointer instead they transfer it, leaving the first auto_ptr object empty. 
    auto_ptr<A> p2(p1);
    p2->show();

    cout<< p1.get() << endl;
    cout<< p2.get() << endl;

    // auto_ptr ENDS

/**************************************************************************
 * UNIQUE POINTER       unique_ptr
 * 
 * std::unique_ptr was developed in C++11 as a replacement for std::auto_ptr. 
 * unique_ptr is a new facility with similar functionality, 
 * but with improved security (no fake copy assignments), added features (deleters) and support for arrays. 
 * It is a container for raw pointers. It explicitly prevents copying of its contained pointer 
 * as would happen with normal assignment i.e. it allows exactly one owner of the underlying pointer.
 * So, when using unique_ptr there can only be at most one unique_ptr at any one resource and when that unique_ptr is destroyed, 
 * the resource is automatically claimed. Also, since there can only be one unique_ptr to any resource, 
 * so any attempt to make a copy of unique_ptr will cause a compile-time error.
****************************************************************************/

    cout<< " UNIQUE POINTER " << endl;
    unique_ptr<A> up1(new A);

    up1->show();
    up1.get();
    // unique_ptr<A> up1 = up1; This fails

    //But, unique_ptr can be moved using the new move semantics 
    //i.e. using std::move() function to transfer ownership of the contained pointer to another unique_ptr.
    unique_ptr<A> up2 = move(up1);

    up2->show();
    cout<< up1.get() << endl;
    cout<< up2.get() << endl;


/***************************************************************************************************
 * SHARED POITER        shared_ptr
 * 
 * A shared_ptr is a container for raw pointers. It is a reference counting ownership model 
 * i.e. it maintains the reference count of its contained pointer in cooperation with all copies of the shared_ptr. 
 * So, the counter is incremented each time a new pointer points to the resource and decremented when the 
 * destructor of the object is called.
 * 
 ***************************************************************************************************/

    cout<< " SHARED POINTER " << endl;
    shared_ptr<A> sp1(new A);

    sp1->show();

    cout<< sp1.get() << endl;

    shared_ptr<A> sp2(sp1);

    sp1->show();
    sp2->show();

    cout<< sp1.get() << endl;
    cout<< sp2.get() << endl; 
    cout<< sp1.use_count() << endl;
    cout<< sp2.use_count() << endl;

    sp1.reset();

    cout<< sp1.get() << endl;
    cout<< sp2.get() << endl; 
    cout<< sp1.use_count() << endl;
    cout<< sp2.use_count() << endl;

    /***********************************************************************************
     * WEAK POINTER         weak_ptr
     * 
     * A weak_ptr is created as a copy of shared_ptr. It provides access to an object that is owned by one or more shared_ptr 
     * instances but does not participate in reference counting. The existence or destruction of weak_ptr has no effect 
     * on the shared_ptr or its other copies. It is required in some cases to break circular references between shared_ptr instances.
     * 
     * Cyclic Dependency (Problems with shared_ptr): Let’s consider a scenario where we have two classes A and B, 
     * both have pointers to other classes. So, it’s always like A is pointing to B and B is pointing to A. 
     * Hence, use_count will never reach zero and they never get deleted.
     * 
     ************************************************************************************/

    return 0;
}