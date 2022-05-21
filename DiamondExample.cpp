#include <iostream>
using namespace std;

class A {
public:
    A( int a )
    { 
        m_na = a;
        cout << "A" << endl;
    };
protected:
    int m_na;
};

class B : public A {
public:
    B( int a, double b ):A( a )
    { 
        m_b = a * b;
        cout << "B" << endl;
    };

    void checkOut( void )
    {
        cout << "a = " << m_na << ", b = " << m_b << endl;
    };
private:
    double m_b;
};

class C : public A {
public:
    C( int a, double c ):A( a )
    { 
        m_c = a * c;
        cout << "C" << endl;
    };
private:
    void checkOut( void )
    {
        cout << "a = " << m_na << ", c = " << m_c << endl;
    };

    double m_c;
};

class D : public B, public C {
public:
    D( int a1, double b, int a2, double c, int d ):
    B( a1, b ), 
    C( a2, c )
    {
        m_nd = d;
        cout << "D" << endl;
    };
private:
    int m_nd;
};

// virtual inheritance

class VB : virtual public A {
public:
    VB( int a, double b ):A( a )
    { 
        m_b = a * b;
        cout << "VB" << endl;
    };

    void checkOut( void )
    {
        cout << "a = " << m_na << ", b = " << m_b << endl;
    };
private:
    double m_b;
};

class VC : virtual public A {
public:
    VC( int a, double c ):A( a )
    { 
        m_c = a * c;
        cout << "VC" << endl;
    };
private:
    void checkOut( void )
    {
        cout << "a = " << m_na << ", c = " << m_c << endl;
    };

    double m_c;
};

class VD : public VB, public VC {
public:
    VD( int a1, double b, int a2, double c, int d ):
    VB( a1, b ), 
    VC( a2, c ), 
    A( a2 )
    {
        m_nd = d;
        cout << "VD" << endl;
    };
private:
    int m_nd;
};

int main( void )
{
    D MyD( 11, 1.1, 22, 2.2, 33 );
    // MyD.checkOut(); // error: member 'checkOut' found in multiple base classes of different types
    MyD.B::checkOut();
    cout << "size of MyD is " << sizeof( MyD ) << endl;

    VD MyVD( 11, 1.1, 22, 2.2, 33 );
    // MyD.checkOut(); // error: member 'checkOut' found in multiple base classes of different types
    MyVD.VB::checkOut();
    cout << "size of MyVD is " << sizeof( MyVD ) << endl;
    return 0;
}