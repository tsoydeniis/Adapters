#pragma once


#include "adapters.h"


struct BaseGenerator {};


template <typename T, typename range_t>
concept generator = requires(T a, range_t range) {
    requires std::is_base_of_v<BaseGenerator, T>;
    a(range);
};


template <typename Function>
class FilterGenerator : BaseGenerator {
public:
    explicit FilterGenerator(Function function)
        : function_(function) {
    }

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyFilterAdapter<Iterator, Function>(std::begin(range), std::end(range), function_);
    }

private:
    Function function_;
};

template <typename Function>
auto filter(Function func) {
    return FilterGenerator<Function>(func);
}




template <typename Function>
class TransformGenerator : BaseGenerator {
public:
    explicit TransformGenerator(Function function)
        : function_(function) {
    }

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyTransformAdapter<Iterator, Function>(std::begin(range), std::end(range), function_);
    }

private:
    Function function_;
};

template <typename Function>
auto transform(Function function) {
    return TransformGenerator<Function>(function);
}




class ReverseGenerator : BaseGenerator {
public:
    ReverseGenerator() = default;

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyReverseAdapter<Iterator>(std::begin(range), std::end(range));
    }
};

ReverseGenerator reverse() {
    return ReverseGenerator();
}




class TakeGenerator : BaseGenerator {
public:
    explicit TakeGenerator(size_t count)
        : count_(count) {
    }

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyTakeAdapter<Iterator>(std::begin(range), std::end(range), count_);
    }

private:
    size_t count_;
};

auto take(size_t count) {
    return TakeGenerator(count);
}




class DropGenerator : BaseGenerator {
public:
    explicit DropGenerator(size_t count)
        : count_(count) {
    }

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyDropAdapter<Iterator>(std::begin(range), std::end(range), count_);
    }

private:
    size_t count_;
};

auto drop(size_t count) {
    return DropGenerator(count);
}




class KeysGenerator : BaseGenerator {
public:
    KeysGenerator() = default;

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyKeysAdapter<Iterator>(std::begin(range), std::end(range));
    }
};

KeysGenerator keys() {
    return KeysGenerator();
}




class ValuesGenerator : BaseGenerator {
public:
    ValuesGenerator() = default;

    template <typename Range>
    auto operator()(Range&& range) const {
        using Iterator = decltype(std::begin(range));
        return LazyValuesAdapter<Iterator>(std::begin(range), std::end(range));
    }
};

ValuesGenerator values() {
    return ValuesGenerator();
}



template <typename range_t, typename generator_t>
    requires range<range_t>&& generator<generator_t, range_t>
auto operator|(range_t&& range, generator_t&& generator) {
    return generator(std::forward<range_t>(range));
}