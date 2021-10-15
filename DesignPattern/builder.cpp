#include <iostream>
#include <string>


using namespace std;

class Plane 
{
    string _planeType;
    string _body;
    string _engine;

public:
    Plane(string planeType):_planeType{planeType} {}

    void SetEngine(string engine) { _engine = engine; }
    void SetBody(string body) { _body = body; }

    string GetBody() const { return _body; }
    string GetEngine() const {return _engine; }

    void Show() {
        cout<< "Plane type : " << _planeType << " Body : " << _body
        << " Engine: " << _engine << endl;
    }

};



class PlaneBuilder
{
protected:
    Plane *_plane;

    public: 
        virtual void GetPartsDone()  = 0;
        virtual void BuildBody() = 0;
        virtual void BuildEngine() = 0;
        
        Plane* GetPlane() { return _plane; }
};

class Boing : public PlaneBuilder
{
public:
    void GetPartsDone() { _plane = new Plane("Boing"); }
    void BuildBody() { _plane->SetBody("Boing Body"); }
    void BuildEngine() { _plane->SetEngine("Boing Engine"); }
};

class AirBus : public PlaneBuilder
{
public:
    void GetPartsDone() { _plane = new Plane("AirBus"); }
    void BuildBody() { _plane->SetBody("AirBus Body"); }
    void BuildEngine() { _plane->SetEngine("AirBus Engine"); }
};

class Director
{
public:
    Plane* CreatePlane(PlaneBuilder* planeBuilder)
    {
        planeBuilder->GetPartsDone();
        planeBuilder->BuildBody();
        planeBuilder->BuildEngine();

        return planeBuilder->GetPlane();

    }
};


int main()
{
    Director d;
    Boing b;
    AirBus a;
    Plane* p1 = d.CreatePlane(&a);
    Plane* p2 = d.CreatePlane(&b);

    p1->Show();

    p2->Show();

    return 0;

}
