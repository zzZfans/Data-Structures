//
// Created by Zfans on 2019/11/19.
//

#ifndef HASHTABLE_CONTACT_H
#define HASHTABLE_CONTACT_H

#include <iostream>

class Contact {
private:
    unsigned long long tellNumber;
    std::string userName;
    std::string address;
public:
    bool operator==(const Contact &rhs) const;

    bool operator!=(const Contact &rhs) const;

    friend std::istream &operator>>(std::istream &in, Contact &addressBook);

    friend std::ostream &operator<<(std::ostream &out, Contact &addressBook);

    [[nodiscard]] unsigned long long getTellNumber() const;

    void setTellNumber(long long int TellNumber);

    [[nodiscard]] const std::string &getUserName() const;

    void setUserName(const std::string &UserName);

    [[nodiscard]] const std::string &getAddress() const;

    void setAddress(const std::string &Address);
};

const std::string &Contact::getUserName() const {
    return userName;
}

void Contact::setUserName(const std::string &UserName) {
    Contact::userName = UserName;
}

const std::string &Contact::getAddress() const {
    return address;
}

void Contact::setAddress(const std::string &Address) {
    Contact::address = Address;
}

std::istream &operator>>(std::istream &in, Contact &addressBook) {
    in >> addressBook.tellNumber >> addressBook.userName >> addressBook.address;
    return in;
}

std::ostream &operator<<(std::ostream &out, Contact &addressBook) {
    out << addressBook.tellNumber << " " << addressBook.userName << " " << addressBook.address << std::endl;
    return out;
}

bool Contact::operator==(const Contact &rhs) const {
    return tellNumber == rhs.tellNumber &&
           userName == rhs.userName &&
           address == rhs.address;
}

bool Contact::operator!=(const Contact &rhs) const {
    return !(rhs == *this);
}

unsigned long long Contact::getTellNumber() const {
    return tellNumber;
}

void Contact::setTellNumber(long long int TellNumber) {
    Contact::tellNumber = TellNumber;
}

#endif //HASHTABLE_CONTACT_H
