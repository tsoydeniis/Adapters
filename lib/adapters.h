#pragma once


#include <iostream>
#include <cstdint>
#include <memory>

template <typename T>
concept range = requires(T a) {
    { a.begin() } -> std::same_as<decltype(a.end())>;
};


class __BaseView {
public:
    __BaseView() = default;
};


template <typename T>
struct get_from_link;

template <typename T>
struct get_from_link<T&> {
    using type = T;
};

template <typename iterator_t>
class ViewIterator {
public:
    ViewIterator(iterator_t in_iterator)
        : in_iterator_(in_iterator) {
    }

    virtual ViewIterator& operator++() {
        ++in_iterator_;
        return *this;
    }

    virtual bool operator==(const ViewIterator& arg) const {
        return in_iterator_ == arg.in_iterator_;
    }

    virtual ViewIterator& operator =(const ViewIterator& other) = default;

protected:
    iterator_t& get_in_iterator() {
        return in_iterator_;
    }
protected:
    iterator_t in_iterator_;
};


template <typename iterator_t, typename wrapped_t>
class WriteIterator : public ViewIterator<iterator_t> {
public:
    WriteIterator(iterator_t in_iterator, iterator_t out_iterator)
        : ViewIterator<iterator_t>(in_iterator), out_iterator_(out_iterator) {
    }

    wrapped_t operator*() {
        *out_iterator_ = *this->get_in_iterator();
        ++out_iterator_;
        return *this->get_in_iterator();
    }
private:
    iterator_t out_iterator_;
};


template <typename iterator_t, typename wrapped_t, typename func_t, typename out_t = wrapped_t>
class FuncWrappedIterator : public ViewIterator<iterator_t> {
public:
    FuncWrappedIterator(iterator_t in_iterator, func_t func)
        : ViewIterator<iterator_t>(in_iterator), func_(func) {
    }

    auto operator*() {
        return func_(*this->get_in_iterator());
    }
private:
    func_t func_;
};


template <typename iterator_t, typename wrapped_t>
class ReverseViewIterator : public ViewIterator<iterator_t> {
public:
    ReverseViewIterator(iterator_t in_iterator)
        : ViewIterator<iterator_t>(in_iterator) {
    }

    virtual wrapped_t operator*() {
        return *this->get_in_iterator();
    }

    ReverseViewIterator& operator++() override {
        --this->get_in_iterator();
        return *this;
    }

    ReverseViewIterator& operator--() {
        ++this->get_in_iterator();
        return *this;
    }
};


template <typename iterator_t, typename func_t>
class LazyTransformAdapter : public __BaseView {
    /// TransformAdapter ///
public:
    using out_t = decltype(*std::declval<iterator_t>());

    LazyTransformAdapter(iterator_t begin, iterator_t end, func_t func)
        : begin_(begin, func), end_(end, func) {
    }

    FuncWrappedIterator<iterator_t, out_t, func_t> begin() {
        return begin_;
    }

    FuncWrappedIterator<iterator_t, out_t, func_t> end() {
        return end_;
    }
private:
    const FuncWrappedIterator<iterator_t, out_t, func_t> begin_;
    const FuncWrappedIterator<iterator_t, out_t, func_t> end_;
};


template <typename iterator_t>
class LazyReverseAdapter : public __BaseView {
    /// ReverseAdapter ///
public:
    using out_t = decltype(*std::declval<iterator_t>());

    LazyReverseAdapter(iterator_t begin, iterator_t end)
        : begin_(--end), end_(--begin) {
    }

    ReverseViewIterator<iterator_t, out_t> begin() {
        return begin_;
    }

    ReverseViewIterator<iterator_t, out_t> end() {
        return end_;
    }
private:
    const ReverseViewIterator<iterator_t, out_t> begin_;
    const ReverseViewIterator<iterator_t, out_t> end_;
};


template <typename iterator_t>
class LazyKeysAdapter : public __BaseView {
    /// KeysAdapter ///
public:
    using pair_t = decltype(*std::declval<iterator_t>());
    using first_t = decltype(std::declval<pair_t>().first);
    using second_t = decltype(std::declval<pair_t>().second);

    template <typename in_t, typename out_t>
    struct func {
        static out_t operator()(in_t arg) {
            return arg.first;
        }
    };

    LazyKeysAdapter(iterator_t begin, iterator_t end)
        : begin_(begin), end_(end) {
    }

    FuncWrappedIterator<iterator_t, pair_t, func<pair_t, first_t>, first_t> begin() {
        return FuncWrappedIterator<iterator_t, pair_t, func<pair_t, first_t>, first_t>(begin_, func_);
    }

    FuncWrappedIterator<iterator_t, pair_t, func<pair_t, first_t>, first_t> end() {
        return FuncWrappedIterator<iterator_t, pair_t, func<pair_t, first_t>, first_t>(end_, func_);
    }
private:
    const iterator_t begin_;
    const iterator_t end_;

    func<pair_t, first_t> func_;
};


template <typename iterator_t>
class LazyValuesAdapter : public __BaseView {
    /// ValuesAdapter ///
public:
    using pair_t = decltype(*std::declval<iterator_t>());
    using first_t = decltype(std::declval<pair_t>().first);
    using second_t = decltype(std::declval<pair_t>().second);

    template <typename in_t, typename out_t>
    struct func {
        static out_t operator()(in_t arg) {
            return arg.second;
        }
    };

    LazyValuesAdapter(iterator_t begin, iterator_t end)
        : begin_(begin), end_(end) {
    }

    FuncWrappedIterator<iterator_t, pair_t, func<pair_t, second_t>, second_t> begin() {
        return FuncWrappedIterator<iterator_t, pair_t, func<pair_t, second_t>, second_t>(begin_, func_);
    }

    FuncWrappedIterator<iterator_t, pair_t, func<pair_t, second_t>, second_t> end() {
        return FuncWrappedIterator<iterator_t, pair_t, func<pair_t, second_t>, second_t>(end_, func_);
    }
private:
    iterator_t begin_;
    iterator_t end_;

    func<pair_t, second_t> func_;
};


template <typename iterator_t, typename func_t>
class LazyFilterAdapter : public __BaseView {
    /// FilterAdapter ///
    class LazyFilterIterator;
public:
    using out_t = decltype(*std::declval<iterator_t>());

    LazyFilterAdapter(iterator_t begin, iterator_t end, func_t func)
        : begin_(begin, end, func), end_(end, end, func) {
    }

    LazyFilterIterator begin() {
        return begin_;
    }

    LazyFilterIterator end() {
        return end_;
    }
private:

    class LazyFilterIterator {
    public:
        LazyFilterIterator(iterator_t begin, iterator_t end, func_t func)
            : in_iterator_(begin), end_(end), func_(func) {
            MoveForward();
        }

        LazyFilterIterator& operator++() {
            if (in_iterator_ != end_) {
                ++in_iterator_;
                MoveForward();
            }
            return *this;
        }

        out_t operator*() {
            return *in_iterator_;
        }

        bool operator==(const LazyFilterIterator& arg) const {
            return in_iterator_ == arg.in_iterator_;
        }
        bool operator!=(const LazyFilterIterator& arg) const {
            return !(*this == arg);
        }
        LazyFilterIterator& operator=(const LazyFilterIterator& other) = default;
    private:
        void MoveForward() {
            while (in_iterator_ != end_ && !func_(*in_iterator_)) {
                ++in_iterator_;
            }
        }
    private:
        iterator_t in_iterator_;
        iterator_t end_;
        func_t func_;
    };

private:
    const LazyFilterIterator begin_;
    const LazyFilterIterator end_;
};


template <typename iterator_t>
class LazyTakeAdapter : public __BaseView {
    /// TakeAdapter ///
    class LazyTakeIterator;
public:
    using out_t = decltype(*std::declval<iterator_t>());

    LazyTakeAdapter(iterator_t begin, iterator_t end, size_t take_cnt)
        : begin_(begin, end, take_cnt), end_(end, end, take_cnt) {
    }

    LazyTakeIterator begin() {
        return begin_;
    }

    LazyTakeIterator end() {
        return end_;
    }
private:

    class LazyTakeIterator {
    public:
        LazyTakeIterator(iterator_t begin, iterator_t end, size_t take_param)
            : in_iterator_(begin), end_(end), take_cnt_(take_param) {
            if (take_cnt_ == 0) {
                in_iterator_ = end_;
            }
            else {
                --take_cnt_;
            }
        }

        LazyTakeIterator& operator ++() {
            if (in_iterator_ != end_ && take_cnt_ != 0) {
                ++in_iterator_;
                --take_cnt_;
            }
            else {
                in_iterator_ = end_;
            }
            return *this;
        }

        out_t operator*() {
            return *in_iterator_;
        }

        bool operator==(const LazyTakeIterator& arg) const {
            return in_iterator_ == arg.in_iterator_;
        }
        bool operator!=(const LazyTakeIterator& arg) const {
            return !(*this == arg);
        }
    private:
        iterator_t in_iterator_;
        const iterator_t end_;
        size_t take_cnt_;
    };

private:
    const LazyTakeIterator begin_;
    const LazyTakeIterator end_;
};


template <typename iterator_t>
class LazyDropAdapter : public __BaseView {
    /// DropAdapter ///
    class LazyDropIterator;
public:
    using out_t = decltype(*std::declval<iterator_t>());

    LazyDropAdapter(iterator_t begin, iterator_t end, size_t drop_cnt)
        : begin_(begin, end, drop_cnt), end_(end, end, drop_cnt) {
    }

    LazyDropIterator begin() {
        return begin_;
    }

    LazyDropIterator end() {
        return end_;
    }
private:

    class LazyDropIterator {
    public:
        LazyDropIterator(iterator_t begin, iterator_t end, size_t drop_param)
            : in_iterator_(begin), end_(end), drop_cnt_(drop_param) {
            while (in_iterator_ != end_ && drop_cnt_ != 0) {
                ++in_iterator_;
                --drop_cnt_;
            }
        }

        LazyDropIterator& operator ++() {
            ++in_iterator_;
            return *this;
        }

        out_t operator*() {
            return *in_iterator_;
        }

        bool operator==(const LazyDropIterator& arg) const {
            return in_iterator_ == arg.in_iterator_;
        }
        bool operator!=(const LazyDropIterator& arg) const {
            return !(*this == arg);
        }
        LazyDropIterator& operator=(const LazyDropIterator& other) = default;
    private:
        iterator_t in_iterator_;
        iterator_t end_;
        size_t drop_cnt_;
    };

private:
    const LazyDropIterator begin_;
    const LazyDropIterator end_;
};
