#ifndef NOVEMBERGAMEJAM_OBJECTWRAPPER_H
#define NOVEMBERGAMEJAM_OBJECTWRAPPER_H

// What is RAII anyways?
// Doesn't sound useful.
// TODO - Probably replace this with std::shared_ptr. Or std::unique_ptr.

template<class T>
class ObjectWrapper {
public:
    explicit ObjectWrapper(T* object) : object_(object) {}
    ObjectWrapper()=default;
    T* update(T* object) { T* old = object_; object_ = object; return old; }
    T* get() const { return object_; }
    T* operator-> () { return object_; }
private:
    T* object_ = nullptr;
};

#endif //NOVEMBERGAMEJAM_OBJECTWRAPPER_H
