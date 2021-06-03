// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME AnaDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "AnaRoot.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_GeData(void *p = 0);
   static void *newArray_GeData(Long_t size, void *p);
   static void delete_GeData(void *p);
   static void deleteArray_GeData(void *p);
   static void destruct_GeData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GeData*)
   {
      ::GeData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GeData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GeData", ::GeData::Class_Version(), "AnaRoot.hh", 7,
                  typeid(::GeData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GeData::Dictionary, isa_proxy, 4,
                  sizeof(::GeData) );
      instance.SetNew(&new_GeData);
      instance.SetNewArray(&newArray_GeData);
      instance.SetDelete(&delete_GeData);
      instance.SetDeleteArray(&deleteArray_GeData);
      instance.SetDestructor(&destruct_GeData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GeData*)
   {
      return GenerateInitInstanceLocal((::GeData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GeData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SiData(void *p = 0);
   static void *newArray_SiData(Long_t size, void *p);
   static void delete_SiData(void *p);
   static void deleteArray_SiData(void *p);
   static void destruct_SiData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SiData*)
   {
      ::SiData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SiData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SiData", ::SiData::Class_Version(), "AnaRoot.hh", 43,
                  typeid(::SiData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SiData::Dictionary, isa_proxy, 4,
                  sizeof(::SiData) );
      instance.SetNew(&new_SiData);
      instance.SetNewArray(&newArray_SiData);
      instance.SetDelete(&delete_SiData);
      instance.SetDeleteArray(&deleteArray_SiData);
      instance.SetDestructor(&destruct_SiData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SiData*)
   {
      return GenerateInitInstanceLocal((::SiData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SiData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SiSiData(void *p = 0);
   static void *newArray_SiSiData(Long_t size, void *p);
   static void delete_SiSiData(void *p);
   static void deleteArray_SiSiData(void *p);
   static void destruct_SiSiData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SiSiData*)
   {
      ::SiSiData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SiSiData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SiSiData", ::SiSiData::Class_Version(), "AnaRoot.hh", 92,
                  typeid(::SiSiData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SiSiData::Dictionary, isa_proxy, 4,
                  sizeof(::SiSiData) );
      instance.SetNew(&new_SiSiData);
      instance.SetNewArray(&newArray_SiSiData);
      instance.SetDelete(&delete_SiSiData);
      instance.SetDeleteArray(&deleteArray_SiSiData);
      instance.SetDestructor(&destruct_SiSiData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SiSiData*)
   {
      return GenerateInitInstanceLocal((::SiSiData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SiSiData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FisEn(void *p = 0);
   static void *newArray_FisEn(Long_t size, void *p);
   static void delete_FisEn(void *p);
   static void deleteArray_FisEn(void *p);
   static void destruct_FisEn(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FisEn*)
   {
      ::FisEn *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FisEn >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FisEn", ::FisEn::Class_Version(), "AnaRoot.hh", 161,
                  typeid(::FisEn), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FisEn::Dictionary, isa_proxy, 4,
                  sizeof(::FisEn) );
      instance.SetNew(&new_FisEn);
      instance.SetNewArray(&newArray_FisEn);
      instance.SetDelete(&delete_FisEn);
      instance.SetDeleteArray(&deleteArray_FisEn);
      instance.SetDestructor(&destruct_FisEn);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FisEn*)
   {
      return GenerateInitInstanceLocal((::FisEn*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FisEn*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SiGammaData(void *p = 0);
   static void *newArray_SiGammaData(Long_t size, void *p);
   static void delete_SiGammaData(void *p);
   static void deleteArray_SiGammaData(void *p);
   static void destruct_SiGammaData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SiGammaData*)
   {
      ::SiGammaData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SiGammaData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SiGammaData", ::SiGammaData::Class_Version(), "AnaRoot.hh", 183,
                  typeid(::SiGammaData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SiGammaData::Dictionary, isa_proxy, 4,
                  sizeof(::SiGammaData) );
      instance.SetNew(&new_SiGammaData);
      instance.SetNewArray(&newArray_SiGammaData);
      instance.SetDelete(&delete_SiGammaData);
      instance.SetDeleteArray(&deleteArray_SiGammaData);
      instance.SetDestructor(&destruct_SiGammaData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SiGammaData*)
   {
      return GenerateInitInstanceLocal((::SiGammaData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SiGammaData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SinglesCal(void *p = 0);
   static void *newArray_SinglesCal(Long_t size, void *p);
   static void delete_SinglesCal(void *p);
   static void deleteArray_SinglesCal(void *p);
   static void destruct_SinglesCal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SinglesCal*)
   {
      ::SinglesCal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SinglesCal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SinglesCal", ::SinglesCal::Class_Version(), "AnaRoot.hh", 203,
                  typeid(::SinglesCal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SinglesCal::Dictionary, isa_proxy, 4,
                  sizeof(::SinglesCal) );
      instance.SetNew(&new_SinglesCal);
      instance.SetNewArray(&newArray_SinglesCal);
      instance.SetDelete(&delete_SinglesCal);
      instance.SetDeleteArray(&deleteArray_SinglesCal);
      instance.SetDestructor(&destruct_SinglesCal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SinglesCal*)
   {
      return GenerateInitInstanceLocal((::SinglesCal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SinglesCal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HFSData(void *p = 0);
   static void *newArray_HFSData(Long_t size, void *p);
   static void delete_HFSData(void *p);
   static void deleteArray_HFSData(void *p);
   static void destruct_HFSData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HFSData*)
   {
      ::HFSData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HFSData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HFSData", ::HFSData::Class_Version(), "AnaRoot.hh", 225,
                  typeid(::HFSData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HFSData::Dictionary, isa_proxy, 4,
                  sizeof(::HFSData) );
      instance.SetNew(&new_HFSData);
      instance.SetNewArray(&newArray_HFSData);
      instance.SetDelete(&delete_HFSData);
      instance.SetDeleteArray(&deleteArray_HFSData);
      instance.SetDestructor(&destruct_HFSData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HFSData*)
   {
      return GenerateInitInstanceLocal((::HFSData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HFSData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SingleData(void *p = 0);
   static void *newArray_SingleData(Long_t size, void *p);
   static void delete_SingleData(void *p);
   static void deleteArray_SingleData(void *p);
   static void destruct_SingleData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SingleData*)
   {
      ::SingleData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SingleData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SingleData", ::SingleData::Class_Version(), "AnaRoot.hh", 277,
                  typeid(::SingleData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SingleData::Dictionary, isa_proxy, 4,
                  sizeof(::SingleData) );
      instance.SetNew(&new_SingleData);
      instance.SetNewArray(&newArray_SingleData);
      instance.SetDelete(&delete_SingleData);
      instance.SetDeleteArray(&deleteArray_SingleData);
      instance.SetDestructor(&destruct_SingleData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SingleData*)
   {
      return GenerateInitInstanceLocal((::SingleData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SingleData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PulserData(void *p = 0);
   static void *newArray_PulserData(Long_t size, void *p);
   static void delete_PulserData(void *p);
   static void deleteArray_PulserData(void *p);
   static void destruct_PulserData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PulserData*)
   {
      ::PulserData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PulserData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PulserData", ::PulserData::Class_Version(), "AnaRoot.hh", 315,
                  typeid(::PulserData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PulserData::Dictionary, isa_proxy, 4,
                  sizeof(::PulserData) );
      instance.SetNew(&new_PulserData);
      instance.SetNewArray(&newArray_PulserData);
      instance.SetDelete(&delete_PulserData);
      instance.SetDeleteArray(&deleteArray_PulserData);
      instance.SetDestructor(&destruct_PulserData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PulserData*)
   {
      return GenerateInitInstanceLocal((::PulserData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PulserData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr GeData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GeData::Class_Name()
{
   return "GeData";
}

//______________________________________________________________________________
const char *GeData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GeData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GeData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GeData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GeData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GeData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GeData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GeData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SiData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SiData::Class_Name()
{
   return "SiData";
}

//______________________________________________________________________________
const char *SiData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SiData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SiData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SiData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SiData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SiData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SiData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SiData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SiSiData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SiSiData::Class_Name()
{
   return "SiSiData";
}

//______________________________________________________________________________
const char *SiSiData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SiSiData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SiSiData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SiSiData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SiSiData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SiSiData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SiSiData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SiSiData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FisEn::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FisEn::Class_Name()
{
   return "FisEn";
}

//______________________________________________________________________________
const char *FisEn::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FisEn*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FisEn::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FisEn*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FisEn::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FisEn*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FisEn::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FisEn*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SiGammaData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SiGammaData::Class_Name()
{
   return "SiGammaData";
}

//______________________________________________________________________________
const char *SiGammaData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SiGammaData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SiGammaData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SiGammaData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SiGammaData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SiGammaData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SiGammaData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SiGammaData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SinglesCal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SinglesCal::Class_Name()
{
   return "SinglesCal";
}

//______________________________________________________________________________
const char *SinglesCal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SinglesCal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SinglesCal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SinglesCal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SinglesCal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SinglesCal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SinglesCal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SinglesCal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HFSData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HFSData::Class_Name()
{
   return "HFSData";
}

//______________________________________________________________________________
const char *HFSData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HFSData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HFSData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HFSData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HFSData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HFSData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HFSData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HFSData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SingleData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SingleData::Class_Name()
{
   return "SingleData";
}

//______________________________________________________________________________
const char *SingleData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SingleData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SingleData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SingleData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SingleData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SingleData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SingleData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SingleData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PulserData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PulserData::Class_Name()
{
   return "PulserData";
}

//______________________________________________________________________________
const char *PulserData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PulserData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PulserData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PulserData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PulserData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PulserData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PulserData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PulserData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void GeData::Streamer(TBuffer &R__b)
{
   // Stream an object of class GeData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GeData::Class(),this);
   } else {
      R__b.WriteClassBuffer(GeData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GeData(void *p) {
      return  p ? new(p) ::GeData : new ::GeData;
   }
   static void *newArray_GeData(Long_t nElements, void *p) {
      return p ? new(p) ::GeData[nElements] : new ::GeData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GeData(void *p) {
      delete ((::GeData*)p);
   }
   static void deleteArray_GeData(void *p) {
      delete [] ((::GeData*)p);
   }
   static void destruct_GeData(void *p) {
      typedef ::GeData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GeData

//______________________________________________________________________________
void SiData::Streamer(TBuffer &R__b)
{
   // Stream an object of class SiData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SiData::Class(),this);
   } else {
      R__b.WriteClassBuffer(SiData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SiData(void *p) {
      return  p ? new(p) ::SiData : new ::SiData;
   }
   static void *newArray_SiData(Long_t nElements, void *p) {
      return p ? new(p) ::SiData[nElements] : new ::SiData[nElements];
   }
   // Wrapper around operator delete
   static void delete_SiData(void *p) {
      delete ((::SiData*)p);
   }
   static void deleteArray_SiData(void *p) {
      delete [] ((::SiData*)p);
   }
   static void destruct_SiData(void *p) {
      typedef ::SiData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SiData

//______________________________________________________________________________
void SiSiData::Streamer(TBuffer &R__b)
{
   // Stream an object of class SiSiData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SiSiData::Class(),this);
   } else {
      R__b.WriteClassBuffer(SiSiData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SiSiData(void *p) {
      return  p ? new(p) ::SiSiData : new ::SiSiData;
   }
   static void *newArray_SiSiData(Long_t nElements, void *p) {
      return p ? new(p) ::SiSiData[nElements] : new ::SiSiData[nElements];
   }
   // Wrapper around operator delete
   static void delete_SiSiData(void *p) {
      delete ((::SiSiData*)p);
   }
   static void deleteArray_SiSiData(void *p) {
      delete [] ((::SiSiData*)p);
   }
   static void destruct_SiSiData(void *p) {
      typedef ::SiSiData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SiSiData

//______________________________________________________________________________
void FisEn::Streamer(TBuffer &R__b)
{
   // Stream an object of class FisEn.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FisEn::Class(),this);
   } else {
      R__b.WriteClassBuffer(FisEn::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FisEn(void *p) {
      return  p ? new(p) ::FisEn : new ::FisEn;
   }
   static void *newArray_FisEn(Long_t nElements, void *p) {
      return p ? new(p) ::FisEn[nElements] : new ::FisEn[nElements];
   }
   // Wrapper around operator delete
   static void delete_FisEn(void *p) {
      delete ((::FisEn*)p);
   }
   static void deleteArray_FisEn(void *p) {
      delete [] ((::FisEn*)p);
   }
   static void destruct_FisEn(void *p) {
      typedef ::FisEn current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FisEn

//______________________________________________________________________________
void SiGammaData::Streamer(TBuffer &R__b)
{
   // Stream an object of class SiGammaData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SiGammaData::Class(),this);
   } else {
      R__b.WriteClassBuffer(SiGammaData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SiGammaData(void *p) {
      return  p ? new(p) ::SiGammaData : new ::SiGammaData;
   }
   static void *newArray_SiGammaData(Long_t nElements, void *p) {
      return p ? new(p) ::SiGammaData[nElements] : new ::SiGammaData[nElements];
   }
   // Wrapper around operator delete
   static void delete_SiGammaData(void *p) {
      delete ((::SiGammaData*)p);
   }
   static void deleteArray_SiGammaData(void *p) {
      delete [] ((::SiGammaData*)p);
   }
   static void destruct_SiGammaData(void *p) {
      typedef ::SiGammaData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SiGammaData

//______________________________________________________________________________
void SinglesCal::Streamer(TBuffer &R__b)
{
   // Stream an object of class SinglesCal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SinglesCal::Class(),this);
   } else {
      R__b.WriteClassBuffer(SinglesCal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SinglesCal(void *p) {
      return  p ? new(p) ::SinglesCal : new ::SinglesCal;
   }
   static void *newArray_SinglesCal(Long_t nElements, void *p) {
      return p ? new(p) ::SinglesCal[nElements] : new ::SinglesCal[nElements];
   }
   // Wrapper around operator delete
   static void delete_SinglesCal(void *p) {
      delete ((::SinglesCal*)p);
   }
   static void deleteArray_SinglesCal(void *p) {
      delete [] ((::SinglesCal*)p);
   }
   static void destruct_SinglesCal(void *p) {
      typedef ::SinglesCal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SinglesCal

//______________________________________________________________________________
void HFSData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HFSData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HFSData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HFSData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HFSData(void *p) {
      return  p ? new(p) ::HFSData : new ::HFSData;
   }
   static void *newArray_HFSData(Long_t nElements, void *p) {
      return p ? new(p) ::HFSData[nElements] : new ::HFSData[nElements];
   }
   // Wrapper around operator delete
   static void delete_HFSData(void *p) {
      delete ((::HFSData*)p);
   }
   static void deleteArray_HFSData(void *p) {
      delete [] ((::HFSData*)p);
   }
   static void destruct_HFSData(void *p) {
      typedef ::HFSData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HFSData

//______________________________________________________________________________
void SingleData::Streamer(TBuffer &R__b)
{
   // Stream an object of class SingleData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SingleData::Class(),this);
   } else {
      R__b.WriteClassBuffer(SingleData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SingleData(void *p) {
      return  p ? new(p) ::SingleData : new ::SingleData;
   }
   static void *newArray_SingleData(Long_t nElements, void *p) {
      return p ? new(p) ::SingleData[nElements] : new ::SingleData[nElements];
   }
   // Wrapper around operator delete
   static void delete_SingleData(void *p) {
      delete ((::SingleData*)p);
   }
   static void deleteArray_SingleData(void *p) {
      delete [] ((::SingleData*)p);
   }
   static void destruct_SingleData(void *p) {
      typedef ::SingleData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SingleData

//______________________________________________________________________________
void PulserData::Streamer(TBuffer &R__b)
{
   // Stream an object of class PulserData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PulserData::Class(),this);
   } else {
      R__b.WriteClassBuffer(PulserData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PulserData(void *p) {
      return  p ? new(p) ::PulserData : new ::PulserData;
   }
   static void *newArray_PulserData(Long_t nElements, void *p) {
      return p ? new(p) ::PulserData[nElements] : new ::PulserData[nElements];
   }
   // Wrapper around operator delete
   static void delete_PulserData(void *p) {
      delete ((::PulserData*)p);
   }
   static void deleteArray_PulserData(void *p) {
      delete [] ((::PulserData*)p);
   }
   static void destruct_PulserData(void *p) {
      typedef ::PulserData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PulserData

namespace {
  void TriggerDictionaryInitialization_AnaDict_Impl() {
    static const char* headers[] = {
"AnaRoot.hh",
0
    };
    static const char* includePaths[] = {
"/home/silvia/root/include/",
"/home/silvia/Desktop/218-219Fr/WM_sort/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "AnaDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  GeData;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  SiData;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  SiSiData;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  FisEn;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  SiGammaData;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  SinglesCal;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  HFSData;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  SingleData;
class __attribute__((annotate("$clingAutoload$AnaRoot.hh")))  PulserData;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "AnaDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "AnaRoot.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"FisEn", payloadCode, "@",
"GeData", payloadCode, "@",
"HFSData", payloadCode, "@",
"PulserData", payloadCode, "@",
"SiData", payloadCode, "@",
"SiGammaData", payloadCode, "@",
"SiSiData", payloadCode, "@",
"SingleData", payloadCode, "@",
"SinglesCal", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("AnaDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_AnaDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_AnaDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_AnaDict() {
  TriggerDictionaryInitialization_AnaDict_Impl();
}
