#ifndef dConFiLanCpp
#define dConFiLanCpp
//headers
#include "ConFiLan.hpp"
//-//external
#include "dTermAPar.dir/fHead.hxx"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
//-//standard
#include <cstddef>
#include <cstdlib>
#include <algorithm>
//defines
#define fActIfEqu(vExpr, vBool, ...) \
	({                                 \
		if((vExpr) == vBool)             \
		{                                \
			__VA_ARGS__;                   \
		}                                \
	})
#define fActIfNot(vExpr, ...) fActIfEqu(vExpr, 0, __VA_ARGS__);
#define fActIfYes(vExpr, ...) fActIfEqu(vExpr, 1, __VA_ARGS__);
//content
namespace nConFiLan
{
//typedef
using tPath = boost::filesystem::path;
//setters
auto tScope::fSet(const tIndex &rIndex, const tValue &rValue) -> tScope *
{
	this->vTable[rIndex] = std::make_shared<tValue>(rValue);
	return this;
}
auto tScope::fSet(const tIndex &rAlias, const tIndex &rIndex) -> tScope *
{
	this->vTable[rAlias] = this->vTable[rIndex];
	return this;
}
//getters
auto tScope::fGet(const tIndex &rIndex) const -> std::optional<tRefer>
{
	auto vFound = this->vTable.find(rIndex);
	auto vEmpty = vFound == this->vTable.end();
	return vEmpty ? std::optional<tRefer>() : vFound->second;
}
//vetters
bool tScope::fVet(const tIndex &rIndex)
{
	auto vFound = this->vTable.find(rIndex);
	auto vEmpty = vFound == this->vTable.end();
	return vEmpty;
}
//actions
auto tScope::fMake(const tData &rData) -> tScope *
{
	return this;
}
template<>
auto tScope::fLoad<tPath>(const tPath &rPath) -> tScope *
{
	//file
	auto vFile = boost::filesystem::ifstream(rPath);
	fActIfNot(vFile.is_open(), throw std::logic_error(rPath.c_str()));
	//size
	vFile.seekg(0, std::ios::end);
	auto vSize = tSize(vFile.tellg());
	vFile.seekg(0, std::ios::beg);
	//data
	auto vData = tData(vSize, '\0');
	while(vFile >> vData)
	{
	}
	//quit
	return this->fMake(vData);
}
template<>
auto tScope::fSave<tPath>(const tPath &rPath) -> tScope *
{
	//file
	auto vFile = boost::filesystem::ofstream(rPath);
	fActIfNot(vFile.is_open(), throw std::logic_error(rPath.c_str()));
	//quit
	return this;
}
//operats
template<>
auto tScope::operator<<(std::ostream &rStream) -> std::ostream &
{
	return rStream;
}
template<>
auto tScope::operator>>(std::istream &rStream) -> std::istream &
{
	return rStream;
}
}//namespace nConFiLan
#ifdef dConFiLanMakeExe
namespace nConFiLan
{
int fMain(int vArgC, char **vArgV)
{
	boost::filesystem::ifstream v;
	boost::filesystem::current_path(dConFiLanPathToInternal);
	nTermAPar::tArgParser vArgParser;
	vArgParser.fSetCmd(
		"tHello",
		[](nTermAPar::tCmd &vCmd)
		{
			fmt::println("HelloWorld");
			return 1;
		}
	);
	vArgParser.fSetCmd(
		"tFileSystem",
		[](nTermAPar::tCmd &vCmd)
		{
			fmt::println(
				"RelativePath={}",
				boost::filesystem::relative(dConFiLanPathToInternal).c_str()
			);
			return 1;
		}
	);
	vArgParser.fSetOpt("f fp file filepath", dConFiLanPathToResource "/exam.cfl");
	vArgParser.fParse(vArgC, vArgV);
	return EXIT_SUCCESS;
}
}//namespace nConFiLan
//actions
int main(int vArgC, char **vArgV)
{
	return nConFiLan::fMain(vArgC, vArgV);
}
#endif//dConFiLanMakeExe
#endif//dConFiLanCpp
