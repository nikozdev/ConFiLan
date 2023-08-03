#ifndef dConFiLanCpp
#define dConFiLanCpp
#include "ConFiLan.hpp"
#include "dTermAPar.dir/fHead.hxx"
#include "boost/filesystem.hpp"
#include <cstddef>
#include <cstdlib>
#include <algorithm>
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
	vArgParser.fSetOpt("f fp file filepath", dConFiLanPathToResource "/exam.cfl");
	vArgParser.fParse(vArgC, vArgV);
	return EXIT_SUCCESS;
}
}//namespace nConFiLan
#ifdef dConFiLanMakeExe
//actions
int main(int vArgC, char **vArgV)
{
	return nConFiLan::fMain(vArgC, vArgV);
}
#endif//dConFiLanMakeExe
#endif//dConFiLanCpp
