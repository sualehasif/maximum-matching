//
// Created by sualehasif on 5/16/21.
//

#ifndef MAXIMUM_MATCHING_LIST_H
#define MAXIMUM_MATCHING_LIST_H

namespace maxmatching {
    template<class T>
    class List;

    /* Basic implementation of elements in a doubly connected list */
    template<class T>
    class ListElement {
    public:
        List<T> *containingList;
        ListElement<T> *prvElem;
        ListElement<T> *nxtElem;
        T *value;

        ListElement();

        explicit ListElement(T *value);

        ~ListElement();

        void deleteFull();
    };

    template<class T>
    ListElement<T>::ListElement()
            : containingList(nullptr), prvElem(nullptr), nxtElem(nullptr), value(nullptr) {}

    template<class T>
    ListElement<T>::ListElement(T *value)
            : containingList(nullptr), prvElem(nullptr), nxtElem(nullptr), value(value) {}


    template<class T>
    ListElement<T>::~ListElement() {
        if (this->containingList != nullptr) {
            this->containingList->remove(this);
        }
    }

    template<class T>
    void ListElement<T>::deleteFull() {
        delete (this->value);
        delete (this);
    }

    template<class T>
    class List {
    private:
        ListElement<T> *firstElem;
        ListElement<T> *lastElem;
        unsigned int size;
    public:
        List();

        ~List();

        void push(T *elem);

        void push(ListElement<T> *elem);

        void append(T *elem);

        void append(ListElement<T> *elem);

        T *pop();

        ListElement<T> *popElem();

        void remove(ListElement<T> *elem);

        void clear();

        void deleteStructure();

        void deleteFull();

        ListElement<T> *getFirstElement();

        ListElement<T> *getLastElement();

        unsigned int getSize();

        bool isEmpty();
    };

    template<class T>
    List<T>::List()
            : firstElem(nullptr), lastElem(nullptr), size(0) {}

    template<class T>
    List<T>::~List() {
        while (this->firstElem != nullptr) {
            this->popElem();
        }
    }


    template<class T>
    void List<T>::push(T *elem) {
        auto *le = new ListElement<T>(elem);
        this->push(le);
    }

    template<class T>
    void List<T>::push(ListElement<T> *elem) {
        elem->containingList = this;
        elem->prvElem = nullptr;
        elem->nxtElem = this->firstElem;
        if (this->firstElem != nullptr) {
            this->firstElem->prvElem = elem;
        } else {
            this->lastElem = elem;
        }
        this->firstElem = elem;
        this->size++;
    }

    template<class T>
    void List<T>::append(T *elem) {
        auto *le = new ListElement<T>(elem);
        this->append(le);
    }

    template<class T>
    void List<T>::append(ListElement<T> *elem) {
        elem->containingList = this;
        elem->prvElem = this->lastElem;
        elem->nxtElem = nullptr;
        if (this->lastElem != nullptr) {
            this->lastElem->nxtElem = elem;
        } else {
            this->firstElem = elem;
        }
        this->lastElem = elem;
        this->size++;
    }

    template<class T>
    T *List<T>::pop() {
        ListElement<T> *buffer = this->popElem();
        if (buffer == nullptr) {
            return nullptr;
        } else {
            T *ret = buffer->value;
            delete (buffer);
            return ret;
        }
    }

    template<class T>
    ListElement<T> *List<T>::popElem() {
        if (this->firstElem == nullptr) {
            return nullptr;
        } else {
            ListElement<T> *ret = this->firstElem;
            this->firstElem = ret->nxtElem;
            if (this->firstElem != nullptr) {
                this->firstElem->prvElem = nullptr;
            }
            if (this->lastElem == ret) {
                this->lastElem = nullptr;
            }
            ret->containingList = nullptr;
            ret->nxtElem = nullptr;
            this->size--;
            return ret;
        }
    }

    template<class T>
    void List<T>::remove(ListElement<T> *elem) {
        if (elem->containingList != this) {
            return;
        }
        if (elem->prvElem != nullptr) {
            elem->prvElem->nxtElem = elem->nxtElem;
        } else if (elem == this->firstElem) {
            this->firstElem = elem->nxtElem;
        }
        if (elem->nxtElem != nullptr) {
            elem->nxtElem->prvElem = elem->prvElem;
        } else if (elem == this->lastElem) {
            this->lastElem = elem->prvElem;
        }
        elem->containingList = nullptr;
        elem->nxtElem = elem->prvElem = nullptr;
        this->size--;
    }

    template<class T>
    void List<T>::clear() {
        while (this->size > 0) {
            (void) this->popElem();
        }
    }


    template<class T>
    void List<T>::deleteStructure() {
        ListElement<T> *iter = this->firstElem;
        while (iter != nullptr) {
            ListElement<T> *buffer = iter->nxtElem;
            delete (iter);
            iter = buffer;
        }
        delete (this);
    }

    template<class T>
    void List<T>::deleteFull() {
        ListElement<T> *iter = this->firstElem;
        while (iter != nullptr) {
            ListElement<T> *buffer = iter->nxtElem;
            iter->deleteFull();
            iter = buffer;
        }
        delete (this);
    }

    template<class T>
    ListElement<T> *List<T>::getFirstElement() {
        return this->firstElem;
    }

    template<class T>
    ListElement<T> *List<T>::getLastElement() {
        return this->lastElem;
    }

    template<class T>
    unsigned int List<T>::getSize() {
        return this->size;
    }

    template<class T>
    bool List<T>::isEmpty() {
        return this->size == 0;
    }

}

#endif //MAXIMUM_MATCHING_LIST_H
