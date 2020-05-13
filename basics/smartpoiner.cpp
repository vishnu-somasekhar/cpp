#include <iostream>

using namespace std;

class referanceCount
{
    int m_iReferanceCount {0};
    public: 
    void Increment() { ++m_iReferanceCount; }
    int Decrement() { return --m_iReferanceCount; }

    int GetCount() { return m_iReferanceCount; }
};


template <typename T>
class smart_pointer{

T* m_Object{nullptr};

referanceCount* m_RefCount{nullptr};

public:

smart_pointer(){}

smart_pointer(T* object):m_Object(object), m_RefCount(new referanceCount) {
    m_RefCount->Increment();
    std::cout<<"Smart pointer created with ref count: "<< m_RefCount->GetCount()<<std::endl;
}

virtual ~smart_pointer()
{
    int iCurrentCount = m_RefCount->Decrement();
    std::cout<<"Destroyed smart_ptr with ref count: "<< iCurrentCount<<std::endl;

    if(iCurrentCount <= 0)
        {
            delete m_RefCount;
            delete m_Object;

            m_RefCount = nullptr;
            m_Object = nullptr;
        }
}

smart_pointer(const smart_pointer<T>& obj):m_Object(obj.m_Object), m_RefCount(obj->m_RefCount)
{
    m_RefCount->Increment();
    std::cout<<"smart ptr copied, ref count:"<< m_RefCount->GetCount()<<std::endl;
}

smart_pointer<T>& operator=(const smart_pointer<T>& obj)
{
    if(this != &obj)
    {
        if(m_RefCount && m_RefCount->Decrement() == 0)
        {
            delete m_RefCount;
            delete m_Object;
        }

        m_Object = obj.m_Object;
        m_RefCount = obj.m_RefCount;
        m_RefCount->Increment();
    }

    std::cout<<"Assignment smart_ptr, ref count: "<< m_RefCount->GetCount()<<std::endl;
    return *this;
}

T* operator->()
{
    return m_Object;
}

T& operator*()
{
    return *m_Object;
}

};

class AirCraft
{
private:
  std::string m_Model;
public:
  AirCraft() :m_Model("Generic Model")
  {
    cout << "Generic model aircraft created" << endl;
  }
  AirCraft(const string& modelName) :m_Model(modelName)
  {
    cout << "Aircraft type" << m_Model << "is created!" << endl;
  }
  void SetAirCraftModel(const string& modelName)
  {
    cout << "Aircraft model changed from  " << m_Model << " to " << modelName << endl;
    m_Model = modelName;
  }
  ~AirCraft()
  {
    cout << "Destroying Aircraft of model:" << m_Model << "!" << endl;
  }

};

int main()
{
    smart_pointer<AirCraft> as(new AirCraft("Test1"));
    as->SetAirCraftModel("Test2");
    (*as).SetAirCraftModel("Test3");
    smart_pointer<AirCraft> as2(new AirCraft("Test4"));

    as2 = as;
    return 0;
}