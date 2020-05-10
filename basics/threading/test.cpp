
class CommandHelper
{

};

struct BaseNonResourceData
{

};

class BaseCommand
{
    protected:
    BaseNonResourceData* pNonResourceData;

};

struct SampleNonResourceData : public BaseNonResourceData
{
    int a;
    float b;
};

class SampleCmd : public BaseCommand
{
    pNonResourceData = new SampleNonResourceData();

};