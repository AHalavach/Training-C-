#pragma once

#include <iostream>
#include <exception>

template <typename T>
constexpr bool AdditionOverflows(const T& a, const T& b) 
{
    return (b >= 0) && (a > std::numeric_limits<T>::max() - b);
}

template <typename T>
constexpr bool AdditionUnderflows(const T& a, const T& b)
{
    return (b < 0) && (a < std::numeric_limits<T>::min() - b);
}

template <typename T>
constexpr bool SubtractionOverflows(const T& a, const T& b) 
{
    return (b < 0) && (a > std::numeric_limits<T>::max() + b);
}

template <typename T>
constexpr bool SubtractionUnderflows(const T& a, const T& b) 
{
    return (b >= 0) && (a < std::numeric_limits<T>::min() + b);
}

template<class T>
constexpr bool MultiplicationUnderflows(const T& a, const T& b) 
{
	if (b == 0)
	{
		return false; 
	}
	return ((b > 0) && (a < 0) && (a < std::numeric_limits<T>::min() / b))
		|| ((b < 0) && (a > 0) && (a > std::numeric_limits<T>::min() / b));
}

template<class T>
constexpr bool MultiplicationOverflows(T& a, T& b)
{
	if (b == 0)
	{
		return false;
	}

	return ((b > 0) && (a > 0) && (a > std::numeric_limits<T>::max() / b))
		|| ((b < 0) && (a < 0) && (a < std::numeric_limits<T>::max() / b));
};


struct ArithmeticException : std::exception 
{};

struct ArithmeticOverflowException : ArithmeticException
{
    virtual char const* what() const override
    { 
        return "Arithmetic overflow exception."; 
    }
};

struct ArithmeticUnderflowException : ArithmeticException
{
    virtual char const* what() const override
    {
        return "Arithmetic underflow exception.";
    }
};

template <typename T>
struct ThrowingPolicy 
{
    static constexpr T OnOverflow()
    {
        std::cout << "Using type: " << typeid(T).name() << std::endl;
		throw new ArithmeticOverflowException{};
	}

	static constexpr T OnUnderflow() 
    {
        std::cout << "Using type: " << typeid(T).name() << std::endl;
		throw new ArithmeticUnderflowException{};
	}
};

template <typename T>
struct SaturationPolicy 
{
	static constexpr T OnOverflow() 
    {
        std::cout << "Using type: " << typeid(T).name() << std::endl;
		return std::numeric_limits<T>::max();
	}

	static constexpr T OnUnderflow() 
    {
        std::cout << "Using type: " << typeid(T).name() << std::endl;
		return std::numeric_limits<T>::min();
	}
};

template <typename T, template<typename> typename Policy>
struct Integer
{
    T value;

    constexpr Integer<T, Policy> operator+(const Integer<T, Policy>& other) const 
    {
        if (AdditionOverflows(value, other.value))
            return { Policy<T>::OnOverflow() };

        if (AdditionUnderflows(value, other.value))
            return { Policy<T>::OnUnderflow() };

        return { value + other.value };
    }

    constexpr Integer<T, Policy> operator-(const Integer<T, Policy>& other) const
    {
        if (SubtractionOverflows(value, other.value))
            return { Policy<T>::OnOverflow() };

        if (SubtractionUnderflows(value, other.value))
            return { Policy<T>::OnUnderflow() };

        return { value - other.value };
    }

    constexpr Integer<T, Policy> operator*(const Integer<T, Policy>& other) const
    {
        if (MultiplicationOverflows(value, other.value))
        {
            return { Policy<T>::OnOverflow() };
        }
    
        if (MultiplicationUnderflows(value, other.value))
            return { Policy<T>::OnUnderflow() };

        return { value * other.value };
    }

    constexpr Integer<T, Policy> operator/(const Integer<T, Policy>& other) const
    {
        if (DivisionOverflows(value, other.value))
            return { Policy<T>::OnOverflow() };

        return { value / other.value };
    }
};
