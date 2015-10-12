/**
*
*	Stack
*	Implementace Stacku v c++ za pouziti templatu a shared_ptr.
*   This file is part of the VZI course
*
*	@file stack.h
*   @version 0.1
*
*	New BSD License
*	https://www.vutbr.cz/studis/student.phtml?gm=gm_detail_predmetu&apid=158780
*
*	C language is all about speed. Hot, nasty, bad-ass speed. - Eleanor Roosevelt, 1936.
*/

#pragma once
#include <iostream>
#include <memory>

/**
*  Struktura, ktera nam tvori uzel spojiteho seznamu. 
*/
template <class T> 
struct node
{
    std::shared_ptr<node> next;
    std::shared_ptr<node> prior;
    std::shared_ptr<T>    data;

    node() {}

    node(std::shared_ptr<T> data_)
    {
        next  = nullptr;
        prior = nullptr;
        data = data_;
    }
};

/**
*  Trida implementujici Stack pomoci obousmerneho spojiteho seznamu.
*/
template<typename T> class Stack
{
public:

    Stack():m_head(nullptr), m_last(nullptr), m_size(0)
    {}

    virtual ~Stack()
    {
        m_head = nullptr;
        m_last = nullptr;
        m_size = 0;
    }

    /**
    *  @brief Ulozi shared_ptr na data do stacku
    *  @param[in] shared_ptr na data typu T
    */
    void push(std::shared_ptr<T> data)
    {
        try
        {
            std::shared_ptr<node<T>> tmp(new node<T>(data));

            if (m_head == nullptr)
            {
                m_head = tmp;
                m_last = m_head;
            }
            else
            {
                m_last->next = tmp;
                tmp->prior = m_last;
                tmp->next = nullptr;
                m_last = tmp;
            }

            m_size++;
        }
        catch (std::bad_alloc const& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    /**
    *  Pretizena varianta Push(), ktera vezme data typu T a zkopiruje je
    *  do nove vytvorene (dynamicky alokovane) promenne
    *  @param[in] Const Reference na ukladane data
    */
    void push(const T& data)
    {
        try
        {
            auto dataPtr = std::make_shared<T>(data);
            push(dataPtr);
        }
        catch (std::bad_alloc const& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    /**
    *  @brief Pop vybere z vrcholu stacku uzel a vraci ulozene data
    *  @return Vraci data typu T
    */
    T pop()
    {

        if (m_size <= 0)
        {
            throw std::underflow_error("Stack is empty!");
        }
        else
        {
            auto data = *m_last->data;
            auto tmp  = m_last;

            if (m_size > 1)
            {
                tmp->prior->next = nullptr;
                m_last = tmp->prior;
            }
            else
            {
                m_last = nullptr;
            }

            m_size--;

            return data;
        }
    }

    /**
    *  @brief Vrati (uint) pocet prvku ve stacku
    *  @return Velikost stacku
    */
    size_t size() const
    {
        return m_size;
    }

    /**
    *  @brief Top vraci referenci na top prvek ve stacku, 
    *  tj. v nasem pripade posledni
    *  @return Reference na data uzlu, ktery je na vrcholu Stacku
    */
    T& top() 
    {
        return *m_last->data;
    }


private:
    std::shared_ptr<node<T>> m_head; ///< zacatek naseho stacku
    std::shared_ptr<node<T>> m_last; ///< posledni prvek stacku
    size_t m_size; ///< velikost stacku
};