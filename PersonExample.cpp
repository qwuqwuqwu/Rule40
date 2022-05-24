#include <iostream>
#include <string.h>
#include <memory> // for std::shared_ptr
using namespace std;

#define Max_Formatted_Field_value_Length    ( 999 )

char g_Name[ 2 ][ Max_Formatted_Field_value_Length ] = { "abc", "def" };
char g_BirthDate[ 2 ][ Max_Formatted_Field_value_Length ] = { "2022/05/20", "2022/05/21" };

class IPerson {
public:
    virtual ~IPerson() {};
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
};

class DatabaseID {
public:
    DatabaseID( int nIndex ) : m_nIndex( nIndex )
    {
        cout << "DatabaseID" << endl;
    };
    int m_nIndex;
};

DatabaseID askUserForDatabaseID( void )
{ 
    char c;
    cout << "Input a or b : ";
    cout << endl;
    cin >> c;
    DatabaseID LocalID( c - 'a' );
    return LocalID;
};

class PersonInfo {
public:
    explicit PersonInfo( DatabaseID pid );
    virtual ~PersonInfo();
    virtual const char* theName() const;
    virtual const char* theBirthDate() const;

private:
    virtual const char* valueDelimOpen() const;
    virtual const char* valueDelimClose() const;

    char* m_pNameChar;
    char* m_pBirthDateChar;
};

PersonInfo::PersonInfo( DatabaseID pid )
{
    m_pNameChar = g_Name[ pid.m_nIndex ];
    m_pBirthDateChar = g_BirthDate[ pid.m_nIndex ];
    cout << "PersonInfo" << endl;
}
PersonInfo::~PersonInfo()
{
    cout << "~PersonInfo" << endl;
}
const char* PersonInfo::valueDelimOpen() const
{
    return "[";
}
const char* PersonInfo::valueDelimClose() const
{
    return "]";
}
const char* PersonInfo::theName() const
{
    static char value[ Max_Formatted_Field_value_Length ];
    strcpy( value, valueDelimOpen() );

    strcat( value, m_pNameChar );

    strcat( value, valueDelimClose() );
    return value;
}
const char* PersonInfo::theBirthDate() const
{
    static char value[ Max_Formatted_Field_value_Length ];
    strcpy( value, valueDelimOpen() );

    strcat( value, m_pBirthDateChar );

    strcat( value, valueDelimClose() );
    return value;
}

class CPerson: public IPerson, private PersonInfo {
public:
    explicit CPerson( DatabaseID pid ): PersonInfo( pid )
    {
        cout << "CPerson" << endl;
    }

    virtual ~CPerson()
    {
        cout << "~CPerson" << endl;
    }

    virtual std::string name() const
    { return PersonInfo::theName(); }

    virtual std::string birthDate() const
    { return PersonInfo::theBirthDate(); }

private:
    const char* valueDelimOpen() const { return "QWU--"; };
    const char* valueDelimClose() const { return "--UWQ"; };
};

std::shared_ptr< IPerson > makePerson( DatabaseID personIdentifier )
{
    std::shared_ptr< IPerson > p( new CPerson( personIdentifier ) );
    return p;
}

int main( void )
{
    // example 1 use IPerson interface to manipulate CPerson
    DatabaseID id( askUserForDatabaseID() );
    std::shared_ptr< IPerson > pp( makePerson( id ) );
    cout << "Your name is " << pp->name() << ", birth date is " << pp->birthDate() << endl;

    // example 2 use PersonInfo
    cout << "USER PERSONINFO" << endl;
    PersonInfo MyPersonInfo( askUserForDatabaseID() );
    cout << "Your name is " << MyPersonInfo.theName() << ", birth date is " << MyPersonInfo.theBirthDate() << endl;
    return 0;
}