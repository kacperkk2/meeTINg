#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

void serialize_int_32(char (&buf)[4], int32_t val)
{
    uint32_t uval = val;
    buf[0] = uval;
    buf[1] = uval >> 8;
    buf[2] = uval >> 16;
    buf[3] = uval >> 24;
}

int32_t parse_int_32(const char (&buf)[4])
{
    uint8_t u0 = buf[0], u1 = buf[1], u2 = buf[2], u3 = buf[3];

    uint32_t uval = u0 | (u1 << 8) | (u2 << 16) | (u3 << 24);
    return uval;
}

int main()
{
    // klient wysyla wiadomosc, inta na bufor daje
    string message;
    //cout << "podaj wiadomosc: "; cin >> message;

    for(int i = 0; i < 9090909; i++)
        message += "a";

    cout << "podales: " << message.size() << " bajtow"<<endl;

    int32_t m_size = message.size();
    char buf[4];

    SerializeInt32(buf, m_size);
    // -----------------------

    // serwer odbiera bufor i go na inta
    int32_t value_from_buf = ParseInt32(buf);
    cout << "rozmiar wiadomosci to: "<< value_from_buf <<endl;

    return 0;
}
