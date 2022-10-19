//
// Created by admin on 2022-10-20.
//

#include "Person.h"


struct Person::PersonImpl
{
    void greet(Person *p);
};

Person::Person()
    :impl(new PersonImpl)
{

}

Person::~Person()
{
    delete impl;
}

// 모든 제어를 PersonImpl::greet()에 위임한다.
void Person::greet()
{
    impl->greet(this);
}

void Person::PersonImpl::greet(Person *p)
{
    printf("hello %s", p->name.c_str());
}
