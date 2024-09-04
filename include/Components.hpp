#pragma once
#include <type_traits>
#include <tuple>
#include <raylib.h>
#include <sys/types.h>

/**
 * REPTILE
 * BLACK MAGIC
*/

// Helper macro to override the component getters in header file
#define OBJECT_OVERRIDE_COMPONENT_H(CompType) \
    ::components::CompType *get_(tag<::components::CompType>) override;

// Helper macro to override the component getters in source file
#define OBJECT_OVERRIDE_COMPONENT_CPP(ClassName, CompType, varName) \
    ::components::CompType *ClassName::get_(tag<::components::CompType>) { \
      return &varName;  \
    }

////////////////////////////////////////////////////////////////////////////////
// Dummy tag to hold one or more types

template <class... T>
struct tag { };


////////////////////////////////////////////////////////////////////////////////
// typename params<F>::type is tag<P1, P2, ... Pn>
// where P's are the parameter types of the function or function-object F.

template <class F>
struct params : params<decltype(&F::operator())> { };

template <class R, class T, class... Params>
struct params<R (T::*)(Params...)> { using type = tag<Params...>; };

template <class R, class T, class... Params>
struct params<R (T::*)(Params...) const> { using type = tag<Params...>; };

template <class R, class... Params>
struct params<R (*)(Params...)> { using type = tag<Params...>; };

template <class R, class... Params>
struct params<R (&)(Params...)> { using type = tag<Params...>; };

////////////////////////////////////////////////////////////////////////////////
// Dereference every pointer in Args and call f with them

template <class F, class Args, std::size_t... Idx>
inline void derefCall(F &&f, Args &args, std::index_sequence<Idx...>) {
    std::forward<F>(f)(*std::get<Idx>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
// Defining your components

namespace components {

    struct Health {
      uint value;
    };

    struct Money {
      uint value;
    };

    struct Speed {
      float value;
    };

    // Direction angle
    struct Direction {
      float value;
    };

    typedef Rectangle Body; // cause Rectangle is struct already
    
    struct EnemyTag { };
    struct PlayerTag { };
}

