#pragma once

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;

template<typename T>
std::wstring OptToString(kstd::optional<T> const & opt)
{
	if (!opt) return L"nullopt";

	return tf::ToString<T>(*opt);
}

#define OptSpecialize(T) \
template<> \
std::wstring tf::ToString<kstd::optional<T>>(kstd::optional<T> const & opt) \
{ \
	return OptToString(opt); \
}

OptSpecialize(int)
