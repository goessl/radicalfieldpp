#ifndef RADICALFIELDPP_QUADRATICELEMENT2_HPP
#define RADICALFIELDPP_QUADRATICELEMENT2_HPP



#include <type_traits> //is_floating_point_v
#include <numbers>     //sqrt2_v
#include <compare>     //strong_ordering
#include <cmath>       //std::abs
#include <ostream>     //ostream



namespace radicalfield {
    
    
    
    //necessary for reliable detection of scalar/QuadraticElement2 types
    struct quadraticelement2_tag {};
    template<typename T>
    struct is_quadraticelement2 : std::is_base_of<quadraticelement2_tag, std::decay_t<T>>{};
    template<typename T>
    inline constexpr bool is_quadraticelement2_v = is_quadraticelement2<T>::value;
    
    
    
    template<typename T=int>
    class QuadraticElement2 : public quadraticelement2_tag {
    private:
        T _a, _b;
        
        template<typename> //different subtype interoperability
        friend class QuadraticElement2;
    
    
    
    public:
        constexpr QuadraticElement2<T>(const T& a={}, const T& b={}): _a(a), _b(b) {}
        constexpr QuadraticElement2<T>(const QuadraticElement2<T>& other) = default; //copy constructor
        constexpr QuadraticElement2<T>(QuadraticElement2<T>&& other) = default; //move constructor
        
        template<typename S>
        constexpr QuadraticElement2<T>& operator=(const S& other) requires (!is_quadraticelement2_v<S>) {
            _a = static_cast<T>(other);
            _b = {};
            return *this;
        }
        constexpr QuadraticElement2<T>& operator=(const QuadraticElement2<T>& other) = default; //copy assignment
        constexpr QuadraticElement2<T>& operator=(QuadraticElement2<T>&& other) = default; //move assignment
        
        
        
        //accessors, like complex
        [[nodiscard]] constexpr const T& a() const noexcept { return _a; }
        [[nodiscard]] constexpr const T& b() const noexcept { return _b; }
        [[nodiscard]] constexpr T& a() noexcept { return _a; }
        [[nodiscard]] constexpr T& b() noexcept { return _b; }
        
        
        
        //conversion
        explicit constexpr operator bool() const {
            return static_cast<bool>(_a) || static_cast<bool>(_b);
        }
        
        [[nodiscard]] constexpr bool is_rational() const {
            return !static_cast<bool>(_b);
        }
        
        template<typename S>
        explicit constexpr operator QuadraticElement2<S>() const {
            return QuadraticElement2<S>{static_cast<S>(_a), static_cast<S>(_b)};
        }
        template<typename S>
        explicit constexpr operator S() const requires (!is_quadraticelement2_v<S>) {
            return _a;
        }
        template<std::floating_point F>
        explicit constexpr operator F() const {
            return static_cast<F>(_a) + std::numbers::sqrt2_v<F> * static_cast<F>(_b);
        }
        
        
        
        //ordering
        template<typename S>
        friend constexpr bool operator==(const QuadraticElement2<T>& lhs, const S& rhs) requires (!is_quadraticelement2_v<S>) {
            return lhs.is_rational() && lhs._a==rhs;
        }
        template<typename S>
        friend constexpr bool operator==(const S& lhs, const QuadraticElement2<T>& rhs) requires (!is_quadraticelement2_v<S>) {
            return lhs==rhs._a && rhs.is_rational();
        }
        template<typename S>
        friend constexpr bool operator==(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            return lhs._a==rhs._a && lhs._b==rhs._b;
        }
        /**$$
         *     \begin{aligned}
         *         c &\lesseqgtr a+b\sqrt{2} &&\mid -a \\
         *         c-a &\lesseqgtr b\sqrt{2} &&\mid \cdot^2 \\
         *         (c-a)|c-a| &\lesseqgtr 2b|b|
         *     \end{aligned}
         * $$
         */
        template<typename S>
        friend constexpr std::strong_ordering operator<=>(const S& lhs, const QuadraticElement2<T>& rhs) requires (!is_quadraticelement2_v<S>) {
            if constexpr (!std::is_floating_point_v<S>) {
                const auto l = lhs - rhs._a;
                return l*std::abs(l) <=> 2*rhs._b*std::abs(rhs._b);
            } else {
                return lhs <=> static_cast<S>(rhs);
            }
        }
        /**$$
         *     \begin{aligned}
         *         a+b\sqrt{2} &\lesseqgtr c &&\mid -a \\
         *         b\sqrt{2} &\lesseqgtr c-a &&\mid \cdot^2 \\
         *         2b|b| &\lesseqgtr (c-a)|c-a|
         *     \end{aligned}
         * $$
         */
        template<typename S>
        friend constexpr std::strong_ordering operator<=>(const QuadraticElement2<T>& lhs, const S& rhs) requires (!is_quadraticelement2_v<S>) {
            if constexpr (!std::is_floating_point_v<S>) {
                const auto r = rhs - lhs._a;
                return 2*lhs._b*std::abs(lhs._b) <=> r*std::abs(r);
            } else {
                return static_cast<S>(lhs) <=> rhs;
            }
        }
        /**$$
         *     \begin{aligned}
         *         a+b\sqrt{2} &\lesseqgtr c+d\sqrt{2} &&\mid -c-b\sqrt{2} \\
         *         a-c &\lesseqgtr (d-b)\sqrt{2} &&\mid \cdot^2 \\
         *         (a-c)|a-c| &\lesseqgtr 2(d-b)|d-b|
         *     \end{aligned}
         * $$
         */
        template<typename S>
        friend constexpr std::strong_ordering operator<=>(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            const auto l = lhs._a - rhs._a;
            const auto r = rhs._b - lhs._b;
            return l*std::abs(l) <=> 2*r*std::abs(r);
        }
        
        
        
        //arithmetic
        
        //conjugation & norm
        constexpr QuadraticElement2<T> conj() const {
            return QuadraticElement2<T>{+_a,
                                        -_b};
        }
        constexpr QuadraticElement2<T>& iconj() {
            _a = +_a;
            _b = -_b;
            return *this;
        }
        
        [[nodiscard]] constexpr T norm() const {
            return _a*_a - 2*_b*_b;
        }
        
        //unary
        constexpr QuadraticElement2<T> operator+() const {
            return QuadraticElement2<T>{+_a,
                                        +_b};
        }
        constexpr QuadraticElement2<T>& ipos() {
            _a = +_a;
            _b = +_b;
            return *this;
        }
        
        constexpr QuadraticElement2<T> operator-() const {
            return QuadraticElement2<T>{-_a,
                                        -_b};
        }
        constexpr QuadraticElement2<T>& ineg() {
            _a = -_a;
            _b = -_b;
            return *this;
        }
        
        //addition
        constexpr QuadraticElement2<T>& operator++() {
            ++_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement2<T> operator++(int) {
            const QuadraticElement2<T> tmp = *this;
            ++(*this);
            return tmp;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator+=(const S& rhs) requires (!is_quadraticelement2_v<S>) {
            _a += rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator+=(const QuadraticElement2<S>& rhs) {
            _a += rhs._a;
            _b += rhs._b;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator+(const S& lhs, const QuadraticElement2<T>& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(lhs + std::declval<T>());
            return QuadraticElement2<R>{lhs + rhs._a,
                              +static_cast<R>(rhs._b)};
        }
        template<typename S>
        friend constexpr auto operator+(const QuadraticElement2<T>& lhs, const S& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(std::declval<T>() + rhs);
            return QuadraticElement2<R>{lhs._a  + rhs,
                         static_cast<R>(lhs._b)};
        }
        template<typename S>
        friend constexpr auto operator+(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(std::declval<S>() + std::declval<T>());
            return QuadraticElement2<R>{lhs._a + rhs._a,
                                        lhs._b + rhs._b};
        }
        
        //subtraction
        constexpr QuadraticElement2<T>& operator--() {
            --_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement2<T> operator--(int) {
            const QuadraticElement2<T> tmp = *this;
            --(*this);
            return tmp;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator-=(const S& rhs) requires (!is_quadraticelement2_v<S>) {
            _a -= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator-=(const QuadraticElement2<S>& rhs) {
            _a -= rhs._a;
            _b -= rhs._b;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator-(const S& lhs, const QuadraticElement2<T>& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(lhs - std::declval<T>());
            return QuadraticElement2<R>{lhs - rhs._a,
                              -static_cast<R>(rhs._b)};
        }
        template<typename S>
        friend constexpr auto operator-(const QuadraticElement2<T>& lhs, const S& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(std::declval<T>() - rhs);
            return QuadraticElement2<R>{lhs._a - rhs, 
                         static_cast<R>(lhs._b)};
        }
        template<typename S>
        friend constexpr auto operator-(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(std::declval<S>() - std::declval<T>());
            return QuadraticElement2<R>{lhs._a - rhs._a,
                                        lhs._b - rhs._b};
        }
        
        //multiplication
        template<typename S>
        constexpr QuadraticElement2<T>& operator*=(const S& rhs) requires (!is_quadraticelement2_v<S>) {
            _a *= rhs;
            _b *= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator*=(const QuadraticElement2<S>& rhs) {
            const auto a_new = _a*rhs._a + 2*_b*rhs._b;
            _b = _a*rhs._b + _b*rhs._a;
            _a = a_new;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator*(const S& lhs, const QuadraticElement2<T>& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(lhs * std::declval<T>());
            return QuadraticElement2<R>{lhs * rhs._a,
                                        lhs * rhs._b};
        }
        template<typename S>
        friend constexpr auto operator*(const QuadraticElement2<T>& lhs, const S& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(std::declval<T>() * rhs);
            return QuadraticElement2<R>{lhs._a * rhs,
                                        lhs._b * rhs};
        }
        template<typename S>
        friend constexpr auto operator*(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(std::declval<S>() * std::declval<T>());
            return QuadraticElement2<R>{lhs._a*rhs._a + 2*lhs._b*rhs._b,
                                        lhs._a*rhs._b +   lhs._b*rhs._a};
        }
        
        //inversion & division
        constexpr QuadraticElement2<T> inv() const {
            return conj() / norm();
        }
        constexpr QuadraticElement2<T>& iinv() {
            iconj();
            *this /= norm();
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator/=(const S& rhs) requires (!is_quadraticelement2_v<S>) {
            _a /= rhs;
            _b /= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator/=(const QuadraticElement2<S>& rhs) {
            *this *= rhs.conj();
            *this /= rhs.norm();
            return *this;
        }
        template<typename S>
        friend constexpr auto operator/(const S& lhs, const QuadraticElement2<T>& rhs) requires (!is_quadraticelement2_v<S>) {
            return lhs * rhs.conj() / rhs.norm();
        }
        template<typename S>
        friend constexpr auto operator/(const QuadraticElement2<T>& lhs, const S& rhs) requires (!is_quadraticelement2_v<S>) {
            using R = decltype(std::declval<T>() / rhs);
            return QuadraticElement2<R>{lhs._a / rhs,
                                        lhs._b / rhs};
        }
        template<typename S>
        friend constexpr auto operator/(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            return lhs * rhs.conj() / rhs.norm();
        }
        
        
        
        //IO
        friend std::ostream& operator<<(std::ostream& os, const QuadraticElement2& x) {
            os << x._a;
            if(x._b >= 0) {
                os << '+';
            }
            os << x._b << "sqrt(" << 2 << ')';
            return os;
        }
    };
    
    
    
}



#endif //RADICALFIELDPP_QUADRATICELEMENT2_HPP
