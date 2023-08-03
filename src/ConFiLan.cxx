#ifndef dConFiLanCxx
#define dConFiLanCxx
#include "ConFiLan.hxx"
#include "dTermAPar.dir/fHead.hxx"
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <iostream>
namespace nConFiLan
{
int fMain(int vArgC, char **vArgV)
{
	nTermAPar::tArgParser vArgParser;
	vArgParser.fSetCmd(
		"tHello",
		[](nTermAPar::tCmd &vCmd)
		{
			fmt::println("HelloWorld");
			return 0;
		}
	);
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
#endif//dConFiLanCxx
