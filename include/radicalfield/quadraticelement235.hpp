#ifndef RADICALFIELDPP_QUADRATICELEMENT235_HPP
#define RADICALFIELDPP_QUADRATICELEMENT235_HPP



#include <type_traits> //is_floating_point_v
#include <numbers>     //sqrt2_v
//#include <compare>     //strong_ordering
//#include <cmath>       //std::abs
#include <ostream>     //ostream
#include <utility>     //std::pair



namespace radicalfield {
    
    
    
    //necessary for reliable detection of scalar/QuadraticElement235 types
    struct quadraticelement235_tag {};
    template<typename T>
    struct is_quadraticelement235 : std::is_base_of<quadraticelement235_tag, std::decay_t<T>>{};
    template<typename T>
    inline constexpr bool is_quadraticelement235_v = is_quadraticelement235<T>::value;
    
    
    
    template<typename T=int>
    class QuadraticElement235 : public quadraticelement235_tag {
    private:
        T _a, _b2, _b3, _b5, _b6, _b10, _b15, _b30;
        
        template<typename> //different subtype interoperability
        friend class QuadraticElement235;
    
    
    
    public:
        constexpr QuadraticElement235<T>(
            const T& a={}, const T& b2={}, const T& b3={}, const T& b5={},
            const T& b6={}, const T& b10={}, const T& b15={}, const T& b30={}):
            _a(a), _b2(b2), _b3(b3), _b5(b5), _b6(b6), _b10(b10), _b15(b15), _b30(b30) {}
        constexpr QuadraticElement235<T>(const QuadraticElement235<T>& other) = default; //copy
        constexpr QuadraticElement235<T>(QuadraticElement235<T>&& other) = default; //move
        
        template<typename S>
        constexpr QuadraticElement235<T>& operator=(const S& other) requires (!is_quadraticelement235_v<S>) {
            _a = static_cast<T>(other);
            _b2 = {};
            _b3 = {};
            _b5 = {};
            _b6 = {};
            _b10 = {};
            _b15 = {};
            _b30 = {};
            return *this;
        }
        constexpr QuadraticElement235<T>& operator=(const QuadraticElement235<T>& other) = default; //copy assignment
        constexpr QuadraticElement235<T>& operator=(QuadraticElement235<T>&& other) = default; //move assignment
        
        
        
        //accessors, like complex
        [[nodiscard]] constexpr const T& a() const noexcept { return _a; }
        [[nodiscard]] constexpr const T& b2() const noexcept { return _b2; }
        [[nodiscard]] constexpr const T& b3() const noexcept { return _b3; }
        [[nodiscard]] constexpr const T& b5() const noexcept { return _b5; }
        [[nodiscard]] constexpr const T& b6() const noexcept { return _b6; }
        [[nodiscard]] constexpr const T& b10() const noexcept { return _b10; }
        [[nodiscard]] constexpr const T& b15() const noexcept { return _b15; }
        [[nodiscard]] constexpr const T& b30() const noexcept { return _b30; }
        [[nodiscard]] constexpr T& a() noexcept { return _a; }
        [[nodiscard]] constexpr T& b2() noexcept { return _b2; }
        [[nodiscard]] constexpr T& b3() noexcept { return _b3; }
        [[nodiscard]] constexpr T& b5() noexcept { return _b5; }
        [[nodiscard]] constexpr T& b6() noexcept { return _b6; }
        [[nodiscard]] constexpr T& b10() noexcept { return _b10; }
        [[nodiscard]] constexpr T& b15() noexcept { return _b15; }
        [[nodiscard]] constexpr T& b30() noexcept { return _b30; }
        
        
        
        //conversion
        explicit constexpr operator bool() const {
            return static_cast<bool>(_a)
                || static_cast<bool>(_b2)
                || static_cast<bool>(_b3)
                || static_cast<bool>(_b5)
                || static_cast<bool>(_b6)
                || static_cast<bool>(_b10)
                || static_cast<bool>(_b15)
                || static_cast<bool>(_b30);
        }
        
        [[nodiscard]] constexpr bool is_rational() const {
            return !(static_cast<bool>(_b2)
                  || static_cast<bool>(_b3)
                  || static_cast<bool>(_b5)
                  || static_cast<bool>(_b6)
                  || static_cast<bool>(_b10)
                  || static_cast<bool>(_b15)
                  || static_cast<bool>(_b30));
        }
        
        template<typename S>
        explicit constexpr operator QuadraticElement235<S>() const {
            return QuadraticElement235<S>{
                static_cast<S>(_a),
                static_cast<S>(_b2),
                static_cast<S>(_b3),
                static_cast<S>(_b5),
                static_cast<S>(_b6),
                static_cast<S>(_b10),
                static_cast<S>(_b15),
                static_cast<S>(_b30)
            };
        }
        template<typename S>
        explicit constexpr operator S() const requires (!is_quadraticelement235_v<S>) {
            return _a;
        }
        template<std::floating_point F>
        explicit constexpr operator F() const {
            return static_cast<F>(_a)
                + std::numbers::sqrt2_v<F>      * static_cast<F>(_b2)
                + std::numbers::sqrt3_v<F>      * static_cast<F>(_b3)
                + std::sqrt(static_cast<F>(5))  * static_cast<F>(_b5)
                + std::sqrt(static_cast<F>(6))  * static_cast<F>(_b6)
                + std::sqrt(static_cast<F>(10)) * static_cast<F>(_b10)
                + std::sqrt(static_cast<F>(15)) * static_cast<F>(_b15)
                + std::sqrt(static_cast<F>(30)) * static_cast<F>(_b30);
        }
        
        
        
        //ordering
        template<typename S>
        friend constexpr bool operator==(const QuadraticElement235<T>& lhs, const S& rhs) requires (!is_quadraticelement235_v<S>) {
            return lhs.is_rational() && lhs._a==rhs;
        }
        template<typename S>
        friend constexpr bool operator==(const S& lhs, const QuadraticElement235<T>& rhs) requires (!is_quadraticelement235_v<S>) {
            return lhs==rhs._a && rhs.is_rational();
        }
        template<typename S>
        friend constexpr bool operator==(const QuadraticElement235<T>& lhs, const QuadraticElement235<S>& rhs) {
            return lhs._a   == rhs._a
                && lhs._b2  == rhs._b2
                && lhs._b3  == rhs._b3
                && lhs._b5  == rhs._b5
                && lhs._b6  == rhs._b6
                && lhs._b10 == rhs._b10
                && lhs._b15 == rhs._b15
                && lhs._b30 == rhs._b30;
        }
        //strong_ordering: TODO
        
        
        
        //arithmetic
        
        //conjugation & norm
        constexpr std::pair<QuadraticElement235<T>, T> conj_and_norm() const {
            const QuadraticElement235<T> c5  = conj5();
            const QuadraticElement235<T> y   = *this * c5;
            const QuadraticElement235<T> c3y = y.conj3();
            const QuadraticElement235<T> z   = y * c3y;
            const QuadraticElement235<T> c2z = z.conj2();
            return {c5*c3y*c2z, static_cast<T>(z*c2z)};
        }
        
        [[nodiscard]] constexpr QuadraticElement235<T> conj() const {
            return conj_and_norm().first;
        }
        constexpr QuadraticElement235<T> conj2() const {
            return QuadraticElement235<T>{+_a,
                                          -_b2,
                                          +_b3,
                                          +_b5,
                                          -_b6,
                                          -_b10,
                                          +_b15,
                                          -_b30};
        }
        constexpr QuadraticElement235<T> conj3() const {
            return QuadraticElement235<T>{+_a,
                                          +_b2,
                                          -_b3,
                                          +_b5,
                                          -_b6,
                                          +_b10,
                                          -_b15,
                                          -_b30};
        }
        constexpr QuadraticElement235<T> conj5() const {
            return QuadraticElement235<T>{+_a,
                                          +_b2,
                                          +_b3,
                                          -_b5,
                                          +_b6,
                                          -_b10,
                                          -_b15,
                                          -_b30};
        }
        constexpr QuadraticElement235<T>& iconj2() {
            _a   = +_a;
            _b2  = -_b2;
            _b3  = +_b3;
            _b5  = +_b5;
            _b6  = -_b6;
            _b10 = -_b10;
            _b15 = +_b15;
            _b30 = -_b30;
            return *this;
        }
        constexpr QuadraticElement235<T>& iconj3() {
            _a   = +_a;
            _b2  = +_b2;
            _b3  = -_b3;
            _b5  = +_b5;
            _b6  = -_b6;
            _b10 = +_b10;
            _b15 = -_b15;
            _b30 = -_b30;
            return *this;
        }
        constexpr QuadraticElement235<T>& iconj5() {
            _a   = +_a;
            _b2  = +_b2;
            _b3  = +_b3;
            _b5  = -_b5;
            _b6  = +_b6;
            _b10 = -_b10;
            _b15 = -_b15;
            _b30 = -_b30;
            return *this;
        }
        
        [[nodiscard]] constexpr T norm() const {
            return conj_and_norm().second;
        }
        
        //unary
        constexpr QuadraticElement235<T> operator+() const {
            return QuadraticElement235<T>{+_a,
                                          +_b2,
                                          +_b3,
                                          +_b5,
                                          +_b6,
                                          +_b10,
                                          +_b15,
                                          +_b30};
        }
        constexpr QuadraticElement235<T>& ipos() {
            _a   = +_a;
            _b2  = +_b2;
            _b3  = +_b3;
            _b5  = +_b5;
            _b6  = +_b6;
            _b10 = +_b10;
            _b15 = +_b15;
            _b30 = +_b30;
            return *this;
        }
        
        constexpr QuadraticElement235<T> operator-() const {
            return QuadraticElement235<T>{-_a,
                                          -_b2,
                                          -_b3,
                                          -_b5,
                                          -_b6,
                                          -_b10,
                                          -_b15,
                                          -_b30};
        }
        constexpr QuadraticElement235<T>& ineg() {
            _a   = -_a;
            _b2  = -_b2;
            _b3  = -_b3;
            _b5  = -_b5;
            _b6  = -_b6;
            _b10 = -_b10;
            _b15 = -_b15;
            _b30 = -_b30;
            return *this;
        }
        
        //addition
        constexpr QuadraticElement235<T>& operator++() {
            ++_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement235<T> operator++(int) {
            const QuadraticElement235<T> tmp = *this;
            ++(*this);
            return tmp;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator+=(const S& rhs) requires (!is_quadraticelement235_v<S>) {
            _a += rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator+=(const QuadraticElement235<S>& rhs) {
            _a   += rhs._a;
            _b2  += rhs._b2;
            _b3  += rhs._b3;
            _b5  += rhs._b5;
            _b6  += rhs._b6;
            _b10 += rhs._b10;
            _b15 += rhs._b15;
            _b30 += rhs._b30;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator+(const S& lhs, const QuadraticElement235<T>& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(lhs + std::declval<T>());
            return QuadraticElement235<R>{
                         lhs + rhs._a,
                static_cast<R>(rhs._b2),
                static_cast<R>(rhs._b3),
                static_cast<R>(rhs._b5),
                static_cast<R>(rhs._b6),
                static_cast<R>(rhs._b10),
                static_cast<R>(rhs._b15),
                static_cast<R>(rhs._b30)
            };
        }
        template<typename S>
        friend constexpr auto operator+(const QuadraticElement235<T>& lhs, const S& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(std::declval<T>() + rhs);
            return QuadraticElement235<R>{
                               lhs._a + rhs,
                static_cast<R>(lhs._b2),
                static_cast<R>(lhs._b3),
                static_cast<R>(lhs._b5),
                static_cast<R>(lhs._b6),
                static_cast<R>(lhs._b10),
                static_cast<R>(lhs._b15),
                static_cast<R>(lhs._b30)
            };
        }
        template<typename S>
        friend constexpr auto operator+(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
            using R = decltype(std::declval<S>() + std::declval<T>());
            return QuadraticElement235<R>{
                lhs._a   + rhs._a,
                lhs._b2  + rhs._b2,
                lhs._b3  + rhs._b3,
                lhs._b5  + rhs._b5,
                lhs._b6  + rhs._b6,
                lhs._b10 + rhs._b10,
                lhs._b15 + rhs._b15,
                lhs._b30 + rhs._b30
            };
        }
        
        //subtraction
        constexpr QuadraticElement235<T>& operator--() {
            --_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement235<T> operator--(int) {
            const QuadraticElement235<T> tmp = *this;
            --(*this);
            return tmp;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator-=(const S& rhs) requires (!is_quadraticelement235_v<S>) {
            _a -= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator-=(const QuadraticElement235<S>& rhs) {
            _a   -= rhs._a;
            _b2  -= rhs._b2;
            _b3  -= rhs._b3;
            _b5  -= rhs._b5;
            _b6  -= rhs._b6;
            _b10 -= rhs._b10;
            _b15 -= rhs._b15;
            _b30 -= rhs._b30;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator-(const S& lhs, const QuadraticElement235<T>& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(lhs - std::declval<T>());
            return QuadraticElement235<R>{
                          lhs - rhs._a,
                -static_cast<R>(rhs._b2),
                -static_cast<R>(rhs._b3),
                -static_cast<R>(rhs._b5),
                -static_cast<R>(rhs._b6),
                -static_cast<R>(rhs._b10),
                -static_cast<R>(rhs._b15),
                -static_cast<R>(rhs._b30)
            };
        }
        template<typename S>
        friend constexpr auto operator-(const QuadraticElement235<T>& lhs, const S& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(std::declval<T>() - rhs);
            return QuadraticElement235<R>{
                               lhs._a - rhs,
                static_cast<R>(lhs._b2),
                static_cast<R>(lhs._b3),
                static_cast<R>(lhs._b5),
                static_cast<R>(lhs._b6),
                static_cast<R>(lhs._b10),
                static_cast<R>(lhs._b15),
                static_cast<R>(lhs._b30)
            };
        }
        template<typename S>
        friend constexpr auto operator-(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
            using R = decltype(std::declval<S>() - std::declval<T>());
            return QuadraticElement235<R>{
                lhs._a   - rhs._a,
                lhs._b2  - rhs._b2,
                lhs._b3  - rhs._b3,
                lhs._b5  - rhs._b5,
                lhs._b6  - rhs._b6,
                lhs._b10 - rhs._b10,
                lhs._b15 - rhs._b15,
                lhs._b30 - rhs._b30
            };
        }
        
        //multiplication
        template<typename S>
        constexpr QuadraticElement235<T>& operator*=(const S& rhs) requires (!is_quadraticelement235_v<S>) {
            _a   *= rhs;
            _b2  *= rhs;
            _b3  *= rhs;
            _b5  *= rhs;
            _b6  *= rhs;
            _b10 *= rhs;
            _b15 *= rhs;
            _b30 *= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator*=(const QuadraticElement235<S>& rhs) {
            const T a  = _a,  b2  = _b2,  b3  = _b3,  b5  = _b5;
            const T b6 = _b6, b10 = _b10, b15 = _b15, b30 = _b30;
            _a   = a*rhs._a   + 2*b2 *rhs._b2 + 3*b3 *rhs._b3  + 5*b5 *rhs._b5  + 6* b6*rhs._b6  + 10*b10*rhs._b10 + 15* b15*rhs._b15 + 30*b30*rhs._b30;
            _b2  = a*rhs._b2  +   b2 *rhs._a  + 3*(b3*rhs._b6  +   b6 *rhs._b3) + 5*(b5*rhs._b10 +    b10*rhs._b5) + 15*(b15*rhs._b30 +    b30*rhs._b15);
            _b3  = a*rhs._b3  +   b3 *rhs._a  + 2*(b2*rhs._b6  +   b6 *rhs._b2) + 5*(b5*rhs._b15 +    b15*rhs._b5) + 10*(b10*rhs._b30 +    b30*rhs._b10);
            _b5  = a*rhs._b5  +   b5 *rhs._a  + 2*(b2*rhs._b10 +   b10*rhs._b2) + 3*(b3*rhs._b15 +    b15*rhs._b3) +  6*(b6 *rhs._b30 +    b30*rhs._b6);
            _b6  = a*rhs._b6  +   b6 *rhs._a  +    b2*rhs._b3  +   b3 *rhs._b2  + 5*(b5*rhs._b30 +    b30*rhs._b5  +     b10*rhs._b15 +    b15*rhs._b10);
            _b10 = a*rhs._b10 +   b10*rhs._a  +    b2*rhs._b5  +   b5 *rhs._b2  + 3*(b3*rhs._b30 +    b30*rhs._b3  +     b6 *rhs._b15 +    b15*rhs._b6);
            _b15 = a*rhs._b15 +   b15*rhs._a  +    b3*rhs._b5  +   b5 *rhs._b3  + 2*(b2*rhs._b30 +    b30*rhs._b2  +     b6 *rhs._b10 +    b10*rhs._b6);
            _b30 = a*rhs._b30 +   b30*rhs._a  +    b2*rhs._b15 +   b15*rhs._b2  +    b3*rhs._b10 +    b10*rhs._b3  +     b5 *rhs._b6  +    b6 *rhs._b5;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator*(const S& lhs, const QuadraticElement235<T>& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(lhs * std::declval<T>());
            return QuadraticElement235<R>{
                lhs * rhs._a,
                lhs * rhs._b2,
                lhs * rhs._b3,
                lhs * rhs._b5,
                lhs * rhs._b6,
                lhs * rhs._b10,
                lhs * rhs._b15,
                lhs * rhs._b30
            };
        }
        template<typename S>
        friend constexpr auto operator*(const QuadraticElement235<T>& lhs, const S& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(std::declval<T>() * rhs);
            return QuadraticElement235<R>{
                lhs._a   * rhs,
                lhs._b2  * rhs,
                lhs._b3  * rhs,
                lhs._b5  * rhs,
                lhs._b6  * rhs,
                lhs._b10 * rhs,
                lhs._b15 * rhs,
                lhs._b30 * rhs};
        }
        template<typename S>
        friend constexpr auto operator*(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
            using R = decltype(std::declval<S>() * std::declval<T>());
            return QuadraticElement235<R>{
                lhs._a*rhs._a   + 2*lhs._b2*rhs._b2 + 3*lhs._b3*rhs._b3   + 5*lhs._b5 *rhs._b5  + 6* lhs._b6*rhs._b6  + 10*lhs._b10*rhs._b10 + 15* lhs._b15*rhs._b15 + 30*lhs._b30*rhs._b30,
                lhs._a*rhs._b2  +   lhs._b2*rhs._a  + 3*(lhs._b3*rhs._b6  +   lhs._b6 *rhs._b3) + 5*(lhs._b5*rhs._b10 +    lhs._b10*rhs._b5) + 15*(lhs._b15*rhs._b30 +    lhs._b30*rhs._b15),
                lhs._a*rhs._b3  +   lhs._b3*rhs._a  + 2*(lhs._b2*rhs._b6  +   lhs._b6 *rhs._b2) + 5*(lhs._b5*rhs._b15 +    lhs._b15*rhs._b5) + 10*(lhs._b10*rhs._b30 +    lhs._b30*rhs._b10),
                lhs._a*rhs._b5  +   lhs._b5*rhs._a  + 2*(lhs._b2*rhs._b10 +   lhs._b10*rhs._b2) + 3*(lhs._b3*rhs._b15 +    lhs._b15*rhs._b3) +  6*(lhs._b6 *rhs._b30 +    lhs._b30*rhs._b6),
                lhs._a*rhs._b6  +   lhs._b6*rhs._a  +    lhs._b2*rhs._b3  +   lhs._b3 *rhs._b2  + 5*(lhs._b5*rhs._b30 +    lhs._b30*rhs._b5  +     lhs._b10*rhs._b15 +    lhs._b15*rhs._b10),
                lhs._a*rhs._b10 +   lhs._b10*rhs._a +    lhs._b2*rhs._b5  +   lhs._b5 *rhs._b2  + 3*(lhs._b3*rhs._b30 +    lhs._b30*rhs._b3  +     lhs._b6 *rhs._b15 +    lhs._b15*rhs._b6),
                lhs._a*rhs._b15 +   lhs._b15*rhs._a +    lhs._b3*rhs._b5  +   lhs._b5 *rhs._b3  + 2*(lhs._b2*rhs._b30 +    lhs._b30*rhs._b2  +     lhs._b6 *rhs._b10 +    lhs._b10*rhs._b6),
                lhs._a*rhs._b30 +   lhs._b30*rhs._a +    lhs._b2*rhs._b15 +   lhs._b15*rhs._b2  +    lhs._b3*rhs._b10 +    lhs._b10*rhs._b3  +     lhs._b5 *rhs._b6  +    lhs._b6 *rhs._b5
            };
        }
        
        //inversion & division
        constexpr QuadraticElement235<T> inv() const {
            const auto [adj, nrm] = conj_and_norm();
            return adj / nrm;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator/=(const S& rhs) requires (!is_quadraticelement235_v<S>) {
            _a   /= rhs;
            _b2  /= rhs;
            _b3  /= rhs;
            _b5  /= rhs;
            _b6  /= rhs;
            _b10 /= rhs;
            _b15 /= rhs;
            _b30 /= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator/=(const QuadraticElement235<S>& rhs) {
            const auto [adj, nrm] = rhs.conj_and_norm();
            *this *= adj;
            *this /= nrm;
            return *this;
        }
        template<typename S>
        friend constexpr auto operator/(const S& lhs, const QuadraticElement235<T>& rhs) requires (!is_quadraticelement235_v<S>) {
            const auto [adj, nrm] = rhs.conj_and_norm();
            return lhs * adj / nrm;
        }
        template<typename S>
        friend constexpr auto operator/(const QuadraticElement235<T>& lhs, const S& rhs) requires (!is_quadraticelement235_v<S>) {
            using R = decltype(std::declval<T>() / rhs);
            return QuadraticElement235<R>{
                lhs._a   / rhs,
                lhs._b2  / rhs,
                lhs._b3  / rhs,
                lhs._b5  / rhs,
                lhs._b6  / rhs,
                lhs._b10 / rhs,
                lhs._b15 / rhs,
                lhs._b30 / rhs
            };
        }
        template<typename S>
        friend constexpr auto operator/(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
            const auto [adj, nrm] = rhs.conj_and_norm();
            return lhs * adj / nrm;
        }
        
        
        
        //IO
        friend std::ostream& operator<<(std::ostream& os, const QuadraticElement235& x) {
            os << x._a;
            
            if(x._b2 >= 0) {
                os << '+';
            }
            os << x._b2 << "sqrt(" << 2 << ')';
            
            if(x._b3 >= 0) {
                os << '+';
            }
            os << x._b3 << "sqrt(" << 3 << ')';
            
            if(x._b5 >= 0) {
                os << '+';
            }
            os << x._b5 << "sqrt(" << 5 << ')';
            
            if(x._b6 >= 0) {
                os << '+';
            }
            os << x._b6 << "sqrt(" << 6 << ')';
            
            if(x._b10 >= 0) {
                os << '+';
            }
            os << x._b10 << "sqrt(" << 10 << ')';
            
            if(x._b15 >= 0) {
                os << '+';
            }
            os << x._b15 << "sqrt(" << 15 << ')';
            
            if(x._b30 >= 0) {
                os << '+';
            }
            os << x._b30 << "sqrt(" << 30 << ')';
            
            return os;
        }
    };
    
    
    
}



#endif //RADICALFIELDPP_QUADRATICELEMENT235_HPP
