#ifndef dConFiLanHpp
#define dConFiLanHpp
//headers
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <variant>
#include <optional>
//defines
#if defined(dConFiLanMakeDll)
#if defined(dConFiLanToolMsvcc)
#define aConFiLanExternal __declspec(dllexport)
#define aConFiLanInternal ()
#endif//dConFiLanToolMsvcc
#if defined(dConFiLanToolGnucc)
#define aConFiLanExternal __attribute__((visibility("default")))
#define aConFiLanInternal __attribute__((visibility("hidden")))
#endif//ifd(dConFiLanToolGnucc)
#else
#define aConFiLanExternal
#define aConFiLanInternal
#endif//ifd(dConFiLanMakeDll)
//content
namespace nConFiLan
{
//typedef
using tData = std::string;
using tSize = size_t;
/* type of scope
 * container of index-value pairs and nested scopes
 */
class aConFiLanExternal tScope
{
public://typedef

	using tLevel = size_t;
	using tIndex = std::string;
	using tValue = std::variant<std::string, tScope>;
	using tRefer = std::shared_ptr<tValue>;
	using tTable = std::map<tIndex, tRefer>;

public://codetor

	tScope(): vLevel{0}, vTable{}
	{
	}

public://setters

	auto fSetValue(const tIndex &rIndex, const tValue &rValue) -> tScope *;
	auto fSetAlias(const tIndex &rIndex, const tIndex &rAlias) -> tScope *;

public://getters

	auto fGetRefer(const tIndex &rIndex) -> tRefer;
	auto fGetValue(const tIndex &rIndex, const tValue&rValue) -> tValue;

public://vetters

	auto fVetIndex(const tIndex &rIndex) -> bool;

public://actions

	auto fMake(const tData &rData) -> tScope *;

	template<typename tPath>
	auto fSave(tPath &rPath) -> tScope *;
	template<typename tPath>
	auto fLoad(tPath &rPath) -> tScope *;

public://operats

  operator tData();

	template<typename tStream>
	auto operator<<(tStream &rStream) -> tStream &
	{
		rStream << static_cast<tData>(*this);
		return rStream;
	}
	template<typename tStream>
	auto operator>>(tStream &rStream) -> tStream &
	{
		auto vFrom = rStream.tellg();
		rStream.seekg(0, std::ios::end);
		auto vSize = tSize(rStream.tellg());
		rStream.seekg(vFrom, std::ios::beg);
		auto vData = tData(vSize, '\0');
		while(rStream >> vData)
		{
		}
		this->fMake(vData);
		return rStream;
	}

private://datadef

	tLevel vLevel;
	tTable vTable;

};//tScope
template<typename tStream>
auto operator<<(tStream &rStream, tScope &rScope) -> tStream &
{
	return rScope.operator<<(rStream);
}
template<typename tStream>
auto operator>>(tStream &rStream, tScope &rScope) -> tStream &
{
	return rScope.operator>>(rStream);
}
}//namespace nConFiLan
#endif//dConFiLanHpp
