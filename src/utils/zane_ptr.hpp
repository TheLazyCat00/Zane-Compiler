#pragma once
#include <cassert>
#include <stdexcept>
#include <utility>
#include <type_traits>

template<typename T> class Ptr;

template<typename T>
struct ControlBlock {
    alignas(T) unsigned char storage[sizeof(T)];
    Ptr<T>* owner    = nullptr;
    Ptr<T>* weakHead = nullptr;

    T*       ptr()       noexcept { return reinterpret_cast<T*>(storage); }
    const T* ptr() const noexcept { return reinterpret_cast<const T*>(storage); }
};

template<typename T>
class Ptr {
    ControlBlock<T>* cb_       = nullptr;
    bool             isStrong_ = false;
    Ptr*             prev_     = nullptr;
    Ptr*             next_     = nullptr;

    void listInsert() {
        next_ = cb_->weakHead;
        prev_ = nullptr;
        if (cb_->weakHead) cb_->weakHead->prev_ = this;
        cb_->weakHead = this;
    }

    void listRemove() {
        if (prev_) prev_->next_ = next_;
        else       cb_->weakHead = next_;
        if (next_) next_->prev_ = prev_;
        prev_ = next_ = nullptr;
    }

    void listReplace(Ptr& o) {
        prev_ = o.prev_;
        next_ = o.next_;
        if (prev_) prev_->next_ = this;
        else       cb_->weakHead = this;
        if (next_) next_->prev_ = this;
        o.prev_ = o.next_ = nullptr;
    }

    Ptr(ControlBlock<T>* cb, bool isStrong)
        : cb_(cb), isStrong_(isStrong) {
        if (!cb_) return;
        if (isStrong_) cb_->owner = this;
        else           listInsert();
    }

    void destroy() {
        Ptr* w = cb_->weakHead;
        while (w) {
            Ptr* next = w->next_;
            w->cb_   = nullptr;
            w->prev_ = w->next_ = nullptr;
            w = next;
        }
        cb_->weakHead = nullptr;
        cb_->owner    = nullptr;
        cb_->ptr()->~T();
        delete cb_;
        cb_ = nullptr;
    }

public:
    Ptr() = default;

    // ── Implicit construction from anything T accepts ────
    //   Ptr<std::string> s = "hello";
    //   Ptr<int>         n = 42;
    template<typename U,
             typename = std::enable_if_t<!std::is_same_v<std::decay_t<U>, Ptr>>>
    Ptr(U&& value) {
        auto* cb = new ControlBlock<T>();
        new (cb->storage) T(std::forward<U>(value));
        cb_       = cb;
        isStrong_ = true;
        cb_->owner = this;
    }

    // ── Copy → always weak ────────────────────
    Ptr(const Ptr& o) : cb_(o.cb_), isStrong_(false) {
        if (cb_) listInsert();
    }
    Ptr& operator=(const Ptr& o) {
        if (this != &o) {
            if (isStrong_)    destroy();
            else if (cb_)     listRemove();
            cb_       = o.cb_;
            isStrong_ = false;
            if (cb_) listInsert();
        }
        return *this;
    }

    // ── Move → carries flag ───────────────────
    Ptr(Ptr&& o) noexcept : cb_(o.cb_), isStrong_(o.isStrong_) {
        if (cb_) {
            if (isStrong_) cb_->owner = this;
            else           listReplace(o);
        }
        o.cb_       = nullptr;
        o.isStrong_ = false;
    }
    Ptr& operator=(Ptr&& o) noexcept {
        if (this != &o) {
            if (isStrong_)  destroy();
            else if (cb_)   listRemove();
            cb_       = o.cb_;
            isStrong_ = o.isStrong_;
            if (cb_) {
                if (isStrong_) cb_->owner = this;
                else           listReplace(o);
            }
            o.cb_       = nullptr;
            o.isStrong_ = false;
        }
        return *this;
    }

    ~Ptr() {
        if (isStrong_)  destroy();
        else if (cb_)   listRemove();
    }

    // ── Ownership transfer ────────────────────
    //   globalObj.member = obj.give();
    //   works on strong or weak — always finds and flips the current strong
    [[nodiscard]] Ptr give() {
        assert(cb_ && "give() called on null Ptr");
        if (isStrong_) {
            isStrong_ = false;
            listInsert();
        } else {
            Ptr* owner = cb_->owner;
            assert(owner && "no strong pointer exists for this object");
            owner->isStrong_ = false;
            owner->listInsert();
        }
        cb_->owner = nullptr;
        return Ptr(cb_, true);
    }

    [[nodiscard]] Ptr weak() const { return Ptr(cb_, false); }

    // ── Accessors ─────────────────────────────
    T& get()        const { check(); return *cb_->ptr(); }
    T& operator*()  const { check(); return *cb_->ptr(); }
    T* operator->() const { check(); return  cb_->ptr(); }

    bool valid()    const noexcept { return cb_ != nullptr; }
    bool isStrong() const noexcept { return isStrong_; }
    explicit operator bool() const noexcept { return valid(); }

private:
    void check() const {
        if (!cb_) throw std::runtime_error("Ptr: null dereference");
    }

    template<typename U, typename... Args>
    friend Ptr<U> makePtr(Args&&...);
};

template<typename T, typename... Args>
Ptr<T> makePtr(Args&&... args) {
    auto* cb = new ControlBlock<T>();
    new (cb->storage) T(std::forward<Args>(args)...);
    return Ptr<T>(cb, true);
}
