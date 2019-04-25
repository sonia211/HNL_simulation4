// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME treeDict

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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "pythiaROOT.h"

// Header files passed via #pragma extra_include

namespace Pythia8 {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *Pythia8_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("Pythia8", 0 /*version*/, "Pythia8/PythiaStdlib.h", 50,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &Pythia8_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *Pythia8_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static TClass *Pythia8cLcLVec4_Dictionary();
   static void Pythia8cLcLVec4_TClassManip(TClass*);
   static void *new_Pythia8cLcLVec4(void *p = 0);
   static void *newArray_Pythia8cLcLVec4(Long_t size, void *p);
   static void delete_Pythia8cLcLVec4(void *p);
   static void deleteArray_Pythia8cLcLVec4(void *p);
   static void destruct_Pythia8cLcLVec4(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Vec4*)
   {
      ::Pythia8::Vec4 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Vec4));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Vec4", "Pythia8/Basics.h", 112,
                  typeid(::Pythia8::Vec4), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLVec4_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Vec4) );
      instance.SetNew(&new_Pythia8cLcLVec4);
      instance.SetNewArray(&newArray_Pythia8cLcLVec4);
      instance.SetDelete(&delete_Pythia8cLcLVec4);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLVec4);
      instance.SetDestructor(&destruct_Pythia8cLcLVec4);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Vec4*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Vec4*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Vec4*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLVec4_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Vec4*)0x0)->GetClass();
      Pythia8cLcLVec4_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLVec4_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLParticle_Dictionary();
   static void Pythia8cLcLParticle_TClassManip(TClass*);
   static void *new_Pythia8cLcLParticle(void *p = 0);
   static void *newArray_Pythia8cLcLParticle(Long_t size, void *p);
   static void delete_Pythia8cLcLParticle(void *p);
   static void deleteArray_Pythia8cLcLParticle(void *p);
   static void destruct_Pythia8cLcLParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Particle*)
   {
      ::Pythia8::Particle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Particle));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Particle", "Pythia8/Event.h", 32,
                  typeid(::Pythia8::Particle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLParticle_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Particle) );
      instance.SetNew(&new_Pythia8cLcLParticle);
      instance.SetNewArray(&newArray_Pythia8cLcLParticle);
      instance.SetDelete(&delete_Pythia8cLcLParticle);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLParticle);
      instance.SetDestructor(&destruct_Pythia8cLcLParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Particle*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Particle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Particle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLParticle_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Particle*)0x0)->GetClass();
      Pythia8cLcLParticle_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLParticle_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLJunction_Dictionary();
   static void Pythia8cLcLJunction_TClassManip(TClass*);
   static void *new_Pythia8cLcLJunction(void *p = 0);
   static void *newArray_Pythia8cLcLJunction(Long_t size, void *p);
   static void delete_Pythia8cLcLJunction(void *p);
   static void deleteArray_Pythia8cLcLJunction(void *p);
   static void destruct_Pythia8cLcLJunction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Junction*)
   {
      ::Pythia8::Junction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Junction));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Junction", "Pythia8/Event.h", 327,
                  typeid(::Pythia8::Junction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLJunction_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Junction) );
      instance.SetNew(&new_Pythia8cLcLJunction);
      instance.SetNewArray(&newArray_Pythia8cLcLJunction);
      instance.SetDelete(&delete_Pythia8cLcLJunction);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLJunction);
      instance.SetDestructor(&destruct_Pythia8cLcLJunction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Junction*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Junction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Junction*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLJunction_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Junction*)0x0)->GetClass();
      Pythia8cLcLJunction_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLJunction_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Pythia8cLcLEvent_Dictionary();
   static void Pythia8cLcLEvent_TClassManip(TClass*);
   static void *new_Pythia8cLcLEvent(void *p = 0);
   static void *newArray_Pythia8cLcLEvent(Long_t size, void *p);
   static void delete_Pythia8cLcLEvent(void *p);
   static void deleteArray_Pythia8cLcLEvent(void *p);
   static void destruct_Pythia8cLcLEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pythia8::Event*)
   {
      ::Pythia8::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Pythia8::Event));
      static ::ROOT::TGenericClassInfo 
         instance("Pythia8::Event", "Pythia8/Event.h", 379,
                  typeid(::Pythia8::Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Pythia8cLcLEvent_Dictionary, isa_proxy, 4,
                  sizeof(::Pythia8::Event) );
      instance.SetNew(&new_Pythia8cLcLEvent);
      instance.SetNewArray(&newArray_Pythia8cLcLEvent);
      instance.SetDelete(&delete_Pythia8cLcLEvent);
      instance.SetDeleteArray(&deleteArray_Pythia8cLcLEvent);
      instance.SetDestructor(&destruct_Pythia8cLcLEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pythia8::Event*)
   {
      return GenerateInitInstanceLocal((::Pythia8::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Pythia8::Event*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Pythia8cLcLEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Pythia8::Event*)0x0)->GetClass();
      Pythia8cLcLEvent_TClassManip(theClass);
   return theClass;
   }

   static void Pythia8cLcLEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLVec4(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Vec4 : new ::Pythia8::Vec4;
   }
   static void *newArray_Pythia8cLcLVec4(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Vec4[nElements] : new ::Pythia8::Vec4[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLVec4(void *p) {
      delete ((::Pythia8::Vec4*)p);
   }
   static void deleteArray_Pythia8cLcLVec4(void *p) {
      delete [] ((::Pythia8::Vec4*)p);
   }
   static void destruct_Pythia8cLcLVec4(void *p) {
      typedef ::Pythia8::Vec4 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Vec4

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLParticle(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Particle : new ::Pythia8::Particle;
   }
   static void *newArray_Pythia8cLcLParticle(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Particle[nElements] : new ::Pythia8::Particle[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLParticle(void *p) {
      delete ((::Pythia8::Particle*)p);
   }
   static void deleteArray_Pythia8cLcLParticle(void *p) {
      delete [] ((::Pythia8::Particle*)p);
   }
   static void destruct_Pythia8cLcLParticle(void *p) {
      typedef ::Pythia8::Particle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Particle

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLJunction(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Junction : new ::Pythia8::Junction;
   }
   static void *newArray_Pythia8cLcLJunction(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Junction[nElements] : new ::Pythia8::Junction[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLJunction(void *p) {
      delete ((::Pythia8::Junction*)p);
   }
   static void deleteArray_Pythia8cLcLJunction(void *p) {
      delete [] ((::Pythia8::Junction*)p);
   }
   static void destruct_Pythia8cLcLJunction(void *p) {
      typedef ::Pythia8::Junction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Junction

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pythia8cLcLEvent(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Event : new ::Pythia8::Event;
   }
   static void *newArray_Pythia8cLcLEvent(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::Pythia8::Event[nElements] : new ::Pythia8::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pythia8cLcLEvent(void *p) {
      delete ((::Pythia8::Event*)p);
   }
   static void deleteArray_Pythia8cLcLEvent(void *p) {
      delete [] ((::Pythia8::Event*)p);
   }
   static void destruct_Pythia8cLcLEvent(void *p) {
      typedef ::Pythia8::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pythia8::Event

namespace ROOT {
   static TClass *vectorlEPythia8cLcLParticlegR_Dictionary();
   static void vectorlEPythia8cLcLParticlegR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLParticlegR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLParticlegR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLParticlegR(void *p);
   static void deleteArray_vectorlEPythia8cLcLParticlegR(void *p);
   static void destruct_vectorlEPythia8cLcLParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::Particle>*)
   {
      vector<Pythia8::Particle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::Particle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::Particle>", -2, "vector", 214,
                  typeid(vector<Pythia8::Particle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLParticlegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::Particle>) );
      instance.SetNew(&new_vectorlEPythia8cLcLParticlegR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLParticlegR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLParticlegR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::Particle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::Particle>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::Particle>*)0x0)->GetClass();
      vectorlEPythia8cLcLParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Particle> : new vector<Pythia8::Particle>;
   }
   static void *newArray_vectorlEPythia8cLcLParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Particle>[nElements] : new vector<Pythia8::Particle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLParticlegR(void *p) {
      delete ((vector<Pythia8::Particle>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLParticlegR(void *p) {
      delete [] ((vector<Pythia8::Particle>*)p);
   }
   static void destruct_vectorlEPythia8cLcLParticlegR(void *p) {
      typedef vector<Pythia8::Particle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::Particle>

namespace ROOT {
   static TClass *vectorlEPythia8cLcLJunctiongR_Dictionary();
   static void vectorlEPythia8cLcLJunctiongR_TClassManip(TClass*);
   static void *new_vectorlEPythia8cLcLJunctiongR(void *p = 0);
   static void *newArray_vectorlEPythia8cLcLJunctiongR(Long_t size, void *p);
   static void delete_vectorlEPythia8cLcLJunctiongR(void *p);
   static void deleteArray_vectorlEPythia8cLcLJunctiongR(void *p);
   static void destruct_vectorlEPythia8cLcLJunctiongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Pythia8::Junction>*)
   {
      vector<Pythia8::Junction> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Pythia8::Junction>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Pythia8::Junction>", -2, "vector", 214,
                  typeid(vector<Pythia8::Junction>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEPythia8cLcLJunctiongR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Pythia8::Junction>) );
      instance.SetNew(&new_vectorlEPythia8cLcLJunctiongR);
      instance.SetNewArray(&newArray_vectorlEPythia8cLcLJunctiongR);
      instance.SetDelete(&delete_vectorlEPythia8cLcLJunctiongR);
      instance.SetDeleteArray(&deleteArray_vectorlEPythia8cLcLJunctiongR);
      instance.SetDestructor(&destruct_vectorlEPythia8cLcLJunctiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Pythia8::Junction> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Pythia8::Junction>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEPythia8cLcLJunctiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Pythia8::Junction>*)0x0)->GetClass();
      vectorlEPythia8cLcLJunctiongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEPythia8cLcLJunctiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEPythia8cLcLJunctiongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Junction> : new vector<Pythia8::Junction>;
   }
   static void *newArray_vectorlEPythia8cLcLJunctiongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Pythia8::Junction>[nElements] : new vector<Pythia8::Junction>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEPythia8cLcLJunctiongR(void *p) {
      delete ((vector<Pythia8::Junction>*)p);
   }
   static void deleteArray_vectorlEPythia8cLcLJunctiongR(void *p) {
      delete [] ((vector<Pythia8::Junction>*)p);
   }
   static void destruct_vectorlEPythia8cLcLJunctiongR(void *p) {
      typedef vector<Pythia8::Junction> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Pythia8::Junction>

namespace {
  void TriggerDictionaryInitialization_treeDict_Impl() {
    static const char* headers[] = {
"pythiaROOT.h",
0
    };
    static const char* includePaths[] = {
"/home/bouchiba/PDM/pythia8240/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/ROOT/6.12.06-0f687/x86_64-slc6-gcc62-opt/include",
"/share/lphe/home/bouchiba/PDM/pythia8240/WORKDIR_D/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "treeDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace Pythia8{class __attribute__((annotate("$clingAutoload$Pythia8/Basics.h")))  __attribute__((annotate("$clingAutoload$pythiaROOT.h")))  Vec4;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$Pythia8/Event.h")))  __attribute__((annotate("$clingAutoload$pythiaROOT.h")))  Particle;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$Pythia8/Event.h")))  __attribute__((annotate("$clingAutoload$pythiaROOT.h")))  Junction;}
namespace Pythia8{class __attribute__((annotate("$clingAutoload$Pythia8/Event.h")))  __attribute__((annotate("$clingAutoload$pythiaROOT.h")))  Event;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "treeDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "pythiaROOT.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Pythia8::Event", payloadCode, "@",
"Pythia8::Junction", payloadCode, "@",
"Pythia8::Particle", payloadCode, "@",
"Pythia8::Vec4", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("treeDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_treeDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_treeDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_treeDict() {
  TriggerDictionaryInitialization_treeDict_Impl();
}
