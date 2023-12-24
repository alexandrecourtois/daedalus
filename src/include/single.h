#ifndef SINGLE_H
#define SINGLE_H

template <typename T> class Single {
private:
	static T*	instance;
	
protected:
	Single() {
	}
	
public:
	static T* get() {
		if (instance == nullptr)
			instance = new T;

		return instance;
	}
};

template <typename T> T* Single<T>::instance = nullptr;

#endif // SINGLE_H
