// Copyright 2018 Dellvin2000 <unknown@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <map>
#include <utility>
#include <stdint.h>

using std::map;
using std::cout;
using std::endl;


struct linkCount {
    int64_t count;
};

static map <int64_t, size_t> linker;

template<typename T>
class SharedPtr {
public:
    SharedPtr() {
        notCleverPTR = nullptr;
    }

    explicit SharedPtr(T *ptr) {
        notCleverPTR = ptr;
        if (linker.find(reinterpret_cast<int64_t>(ptr)) != linker.end())
            linker[reinterpret_cast<int64_t>(ptr)]++;
        else
            linker.insert({reinterpret_cast<int64_t>(ptr), 1});
    }

    SharedPtr(const SharedPtr &r) {
        notCleverPTR = r.notCleverPTR;
        linker[reinterpret_cast<int64_t>(r.notCleverPTR)]++;
    }

    SharedPtr(SharedPtr &&r) {
        notCleverPTR = r->notCleverPTR;
        linker[reinterpret_cast<int64_t>(r.notCleverPTR)]++;
        delete (r);
    }

    ~SharedPtr() {
    }

    auto operator=(const SharedPtr &r) -> SharedPtr &;

    auto operator=(SharedPtr &&r) -> SharedPtr &;

    // проверяет, указывает ли указатель на объект
    operator bool() const;

    auto operator*() const -> T &;

    auto operator->() const -> T *;

    auto get() -> T * {
        return notCleverPTR;
    };

    void reset() {
        if (linker[reinterpret_cast<int64_t>(this->notCleverPTR)] == 0) {
            delete (this->notCleverPTR);
            linker[reinterpret_cast<int64_t>(this->notCleverPTR)] = 0;
            linker.erase(reinterpret_cast<int64_t>(this->notCleverPTR));
        } else {
            linker[reinterpret_cast<int64_t>(this->notCleverPTR)]--;
            notCleverPTR = nullptr;
        }
    }

    void reset(T *ptr) {
        if (linker[reinterpret_cast<int64_t>(ptr)] == 1) {
            delete (this->notCleverPTR);
            linker[reinterpret_cast<int64_t>(ptr)] = 0;
            linker.erase(reinterpret_cast<int64_t>(ptr));
        } else {
            linker[reinterpret_cast<int64_t>(ptr)]--;
            notCleverPTR = nullptr;
        }
    }

    void swap(SharedPtr &r) {
        T *temporaryPTR;
        temporaryPTR = r.notCleverPTR;
        r.notCleverPTR = notCleverPTR;
        notCleverPTR = temporaryPTR;
    }

    // возвращает количество объектов SharedPtr,
    // которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t {
        return linker[reinterpret_cast<int64_t>(this->notCleverPTR)];
    };

public:
    T *notCleverPTR;
};

#endif // INCLUDE_HEADER_HPP_
