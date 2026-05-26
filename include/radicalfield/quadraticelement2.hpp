#ifndef RADICALFIELD_QUADRATICELEMENT2_HPP
#define RADICALFIELD_QUADRATICELEMENT2_HPP



#include <type_traits> //is_floating_point_v
#include <numbers>     //sqrt2_v
#include <compare>     //strong_ordering
#include <cmath>       //abs
#include <ostream>     //ostream



namespace radicalfield {
    
    
    
    //necessary for reliable detection of scalar/QuadraticElement2 types
    struct quadraticelement2_tag {};
    template<typename T>
    struct is_quadraticelement2 : std::is_base_of<quadraticelement2_tag, std::decay_t<T>>{};
    template<typename T>
    inline constexpr bool is_quadraticelement2_v = is_quadraticelement2<T>::value;
    
    
    
    /**
     * Element of the quadratic rationals $\mathbb{K}\left(\sqrt{2}\right)$.
     * 
     * An instance represents an exact rational extension element of the form
     * 
     * $$
     *     a+b\sqrt{2} \qquad a, b\in\mathbb{K}
     * $$
     * 
     * where $\mathbb{K}$ is expected to be an integral ($\mathbb{Z}$)
     * or rational type ($\mathbb{Q}$).
     * 
     * The class is intended to behave similarly to complex<T>,
     * but additionally support mixed type operations and behave like their
     * coefficient types (QuadraticElement2<int> + QuadraticElement2<long> = QuadraticElement2<long>).
     * 
     * [Wikipedia - Quadratic integers](https://en.wikipedia.org/wiki/Quadratic_integer)
     */
    template<typename T=int>
    class [[nodiscard]] QuadraticElement2 : public quadraticelement2_tag {
    private:
        T _a, _b;
        
        template<typename> //different subtype interoperability
        friend class QuadraticElement2;
    
    
    
    public:
        //constructors
        //QuadraticElement2<T>{(a), (b)}
        //QuadraticElement2<T>{QuadraticElement2<S>}
        //QuadraticElement2<T>{QuadraticElement2<T>}
        //QuadraticElement2<T>{std::move(QuadraticElement2<T>)}
        constexpr QuadraticElement2<T>(const T& a=T{}, const T& b=T{}): _a(a), _b(b) {}
        template<typename S>
        constexpr QuadraticElement2<T>(const QuadraticElement2<S>& other):
            _a(static_cast<T>(other._a)), _b(static_cast<T>(other._b)) {} //converting
        constexpr QuadraticElement2<T>(const QuadraticElement2<T>& other) = default; //move
        constexpr QuadraticElement2<T>(QuadraticElement2<T>&& other) = default; //move
        
        //assignments
        //QuadraticElement2<T> = S
        //QuadraticElement2<T> = QuadraticElement2<S>
        //QuadraticElement2<T> = QuadraticElement2<T>
        //QuadraticElement2<T> = std::move(QuadraticElement2<T>)
        template<typename S> requires (!is_quadraticelement2_v<S>)
        constexpr QuadraticElement2<T>& operator=(const S& other) {
            _a = static_cast<T>(other);
            _b = T{};
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator=(const QuadraticElement2<S>& other) { //converting
            _a = static_cast<T>(other._a);
            _b = static_cast<T>(other._b);
            return *this;
        }
        constexpr QuadraticElement2<T>& operator=(const QuadraticElement2<T>& other) = default; //copy
        constexpr QuadraticElement2<T>& operator=(QuadraticElement2<T>&& other) = default; //move
        
        
        
        //accessors
        [[nodiscard]] constexpr const T& a() const noexcept { return _a; }
        [[nodiscard]] constexpr const T& b() const noexcept { return _b; }
        [[nodiscard]] constexpr T& a() noexcept { return _a; }
        [[nodiscard]] constexpr T& b() noexcept { return _b; }
        
        
        
        //conversion
        [[nodiscard]] constexpr bool is_rational() const {
            return !static_cast<bool>(_b);
        }
        //static_cast<bool>(QuadraticElement2<T>)
        //static_cast<QuadraticElement2<S>>(QuadraticElement2<T>)
        //static_cast<S>(QuadraticElement2<T>)
        //static_cast<F>(QuadraticElement2<T>)
        [[nodiscard]] constexpr explicit operator bool() const {
            return static_cast<bool>(_a) || static_cast<bool>(_b);
        }
        template<typename S> //NEVER REMOVE EXPLICIT: all binary casts would break
        [[nodiscard]] constexpr explicit operator QuadraticElement2<S>() const {
            return QuadraticElement2<S>{*this};
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] constexpr explicit operator S() const {
            return _a;
        }
        template<std::floating_point F>
        [[nodiscard]] constexpr explicit operator F() const {
            return static_cast<F>(_a) + std::numbers::sqrt2_v<F> * static_cast<F>(_b);
        }
        
        
        
        //ordering
        //                  S  == QuadraticElement2<T>
        //QuadraticElement2<T> ==                   S
        //QuadraticElement2<S> == QuadraticElement2<T>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr bool operator==(const S& lhs, const QuadraticElement2<T>& rhs) {
            return lhs==rhs._a && rhs.is_rational();
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr bool operator==(const QuadraticElement2<T>& lhs, const S& rhs) {
            return lhs._a==rhs && lhs.is_rational();
        }
        template<typename S>
        [[nodiscard]] friend constexpr bool operator==(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            return lhs._a==rhs._a && lhs._b==rhs._b;
        }
        
        //                  S  <=> QuadraticElement2<T>
        //QuadraticElement2<T> <=>                   S
        //QuadraticElement2<S> <=> QuadraticElement2<T>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr std::strong_ordering operator<=>(const S& lhs, const QuadraticElement2<T>& rhs) {
            //  c          <=> a+b*sqrt(2)   | -a
            //  c-a        <=>   b*sqrt(2)   | ^2
            // (c-a)*|c-a| <=> 2*b*|b|
            if constexpr (!std::is_floating_point_v<S>) {
                const auto l = lhs - rhs._a;
                return l*std::abs(l) <=> 2*rhs._b*std::abs(rhs._b);
            } else {
                return lhs <=> static_cast<S>(rhs);
            }
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr std::strong_ordering operator<=>(const QuadraticElement2<T>& lhs, const S& rhs) {
            // a+b*sqrt(2) <=>  c            | -a
            //   b*sqrt(2) <=>  c-a          | ^2
            // 2*b*|b|     <=> (c-a)*|c-a|
            if constexpr (!std::is_floating_point_v<S>) {
                const auto r = rhs - lhs._a;
                return 2*lhs._b*std::abs(lhs._b) <=> r*std::abs(r);
            } else {
                return static_cast<S>(lhs) <=> rhs;
            }
        }
        template<typename S>
        [[nodiscard]] friend constexpr std::strong_ordering operator<=>(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            //  a+b*sqrt(2) <=>    c+d *sqrt(2)   | -c-b*sqrt(2)
            //  a-c         <=>   (d-b)*sqrt(2)   | ^2
            // (a-c)*|a-c|  <=> 2*(d-b)*|d-b|
            const auto l = lhs._a - rhs._a;
            const auto r = rhs._b - lhs._b;
            return l*std::abs(l) <=> 2*r*std::abs(r);
        }
        
        
        
        //arithmetic
        
        //conjugation & norm
        [[nodiscard]] constexpr auto conj() const {
            //maybe unary operators change types, who knows
            using R = decltype((+std::declval<T>()) + (-std::declval<T>()));
            return QuadraticElement2<R>{+_a,
                                        -_b};
        }
        constexpr QuadraticElement2<T>& iconj() {
            _a = +_a;
            _b = -_b;
            return *this;
        }
        
        [[nodiscard]] constexpr auto norm() const {
            return _a*_a - 2*_b*_b;
        }
        
        
        //unary
        //+QuadraticElement2<T>
        // QuadraticElement2<T>.ipos()
        [[nodiscard]] constexpr auto operator+() const {
            using R = decltype(+std::declval<T>());
            return QuadraticElement2<R>{+_a,
                                        +_b};
        }
        constexpr QuadraticElement2<T>& ipos() {
            _a = +_a;
            _b = +_b;
            return *this;
        }
        
        //-QuadraticElement2<T>
        // QuadraticElement2<T>.ineg()
        [[nodiscard]] constexpr auto operator-() const {
            using R = decltype(-std::declval<T>());
            return QuadraticElement2<R>{-_a,
                                        -_b};
        }
        constexpr QuadraticElement2<T>& ineg() {
            _a = -_a;
            _b = -_b;
            return *this;
        }
        
        
        //addition
        //++QuadraticElement2<T>
        //  QuadraticElement2<T>++
        constexpr QuadraticElement2<T>& operator++() {
            ++_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement2<T> operator++(int) {
            const QuadraticElement2<T> tmp = *this;
            ++(*this);
            return tmp;
        }
        
        //QuadraticElement2<T> +=                   S
        //QuadraticElement2<T> += QuadraticElement2<S>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        constexpr QuadraticElement2<T>& operator+=(const S& rhs) {
            _a += rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator+=(const QuadraticElement2<S>& rhs) {
            _a += rhs._a;
            _b += rhs._b;
            return *this;
        }
        
        //                  S  + QuadraticElement2<T>
        //QuadraticElement2<T> +                   S
        //QuadraticElement2<S> + QuadraticElement2<T>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator+(const S& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(lhs + std::declval<T>());
            return QuadraticElement2<R>{lhs + rhs._a,
                              +static_cast<R>(rhs._b)};
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator+(const QuadraticElement2<T>& lhs, const S& rhs) {
            using R = decltype(std::declval<T>() + rhs);
            return QuadraticElement2<R>{lhs._a  + rhs,
                         static_cast<R>(lhs._b)};
        }
        template<typename S>
        [[nodiscard]] friend constexpr auto operator+(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(std::declval<S>() + std::declval<T>());
            return QuadraticElement2<R>{lhs._a + rhs._a,
                                        lhs._b + rhs._b};
        }
        
        
        //subtraction
        //--QuadraticElement2<T>
        //  QuadraticElement2<T>--
        constexpr QuadraticElement2<T>& operator--() {
            --_a;
            return *this;
        }
        [[nodiscard]] constexpr QuadraticElement2<T> operator--(int) {
            const QuadraticElement2<T> tmp = *this;
            --(*this);
            return tmp;
        }
        
        //QuadraticElement2<T> -=                   S
        //QuadraticElement2<T> -= QuadraticElement2<S>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        constexpr QuadraticElement2<T>& operator-=(const S& rhs) {
            _a -= rhs;
            return *this;
        }
        template<typename S>
        constexpr QuadraticElement2<T>& operator-=(const QuadraticElement2<S>& rhs) {
            _a -= rhs._a;
            _b -= rhs._b;
            return *this;
        }
        
        //                  S  - QuadraticElement2<T>
        //QuadraticElement2<T> -                   S
        //QuadraticElement2<S> - QuadraticElement2<T>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator-(const S& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(lhs - std::declval<T>());
            return QuadraticElement2<R>{lhs - rhs._a,
                              -static_cast<R>(rhs._b)};
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator-(const QuadraticElement2<T>& lhs, const S& rhs) {
            using R = decltype(std::declval<T>() - rhs);
            return QuadraticElement2<R>{lhs._a - rhs, 
                         static_cast<R>(lhs._b)};
        }
        template<typename S>
        [[nodiscard]] friend constexpr auto operator-(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(std::declval<S>() - std::declval<T>());
            return QuadraticElement2<R>{lhs._a - rhs._a,
                                        lhs._b - rhs._b};
        }
        
        
        //multiplication
        //QuadraticElement2<T> *=                   S
        //QuadraticElement2<T> *= QuadraticElement2<S>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        constexpr QuadraticElement2<T>& operator*=(const S& rhs) {
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
        
        //                  S  * QuadraticElement2<T>
        //QuadraticElement2<T> *                   S
        //QuadraticElement2<S> * QuadraticElement2<T>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator*(const S& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(lhs * std::declval<T>());
            return QuadraticElement2<R>{lhs * rhs._a,
                                        lhs * rhs._b};
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator*(const QuadraticElement2<T>& lhs, const S& rhs) {
            using R = decltype(std::declval<T>() * rhs);
            return QuadraticElement2<R>{lhs._a * rhs,
                                        lhs._b * rhs};
        }
        template<typename S>
        [[nodiscard]] friend constexpr auto operator*(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            using R = decltype(std::declval<S>() * std::declval<T>());
            return QuadraticElement2<R>{lhs._a*rhs._a + 2*lhs._b*rhs._b,
                                        lhs._a*rhs._b +   lhs._b*rhs._a};
        }
        
        
        //inversion & division
        //for division by a QuadraticElement2<T> y always do
        //y / x = y * x.conj() / x.norm() = (y * x.conj()) / x.norm()
        //the multiplication first to avoid early cancellation/truncation
        [[nodiscard]] constexpr QuadraticElement2<T> inv() const {
            return conj() / norm();
        }
        constexpr QuadraticElement2<T>& iinv() {
            iconj();
            *this /= norm();
            return *this;
        }
        
        //QuadraticElement2<T> /=                   S
        //QuadraticElement2<T> /= QuadraticElement2<S>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        constexpr QuadraticElement2<T>& operator/=(const S& rhs) {
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
        
        //                  S  / QuadraticElement2<T>
        //QuadraticElement2<T> /                   S
        //QuadraticElement2<S> / QuadraticElement2<T>
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator/(const S& lhs, const QuadraticElement2<T>& rhs) {
            return lhs * rhs.conj() / rhs.norm();
        }
        template<typename S> requires (!is_quadraticelement2_v<S>)
        [[nodiscard]] friend constexpr auto operator/(const QuadraticElement2<T>& lhs, const S& rhs) {
            using R = decltype(std::declval<T>() / rhs);
            return QuadraticElement2<R>{lhs._a / rhs,
                                        lhs._b / rhs};
        }
        template<typename S>
        [[nodiscard]] friend constexpr auto operator/(const QuadraticElement2<S>& lhs, const QuadraticElement2<T>& rhs) {
            return lhs * rhs.conj() / rhs.norm();
        }
        
        
        
        //IO
        friend std::ostream& operator<<(std::ostream& os, const QuadraticElement2& x) {
            const std::ios_base::fmtflags old_flags = os.flags();
            os << x._a;
            os << std::showpos << x._b << "sqrt(2)";
            os.flags(old_flags);
            return os;
        }
    };
    
    
    
}



#endif //RADICALFIELD_QUADRATICELEMENT2_HPP
