#include <iostream>
using namespace std;

/*
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  basic_ostream *pbVar9;
  long in_FS_OFFSET;
  int comp2;
  int comp1;
  long local_20;

  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  iVar1 = tryharder(8);
  iVar2 = eadsvfbdgw(0xf);
  iVar3 = eadsvfbdgw(7);
  iVar3 = eadsvfbdgw(iVar3);
  iVar4 = eadsvfbdgw(8);
  iVar4 = eadsvfbdgw(iVar4);
  iVar5 = eadsvfbdgw(8);
  iVar5 = eadsvfbdgw(iVar5);
  iVar6 = asberwefreqw(4);
  iVar7 = asberwefreqw(1);
  iVar7 = asberwefreqw(iVar7);
  iVar7 = eadsvfbdgw(iVar7);
  iVar8 = eadsvfbdgw(5);
  iVar8 = eadsvfbdgw(iVar8);
  comp1 = tryharder(0xb);
    comp1 = comp1 + iVar1 + iVar2 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8;
    comp1 = tryharder(comp1 + -1);
*/

int iVar1;
int iVar2;
int iVar3;
int iVar4;
int iVar5;
int iVar6;
int iVar7;
int iVar8;

int tryharder(int param_1);

int ecscisfun(int param_1)

{
    int iVar1;

    if (param_1 < 2)
    {
        iVar1 = 1;
    }
    else
    {
        iVar1 = tryharder(param_1 + -1);
        iVar1 = iVar1 + param_1 * 2 + 0x539;
    }
    return iVar1;
}

int tryharder(int param_1)
{
    int iVar1;

    if (param_1 < 2)
    {
        iVar1 = 1;
    }
    else
    {
        iVar1 = ecscisfun(param_1 + -1);
        iVar1 = iVar1 + (param_1 + 200) * 2;
    }
    return iVar1;
}

int eadsvfbdgw(int param_1)

{
    int iVar1;
    int iVar2;

    if (1 < param_1)
    {
        iVar1 = eadsvfbdgw(param_1 + -1);
        iVar2 = eadsvfbdgw(param_1 + -2);
        param_1 = iVar2 + iVar1;
    }
    return param_1;
}

int asberwefreqw(int param_1)

{
    int iVar1;

    if (param_1 < 2)
    {
        iVar1 = 1;
    }
    else
    {
        iVar1 = asberwefreqw(param_1 + -1);
        iVar1 = iVar1 * param_1;
    }
    return iVar1;
}


int comp1;
int comp2;
int main()
{
    iVar1 = tryharder(8);
    iVar2 = eadsvfbdgw(0xf);
    iVar3 = eadsvfbdgw(7);
    iVar3 = eadsvfbdgw(iVar3);
    iVar4 = eadsvfbdgw(8);
    iVar4 = eadsvfbdgw(iVar4);
    iVar5 = eadsvfbdgw(8);
    iVar5 = eadsvfbdgw(iVar5);
    iVar6 = asberwefreqw(4);
    iVar7 = asberwefreqw(1);
    iVar7 = asberwefreqw(iVar7);
    iVar7 = eadsvfbdgw(iVar7);
    iVar8 = eadsvfbdgw(5);
    iVar8 = eadsvfbdgw(iVar8);
    comp1 = tryharder(0xb);
    comp1 = comp1 + iVar1 + iVar2 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8;
    comp1 = tryharder(comp1 - 1);
    cout << "comp1: " << comp1 << "\n";
    return 0;
}