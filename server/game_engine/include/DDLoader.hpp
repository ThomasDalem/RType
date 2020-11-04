/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-romeo.talovici
** File description:
** DDLoader
*/

#ifndef DDLOADER_HPP_
#define DDLOADER_HPP_
#include <dlfcn.h>
#include <stdio.h>
#include <cstddef>

template <typename T>
class DDloader
{
public:
    DDloader(){};
    ~DDloader(){};
    int loadLibrary(const char *name)
    {
        this->handle = dlopen(name, RTLD_LAZY | RTLD_NOW);
        if (this->handle == NULL)
        {
            printf("%s\n", dlerror());
            return (84);
        }
        return (0);
    }
    int closeLibrary()
    {
        dlclose(this->handle);
        return (0);
    }
    T *getInstance(const char *name)
    {
        T *newClass;

        *(void **)(&this->entryPoint) = dlsym(this->handle, name);
        if (entryPoint == nullptr)
            return (nullptr);
        newClass = (T *)(*entryPoint)();
        return (newClass);
    }

protected:
private:
    void *handle;
    void *(*entryPoint)();
};

#endif /* !DDLOADER_HPP_ */
