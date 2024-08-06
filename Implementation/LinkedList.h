#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = new Node<T>(T());
    head->next = NULL;
    head->prev = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs) {
    
    head = new Node<T>(T());
    head->next = NULL;
    head->prev = NULL;
    size = 0;
    if (rhs.head) {
        Node<T>* rhs_current = rhs.head->next; 
        Node<T>* current = head; 
        while (rhs_current != NULL) {
            Node<T>* n_node = new Node<T>(rhs_current->data);
            current->next = n_node;
            n_node->prev = current;
        
            current = n_node;
            rhs_current = rhs_current->next;
        
            size++;
        }
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{   
    Node<T>* tmp = head;
    while(tmp != NULL) {
        Node<T>* tmp2 = tmp->next;
        delete tmp;
        tmp = tmp2;
    }
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if(this == &rhs) return *this;
    removeAllNodes();
    delete head;

    head = new Node<T>(T());
    head->next = NULL;
    head->prev = NULL;
    size = 0;

    Node<T>* rhs_current = rhs.head->next;
    Node<T>* our_current = head;
    while(rhs_current != NULL) {
        Node<T>* n_node = new Node<T>(rhs_current->data);

        our_current->next = n_node;
        n_node->prev = our_current;

        our_current = n_node;
        rhs_current = rhs_current->next;

        size++;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return head->next == NULL;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    Node<T>* current = head->next;
    while(current != NULL) {
        if(current == node) return true;
        current = current->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if(isEmpty()) return NULL;
    return head->next;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if(isEmpty()) return NULL;
    int index = 0;
    Node<T>* last_node = head;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    return last_node;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T>* ret_node = head->next;
    while(ret_node != NULL) {
        if(ret_node->data == data) return ret_node;
        ret_node = ret_node->next;
    }
    return NULL;
}


template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{   
    if(index < 0 || index >= size) return NULL;
    /*index 0*/
    Node<T>* ret_node = head;
    int i;
    for(i = 0; i <= index; i++){
        ret_node = ret_node->next;
    }
    return ret_node;
}   

template<class T>
void LinkedList<T>::append(const T &data)
{   
    Node<T>* n_node = new Node<T>(data);
    if(isEmpty()) {
        head->next = n_node;
        n_node->prev = head;
    }
    
    else{
        
        Node<T>* last = getLastNode();
        last->next = n_node;
        n_node->next = NULL;
        n_node->prev = last;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    Node<T>* n_node = new Node<T>(data);
    if(isEmpty()) {
        head->next = n_node;
        n_node->prev = head;
    }

    else {
        Node<T>* nextofour = head->next;
        head->next = n_node;
        n_node->next = nextofour;
        nextofour->prev = n_node;
        n_node->prev = head;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (!containsNode(node)) return;
    
    Node<T>* n_node = new Node<T>(data);
    Node<T>* nextofnode = node->next;

    node->next = n_node;
    n_node->prev = node;

    if (nextofnode != NULL) {
        nextofnode->prev = n_node;
        n_node->next = nextofnode;
    } else {
        n_node->next = NULL;
    }

    size++;
}


template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if(index >= size || index < 0) return;
    else if(index == 0) prepend(data);

    Node<T>* beforenode = getNodeAtIndex(index-1);
    insertAfterNode(data, beforenode);

    return;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    if(!containsNode(node)) return -1;
    int index = 0;
    Node<T>* current = head->next;
    while(current != NULL) {
        if(current == node) return index;
        index++;
        current = current->next;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if(currentIndex >= size || currentIndex < 0 || newIndex < 0) return;

    Node<T>* current = getNodeAtIndex(currentIndex);
    current->next->prev = current->prev;
    current->prev->next = current->next;
    if(newIndex >= size-1) {
        Node<T>* lastnode = getLastNode();
        lastnode->next = current;
        current->prev = lastnode;
        current->next = NULL;
    }
    else {
        Node<T>* othernode = getNodeAtIndex(newIndex);
        othernode->prev->next = current;
        current->next = othernode;
        current->prev = othernode->prev;
        othernode->prev = current;
    }
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    if (sourceIndex < 0 || sourceIndex >= size || destIndex < 0 || destIndex >= size) {
        return;
    }

    Node<T>* sourceN = getNodeAtIndex(sourceIndex);
    Node<T>* destN = getNodeAtIndex(destIndex);

    if (!sourceN || !destN) {
        return;
    }

    destN->data = destN->data + sourceN->data;

    
    sourceN->prev->next = sourceN->next;
    if (sourceN->next) {
        sourceN->next->prev = sourceN->prev;
    }

    size--;
    delete sourceN;
}


template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
    if(!containsNode(node) || node == NULL) return;

    if(node->next != NULL){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        size--; 
        delete node;
    }

    else {
        node->prev->next = NULL;
        size--;
        delete node;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{   
    Node<T>* wbrnode;
    while(wbrnode = getNode(data)){
        removeNode(wbrnode);
    }
    return;
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (index < 0 || index >= size || isEmpty()) return;
    
    Node<T>* wbrnode = getNodeAtIndex(index);
    
    if (wbrnode->prev)
        wbrnode->prev->next = wbrnode->next;
    if (wbrnode->next)
        wbrnode->next->prev = wbrnode->prev;
    
    delete wbrnode;
    size--;
}

template<class T>
void LinkedList<T>::removeAllNodes()
{   
    Node<T>* current = head->next;
    while (current != NULL) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head->next = NULL;
    size = 0;
}


template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H