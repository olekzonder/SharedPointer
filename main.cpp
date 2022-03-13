#include <iostream>

using namespace std;

template <class T>
class MyPointer{
   public:
    MyPointer(T* _data){
        data = _data;
        count = new int(1);
    };

    ~MyPointer(){
        if(count != nullptr){
            dec();
            if(*count==0){ //если указатель больше нигде не используется, высвобождаем память
                delete data;
                delete count;
            }
        }

    };

    MyPointer(MyPointer<T>& ptr){ //создание нового шаред поинтера
        data = ptr.data;
        count = ptr.count;
        inc();
    }

    T* get(){
        return data;
    }

    T& operator*(){
        return *data;
    }
    T* operator->(){
        return data;
    }

    MyPointer<T>& operator=(MyPointer<T>& ptr){ //перегрузка для возможности создать новый умный указатель через оператор =
        data = ptr.data;;
        count = ptr.count;
        inc();
        return *this;
    }

    private:
        T* data;
        int* count; //счётчик указателей, тип данных int* для того, чтобы при создании нового умного указателя счётчик увеличивался во всех остальных

        void inc(){ //инкремент
            (*count)++;
        }
        void dec(){ //декремент
            (*count)--;
        }
};

class A{ //класс для примера работы
    int i;
    public:
    A(int _i){
        i = _i;
    }
    ~A(){
        cout << "deleting A";
    };
    int getValue(){
        return i;
    }
};


int main()
{
    MyPointer shrdA(new A(420));
    MyPointer shrdB(shrdA);
    MyPointer shrdC = shrdB;
    std::cout << shrdA.get() << endl;
    std::cout << shrdB.get()->getValue() << endl;
    std::cout << shrdC->getValue() << endl;
    std::cout << shrdC.get() << endl;
    return 0;
}
