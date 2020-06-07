#pragma once
#ifndef ql_cliquet_option_hpp
#define ql_cliquet_option_hpp

#include <ql/instruments/oneassetoption.hpp>
#include <ql/instruments/payoffs.hpp>
#include <ql/time/date.hpp>
#include <vector>

namespace QuantLib {

    class EuropeanExercise;

    //author Xu Tao
    //! Snowball option
    /*! A Snowball is an Autocall product with Kick-In Put
    */
    class Snowball : public OneAssetOption {
    public:
        class arguments;
        class engine;
        Snowball(const ext::shared_ptr<PercentageStrikePayoff>&,
            const ext::shared_ptr<EuropeanExercise>& maturity,
            const std::vector<Date>& resetDates);
        void setupArguments(PricingEngine::arguments*) const;
    private:
        std::vector<Date> resetDates_;
    };

    //! %Arguments for cliquet option calculation
    // should inherit from a strikeless version of VanillaOption::arguments
    class Snowball::arguments : public OneAssetOption::arguments {
    public:
        arguments() : accruedCoupon(Null<Real>()),
            lastFixing(Null<Real>()),
            localCap(Null<Real>()),
            localFloor(Null<Real>()),
            globalCap(Null<Real>()),
            globalFloor(Null<Real>()) {}
        void validate() const;
        Real accruedCoupon, lastFixing;
        Real localCap, localFloor, globalCap, globalFloor;
        std::vector<Date> resetDates;
    };

    //! Snowball %engine base class
    class Snowball::engine
        : public GenericEngine<Snowball::arguments,
        Snowball::results> {};

}
#endif
