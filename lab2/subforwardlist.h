
#include <initializer_list>
#include <sstream>
#include <cmath>
#include <stdexcept>
template <typename T>
class subforwardlist {
    // структура, описывающая узел списка
    struct Node {
        T data;
        Node* next;
    };

    Node* begin_;//указатель на первую node для 
    Node* end_;//указатель на node за последней для быстрого pushback
    unsigned int top_;//сколько nodes используется как лист
    unsigned int capacity_;  // сколько нод аллоцировано
   public:
    subforwardlist() : begin_(nullptr), end_(nullptr), top_(0), capacity_(0) {
    }//default ctor

    explicit subforwardlist(unsigned int count) : subforwardlist() {

        for (unsigned int i = 0; i < count; i++) {
            push_back(T{});
        }
    }//ctor.Создаём nodes с дефолтным значением

    subforwardlist(unsigned int count, const T& value) : subforwardlist() {
        for (unsigned int i = 0; i < count; i++) {
            push_back(value);
        }
    }//ctor.Создаём nodes с заданным значением


    subforwardlist(std::initializer_list<T> init) : subforwardlist() {
        for (const auto& x : init) {
            push_back(x);
        }
    }//convinient ctor to do like this: subforwardlist<int> x = {1, 2, 3};

    subforwardlist(const subforwardlist& other) : subforwardlist() {
        Node* copy = other.begin_;

        while (copy != other.end_) {
            push_back(copy->data);
            copy = copy->next;
        }
    }//copy ctor

    subforwardlist(subforwardlist&& other) : subforwardlist() {
        swap(other);
    }//move ctor

    subforwardlist& operator=(const subforwardlist& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        Node* copy = other.begin_;

        while (copy != other.end_) {
            push_back(copy->data);
            copy = copy->next;
        }
        return *this;
    }//assign operator

    subforwardlist& operator=(subforwardlist&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        clear();
        swap(other);
        return *this;
    }//move assign operator

    ~subforwardlist() {
        clear();//очищение содержимого листа, но память всё ещё занята (ноды аллоцированы)
        shrink_to_fit();//так как список теперь пустой, этот метод удалит все аллоцированные ноды
    }

    void swap(subforwardlist& other) {
        std::swap(begin_, other.begin_);
        std::swap(end_, other.end_);
        std::swap(top_, other.top_);
        std::swap(capacity_, other.capacity_);
    }

    void push_back(const T& data) {//в отличие от push forward, не делаем new при каждом push_back, 
        top_++;                    //если конечно после end есть ещё аллоцированные nodes
        if (end_ != nullptr) {
            if (end_->next != nullptr) {
                end_->data = data;
                end_ = end_->next;
                return;
            }
            capacity_++;
            end_->next = new Node{T{}, nullptr};
            end_->data = data;
            end_ = end_->next;
            return;
        }
        capacity_ += 2;


        Node* new_node = new Node{data, nullptr};
        Node* new_end = new Node{T{}, nullptr};
        new_node->next = new_end;
        begin_ = new_node;
        end_ = new_end;
    }

    T pop_back() {// в отличие от pop_forward просто сдвигаем конец на 1 влево
        //делаем значение удалённой node дефолтным
        //так мы не делаем delete при каждом popback
        if (top_ == 0) {
            return T{};
        }
        top_--;
        Node* copy = begin_;
        if (copy->next == end_) {
            T x = copy->data;
            copy->data = T{};
            end_ = copy;
            return x;
        }
        while (copy->next->next != end_) {
            copy = copy->next;
        }
        T x = copy->next->data;
        copy->next->data = T{}; //делаем значение удалённой node дефолтным
        end_ = copy->next;
        copy->next = end_;//просто сдвигаем конец листа на 1 влево
        return x;
    }

    void clear() {
        if (top_ == 0) {
            return;
        }
        end_ = begin_;
        top_ = 0;
    }

    void shrink_to_fit() {  // учитывая то, что мы не удаляем ноды при pop_back (во имя
                            // оптимизации), то мы хотим иметь способ освобождать неиспользуемую
                            // память без удаления всех данных
        if (top_ == 0) {   
            if (capacity_ == 0) {
                return;
            }
            Node* copy = begin_;
            while (copy != nullptr) {
                Node* bridge = copy->next;
                copy->next = nullptr;
                delete copy;
                copy = bridge;
            }


            begin_ = nullptr;
            end_ = nullptr;
            top_ = 0;
            capacity_ = 0;
            return;
        }


        if (top_ == capacity_ - 1) {
            return;
        }
        Node* copy = end_->next;
        while (copy != nullptr) {


            Node* bridge = copy->next;
            copy->next = nullptr;

            delete copy;
            copy = bridge;
        }
        end_->next = nullptr;
        capacity_ = top_ + 1;
    }

    void push_forward(const T& data) {
        if (top_ == 0) {
            push_back(data);
            return;
        }
        top_++;
        capacity_++;
        Node* new_node = new Node{data, begin_};//создали node с заданным значением(её добавляем)
        begin_ = new_node;//добавили node, которую сделали начальной
    }

    

    T pop_forward() {
        if (top_ == 0) {
            return T{};
        }
        top_--;
        capacity_--;
        T x = begin_->data;//берём значение удаляемого элемента
        Node* copy = begin_;
        begin_ = begin_->next;//делаем следующий после удаляемого элемента начальным
        delete copy;//удаляем node
        return x;//возвращаем значение удалённого элемента
    }



    void push_where(unsigned int where, const T& data) {
        if (where >= top_) {
            return;
        }


        if (where == 0) {
            push_forward(data);
            return;
        }
        Node* new_node = new Node{data, nullptr};

        Node* copy = begin_;
        for (unsigned int i = 0; i < where - 1; i++) {
            copy = copy->next;
        }


        new_node->next = copy->next;
        copy->next = new_node;
        top_++;
        capacity_++;
    }
    
    T erase_where(unsigned int where) {
        if (top_ == 0 || where >= top_) {
            return T{};
        }

        if (where == 0) {
            return pop_forward();
        }

        Node* copy = begin_;
        for (unsigned int i = 0; i < where - 1; i++) {


            copy = copy->next;
        }

        Node* node = copy->next;
        T data = node->data;
        copy->next = node->next;

        delete node;
        node = nullptr;
        top_--;
        capacity_--;
        return data;
    }

    unsigned int size() const {
        return top_;
    }

    unsigned int capacity() const {
        return capacity_;
    }
};
