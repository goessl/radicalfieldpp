#ifndef RADICALFIELD_QUADRATICELEMENT235_HPP
#define RADICALFIELD_QUADRATICELEMENT235_HPP



#include <type_traits> //is_floating_point_v
#include <numbers>     //sqrt2_v
//#include <compare>     //strong_ordering
#include <cmath>       //abs, sqrt
#include <utility>     //pair
#include <ostream>     //ostream



namespace radicalfield {
    
    
    
    //necessary for reliable detection of scalar/QuadraticElement235 types
    struct quadraticelement235_tag {};
    template<typename T>
    struct is_quadraticelement235 : std::is_base_of<quadraticelement235_tag, std::decay_t<T>>{};
    template<typename T>
    inline constexpr bool is_quadraticelement235_v = is_quadraticelement235<T>::value;
    
    
    
    /**
     * Element of the quadratic rationals $\mathbb{K}\left(\sqrt{2}, \sqrt{3}, \sqrt{5}\right)$.
     * 
     * An instance represents an exact rational extension element of the form
     * 
     * $$
     *     a+b_2\sqrt{2}+b_3\sqrt{3}+b_5\sqrt{5}+b_6\sqrt{6}+b_{10}\sqrt{10}+b_{15}\sqrt{15}+b_{30}\sqrt{30} \qquad a, b_2, b_3, b_5, b_6, b_{10}, b_{15}, b_{30}\in\mathbb{K}
     * $$
     * 
     * where $\mathbb{K}$ is expected to be an integral ($\mathbb{Z}$)
     * or rational type ($\mathbb{Q}$).
     * 
     * The class is intended to behave similarly to complex<T>,
     * but additionally support mixed type operations and behave like their
     * coefficient types (QuadraticElement235<int> + QuadraticElement235<long> = QuadraticElement235<long>).
     * 
     * [Wikipedia - Quadratic integers](https://en.wikipedia.org/wiki/Quadratic_integer)
     */
    template<typename T=int>
    class [[nodiscard]] QuadraticElement235 : public quadraticelement235_tag {
    private:
        T _a, _b2, _b3, _b5, _b6, _b10, _b15, _b30;
        
        template<typename> //different subtype interoperability
        friend class QuadraticElement235;
    
    
    
    public:
        //constructors
        //QuadraticElement235<T>{(a), (b2), (b3), ...}
        //QuadraticElement235<T>{QuadraticElement235<S>}
        //QuadraticElement235<T>{QuadraticElement235<T>}
        //QuadraticElement235<T>{std::move(QuadraticElement235<T>)}
        constexpr QuadraticElement235<T>(
            const T& a=T{}, const T& b2=T{}, const T& b3=T{}, const T& b5=T{},
            const T& b6=T{}, const T& b10=T{}, const T& b15=T{}, const T& b30=T{}):
            _a(a), _b2(b2), _b3(b3), _b5(b5), _b6(b6), _b10(b10), _b15(b15), _b30(b30) {}
        template<typename S>
        constexpr QuadraticElement235<T>(const QuadraticElement235<S>& other): //converting
            _a(static_cast<T>(other._a)), _b2(static_cast<T>(other._b2)),
            _b3(static_cast<T>(other._b3)), _b5(static_cast<T>(other._b5)),
            _b6(static_cast<T>(other._b6)), _b10(static_cast<T>(other._b10)),
            _b15(static_cast<T>(other._b15)), _b30(static_cast<T>(other._b30)) {}
        constexpr QuadraticElement235<T>(const QuadraticElement235<T>& other) = default; //copy
        constexpr QuadraticElement235<T>(QuadraticElement235<T>&& other) = default; //move
        
        //assignments
        //QuadraticElement235<T> = S
        //QuadraticElement235<T> = QuadraticElement235<S>
        //QuadraticElement235<T> = QuadraticElement235<T>
        //QuadraticElement235<T> = std::move(QuadraticElement235<T>)
        template<typename S> requires (!is_quadraticelement235_v<S>)
        constexpr QuadraticElement235<T>& operator=(const S& other) {
            _a   = static_cast<T>(other);
            _b2  = {};
            _b3  = {};
            _b5  = {};
            _b6  = {};
            _b10 = {};
            _b15 = {};
            _b30 = {};
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement235<T>& operator=(const QuadraticElement235<S>& other) { //converting
            _a   = static_cast<T>(other._a);
            _b2  = static_cast<T>(other._b2);
            _b3  = static_cast<T>(other._b3);
            _b5  = static_cast<T>(other._b5);
            _b6  = static_cast<T>(other._b6);
            _b10 = static_cast<T>(other._b10);
            _b15 = static_cast<T>(other._b15);
            _b30 = static_cast<T>(other._b30);
            return *this;
        }
        constexpr QuadraticElement235<T>& operator=(const QuadraticElement235<T>& other) = default; //copy
        constexpr QuadraticElement235<T>& operator=(QuadraticElement235<T>&& other) = default; //move
        
        
        
        //accessors
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
        [[nodiscard]] constexpr bool is_rational() const {
            return !(static_cast<bool>(_b2)
                  || static_cast<bool>(_b3)
                  || static_cast<bool>(_b5)
                  || static_cast<bool>(_b6)
                  || static_cast<bool>(_b10)
                  || static_cast<bool>(_b15)
                  || static_cast<bool>(_b30));
        }
        //static_cast<bool>(QuadraticElement235<T>)
        //static_cast<QuadraticElement235<S>>(QuadraticElement235<T>)
        //static_cast<S>(QuadraticElement235<T>)
        //static_cast<F>(QuadraticElement235<T>)
        [[nodiscard]] constexpr explicit operator bool() const {
            return static_cast<bool>(_a)
                || static_cast<bool>(_b2)
                || static_cast<bool>(_b3)
                || static_cast<bool>(_b5)
                || static_cast<bool>(_b6)
                || static_cast<bool>(_b10)
                || static_cast<bool>(_b15)
                || static_cast<bool>(_b30);
        }
        template<typename S> //NEVER REMOVE EXPLICIT: all binary casts would break
        [[nodiscard]] constexpr explicit operator QuadraticElement235<S>() const {
            return QuadraticElement235<S>{*this};
        }
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] constexpr explicit operator S() const {
            return _a;
        }
        template<std::floating_point F>
        [[nodiscard]] constexpr explicit operator F() const {
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
        //                    S  == QuadraticElement235<T>
        //QuadraticElement235<T> ==                     S
        //QuadraticElement235<S> == QuadraticElement235<T>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr bool operator==(const S& lhs, const QuadraticElement235<T>& rhs) {
            return lhs==rhs._a && rhs.is_rational();
        }
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr bool operator==(const QuadraticElement235<T>& lhs, const S& rhs) {
            return lhs._a==rhs && lhs.is_rational();
        }
        template<typename S>
        [[nodiscard]] friend constexpr bool operator==(const QuadraticElement235<T>& lhs, const QuadraticElement235<S>& rhs) {
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
        [[nodiscard]] constexpr auto conj_and_norm() const {
            const auto c5  = conj5();
            const auto y   = *this * c5; //K(sqrt(2), sqrt(3))
            const auto c3y = y.conj3();
            const auto z   = y * c3y;    //K(sqrt(2))
            const auto c2z = z.conj2();
            return std::make_pair(c5*c3y*c2z, (z*c2z).a());
        }
        
        [[nodiscard]] constexpr auto conj() const {
            return conj_and_norm().first;
        }
        [[nodiscard]] constexpr auto conj2() const {
            using R = decltype((+std::declval<T>()) + (-std::declval<T>()));
            return QuadraticElement235<R>{+_a,
                                          -_b2,
                                          +_b3,
                                          +_b5,
                                          -_b6,
                                          -_b10,
                                          +_b15,
                                          -_b30};
        }
        [[nodiscard]] constexpr auto conj3() const {
            using R = decltype((+std::declval<T>()) + (-std::declval<T>()));
            return QuadraticElement235<R>{+_a,
                                          +_b2,
                                          -_b3,
                                          +_b5,
                                          -_b6,
                                          +_b10,
                                          -_b15,
                                          -_b30};
        }
        [[nodiscard]] constexpr auto conj5() const {
            using R = decltype((+std::declval<T>()) + (-std::declval<T>()));
            return QuadraticElement235<R>{+_a,
                                          +_b2,
                                          +_b3,
                                          -_b5,
                                          +_b6,
                                          -_b10,
                                          -_b15,
                                          -_b30};
        }
        constexpr QuadraticElement235<T>& iconj2() {
            if constexpr (requires { std::declval<T>().ipos(); }) {
                _a.ipos();
                _b3.ipos();
                _b5.ipos();
                _b15.ipos();
            } else {
                _a   = +_a;
                _b3  = +_b3;
                _b5  = +_b5;
                _b15 = +_b15;
            }
            if constexpr (requires { std::declval<T>().ineg(); }) {
                _b2.ineg();
                _b6.ineg();
                _b10.ineg();
                _b30.ineg();
            } else {
                _b2  = -_b2;
                _b6  = -_b6;
                _b10 = -_b10;
                _b30 = -_b30;
            }
            return *this;
        }
        constexpr QuadraticElement235<T>& iconj3() {
            if constexpr (requires { std::declval<T>().ipos(); }) {
                _a.ipos();
                _b2.ipos();
                _b5.ipos();
                _b10.ipos();
            } else {
                _a   = +_a;
                _b2  = +_b2;
                _b5  = +_b5;
                _b10 = +_b10;
            }
            if constexpr (requires { std::declval<T>().ineg(); }) {
                _b3.ineg();
                _b6.ineg();
                _b15.ineg();
                _b30.ineg();
            } else {
                _b3  = -_b3;
                _b6  = -_b6;
                _b15 = -_b15;
                _b30 = -_b30;
            }
            return *this;
        }
        constexpr QuadraticElement235<T>& iconj5() {
            if constexpr (requires { std::declval<T>().ipos(); }) {
                _a.ipos();
                _b2.ipos();
                _b3.ipos();
                _b6.ipos();
            } else {
                _a   = +_a;
                _b2  = +_b2;
                _b3  = +_b3;
                _b6  = +_b6;
            }
            if constexpr (requires { std::declval<T>().ineg(); }) {
                _b5.ineg();
                _b10.ineg();
                _b15.ineg();
                _b30.ineg();
            } else {
                _b5  = -_b5;
                _b10 = -_b10;
                _b15 = -_b15;
                _b30 = -_b30;
            }
            return *this;
        }
        
        [[nodiscard]] constexpr auto norm() const {
            const auto y = *this * conj5();
            const auto z = y * y.conj3();
            return (z*z.conj2()).a();
        }
        
        
        //unary
        //+QuadraticElement235<T>
        // QuadraticElement235<T>.ipos()
        [[nodiscard]] constexpr auto operator+() const {
            using R = decltype(+std::declval<T>());
            return QuadraticElement235<R>{+_a,
                                          +_b2,
                                          +_b3,
                                          +_b5,
                                          +_b6,
                                          +_b10,
                                          +_b15,
                                          +_b30};
        }
        constexpr QuadraticElement235<T>& ipos() {
            if constexpr (requires { std::declval<T>().ipos(); }) {
                _a.ipos();
                _b2.ipos();
                _b3.ipos();
                _b5.ipos();
                _b6.ipos();
                _b10.ipos();
                _b15.ipos();
                _b30.ipos();
            } else {
                _a   = +_a;
                _b2  = +_b2;
                _b3  = +_b3;
                _b5  = +_b5;
                _b6  = +_b6;
                _b10 = +_b10;
                _b15 = +_b15;
                _b30 = +_b30;
            }
            return *this;
        }
        
        //-QuadraticElement235<T>
        // QuadraticElement235<T>.ineg()
        [[nodiscard]] constexpr auto operator-() const {
            using R = decltype(-std::declval<T>());
            return QuadraticElement235<R>{-_a,
                                          -_b2,
                                          -_b3,
                                          -_b5,
                                          -_b6,
                                          -_b10,
                                          -_b15,
                                          -_b30};
        }
        constexpr QuadraticElement235<T>& ineg() {
            if constexpr (requires { std::declval<T>().ineg(); }) {
                _a.ineg();
                _b2.ineg();
                _b3.ineg();
                _b5.ineg();
                _b6.ineg();
                _b10.ineg();
                _b15.ineg();
                _b30.ineg();
            } else {
                _a   = -_a;
                _b2  = -_b2;
                _b3  = -_b3;
                _b5  = -_b5;
                _b6  = -_b6;
                _b10 = -_b10;
                _b15 = -_b15;
                _b30 = -_b30;
            }
            return *this;
        }
        
        
        //addition
        //++QuadraticElement235<T>
        //  QuadraticElement235<T>++
        constexpr QuadraticElement235<T>& operator++() {
            ++_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement235<T> operator++(int) {
            const QuadraticElement235<T> tmp = *this;
            ++(*this);
            return tmp;
        }
        
        //QuadraticElement235<T> +=                     S
        //QuadraticElement235<T> += QuadraticElement235<S>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        constexpr QuadraticElement235<T>& operator+=(const S& rhs) {
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
        
        //                    S  + QuadraticElement235<T>
        //QuadraticElement235<T> +                     S
        //QuadraticElement235<S> + QuadraticElement235<T>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator+(const S& lhs, const QuadraticElement235<T>& rhs) {
            using R = decltype(lhs + std::declval<T>());
            return QuadraticElement235<R>{
                lhs +                rhs._a,
                    + static_cast<R>(rhs._b2),
                    + static_cast<R>(rhs._b3),
                    + static_cast<R>(rhs._b5),
                    + static_cast<R>(rhs._b6),
                    + static_cast<R>(rhs._b10),
                    + static_cast<R>(rhs._b15),
                    + static_cast<R>(rhs._b30)
            };
        }
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator+(const QuadraticElement235<T>& lhs, const S& rhs) {
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
        [[nodiscard]] friend constexpr auto operator+(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
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
        //--QuadraticElement235<T>
        //  QuadraticElement235<T>--
        constexpr QuadraticElement235<T>& operator--() {
            --_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement235<T> operator--(int) {
            const QuadraticElement235<T> tmp = *this;
            --(*this);
            return tmp;
        }
        
        //QuadraticElement235<T> -=                     S
        //QuadraticElement235<T> -= QuadraticElement235<S>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        constexpr QuadraticElement235<T>& operator-=(const S& rhs) {
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
        
        //                    S  - QuadraticElement235<T>
        //QuadraticElement235<T> -                     S
        //QuadraticElement235<S> - QuadraticElement235<T>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator-(const S& lhs, const QuadraticElement235<T>& rhs) {
            using R = decltype(lhs - std::declval<T>());
            return QuadraticElement235<R>{
                lhs -                rhs._a,
                    - static_cast<R>(rhs._b2),
                    - static_cast<R>(rhs._b3),
                    - static_cast<R>(rhs._b5),
                    - static_cast<R>(rhs._b6),
                    - static_cast<R>(rhs._b10),
                    - static_cast<R>(rhs._b15),
                    - static_cast<R>(rhs._b30)
            };
        }
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator-(const QuadraticElement235<T>& lhs, const S& rhs) {
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
        [[nodiscard]] friend constexpr auto operator-(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
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
        //QuadraticElement235<T> *=                     S
        //QuadraticElement235<T> *= QuadraticElement235<S>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        constexpr QuadraticElement235<T>& operator*=(const S& rhs) {
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
            *this = *this * rhs;
            return *this;
        }
        
        //                    S  * QuadraticElement235<T>
        //QuadraticElement235<T> *                     S
        //QuadraticElement235<S> * QuadraticElement235<T>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator*(const S& lhs, const QuadraticElement235<T>& rhs) {
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
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator*(const QuadraticElement235<T>& lhs, const S& rhs) {
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
        [[nodiscard]] friend constexpr auto operator*(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
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
        //for division by a QuadraticElement235<T> y always do
        //y / x = y * x.conj() / x.norm() = (y * x.conj()) / x.norm()
        //the multiplication first to avoid early cancellation/truncation
        [[nodiscard]] constexpr QuadraticElement235<T> inv() const {
            const auto [adj, nrm] = conj_and_norm();
            return adj / nrm;
        }
        
        //QuadraticElement235<T> /=                     S
        //QuadraticElement235<T> /= QuadraticElement235<S>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        constexpr QuadraticElement235<T>& operator/=(const S& rhs) {
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
        
        //                    S  / QuadraticElement235<T>
        //QuadraticElement235<T> /                     S
        //QuadraticElement235<S> / QuadraticElement235<T>
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator/(const S& lhs, const QuadraticElement235<T>& rhs) {
            const auto [adj, nrm] = rhs.conj_and_norm();
            return lhs * adj / nrm;
        }
        template<typename S> requires (!is_quadraticelement235_v<S>)
        [[nodiscard]] friend constexpr auto operator/(const QuadraticElement235<T>& lhs, const S& rhs) {
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
        [[nodiscard]] friend constexpr auto operator/(const QuadraticElement235<S>& lhs, const QuadraticElement235<T>& rhs) {
            const auto [adj, nrm] = rhs.conj_and_norm();
            return lhs * adj / nrm;
        }
        
        
        
        //IO
        friend std::ostream& operator<<(std::ostream& os, const QuadraticElement235& x) {
            const std::ios_base::fmtflags old_flags = os.flags();
            
            os << x._a;
            os << std::showpos;
            os << x._b2 << "sqrt(2)";
            os << x._b3 << "sqrt(3)";
            os << x._b5 << "sqrt(5)";
            os << x._b6 << "sqrt(6)";
            os << x._b10 << "sqrt(10)";
            os << x._b15 << "sqrt(15)";
            os << x._b30 << "sqrt(30)";
            
            os.flags(old_flags);
            return os;
        }
        
        friend std::ostream& pretty_print(std::ostream& os, const QuadraticElement235<T>& x) {
            const std::ios_base::fmtflags old_flags = os.flags();
            
            bool printed = false;
            if(static_cast<bool>(x._a)) {
                os << x._a;
                printed = true;
            }
            if(static_cast<bool>(x._b2)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b2 << "\u221A2";
                printed = true;
            }
            if(static_cast<bool>(x._b3)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b3 << "\u221A3";
                printed = true;
            }
            if(static_cast<bool>(x._b5)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b5 << "\u221A5";
                printed = true;
            }
            if(static_cast<bool>(x._b6)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b6 << "\u221A6";
                printed = true;
            }
            if(static_cast<bool>(x._b10)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b10 << "\u221A10";
                printed = true;
            }
            if(static_cast<bool>(x._b15)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b15 << "\u221A15";
                printed = true;
            }
            if(static_cast<bool>(x._b30)) {
                if(printed) {
                    os << std::showpos;
                }
                os << x._b30 << "\u221A30";
                printed = true;
            }
            
            if(!printed) {
                os << '0';
            }
            
            os.flags(old_flags);
            return os;
        }
    };
    
    
    
}



#endif //RADICALFIELD_QUADRATICELEMENT235_HPP
