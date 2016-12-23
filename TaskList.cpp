

#include <iostream>
#include <deque>

using namespace std;

class Base1
{
public:
    void func1()
    {
        cout<<"Base1::func1()"<<endl;
    }
    void func2()
    {
        cout<<"Base1::func2()"<<endl;
    }
};

class Base2
{
public:
    void func1()
    {
        cout<<"Base2::func1()"<<endl;
    }
    void func2()
    {
        cout<<"Base2::func2()"<<endl;
    }
};

template<class T> class Taskque
{
public:

    typedef void (T::*Tfunc)();

	typedef pair<T*, Tfunc> TaskElement;

    void postTask(T* classPtr, Tfunc classFunc);

    void popTask();

public:

     deque<TaskElement> taskVec;
};

template<class Input>
void makeTask(Input* tPtr, void (Input::*tFunc)())
{
    (tPtr->*tFunc)();
}

template<class T> void Taskque<T>::postTask(T* classPtr, Tfunc classFunc)
{
	if ((NULL != classPtr) && (NULL != classFunc))
	{
	   TaskElement newTask(classPtr, classFunc);
       taskVec.push_front(newTask);
	}
    
}

template<class T> void Taskque<T>::popTask()
{
    if (!taskVec.empty())
    {
        TaskElement tmp = taskVec.back();
        (tmp.first->*(tmp.second))();
		taskVec.pop_back();
    }
}

int main()
{
    Taskque<Base1>::Tfunc ppo;
	Taskque<Base1> taskQue;
	Base2* pBase2 = new Base2();
	// taskQue.postTask(pBase1,&Base1::func2);
	// taskQue.popTask();
    makeTask(pBase2, &Base2::func1);
	return 0;
}

