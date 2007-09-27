
/*
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef qla_capletvolstructure_hpp
#define qla_capletvolstructure_hpp

#include <qlo/termstructures.hpp>
#include <ql/voltermstructures/interestrate/optionlet/optionletstripper.hpp>
#include <ql/voltermstructures/interestrate/optionlet/optionletstripperadapter.hpp>

namespace QuantLib {
    class OptionletVolatilityStructure;
    class Period;
    class SmileSection;
    class IborIndex;
    class CapFloorTermVolSurface;
    class CapFloorTermVolCurve;
    class OptionletStripper;
    class OptionletStripper2;
    class OptionletStripperAdapter;
}

namespace QuantLibAddin {
    
    OH_OBJ_CLASS(OptionletVolatilityStructure, TermStructure);

    class ConstantOptionletVol : public OptionletVolatilityStructure {
      public:
        ConstantOptionletVol(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                             const QuantLib::Handle<QuantLib::Quote>& volatility,
                             const QuantLib::Calendar& cal,
                             const QuantLib::DayCounter& dayCounter,
                             bool permanent);
    };
      
    class OptionletStripperAdapter : public OptionletVolatilityStructure {
      public:
      OptionletStripperAdapter(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                               const QuantLib::Handle<QuantLib::OptionletStripper>& optionletStripper,
                               bool permanent);
    };

    class CapsStripper : public OptionletVolatilityStructure {
        public:

        CapsStripper(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                     const std::vector<QuantLib::Period>& tenors,
                     const std::vector<QuantLib::Rate>& strikes,
                     const boost::shared_ptr<QuantLib::CapFloorTermVolSurface>& surface,
                     const boost::shared_ptr<QuantLib::IborIndex>& index,
                     QuantLib::Period timeStep,
                     const QuantLib::Handle<QuantLib::YieldTermStructure>,
                     const QuantLib::DayCounter& volatilityDayCounter,
                     QuantLib::Real impliedVolatilityAccuracy,
                     QuantLib::Size maxEvaluations,
                     bool allowExtrapolation,
                     bool decoupleInterpolation,
                     bool permanent);

        CapsStripper(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                     const std::vector<QuantLib::Period>& tenors,
                     const std::vector<QuantLib::Rate>& strikes,
                     const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& volatilities,
                     const boost::shared_ptr<QuantLib::IborIndex>& index,
                     const QuantLib::Handle<QuantLib::YieldTermStructure> yieldTermStructure,
                     const QuantLib::DayCounter& dayCounter,
                     QuantLib::Real impliedVolatilityAccuracy,
                     QuantLib::Size maxEvaluations,
                     bool decoupledInterpolation,
                     bool permanent);

         CapsStripper(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                      const std::vector<QuantLib::Period>& tenors,
                      const std::vector<QuantLib::Rate>& strikes,
                      const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& volatilities,
                      const boost::shared_ptr<QuantLib::IborIndex>& index,
                      const QuantLib::Handle<QuantLib::YieldTermStructure> yieldTermStructure,
                      const QuantLib::DayCounter& dayCounter,
                      QuantLib::Real impliedVolatilityAccuracy,
                      QuantLib::Size maxEvaluations,
                      const std::vector<boost::shared_ptr<QuantLib::SmileSection> >& 
                        smileSectionInterfaces,
                      bool decoupledInterpolation,
                      bool permanent);

    };

    class SmileSectionsVolStructure: public OptionletVolatilityStructure {
      public:
        SmileSectionsVolStructure(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Date& referenceDate,
        const QuantLib::DayCounter& dayCounter,
        const std::vector<boost::shared_ptr<QuantLib::SmileSection> >& smileSections,
        bool permanent);
        
        };

    class SpreadedOptionletVol : public OptionletVolatilityStructure {
      public:
        SpreadedOptionletVol(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::OptionletVolatilityStructure>& underlyingVolStructure,
            const QuantLib::Handle<QuantLib::Quote>&,
            bool permanent);

    };

      class GenericCapletVolStructure : public OptionletVolatilityStructure {
      public:
          GenericCapletVolStructure(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                    std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& capletVols,
                                    const std::vector<QuantLib::Rate>& strikes,
                                    const std::vector<QuantLib::Time>& tenors,
                                    bool permanent);
    };

    OH_OBJ_CLASS(CapFloorTermVolatilityStructure, TermStructure);

    class CapFloorTermVolCurve : public CapFloorTermVolatilityStructure {
      public:
      CapFloorTermVolCurve(
          const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
          QuantLib::Natural settlementDays,
          const QuantLib::Calendar& calendar,
          const std::vector<QuantLib::Period>& optionTenors,
          const std::vector<QuantLib::Handle<QuantLib::Quote> >& volatilities,
          const QuantLib::DayCounter& dayCounter,
          bool permanent);
    };

    class CapFloorTermVolSurface : public CapFloorTermVolatilityStructure {
      public:
      CapFloorTermVolSurface(
          const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
          QuantLib::Natural settlementDays,
          const QuantLib::Calendar& calendar,
          const std::vector<QuantLib::Period>& optionTenors,
          const std::vector<QuantLib::Rate>& strikes,
          const std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > >& volatilities,
          const QuantLib::DayCounter& dc,
          bool permanent);
    };

    OH_LIB_CLASS(dummyClass, QuantLib::OptionletStripper);

    class OptionletStripper : public dummyClass {
      public:
        OptionletStripper(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                          const boost::shared_ptr<QuantLib::CapFloorTermVolSurface>& surface,
                          const boost::shared_ptr<QuantLib::IborIndex>& index,
                          QuantLib::Rate switchStrike,
                          bool permanent);
    };


    OH_LIB_CLASS(dummyClass1, QuantLib::OptionletStripper2);

    class OptionletStripper2 : public dummyClass1 {
      public:
        OptionletStripper2(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                           const QuantLib::Handle<QuantLib::OptionletStripper>& optionletStripper,
                           const QuantLib::Handle<QuantLib::CapFloorTermVolCurve>& atmCapFloorTermVolCurve,
                           bool permanent);
    };

}

#endif
