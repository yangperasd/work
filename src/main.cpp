/*************************************************************************
	> File Name: src/main.cpp
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: Tue 07 Mar 2017 08:23:12 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include "BiTree.h"
using namespace std;
template<typename T>
bool matrixFind(vector<vector<T>> const& matrix,
                    T const& value)
{/*{{{*/
    if(matrix.empty()||matrix[0].empty())
        return false;
    for(int row=0,col=matrix[0].size()-1;
            row<matrix.size()&&col>=0;)
    {
        auto iter=(matrix.begin()+row)->begin()+col;
        if(*iter==value)
            return true;
        else if(*iter > value)
            --col;
        else
            ++row;
    }
    return false;
}/*}}}*/

bool replaceSpace(vector<char>& source,int maxLen)
{/*{{{*/
    //get total nb of space 
    char space=' ';
    int count=0;
    for(auto const& elem:source)
    {
        elem==space&&++count;
    }
    if((source.size()+2*count)>maxLen)
        return false;
    //increase contain size 
    source.resize(source.size()+2*count);
    //move and insert "%20"
    for(auto iter=source.rbegin(),cur=iter+2*count;
            cur!=source.rend();)
    {
        if(*cur==space)
        {
            *iter++='0';
            *iter++='2';
            *iter++='%';
            ++cur;
        }
        else
            *iter++=*cur++;
    }
    return true;
}/*}}}*/

int main()
{
   BiTree<> tree;
   vector<int> preOrder{1,2,4,7,3,5,6,8};
   vector<int> midOrder{4,7,2,1,5,3,8,6};
   reBuildFromMidFirstOrder(tree,preOrder,midOrder);
   tree.traverse(0);
}
