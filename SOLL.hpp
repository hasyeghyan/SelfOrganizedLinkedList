#ifndef SOLL_HPP
#define SOLL_HPP

#include <iostream>
#include <limits>

template <typename T>
class SOLL {
    private:
        struct Node {
            T val;
            Node* next;
            Node* prev;
            Node* asc;
            Node* desc;

            Node(T _val = T(), Node* n = nullptr, Node* p = nullptr, Node* asc = nullptr, Node* desc = nullptr) : val{_val}, next{n}, prev{p}, asc{asc}, desc{desc} {}
            template <typename... Args>
            Node(Node* n, Node* p, Node* asc, Node* desc, Args&&... args) : val{std::forward<Args>(args)...}, next{n}, prev{p}, asc{asc}, desc{desc} {}
        }; 
        
        Node* sentinel;
        Node* sorted;
        size_t size = 0;

    public:

        template<bool b>
        class Iter {
            private:
                Node* curr;
            public:
                friend class SOLL<T>;

                Iter(Node* c) : curr{c} {}
                Iter(const Iter& other) : curr{other.curr} {}
                
                bool operator !=(Iter<true> other) const { return curr != other.curr; }  
                bool operator ==(Iter<true> other) const { return curr == other.curr; }                        
                
                Iter& operator++() { 
                    curr = b ? curr->next : curr->asc; 
                    return *this;
                }
                Iter<true> operator++(int) { 
                    Iter<true> tmp{curr}; 
                    curr = b ? curr->next : curr->asc;   
                    return tmp;
                }
                Iter& operator--() { 
                    curr = b ? curr->prev : curr->desc; 
                    return *this;
                }
                Iter<true> operator--(int) { 
                    Iter<true> tmp{curr}; 
                    curr = b ? curr->prev : curr->desc;   
                    return tmp;
                }
                T& operator*() const { return curr->val; }
                T* operator->() const { return &(curr->val); }
        };
        
        template<bool b>
        class const_Iter {
            private:
                const Node* curr;
            public:
                friend class SOLL<T>;

                const_Iter(Node* c) : curr{c} {}
               
                bool operator !=(const_Iter<true> other) const { return curr != other.curr; }  
                bool operator ==(const_Iter<true> other) const { return curr == other.curr; }                        
                
                const_Iter& operator++() { 
                    curr = b ? curr->next : curr->asc; 
                    return *this;
                }
                const_Iter<true> operator++(int) { 
                    const_Iter<true> tmp{curr}; 
                    curr = b ? curr->next : curr->asc;   
                    return tmp;
                }
                const_Iter& operator--() { 
                    curr = b ? curr->prev : curr->desc;   
                    return *this;
                }
                const_Iter<true> operator--(int) { 
                    const_Iter<true> tmp{curr}; 
                    curr = b ? curr->prev : curr->desc;   
                    return tmp;
                }
                const T& operator*() const { return curr->val; }
                const T* operator->() const { return &(curr->val); }
        };

        template<bool b>
        class reverse_Iter {
            private:
                Iter<b> curr_iter;
            public:
                friend class SOLL<T>;

                reverse_Iter(Iter<true> c) : curr_iter{c} {}
                
                bool operator !=(reverse_Iter<true> other) const { return curr_iter != other.curr_iter; }  
                bool operator ==(reverse_Iter<true> other) const { return curr_iter == other.curr_iter; }                        
               
                reverse_Iter& operator++() { 
                    --curr_iter;
                    return *this;
                }
                reverse_Iter<true> operator++(int) { 
                    reverse_Iter<true> tmp{curr_iter}; 
                    --curr_iter;   
                    return tmp;
                }
                reverse_Iter& operator--() { 
                    ++curr_iter;
                    return *this;
                }
                reverse_Iter<true> operator--(int) { 
                    reverse_Iter<true> tmp{curr_iter}; 
                    ++curr_iter;   
                    return tmp;
                }
                T& operator*() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return *tmp;
                }
                T* operator->() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return tmp.operator->(); 
                }
        };

        template<bool b>
        class const_reverse_Iter {
            private:
                const_Iter<b> curr_iter;
            public:
                friend class SOLL<T>;

                const_reverse_Iter(const_Iter<true> c) : curr_iter{c} {}
               
                bool operator !=(const_reverse_Iter<true> other) const { return curr_iter != other.curr_iter; }  
                bool operator ==(const_reverse_Iter<true> other) const { return curr_iter == other.curr_iter; }                        
               
                const_reverse_Iter& operator++() { 
                    --curr_iter;
                    return *this;
                }
                const_reverse_Iter<true> operator++(int) { 
                    const_reverse_Iter<true> tmp{curr_iter}; 
                    --curr_iter;   
                    return tmp;
                }
                const_reverse_Iter& operator--() { 
                    ++curr_iter;
                    return *this;
                }
                const_reverse_Iter<true> operator--(int) { 
                    const_reverse_Iter<true> tmp{curr_iter}; 
                    ++curr_iter;   
                    return tmp;
                }
                const T& operator*() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return *tmp;
                }
                const T* operator->() const { 
                    auto tmp = curr_iter;
                    --tmp;
                    return tmp.operator->(); 
                }
        };

        Iter<true> begin() const {
            return Iter{sentinel->next};
        }
        
        Iter<true> end() const {
            return Iter{sentinel};
        }

        const_Iter<true> cbegin() const {
            return const_Iter{sentinel->next};
        }
        
        const_Iter<true> cend() const {
            return const_Iter{sentinel};
        }

        reverse_Iter<true> rbegin() const {
            return reverse_Iter{end()};
        }

        reverse_Iter<true> rend() const {
            return reverse_Iter{begin()};
        }

        const_reverse_Iter<true> crbegin() const {
            return const_reverse_Iter{end()};
        }

        const_reverse_Iter<true> crend() const {
            return const_reverse_Iter{begin()};
        }

        Iter<false> sortedbegin() const {
            return Iter{sorted->asc};
        }
        
        Iter<false> sortedend() const {
            return Iter{sorted};
        }

        const_Iter<false> sortedcbegin() const {
            return const_Iter{sorted->asc};
        }
        
        const_Iter<false> sortedcend() const {
            return const_Iter{sorted};
        }

        reverse_Iter<false> sortedrbegin() const {
            return reverse_Iter{sortedend()};
        }

        reverse_Iter<false> sortedrend() const {
            return reverse_Iter{sortedbegin()};
        }

        const_reverse_Iter<false> sortedcrbegin() const {
            return const_reverse_Iter{sortedend()};
        }

        const_reverse_Iter<false> sortedcrend() const {
            return const_reverse_Iter{sortedbegin()};
        }

        SOLL();
        SOLL(size_t count, const T& _val);
        SOLL(std::initializer_list<T> init);
        SOLL(Iter<true> first,Iter<true> last);
        SOLL(const SOLL& other);
        SOLL(SOLL&& other) noexcept;
        ~SOLL();

        SOLL& operator=(const SOLL& other);
        SOLL& operator=(SOLL&& other) noexcept;
        SOLL& operator=(std::initializer_list<T> init);  
        void assign(size_t count, const T& _val);
        void assign(std::initializer_list<T> init);
       
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        T& sortedfront();
        const T& sortedfront() const;
        T& sortedback();
        const T& sortedback() const;
       
        bool empty () const noexcept { return sentinel->next == sentinel; }
        size_t get_size() const noexcept { return size; }
        size_t max_size() const noexcept { return std::numeric_limits<size_t>::max(); } 
        Node* get_sentinel()const noexcept { return sentinel; }


        void clear() noexcept;
        void push_back(const T& value);
        void push_back(T&& value);
        void pop_back();
        void push_front(const T& value);
        void push_front(T&& value);
        void pop_front();
        void resize(size_t count );
        void resize(size_t count, const T& value);
        void swap(SOLL& other ) noexcept;
        void insert_sorted(Node* nn);
        Iter<true> insert(Iter<true> pos, const T &value);
        Iter<true> insert(Iter<true> pos, T&& value );
        Iter<true> insert(Iter<true> pos, size_t count, const T& value );
        Iter<true> insert(Iter<true> pos, std::initializer_list<T> ilist);
        Iter<true> insert(Iter<true> pos, Iter<true> first, Iter<true> last);
        void erase_sorted(Node* n);
        Iter<true> erase(Iter<true> pos);
        Iter<true> erase(Iter<true> first, Iter<true> last);
        void splice(Iter<true> pos, SOLL& other);
        void splice(Iter<true> pos, SOLL&& other);
        void splice(Iter<true> pos, SOLL& other, Iter<true> it);
        void splice(Iter<true> pos, SOLL&& other, Iter<true> it);
        void splice(Iter<true> pos, SOLL& other, Iter<true> first,Iter<true> last);
        void splice(Iter<true> pos, SOLL&& other, Iter<true> first, Iter<true> last);
        template <typename... Args>
        void emplace_back(Args&&... args);
        template <typename... Args>
        void emplace_front(Args&&... args);
        template <typename... Args>
        void emplace(Iter<true> pos, Args&&... args);

        void merge(SOLL& other);
        size_t remove(const T& value);
        void reverse();
        void unique();

        template <typename U>
        friend bool operator==(const SOLL<U>& l,const SOLL<U>& r);
        template <typename U>
        friend bool operator!=(const SOLL<U>& l,const SOLL<U>& r) { return !(l == r); }
        template <typename U>
        friend bool operator<(const SOLL<U>& l,const SOLL<U>& r);
        template <typename U>
        friend bool operator<=(const SOLL<U>& l,const SOLL<U>& r) { return !(r < l); }
        template <typename U>
        friend bool operator>(const SOLL<U>& l,const SOLL<U>& r) { return r < l; }
        template <typename U>
        friend bool operator>=(const SOLL<U>& l,const SOLL<U>& r) { return !(l < r); }
};

template <typename T>
SOLL<T>::SOLL() : sentinel{new Node} {
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    sorted->asc = sorted;
    sorted->desc = sorted;
}

template <typename T>
SOLL<T>::SOLL(size_t count, const T& _val) : SOLL() {
    for (size_t i{}; i < count; ++i) {
        push_back(_val);
    }
}

template <typename T>
SOLL<T>::SOLL(std::initializer_list<T> init) : SOLL() {
    for (auto i : init) {
        push_back(i);
    }
}

template <typename T>    
SOLL<T>::SOLL(Iter<true> first,Iter<true> last) : SOLL() {
    insert(begin(), first, last);
}

template <typename T>
SOLL<T>::SOLL(const SOLL& other) : SOLL() {
    const auto* tmp = other.sentinel->next;
    while (tmp != other.sentinel) {
        push_back(tmp->val);
        tmp = tmp->next;
    }
}

template <typename T>
SOLL<T>::SOLL(SOLL&& other) noexcept : sentinel{other.sentinel}, sorted{other.sorted}, size{other.size} {
    other.sentinel = new Node(); 
    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;
    other.sorted = new Node();
    other.sorted->asc = other.sorted;
    other.sorted->desc = other.sorted;
    other.size = 0;
}

template <typename T>
SOLL<T>::~SOLL() {
    clear();
    delete sentinel;
    delete sorted;
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(const SOLL& other) {
    if (this != &other) {
        clear();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        sorted->asc = sorted;
        sorted->desc = sorted;
        const auto* tmp = other.sentinel->next;
        while (tmp != other.sentinel) {
            push_back(tmp->val);
            tmp = tmp->next;
        }
    }
    return *this;
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(SOLL&& other) noexcept {
    if (this != &other) {
        clear();
        sentinel = other.sentinel;
        sorted = other.sorted;
        size = other.size;
        other.sentinel = new Node(); 
        other.sentinel->next = other.sentinel;
        other.sentinel->prev = other.sentinel;
        other.sorted = new Node(); 
        other.sorted->asc = other.sorted;
        other.sorted->desc = other.sorted;
        other.size = 0;
    }
    return *this;
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(std::initializer_list<T> init) {
    clear();
    for (auto i : init) {
        emplace_back(i);
    }
    return *this;
}

template <typename T>
void SOLL<T>::assign(size_t count, const T& _val) {
    SOLL<T> tmp(count, _val);
    swap(tmp); 
}

template <typename T>
void SOLL<T>::assign( std::initializer_list<T> init) {
    SOLL<T> tmp(init);
    swap(tmp);
}

template <typename T>
T& SOLL<T>::front() {
    if (empty()) throw std::logic_error("Can't get empty list's first element.");
    return sentinel->next->val;
}

template <typename T>
const T& SOLL<T>::front() const {
    if (empty()) throw std::logic_error("Can't get empty list's first element.");
    return sentinel->next->val;
}

template <typename T>
T& SOLL<T>::back() {
    if (empty()) throw std::logic_error("Can't get empty list's last element.");
    return sentinel->prev->val;
}

template <typename T>
const T& SOLL<T>::back() const {
    if (empty()) throw std::logic_error("Can't get empty list's last element.");
    return sentinel->prev->val;
}

template <typename T>
T& SOLL<T>::sortedfront() {
    if (empty()) throw std::logic_error("Can't get empty list's first element.");
    return sorted->asc->val;
}

template <typename T>
const T& SOLL<T>::sortedfront() const {
    if (empty()) throw std::logic_error("Can't get empty list's first element.");
    return sorted->asc->val;
}

template <typename T>
T& SOLL<T>::sortedback() {
    if (empty()) throw std::logic_error("Can't get empty list's last element.");
    return sorted->desc->val;
}

template <typename T>
const T& SOLL<T>::sortedback() const {
    if (empty()) throw std::logic_error("Can't get empty list's last element.");
    return sorted->desc->val;
}

template <typename T>
void SOLL<T>::clear() noexcept {
    erase(begin(), end());
}

template <typename T>
void SOLL<T>::push_back(const T& value) {
    insert(end(), value); 
}

template <typename T>
void SOLL<T>::push_back(T&& value) {
    insert(end(), std::move(value));
}

template <typename T>
void SOLL<T>::pop_back() {
    erase(--end());
}

template <typename T>
void SOLL<T>::push_front(const T& value) {
    insert(begin(), value);
}

template <typename T>
void SOLL<T>::push_front(T&& value) {
    insert(begin(), std::move(value));
}

template <typename T>
void SOLL<T>::pop_front() {
    erase(begin());
}

template <typename T>
void SOLL<T>::resize(size_t count) {
    if (count == size) return;
    
    if (size > count) {
        for (size_t i{}; i < size - count; ++i) 
            pop_back();
    }

    else if (size < count) {
        for (size_t i{}; i < count - size; ++i) 
            push_back(T());
    }
}

template <typename T>
void SOLL<T>::resize(size_t count, const T& value) {
    if (count == size) return;
    
    if (size > count) {
        for (size_t i{}; i < size - count; ++i) 
            pop_back();
    }

    else if (size < count) {
        for (size_t i{}; i < count - size; ++i) 
            push_back(value);
    }
}

template <typename T>
void SOLL<T>::swap(SOLL& other) noexcept {
    std::swap(sentinel,other.sentinel);
    std::swap(sorted, other.sorted);
    std::swap(size,other.size);
}

template<typename T>
void SOLL<T>::insert_sorted(Node* nn) {
    Node* curr = sorted->asc;

    while (curr != sorted && curr->val < nn->val) curr = curr->asc;
    nn->asc = curr;
    nn->desc = curr->desc;
    curr->desc->asc = nn;
    curr->desc = nn;
}

template <typename T>
typename SOLL<T>::Iter<true> SOLL<T>::insert(Iter<true> pos, const T& value) {
    auto* ins = pos.curr;

    auto* newNode = new Node(ins, ins->prev, value);
    ins->prev->next = newNode;
    ins->prev = newNode;
    
    ++size;
    insert_sorted(newNode);
    return Iter(newNode);
}

template <typename T>
typename SOLL<T>::Iter<true> SOLL<T>::insert(Iter<true> pos, T&& value) {
    auto* ins = pos.curr;

    auto* newNode = new Node(ins, ins->prev, std::move(value));
    ins->prev->next = newNode;
    ins->prev = newNode;
    
    ++size;
    insert_sorted(newNode);
    return Iter(newNode);
}

template <typename T>
typename SOLL<T>::Iter<true>  SOLL<T>::insert(Iter<true> pos, size_t count, const T& value ) {
    int i{};
    auto ans = pos;
    for (size_t j{}; j < count; ++j) {
        auto ret = insert(pos,value);
        if (i++ == 0) ans = ret;
    }
    return ans;
}

template <typename T>
typename SOLL<T>::Iter<true> SOLL<T>::insert(Iter<true> pos, std::initializer_list<T> ilist) {
    int i{};
    auto ans = pos;
    for (auto i : ilist) {
        auto ret = insert(pos,i);
        if (i++ == 0) ans = ret; 
    }
    return ans;
}

template <typename T>
typename SOLL<T>::Iter<true> SOLL<T>::insert(Iter<true> pos, Iter<true> first, Iter<true> last) {
    int i{};
    auto ans = pos;
    for (auto it = first; it != last; ++it) {
        auto ret = insert(pos, *it);
        if (i++ == 0) ans = ret;
    }
    return ans;
}

template<typename T>
void SOLL<T>::erase_sorted(Node* n) {
    Node* curr = sorted->asc;

    while (curr != sorted && curr != n) curr = curr->asc;

    curr->desc->asc = curr->asc;
    curr->asc->desc = curr->desc;
}

template <typename T>
typename SOLL<T>::Iter<true> SOLL<T>::erase(Iter<true> pos) {
    if(empty() || pos.curr == sentinel) return pos;
    --size;
     
    auto* tmp = pos.curr;
    auto it = Iter(tmp->next);
    
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    
    erase_sorted(tmp);
    delete tmp;
    return it;
}

template <typename T>
typename SOLL<T>::Iter<true> SOLL<T>::erase(Iter<true> first, Iter<true> last) {
    if (first == last) return last;
    auto ans = first;;
    for (auto it = first; it != last; it = ans) {
        ans = erase(it);
    }
    return ans;
}

template <typename T>
void SOLL<T>::splice(Iter<true> pos, SOLL& other) {
    if (this == &other || other.empty()) return;
    
    for (auto it = other.begin(); it != other.end(); ++it) {
        insert_sorted(it.curr);
    }

    Node* ins = pos.curr;
    Node* first = other.sentinel->next;
    Node* last = other.sentinel->prev;

    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;

    Node* prevNode = ins->prev;

    prevNode->next = first;
    first->prev = prevNode;

    last->next = ins;
    ins->prev = last;

    size += other.size;
    other.size = 0;
}

template <typename T>
void  SOLL<T>::splice(Iter<true> pos, SOLL&& other) {
    splice(pos,other);
}

template <typename T>
void  SOLL<T>::splice(Iter<true> pos, SOLL& other, Iter<true> it) {
    if (this == &other && (pos == it || pos.curr == it.curr->next)) return;
     
    insert_sorted(it.curr);

    Node* ins = pos.curr;
    Node* prevNode = ins->prev;

    Node* tmp = it.curr;
    Node* tmpPrev = tmp->prev;
    tmpPrev->next = tmp->next;
    tmp->next->prev = tmpPrev;
    --other.size;
    
    prevNode->next = tmp;
    ins->prev = tmp;
    tmp->next = ins;
    tmp->prev = prevNode;
    ++size;
}

template <typename T>
void  SOLL<T>::splice(Iter<true> pos, SOLL&& other, Iter<true> it) {
    splice(pos,other,it);
}

template <typename T>
void SOLL<T>::splice(Iter<true> pos, SOLL& other, Iter<true> first, Iter<true> last) {
    if (first == last) return;
 
    for (auto tmp = first; tmp != last; ++tmp) insert_sorted(tmp.curr);
     
    Node* firstNode = first.curr;
    Node* lastNode  = last.curr->prev; 
    Node* srcBefore = firstNode->prev;
    Node* srcAfter  = last.curr;

    Node* ins = pos.curr;
    Node* destPrev = ins->prev;

    srcBefore->next = srcAfter;
    srcAfter->prev = srcBefore;

    destPrev->next = firstNode;
    firstNode->prev = destPrev;
    
    lastNode->next = ins;
    ins->prev = lastNode;

    if (this != &other) {
        size_t count = 0;
        for (auto it = first; it != last; ++it) ++count;
        size += count;
        other.size -= count;
    }
}
template <typename T>
void SOLL<T>::splice(Iter<true> pos, SOLL&& other, Iter<true> first, Iter<true> last) {
    splice(pos,other,first,last);
}

template <typename T>
template <typename... Args>
void SOLL<T>::emplace_back(Args&&... args) {
    ++size;
    auto* tmp = new Node(sentinel, sentinel->prev, std::forward<Args>(args)...);
    sentinel->prev->next = tmp;
    sentinel->prev = tmp;
    insert_sorted(tmp);
}

template <typename T>
template <typename... Args>
void SOLL<T>::emplace_front(Args&&... args) {
    ++size;
    auto* tmp = new Node(sentinel->next, sentinel, std::forward<Args>(args)...);
    sentinel->next->prev = tmp;
    sentinel->next = tmp;
    insert_sorted(tmp);
}

template <typename T>
template <typename... Args>
void SOLL<T>::emplace(Iter<true> pos, Args&&... args) {
    auto* ins = pos.curr;

    auto* newNode = new Node(ins, ins->prev, std::forward<Args>(args)...);
    ins->prev->next = newNode;
    ins->prev = newNode;
    
    insert_sorted(newNode);
    ++size;
}


template <typename T>
void SOLL<T>::merge(SOLL& other) {
    if (this == &other) return;
    
    for (auto tmp = other.begin(); tmp != other.end(); ++tmp) {
        insert_sorted(tmp.curr);
    }

    if (empty()) { 
        swap(other);
        return;
    }

    size += other.size;
    auto* tmp1 = sentinel->next;
    auto* current = other.sentinel->next;

    while (current != other.sentinel) {
        auto* tmp2 = current;
        if (tmp2->val >= tmp1->val) {
            if (tmp1 == sentinel->prev) { 
                current = current->next;
                tmp2->next = sentinel;
                tmp2->prev = tmp1;
                tmp1->next = tmp2;
                sentinel->prev = tmp2;
            }
            tmp1 = tmp1->next;
            continue;
        }
        
        current = current->next;        
        
        tmp2->next = tmp1;
        tmp2->prev = tmp1->prev;
        tmp1->prev->next = tmp2;
        tmp1->prev = tmp2; 
    }
    other.sentinel->next = other.sentinel;
    other.sentinel->prev = other.sentinel;
    other.size = 0;
}

template <typename T>
size_t SOLL<T>::remove(const T& value) {
    if (empty()) return 0;
    
    size_t count = 0;
    auto* tmp = sentinel->next;

    while (tmp != sentinel) {
        if (tmp ->val == value) {
            auto* current = tmp;
            
            current->next->prev = current->prev;
            current->prev->next = current->next;
            tmp = tmp->next;
            erase_sorted(current);
            delete current;
            
            ++count;
            --size;
        }
        else { 
            tmp = tmp->next;
        }
    }
    return count;
}

template <typename T>
void SOLL<T>::reverse() {
    if (empty()) return;
    
    auto* tmp = sentinel->next;
    while (tmp != sentinel) {
        std::swap(tmp->next,tmp->prev);
        tmp = tmp->prev;
    }   
    std::swap(sentinel->next,sentinel->prev);
}

template <typename T>
void SOLL<T>::unique() {
    if (empty()) return;
    
    auto* tmp = sentinel->next;
    while (tmp != sentinel->prev) {
        if (tmp->val == tmp->next->val) {
            auto* tmp2 = tmp->next;

            tmp2->next->prev = tmp;
            tmp->next = tmp2->next;
            
            erase_sorted(tmp2);
            delete tmp2;
            --size;
        }
        else tmp = tmp->next;
    }
}

template <typename T>
bool operator==(const SOLL<T>& l,const SOLL<T>& r) {
    if (l.get_size() != r.get_size()) return false;
   
    auto* tmp1 = l.get_sentinel()->next;
    auto* tmp2 = r.get_sentinel()->next; 
    
    while (tmp1 != l.get_sentinel()) {
        if(tmp1->val != tmp2->val) return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return true;
}

template <typename T>
bool operator<(const SOLL<T>& l,const SOLL<T>& r) {    
    auto* tmp1 = l.get_sentinel()->next;
    auto* tmp2 = r.get_sentinel()->next; 
    
    while (tmp1 != l.get_sentinel() && tmp2 != r.get_sentinel()) {
        if(tmp1->val < tmp2->val) return true;
        else if(tmp1->val > tmp2->val) return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    if (l.get_size() < r.get_size()) return true;
    return false;
}

#endif