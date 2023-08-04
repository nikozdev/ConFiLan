#ifndef dConFiLanCpp
#define dConFiLanCpp
//headers
#include "ConFiLan.hpp"
//-//external
#include "dTermAPar.dir/fHead.hxx"
#include "fmt/format.h"
#include "fmt/ranges.h"
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
auto tScope::fSetValue(const tIndex &rIndex, const tValue &rValue) -> tScope *
{
	this->vTable[rIndex] = std::make_shared<tValue>(rValue);
  fmt::println("this->vTable[{}]={}", rIndex, *std::get_if<tData>(this->vTable[rIndex].get()));
	return this;
}
auto tScope::fSetAlias(const tIndex &rIndex, const tIndex&rAlias) -> tScope *
{
  fActIfNot(this->fVetIndex(rIndex), return nullptr);
	this->vTable[rAlias] = tRefer(this->vTable[rIndex]);
	return this;
}
//getters
auto tScope::fGetRefer(const tIndex &rIndex) -> tRefer
{
	auto vFound = this->vTable.find(rIndex);
	auto vEmpty = vFound == this->vTable.end();
	return vEmpty ? tRefer{} : vFound->second;
}
auto tScope::fGetValue(const tIndex &rIndex, const tValue &rValue) -> tValue
{
	auto vRefer = fGetRefer(rIndex);
	auto vValue = vRefer ? *vRefer : rValue;
	return vValue;
}
//vetters
bool tScope::fVetIndex(const tIndex &rIndex)
{
	auto vFound = this->vTable.find(rIndex);
	auto vEmpty = vFound == this->vTable.end();
	return vEmpty;
}
//actions
tScope::operator tData()
{
	tData vData;
	for(auto vIter: this->vTable)
	{
		if(auto pScope = std::get_if<tScope>(vIter.second.get()))
		{
      auto vTemp = static_cast<tData>(*pScope);
			vData += fmt::format("[{0}]=({1})=[{0}]", vIter.first, vTemp);
		}
		else if(auto pData = std::get_if<std::string>(vIter.second.get()))
		{
      auto vTemp = *pData;
			vData += fmt::format("[{0}]=({1})=[{0}]", vIter.first, *pData);
		}
		else
		{
			throw std::logic_error("malformed scope !");
		}
	}
	return vData;
}
auto tScope::fMake(const tData &rData) -> tScope *
{
	tScope vScope;
	return this;
}
template<>
auto tScope::fLoad<tPath>(tPath &rPath) -> tScope *
{
	auto vFile = boost::filesystem::ifstream(rPath);
	fActIfNot(vFile.is_open(), throw std::logic_error(rPath.c_str()));
	vFile >> *this;
	return this;
}
template<>
auto tScope::fSave<tPath>(tPath &rPath) -> tScope *
{
	auto vFile = boost::filesystem::ofstream(rPath);
	fActIfNot(vFile.is_open(), throw std::logic_error(rPath.c_str()));
	vFile << *this;
	return this;
}
}//namespace nConFiLan
#ifdef dConFiLanMakeExe
namespace nConFiLan
{
int fMain(int vArgC, char **vArgV)
{
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
	vArgParser
		.fSetCmd(
			"tFileSave",
			[](nTermAPar::tCmd &vCmd)
			{
				tScope vScope;
				vScope.fSetValue("index", "value");
				vScope.fSetAlias("index", "alias");
				tPath vPath = vCmd.fGetOptVal("file");
				fActIfNot(vScope.fSave(vPath), throw std::logic_error("failed save !"));
				std::cout << vScope << std::endl;
				return 1;
			}
		)
		->fSetOpt("file", dConFiLanPathToResource "/save.cfl");
	vArgParser
		.fSetCmd(
			"tFileLoad",
			[](nTermAPar::tCmd &vCmd)
			{
				tScope vScope;
				tPath	 vPath = vCmd.fGetOptVal("file");
				fActIfNot(vScope.fLoad(vPath), throw std::logic_error("failed load !"));
				return 1;
			}
		)
		->fSetOpt("file", dConFiLanPathToResource "/save.cfl");
	try
	{
		vArgParser.fParse(vArgC, vArgV);
	}
	catch(const std::exception &vError)
	{
		fmt::println(stderr, "[exception]={}", vError.what());
		return EXIT_FAILURE;
	}
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
