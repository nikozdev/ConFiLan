#ifndef dConFiLanCxx
#define dConFiLanCxx
#include "ConFiLan.hxx"
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <iostream>
namespace nConFiLan
{
int fMain(int vArgC, char **vArgV)
{
	std::copy(
		vArgV, vArgV + vArgC, std::ostream_iterator<const char *>(std::clog, "\n")
	);
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
