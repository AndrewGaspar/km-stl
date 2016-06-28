#include "stdafx.h"

#include "..\inc\type_traits"
#include "..\inc\utility"

template <class T, class V = void> struct is_complete : std::false_type {};
template <class T> struct is_complete<T, decltype(void(sizeof(T)))> : std::true_type {};

struct S1 {};
struct S2;

static_assert(is_complete<S1>::value, "fail"); // fail in VS2015 RTM
static_assert(!is_complete<S2>::value, "fail");

struct Foo {};

static_assert(kstd::is_constructible<Foo>::value, "Foo should be default constructible");
static_assert(!kstd::is_constructible<Foo, int, float>::value, "");

static_assert(kstd::is_move_constructible<Foo>::value, "Foo is move constructible");

static_assert(kstd::is_function<int(float)               >::value, "");
static_assert(kstd::is_function<int(float) const         >::value, "");
static_assert(kstd::is_function<int(float) volatile      >::value, "");
static_assert(kstd::is_function<int(float) const volatile>::value, "");
static_assert(kstd::is_function<int(float)               &>::value, "");
static_assert(kstd::is_function<int(float) const         &>::value, "");
static_assert(kstd::is_function<int(float) volatile      &>::value, "");
static_assert(kstd::is_function<int(float) const volatile&>::value, "");
static_assert(kstd::is_function<int(float)               &&>::value, "");
static_assert(kstd::is_function<int(float) const         &&>::value, "");
static_assert(kstd::is_function<int(float) volatile      &&>::value, "");
static_assert(kstd::is_function<int(float) const volatile&&>::value, "");
static_assert(kstd::is_function<int(float, ...)               >::value, "");
static_assert(kstd::is_function<int(float, ...) const         >::value, "");
static_assert(kstd::is_function<int(float, ...) volatile      >::value, "");
static_assert(kstd::is_function<int(float, ...) const volatile>::value, "");
static_assert(kstd::is_function<int(float, ...)               &>::value, "");
static_assert(kstd::is_function<int(float, ...) const         &>::value, "");
static_assert(kstd::is_function<int(float, ...) volatile      &>::value, "");
static_assert(kstd::is_function<int(float, ...) const volatile&>::value, "");
static_assert(kstd::is_function<int(float, ...)               &&>::value, "");
static_assert(kstd::is_function<int(float, ...) const         &&>::value, "");
static_assert(kstd::is_function<int(float, ...) volatile      &&>::value, "");
static_assert(kstd::is_function<int(float, ...) const volatile&&>::value, "");

auto lambda = []() {};
int foo(float b) { return 0; }

static_assert(!kstd::is_function<decltype(lambda)>::value, "");
static_assert(!kstd::is_function<int(*)(float)>::value,    "");

static_assert(kstd::is_same<int*, kstd::add_pointer_t<int>>::value, "");
static_assert(kstd::is_same<int**, kstd::add_pointer_t<int*>>::value, "");
static_assert(kstd::is_same<int(*)(float), kstd::add_pointer_t<int(float)>>::value, "");
static_assert(kstd::is_same<int(float) const volatile, kstd::add_pointer_t<int(float) const volatile>>::value, "");

static_assert(kstd::is_same<int*, kstd::decay_t<int[]>>::value, "");
static_assert(kstd::is_same<int*, kstd::decay_t<int[3]>>::value, "");
static_assert(kstd::is_same<int*, kstd::decay_t<int(&)[3]>>::value, "");
static_assert(kstd::is_same<int(*)(float), kstd::decay_t<int(float)>>::value, "");
static_assert(kstd::is_same<int, kstd::decay_t<int const>>::value, "");
static_assert(kstd::is_same<int, kstd::decay_t<int const &>>::value, "");
static_assert(kstd::is_same<int, kstd::decay_t<int const volatile &>>::value, "");
static_assert(kstd::is_same<int, kstd::decay_t<int volatile &>>::value, "");


static_assert(kstd::is_same<double, kstd::common_type_t<int, double>>::value, "");