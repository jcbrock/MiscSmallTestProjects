#include <iostream>
#include <string>

class JsonVisitor;

class Json
{
public:
    std::string PrintHeaderMessage() const {
        return "I'm JSON!";
    }    
    virtual void Accept(const JsonVisitor* visitor) = 0;
};


class JsonString : public Json
{
public:
    JsonString(std::string value) : mValue(value) {}
    std::string Value() const { return mValue; }    
    void Accept(const JsonVisitor* visitor);
private:
    std::string mValue;
};

class JsonInt : public Json
{
public:
    JsonInt(int value) : mValue(value) {}
    int Value() const { return mValue; }
    void Accept(const JsonVisitor* visitor);
private:
    int mValue;
};

class JsonVisitor
{
public:
    virtual void VisitJsonString(JsonString* const element) const = 0;
    virtual void VisitJsonInt(JsonInt* const element) const = 0;
};

class JsonPrintVisitor : public JsonVisitor
{
public:
    void VisitJsonString(JsonString* const element) const
    {
        std::cout << element->PrintHeaderMessage() << " " << element->Value() << std::endl;
    }

    void VisitJsonInt(JsonInt* const element) const
    {
        std::cout << element->PrintHeaderMessage() << " " << element->Value() << std::endl;
    }

};

class JsonDuplicateVisitor : public JsonVisitor
{
public:
    void VisitJsonString(JsonString* const element) const
    {
        std::cout << element->PrintHeaderMessage() << " " << element->Value() + element->Value() << std::endl;
    }

    void VisitJsonInt(JsonInt* const element) const
    {
        std::cout << element->PrintHeaderMessage() << " " << element->Value() + element->Value() << std::endl;
    }
};

void JsonString::Accept(const JsonVisitor* visitor)
{
        visitor->VisitJsonString(this);
}

void JsonInt::Accept(const JsonVisitor* visitor)
{
    visitor->VisitJsonInt(this);
}





int main()
{

    JsonString str("foobar");
    JsonInt i(100);

    JsonPrintVisitor printer;
    JsonDuplicateVisitor duplicator;

    str.Accept(&printer);
    str.Accept(&duplicator);

    i.Accept(&printer);
    i.Accept(&duplicator);

    system("pause");
    return 0;
}