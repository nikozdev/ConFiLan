#ifndef dConFiLanHpp
#define dConFiLanHpp
//headers
#include <string>
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

	auto fSet(const tIndex &rAlias, const tIndex &rIndex) -> tScope *;
	auto fSet(const tIndex &rIndex, const tValue &rValue) -> tScope *;

public://getters

	auto fGet(const tIndex &rIndex) const -> std::optional<tRefer>;

public://vetters

	auto fVet(const tIndex &rIndex) -> bool;

public://actions

	auto fMake(const tData &rData) -> tScope *;

	template<typename tPath>
	auto fSave(const tPath &rPath) -> tScope *;
	template<typename tPath>
	auto fLoad(const tPath &rPath) -> tScope *;

public://operats

	template<typename tStream>
	auto operator<<(tStream &rStream) -> tStream &;
	template<typename tStream>
	auto operator>>(tStream &rStream) -> tStream &;

private://datadef

	tLevel vLevel;
	tTable vTable;

};//tScope
template<typename tStream>
auto operator<<(tStream &rStream, tScope &rScope)
{
	return rScope.operator<<(rStream);
}
template<typename tStream>
auto operator>>(tStream &rStream, tScope &rScope)
{
	return rScope.operator>>(rStream);
}
}//namespace nConFiLan
#endif//dConFiLanHpp
